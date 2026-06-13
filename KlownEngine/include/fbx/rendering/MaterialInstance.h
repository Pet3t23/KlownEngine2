/**
 * @file MaterialInstance.h
 * @brief Declara la clase MaterialInstance utilizada para configurar materiales por objeto.
 * @ingroup rendering
 */
#pragma once

#include "Prerequisites.h"
#include "Rendering/RenderTypes.h"

class Material;
class DeviceContext;
class Texture;

/**
 * @class MaterialInstance
 * @brief Instancia concreta de un Material con texturas y parámetros PBR propios.
 *
 * Permite reutilizar un mismo Material (shader + estados de renderizado)
 * con diferentes combinaciones de texturas y valores PBR para cada objeto.
 *
 * Slots de textura (deben coincidir con los registros t# del Pixel Shader):
 * - t0 : Albedo
 * - t1 : Normal
 * - t2 : Metallic
 * - t3 : Roughness
 * - t4 : Ambient Occlusion (AO)
 * - t5 : Emissive
 * - t6 : Shadow Map (asignado por ForwardRenderer)
 */
class MaterialInstance {
public:

    /**
     * @brief Asigna el material base.
     *
     * @param material Material a utilizar.
     */
    void setMaterial(Material* material) { m_material = material; }

    /**
     * @brief Asigna la textura de albedo.
     *
     * @param texture Textura de color base.
     */
    void setAlbedo(Texture* texture) { m_albedo = texture; }

    /**
     * @brief Asigna la textura normal map.
     *
     * @param texture Textura de normales.
     */
    void setNormal(Texture* texture) { m_normal = texture; }

    /**
     * @brief Asigna la textura metálica.
     *
     * @param texture Mapa de metallic.
     */
    void setMetallic(Texture* texture) { m_metallic = texture; }

    /**
     * @brief Asigna la textura de rugosidad.
     *
     * @param texture Mapa de roughness.
     */
    void setRoughness(Texture* texture) { m_roughness = texture; }

    /**
     * @brief Asigna la textura de ambient occlusion.
     *
     * @param texture Mapa AO.
     */
    void setAO(Texture* texture) { m_ao = texture; }

    /**
     * @brief Asigna la textura emisiva.
     *
     * @param texture Mapa emissive.
     */
    void setEmissive(Texture* texture) { m_emissive = texture; }

    /**
     * @brief Obtiene el material asociado.
     *
     * @return Material configurado.
     */
    Material* getMaterial() const { return m_material; }

    /**
     * @brief Obtiene la textura de albedo.
     *
     * @return Textura de color base.
     */
    Texture* getAlbedo() const { return m_albedo; }

    /**
     * @brief Obtiene la textura de normales.
     *
     * @return Normal map.
     */
    Texture* getNormal() const { return m_normal; }

    /**
     * @brief Obtiene la textura metálica.
     *
     * @return Mapa metallic.
     */
    Texture* getMetallic() const { return m_metallic; }

    /**
     * @brief Obtiene la textura de rugosidad.
     *
     * @return Mapa roughness.
     */
    Texture* getRoughness() const { return m_roughness; }

    /**
     * @brief Obtiene la textura de ambient occlusion.
     *
     * @return Mapa AO.
     */
    Texture* getAO() const { return m_ao; }

    /**
     * @brief Obtiene la textura emisiva.
     *
     * @return Mapa emissive.
     */
    Texture* getEmissive() const { return m_emissive; }

    /**
     * @brief Obtiene los parámetros PBR editables.
     *
     * @return Referencia a los parámetros del material.
     */
    MaterialParams& getParams() { return m_params; }

    /**
     * @brief Obtiene los parámetros PBR en modo lectura.
     *
     * @return Referencia constante a los parámetros del material.
     */
    const MaterialParams& getParams() const { return m_params; }

    /**
     * @brief Enlaza todas las texturas válidas al Pixel Shader.
     *
     * Cada textura se enlaza en el slot correspondiente definido
     * por la convención del motor.
     *
     * @param deviceContext Contexto de dispositivo activo.
     */
    void bindTextures(DeviceContext& deviceContext) const;

private:

    /** Material base compartido. */
    Material* m_material = nullptr;

    /** Textura de color base (Albedo). */
    Texture* m_albedo = nullptr;

    /** Normal map. */
    Texture* m_normal = nullptr;

    /** Mapa de metallic. */
    Texture* m_metallic = nullptr;

    /** Mapa de roughness. */
    Texture* m_roughness = nullptr;

    /** Mapa de ambient occlusion. */
    Texture* m_ao = nullptr;

    /** Mapa emissive. */
    Texture* m_emissive = nullptr;

    /** Parámetros PBR propios de esta instancia. */
    MaterialParams m_params;
};