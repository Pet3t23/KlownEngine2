/**
 * @file RenderScene.h
 * @brief Declara la clase RenderScene utilizada para almacenar los elementos visibles de una escena.
 * @ingroup rendering
 */
#pragma once

#include "Prerequisites.h"
#include "Rendering/RenderTypes.h"

class Skybox;

/**
 * @class RenderScene
 * @brief Contenedor temporal de los datos necesarios para renderizar una escena.
 *
 * Agrupa los objetos visibles, las luces activas y el skybox que serán
 * procesados por el renderer durante un frame.
 *
 * Las listas se rellenan normalmente durante la fase de recopilación
 * de la escena y posteriormente son consumidas por el pipeline de render.
 */
class RenderScene {
public:

    /**
     * @brief Limpia todo el contenido de la escena.
     *
     * Elimina los objetos renderizables, las luces registradas y
     * restablece la referencia al skybox.
     */
    void clear();

public:

    /**
     * @brief Lista de objetos opacos.
     *
     * Estos objetos suelen renderizarse primero para aprovechar
     * el Z-Buffer y minimizar el overdraw.
     */
    std::vector<RenderObject> opaqueObjects;

    /**
     * @brief Lista de objetos transparentes.
     *
     * Generalmente se renderizan después de los objetos opacos
     * y ordenados según la distancia a la cámara.
     */
    std::vector<RenderObject> transparentObjects;

    /**
     * @brief Luces direccionales activas de la escena.
     */
    std::vector<LightData> directionalLights;

    /**
     * @brief Skybox utilizado para renderizar el fondo de la escena.
     */
    Skybox* skybox = nullptr;
};