/**
 * @file RenderTypes.h
 * @brief Define los tipos, enumeraciones y estructuras utilizados por el sistema de renderizado.
 * @ingroup rendering
 */
#pragma once

#include "Prerequisites.h"

class Mesh;
class MaterialInstance;

/**
 * @enum MaterialDomain
 * @brief Define el dominio de renderizado de un material.
 */
enum class MaterialDomain {

    /** Geometría completamente opaca. */
    Opaque = 0,

    /** Geometría con descarte por alfa (alpha test). */
    Masked,

    /** Geometría transparente con blending. */
    Transparent
};

/**
 * @enum BlendMode
 * @brief Modos de mezcla soportados por el renderer.
 */
enum class BlendMode {

    /** Sin mezcla; sobrescribe el color destino. */
    Opaque = 0,

    /** Mezcla alfa tradicional. */
    Alpha,

    /** Mezcla aditiva. */
    Additive,

    /** Mezcla con alfa premultiplicado. */
    PremultipliedAlpha
};

/**
 * @enum RenderPassType
 * @brief Tipos de pases de render utilizados por el pipeline.
 */
enum class RenderPassType {

    /** Pase de generación de sombras. */
    Shadow = 0,

    /** Pase principal de objetos opacos. */
    Opaque,

    /** Pase de renderizado del skybox. */
    Skybox,

    /** Pase de objetos transparentes. */
    Transparent,

    /** Pase de visualización del editor. */
    Editor
};

/**
 * @enum LightType
 * @brief Tipos de luces soportados por el motor.
 */
enum class LightType {

    /** Luz direccional infinita. */
    Directional = 0,

    /** Luz puntual omnidireccional. */
    Point,

    /** Luz tipo reflector (spotlight). */
    Spot
};

/**
 * @struct LightData
 * @brief Describe una fuente de luz utilizada durante el renderizado.
 */
struct LightData {

    /** Tipo de luz. */
    LightType type = LightType::Directional;

    /** Color de la luz. */
    EU::Vector3 color = EU::Vector3(1.0f, 1.0f, 1.0f);

    /** Intensidad de la luz. */
    float intensity = 1.0f;

    /** Dirección de emisión para luces direccionales y spot. */
    EU::Vector3 direction = EU::Vector3(0.0f, -1.0f, 0.0f);

    /** Alcance máximo para luces puntuales y spot. */
    float range = 0.0f;

    /** Posición de la luz. */
    EU::Vector3 position = EU::Vector3(0.0f, 0.0f, 0.0f);

    /** Ángulo de apertura para luces spot. */
    float spotAngle = 0.0f;
};

/**
 * @struct MaterialParams
 * @brief Parámetros PBR configurables por instancia de material.
 */
struct MaterialParams {

    /** Color base del material. */
    XMFLOAT4 baseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

    /** Nivel de metalicidad. */
    float metallic = 1.0f;

    /** Rugosidad de la superficie. */
    float roughness = 1.0f;

    /** Intensidad de ambient occlusion. */
    float ao = 1.0f;

    /** Escala aplicada al normal map. */
    float normalScale = 1.0f;

    /** Intensidad de emisión. */
    float emissiveStrength = 1.0f;

    /** Umbral para materiales Masked. */
    float alphaCutoff = 0.5f;
};

/**
 * @struct CBPerFrame
 * @brief Constant Buffer actualizado una vez por frame.
 *
 * Contiene información global compartida por todos los objetos renderizados.
 */
struct CBPerFrame {

    /** Matriz de vista. */
    XMFLOAT4X4 View{};

    /** Matriz de proyección. */
    XMFLOAT4X4 Projection{};

    /** Posición de la cámara. */
    EU::Vector3 CameraPos{};

    float pad0 = 0.0f;

    /** Dirección de la luz principal. */
    EU::Vector3 LightDir = EU::Vector3(0.0f, -1.0f, 0.0f);

    float pad1 = 0.0f;

    /** Color de la luz principal. */
    EU::Vector3 LightColor = EU::Vector3(1.0f, 1.0f, 1.0f);

    float pad2 = 0.0f;
};

/**
 * @struct CBPerObject
 * @brief Constant Buffer actualizado para cada objeto renderizado.
 */
struct CBPerObject {

    /** Matriz de transformación mundial. */
    XMFLOAT4X4 World{};
};

/**
 * @struct CBPerMaterial
 * @brief Constant Buffer actualizado para cada material.
 *
 * Contiene los parámetros enviados al shader durante el renderizado.
 */
struct CBPerMaterial {

    /** Color base del material. */
    XMFLOAT4 BaseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

    /** Valor de metalicidad. */
    float Metallic = 1.0f;

    /** Valor de rugosidad. */
    float Roughness = 1.0f;

    /** Intensidad de AO. */
    float AO = 1.0f;

    /** Escala del normal map. */
    float NormalScale = 1.0f;

    /** Intensidad emisiva. */
    float EmissiveStrength = 1.0f;

    /** Umbral de descarte alfa. */
    float AlphaCutoff = 0.0f;

    /** Padding para alineación GPU. */
    float pad0 = 0.0f;
    float pad1 = 0.0f;
    float pad2 = 0.0f;
    float pad3 = 0.0f;
    float pad4 = 0.0f;
    float pad5 = 0.0f;
};

/**
 * @struct RenderObject
 * @brief Representa una instancia renderizable dentro de una escena.
 *
 * Contiene la geometría, materiales y datos necesarios para que el
 * renderer procese el objeto durante los distintos pases de render.
 */
struct RenderObject {

    /** Malla a renderizar. */
    Mesh* mesh = nullptr;

    /** Material principal utilizado por el objeto. */
    MaterialInstance* materialInstance = nullptr;

    /** Materiales asociados a cada Submesh. */
    std::vector<MaterialInstance*> materialInstances;

    /** Transformación mundial del objeto. */
    XMMATRIX world = XMMatrixIdentity();

    /** Indica si el objeto genera sombras. */
    bool castShadow = true;

    /** Indica si debe procesarse como transparente. */
    bool transparent = false;

    /** Distancia a la cámara utilizada para ordenamiento. */
    float distanceToCamera = 0.0f;
};