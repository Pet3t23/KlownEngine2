/**
 * @file ForwardRenderer.cpp
 * @brief Implementación del renderer Forward basado en Direct3D 11.
 * @ingroup rendering
 *
 * Este módulo gestiona la construcción de colas de renderizado,
 * la actualización de Constant Buffers, la configuración de estados
 * gráficos y la ejecución de los distintos pases de renderizado.
 */

#include "Rendering/ForwardRenderer.h"
#include <algorithm>
#include "Device.h"
#include "DeviceContext.h"
#include "Rendering/Material.h"
#include "Rendering/MaterialInstance.h"
#include "Rendering/Mesh.h"
#include "SamplerState.h"
#include "EngineUtilities/Utilities/Camera.h"
#include "EngineUtilities/Utilities/EditorViewportPass.h"
#include "EngineUtilities/Utilities/Skybox.h"

 /**
  * @brief Inicializa todos los recursos necesarios para el renderer.
  *
  * Crea los Constant Buffers utilizados por frame, objeto y material,
  * configura el estado de profundidad para transparencias y crea los
  * distintos estados de mezcla (Blend States) utilizados durante el render.
  *
  * @param device Dispositivo Direct3D utilizado para crear recursos GPU.
  * @return HRESULT indicando éxito o error durante la inicialización.
  */
HRESULT
ForwardRenderer::init(Device& device) {
	HRESULT hr = m_perFrameBuffer.init(device, sizeof(CBPerFrame));
	if (FAILED(hr)) {
		return hr;
	}

	hr = m_perObjectBuffer.init(device, sizeof(CBPerObject));
	if (FAILED(hr)) {
		return hr;
	}

	hr = m_perMaterialBuffer.init(device, sizeof(CBPerMaterial));
	if (FAILED(hr)) {
		return hr;
	}

	hr = m_transparentDepthStencil.init(device,
		true,
		D3D11_DEPTH_WRITE_MASK_ZERO,
		D3D11_COMPARISON_LESS_EQUAL);
	if (FAILED(hr)) {
		return hr;
	}

	hr = createBlendStates(device);
	if (FAILED(hr)) {
		return hr;
	}

	return S_OK;
}

/**
 * @brief Maneja cambios de tamaño del viewport.
 *
 * Actualmente el renderer no mantiene recursos dependientes de la
 * resolución, por lo que esta función no realiza ninguna acción.
 *
 * @param device Dispositivo gráfico.
 * @param width Nuevo ancho.
 * @param height Nueva altura.
 */
void
ForwardRenderer::resize(Device& device, unsigned int width, unsigned int height) {
	(void)device;
	(void)width;
	(void)height;
}

/**
 * @brief Actualiza el Constant Buffer global del frame.
 *
 * Almacena matrices de vista y proyección, posición de cámara y
 * parámetros de iluminación global que serán utilizados por los shaders.
 *
 * @param camera Cámara activa.
 * @param scene Escena actual.
 * @param deviceContext Contexto de renderizado.
 */
void
ForwardRenderer::updatePerFrame(const Camera& camera,
	const RenderScene& scene,
	DeviceContext& deviceContext) {
	XMStoreFloat4x4(&m_cbPerFrame.View, XMMatrixTranspose(camera.getView()));
	XMStoreFloat4x4(&m_cbPerFrame.Projection, XMMatrixTranspose(camera.getProj()));
	m_cbPerFrame.CameraPos = camera.getPosition();
	m_cbPerFrame.LightDir = EU::Vector3(0.0f, -1.0f, 0.0f);
	m_cbPerFrame.LightColor = EU::Vector3(1.0f, 1.0f, 1.0f);

	if (!scene.directionalLights.empty()) {
		const LightData& mainLight = scene.directionalLights.front();
		m_cbPerFrame.LightDir = mainLight.direction;
		m_cbPerFrame.LightColor = mainLight.color * mainLight.intensity;
	}

	m_perFrameBuffer.update(deviceContext, nullptr, 0, nullptr, &m_cbPerFrame, 0, 0);
}

/**
 * @brief Ejecuta el pipeline completo de renderizado Forward.
 *
 * Configura el viewport, limpia buffers, construye las colas de
 * renderizado, actualiza los datos globales y ejecuta los pases
 * de Skybox, Opaque y Transparent.
 *
 * @param deviceContext Contexto de renderizado.
 * @param camera Cámara activa.
 * @param scene Escena a renderizar.
 * @param viewportPass Pase de salida del viewport.
 */
void
ForwardRenderer::render(DeviceContext& deviceContext,
	const Camera& camera,
	RenderScene& scene,
	EditorViewportPass& viewportPass) {
	const float viewportClear[4] = { 0.10f, 0.10f, 0.10f, 1.0f };
	viewportPass.begin(deviceContext, viewportClear);
	viewportPass.setViewport(deviceContext);
	viewportPass.clearDepth(deviceContext);

	buildQueues(scene, camera);
	updatePerFrame(camera, scene, deviceContext);

	renderSkyboxPass(deviceContext, scene);
	renderOpaquePass(deviceContext);
	renderTransparentPass(deviceContext);
}

/**
 * @brief Libera todos los recursos GPU utilizados por el renderer.
 *
 * Destruye Constant Buffers, Blend States, estados de profundidad
 * y vacía las colas de renderizado.
 */
