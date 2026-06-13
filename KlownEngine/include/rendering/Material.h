/**
 * @file Material.h
 * @brief Declara la clase Material utilizada para definir el estado de renderizado de una superficie.
 * @ingroup rendering
 */
#pragma once

#include "Prerequisites.h"
#include "Rendering/RenderTypes.h"

class ShaderProgram;
class RasterizerState;
class DepthStencilState;
class SamplerState;

/**
 * @class Material
 * @brief Representa un material utilizado durante el renderizado.
 *
 * Un material agrupa los recursos y estados gráficos necesarios para
 * renderizar una superficie, incluyendo shaders, estados de rasterización,
 * profundidad, muestreo y configuración de mezcla.
 */
class Material {
public:

    /**
     * @brief Asigna el programa de shaders del material.
     *
     * @param shader Programa de shaders a utilizar.
     */
    void setShader(ShaderProgram* shader) { m_shader = shader; }

    /**
     * @brief Asigna el estado de rasterización.
     *
     * @param state Estado de rasterización.
     */
    void setRasterizerState(RasterizerState* state) { m_rasterizerState = state; }

    /**
     * @brief Asigna el estado de profundidad y stencil.
     *
     * @param state Estado Depth-Stencil.
     */
    void setDepthStencilState(DepthStencilState* state) { m_depthStencilState = state; }

    /**
     * @brief Asigna el estado de muestreo de texturas.
     *
     * @param state Estado de sampler.
     */
    void setSamplerState(SamplerState* state) { m_samplerState = state; }

    /**
     * @brief Define el dominio del material.
     *
     * @param domain Dominio de renderizado del material.
     */
    void setDomain(MaterialDomain domain) { m_domain = domain; }

    /**
     * @brief Define el modo de mezcla utilizado por el material.
     *
     * @param blendMode Modo de blending.
     */
    void setBlendMode(BlendMode blendMode) { m_blendMode = blendMode; }

    /**
     * @brief Obtiene el programa de shaders asociado.
     *
     * @return Puntero al programa de shaders.
     */
    ShaderProgram* getShader() const { return m_shader; }

    /**
     * @brief Obtiene el estado de rasterización.
     *
     * @return Estado de rasterización actual.
     */
    RasterizerState* getRasterizerState() const { return m_rasterizerState; }

    /**
     * @brief Obtiene el estado de profundidad y stencil.
     *
     * @return Estado Depth-Stencil actual.
     */
    DepthStencilState* getDepthStencilState() const { return m_depthStencilState; }

    /**
     * @brief Obtiene el estado de muestreo.
     *
     * @return Estado de sampler actual.
     */
    SamplerState* getSamplerState() const { return m_samplerState; }

    /**
     * @brief Obtiene el dominio del material.
     *
     * @return Dominio configurado.
     */
    MaterialDomain getDomain() const { return m_domain; }

    /**
     * @brief Obtiene el modo de mezcla configurado.
     *
     * @return Modo de blending actual.
     */
    BlendMode getBlendMode() const { return m_blendMode; }

private:

    /** Programa de shaders utilizado para renderizar el material. */
    ShaderProgram* m_shader = nullptr;

    /** Estado de rasterización asociado al material. */
    RasterizerState* m_rasterizerState = nullptr;

    /** Estado de profundidad y stencil asociado al material. */
    DepthStencilState* m_depthStencilState = nullptr;

    /** Estado de muestreo utilizado para las texturas. */
    SamplerState* m_samplerState = nullptr;

    /** Dominio de renderizado del material. */
    MaterialDomain m_domain = MaterialDomain::Opaque;

    /** Modo de mezcla utilizado durante el renderizado. */
    BlendMode m_blendMode = BlendMode::Opaque;
};