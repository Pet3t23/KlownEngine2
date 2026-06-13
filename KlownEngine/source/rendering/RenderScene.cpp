/**
 * @file RenderScene.cpp
 * @brief Implementación de la clase RenderScene.
 * @ingroup rendering
 *
 * Este módulo proporciona las operaciones básicas para gestionar
 * los elementos renderizables de una escena durante un frame.
 */

#include "Rendering/RenderScene.h"

 /**
  * @brief Limpia todo el contenido de la escena.
  *
  * Elimina los objetos opacos y transparentes registrados,
  * descarta las luces direccionales almacenadas y restablece
  * la referencia al skybox.
  *
  * Esta función suele invocarse al inicio de cada frame antes
  * de reconstruir la escena visible para el renderer.
  */
void
RenderScene::clear() {
    opaqueObjects.clear();
    transparentObjects.clear();
    directionalLights.clear();
    skybox = nullptr;
}