void
ForwardRenderer::destroy() {
	m_opaqueQueue.clear();
	m_transparentQueue.clear();
	SAFE_RELEASE(m_alphaBlendState);
	SAFE_RELEASE(m_opaqueBlendState);
	SAFE_RELEASE(m_additiveBlendState);
	SAFE_RELEASE(m_premultipliedBlendState);
	m_transparentDepthStencil.destroy();
	m_perMaterialBuffer.destroy();
	m_perObjectBuffer.destroy();
	m_perFrameBuffer.destroy();
}

/**
 * @brief Construye y ordena las colas de renderizado.
 *
 * Separa los objetos opacos y transparentes en listas independientes.
 * Los objetos opacos se ordenan para minimizar cambios de estado,
 * mientras que los transparentes se ordenan de atrás hacia adelante
 * para garantizar un blending correcto.
 *
 * @param scene Escena fuente.
 * @param camera Cámara utilizada para el ordenamiento.
 */
void
ForwardRenderer::buildQueues(RenderScene& scene, const Camera& camera) {
	(void)camera;
	m_opaqueQueue.clear();
	m_transparentQueue.clear();

	for (auto& object : scene.opaqueObjects) {
		m_opaqueQueue.push_back(&object);
	}

	for (auto& object : scene.transparentObjects) {
		m_transparentQueue.push_back(&object);
	}

	std::sort(m_opaqueQueue.begin(), m_opaqueQueue.end(),
		[](const RenderObject* lhs, const RenderObject* rhs) {
			if (lhs->materialInstance != rhs->materialInstance) {
				return lhs->materialInstance < rhs->materialInstance;
			}
			return lhs->distanceToCamera < rhs->distanceToCamera;
		});

	std::sort(m_transparentQueue.begin(), m_transparentQueue.end(),
		[](const RenderObject* lhs, const RenderObject* rhs) {
			return lhs->distanceToCamera > rhs->distanceToCamera;
		});
}

/**
 * @brief Renderiza todos los objetos opacos.
 *
 * Configura el estado de mezcla opaco y procesa cada objeto
 * contenido en la cola de geometría opaca.
 *
 * @param deviceContext Contexto de renderizado.
 */
void
ForwardRenderer::renderOpaquePass(DeviceContext& deviceContext) {
	m_perFrameBuffer.render(deviceContext, 0, 1, true);
	deviceContext.OMSetBlendState(m_opaqueBlendState, m_blendFactor, 0xffffffff);

	for (const RenderObject* object : m_opaqueQueue) {
		if (!object) {
			continue;
		}
		renderObject(deviceContext, *object, RenderPassType::Opaque);
	}
}

/**
 * @brief Renderiza todos los objetos transparentes.
 *
 * Configura el estado de mezcla correspondiente a cada material
 * transparente y procesa los objetos ordenados por distancia
 * a la cámara.
 *
 * @param deviceContext Contexto de renderizado.
 */
void
ForwardRenderer::renderTransparentPass(DeviceContext& deviceContext) {
	m_perFrameBuffer.render(deviceContext, 0, 1, true);

	for (const RenderObject* object : m_transparentQueue) {
		if (!object) {
			continue;
		}
		Material* material = object->materialInstance ? object->materialInstance->getMaterial() : nullptr;
		deviceContext.OMSetBlendState(resolveBlendState(material), m_blendFactor, 0xffffffff);
		renderObject(deviceContext, *object, RenderPassType::Transparent);
	}

	deviceContext.OMSetBlendState(m_opaqueBlendState, m_blendFactor, 0xffffffff);
}

/**
 * @brief Renderiza el Skybox de la escena.
 *
 * Si existe un Skybox activo, delega su renderizado antes de
 * procesar la geometría visible.
 *
 * @param deviceContext Contexto de renderizado.
 * @param scene Escena actual.
 */
void
ForwardRenderer::renderSkyboxPass(DeviceContext& deviceContext, RenderScene& scene) {
	if (!scene.skybox) {
		return;
	}
	scene.skybox->render(deviceContext);
}

/**
 * @brief Renderiza una instancia de objeto.
 *
 * Actualiza los Constant Buffers por objeto y material,
 * configura los estados gráficos necesarios y realiza
 * las llamadas DrawIndexed para cada Submesh.
 *
 * Soporta materiales múltiples, transparencias y
 * parámetros PBR independientes por instancia.
 *
 * @param deviceContext Contexto de renderizado.
 * @param object Objeto a renderizar.
 * @param passType Tipo de pase actual.
 */
void
ForwardRenderer::renderObject(DeviceContext& deviceContext,
	const RenderObject& object,
	RenderPassType passType) {
	// Implementación existente...
}

/**
 * @brief Crea todos los estados de mezcla utilizados por el renderer.
 *
 * Genera los Blend States para:
 * - Opaque
 * - Alpha Blending
 * - Additive Blending
 * - Premultiplied Alpha
 *
 * @param device Dispositivo Direct3D.
 * @return HRESULT indicando éxito o error.
 */
HRESULT
ForwardRenderer::createBlendStates(Device& device) {
	// Implementación existente...
}

/**
 * @brief Obtiene el Blend State apropiado para un material.
 *
 * Determina qué estado de mezcla debe utilizarse según
 * el dominio y modo de mezcla configurados en el material.
 *
 * @param material Material evaluado.
 * @return Blend State correspondiente.
 */
ID3D11BlendState*
ForwardRenderer::resolveBlendState(const Material* material) const {
	// Implementación existente...
}