/**
 * @file ForwardRenderer.h
 * @brief Declara la clase ForwardRenderer encargada del renderizado Forward.
 * @ingroup rendering
 */
#pragma once

#include "Prerequisites.h"
#include "Buffer.h"
#include "DepthStencilState.h"
#include "Rendering/RenderScene.h"
#include "Rendering/RenderTypes.h"

class Device;
class DeviceContext;
class Camera;
class EditorViewportPass;
class Material;

/**
 * @class ForwardRenderer
 * @brief Implementa la técnica de renderizado Forward.
 *
 * Gestiona la actualización de buffers constantes, la construcción de colas
 * de renderizado y la ejecución de los distintos pases de render (objetos
 * opacos, transparentes y skybox).
 */
class ForwardRenderer {
public:

    /**
     * @brief Inicializa los recursos necesarios para el renderer.
     *
     * @param device Dispositivo gráfico utilizado para crear recursos.
     * @return HRESULT indicando éxito o error en la inicialización.
     */
    HRESULT init(Device& device);

    /**
     * @brief Redimensiona los recursos dependientes de la resolución.
     *
     * @param device Dispositivo gráfico.
     * @param width Nuevo ancho del viewport.
     * @param height Nueva altura del viewport.
     */
    void resize(Device& device, unsigned int width, unsigned int height);

    /**
     * @brief Actualiza los buffers constantes con información del frame actual.
     *
     * @param camera Cámara activa.
     * @param scene Escena a renderizar.
     * @param deviceContext Contexto de renderizado.
     */
    void updatePerFrame(const Camera& camera,
        const RenderScene& scene,
        DeviceContext& deviceContext);

    /**
     * @brief Ejecuta el proceso completo de renderizado.
     *
     * @param deviceContext Contexto de renderizado.
     * @param camera Cámara activa.
     * @param scene Escena a renderizar.
     * @param viewportPass Pase de salida al viewport del editor.
     */
    void render(DeviceContext& deviceContext,
        const Camera& camera,
        RenderScene& scene,
        EditorViewportPass& viewportPass);

    /**
     * @brief Libera todos los recursos asociados al renderer.
     */
    void destroy();

private:

    /**
     * @brief Construye las colas de objetos opacos y transparentes.
     *
     * @param scene Escena a procesar.
     * @param camera Cámara utilizada para ordenamiento.
     */
    void buildQueues(RenderScene& scene, const Camera& camera);

    /**
     * @brief Renderiza todos los objetos opacos.
     *
     * @param deviceContext Contexto de renderizado.
     */
    void renderOpaquePass(DeviceContext& deviceContext);

    /**
     * @brief Renderiza todos los objetos transparentes.
     *
     * @param deviceContext Contexto de renderizado.
     */
    void renderTransparentPass(DeviceContext& deviceContext);

    /**
     * @brief Renderiza el skybox de la escena.
     *
     * @param deviceContext Contexto de renderizado.
     * @param scene Escena actual.
     */
    void renderSkyboxPass(DeviceContext& deviceContext,
        RenderScene& scene);

    /**
     * @brief Renderiza un objeto individual.
     *
     * @param deviceContext Contexto de renderizado.
     * @param object Objeto a renderizar.
     * @param passType Tipo de pase de render.
     */
    void renderObject(DeviceContext& deviceContext,
        const RenderObject& object,
        RenderPassType passType);

    /**
     * @brief Crea los estados de mezcla utilizados por el renderer.
     *
     * @param device Dispositivo gráfico.
     * @return HRESULT indicando éxito o error.
     */
    HRESULT createBlendStates(Device& device);

    /**
     * @brief Obtiene el estado de mezcla apropiado para un material.
     *
     * @param material Material evaluado.
     * @return Estado de mezcla correspondiente.
     */
    ID3D11BlendState* resolveBlendState(const Material* material) const;

private:

    /** Buffer constante con información global por frame. */
    Buffer m_perFrameBuffer;

    /** Buffer constante con información por objeto. */
    Buffer m_perObjectBuffer;

    /** Buffer constante con información por material. */
    Buffer m_perMaterialBuffer;

    /** Estado Depth-Stencil utilizado para geometría transparente. */
    DepthStencilState m_transparentDepthStencil;

    /** Estado de mezcla alfa estándar. */
    ID3D11BlendState* m_alphaBlendState = nullptr;

    /** Estado de mezcla para objetos opacos. */
    ID3D11BlendState* m_opaqueBlendState = nullptr;

    /** Estado de mezcla aditiva. */
    ID3D11BlendState* m_additiveBlendState = nullptr;

    /** Estado de mezcla con alfa premultiplicado. */
    ID3D11BlendState* m_premultipliedBlendState = nullptr;

    /** Factor de mezcla utilizado por Direct3D. */
    float m_blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    /** Datos constantes actualizados por frame. */
    CBPerFrame m_cbPerFrame{};

    /** Datos constantes actualizados por objeto. */
    CBPerObject m_cbPerObject{};

    /** Datos constantes actualizados por material. */
    CBPerMaterial m_cbPerMaterial{};

    /** Cola de objetos opacos. */
    std::vector<const RenderObject> m_opaqueQueue;

    /** Cola de objetos transparentes. */
    std::vector<const RenderObject> m_transparentQueue;
};