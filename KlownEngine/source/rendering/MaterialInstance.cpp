/**
 * @file MaterialInstance.cpp
 * @brief Implementación de MaterialInstance.
 * @ingroup rendering
 *
 * Este módulo gestiona el enlace de texturas asociadas a una instancia
 * de material para su utilización durante el renderizado.
 */

#include "Rendering/MaterialInstance.h"
#include "DeviceContext.h"
#include "Texture.h"

 /**
  * @brief Enlaza las texturas de la instancia al Pixel Shader.
  *
  * Primero limpia los slots de textura utilizados por el sistema PBR
  * para evitar referencias residuales de draw calls anteriores.
  *
  * Posteriormente enlaza cada textura válida en su slot correspondiente:
  *
  * - t0 : Albedo
  * - t1 : Normal
  * - t2 : Metallic
  * - t3 : Roughness
  * - t4 : Ambient Occlusion (AO)
  * - t5 : Emissive
  *
  * Los slots sin textura permanecen enlazados a nullptr.
  *
  * @param deviceContext Contexto de renderizado activo.
  */
void
MaterialInstance::bindTextures(DeviceContext& deviceContext) const {
    ID3D11ShaderResourceView* nullTextures[6] = {
        nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr
    };

    deviceContext.PSSetShaderResources(0, 6, nullTextures);

    if (m_albedo) {
        m_albedo->render(deviceContext, 0, 1);
    }

    if (m_normal) {
        m_normal->render(deviceContext, 1, 1);
    }

    if (m_metallic) {
        m_metallic->render(deviceContext, 2, 1);
    }

    if (m_roughness) {
        m_roughness->render(deviceContext, 3, 1);
    }

    if (m_ao) {
        m_ao->render(deviceContext, 4, 1);
    }

    if (m_emissive) {
        m_emissive->render(deviceContext, 5, 1);
    }
}