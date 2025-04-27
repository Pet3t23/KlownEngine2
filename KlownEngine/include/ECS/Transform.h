#pragma once
#include "Prerequisites.h"
#include "ECS/Component.h"
#include "utilities/Vectors/Vector3.h"

class
Transform : public Component {
public:
  /**
   * @brief Constructor que inicializa position, rotation y scale a valores por defecto.
   */
  Transform() : position(),
                rotation(),
                scale(),
                matrix(),
                Component(ComponentType::TRANSFORM) {}

  /**
   * @brief Inicializa datos internos del Transform.
   */
  void
  init();

  /**
   * @brief Actualiza los valores del Transform cada fotograma.
   * @param deltaTime Tiempo transcurrido desde el último fotograma.
   */
  void
  update(float deltaTime) override;

  /**
   * @brief Render por defecto del Transform (no hace nada en esta clase).
   */
  void
  render(DeviceContext& deviceContext) override {};

  /**
   * @brief  Libera los recursos del Transform.
   */
  void
  destroy() {}

  /**
   * @brief Obtiene la posición actual.
   * @return Referencia constante a position.
   */
  const EngineUtilities::Vector3& 
  getPosition() const { return position; }
  
  /**
   * @brief @brief Establece una nueva posición.
   * @param newPos Nuevo valor para position.
   */
  void
  setPosition(const EngineUtilities::Vector3& newPos) { position = newPos; }

  /**
   * @brief Obtiene la rotación actual.
   * @return Referencia constante a rotation.
   */
  const EngineUtilities::Vector3& 
  getRotation() const { return rotation; }

  /**
   * @brief Establece una nueva rotación.
   * @param newRot Nuevo valor para rotation.
   */
  void
  setRotation(const EngineUtilities::Vector3& newRot) { rotation = newRot; }

  /**
   * @brief Obtiene la escala actual.
   * @return Referencia constante a scale.
   */
  const EngineUtilities::Vector3& 
  getScale() const { return scale; }

  /**
   * @brief Establece una nueva escala.
   * @param newScale Nuevo valor para scale.
   */
  void
  setScale(const EngineUtilities::Vector3& newScale) { scale = newScale; }

  /*
  * @brief Establece posición, rotación y escala al mismo tiempo
  */
  void
  setTransform(const EngineUtilities::Vector3& newPos, 
               const EngineUtilities::Vector3& newRot,
               const EngineUtilities::Vector3& newSca);

private:
  EngineUtilities::Vector3 position;
  EngineUtilities::Vector3 rotation;
  EngineUtilities::Vector3 scale;

public:
  XMMATRIX matrix;
};