#pragma once
#include "Prerequisites.h"
#include "ECS/Entity.h"
#include "Buffer.h"
#include "Texture.h"
#include "SamplerState.h"
#include "Transform.h"
using namespace std;

// Forward Declarations
class Device;
class Component;

class Actor : Entity {
public:
  /*
  * @brief Destructor por defecto
  */
  Actor() = default;

  /*
  * @brief Contructor que inicializa el Device
  */
  Actor(Device& device);

  /*
  * @brief Destructor virtual 
  */
  virtual ~Actor() = default;

  /*
  * @briefctualiza el estado del Actor en función del tiempo transcurrido.
  * @param deltaTime Tiempo transcurrido desde la última actualización.
  * @param deviceContext Contexto del dispositivo utilizado para actualizar buffers y recursos gráficos.
  */
  void
  update(float deltaTime, DeviceContext& deviceContext) override;

  /*
  * @brief Renderiza el Actor utilizando el contexto gráfico especificado.
  * @param deviceContext Contexto del dispositivo utilizado para la renderización.
  */
  void
  render(DeviceContext& deviceContext) override;

  /**
   * @brief Libera los recursos asociados al Actor
   */
  void
  destroy();

  /**
   * Asigna una o más mallas al Actor.
   * @param device Referencia al dispositivo utilizado para cargar y configurar buffers.
   * @param meshes Vector de objetos que representan las mallas a utilizar.
 */
  void 
  setMesh(Device& device, std::vector<MeshComponent> meshes);

  /**
  * @brief Establece las texturas asociadas al Actor.
  * @param textures Vector de objetos Texture que serán utilizados durante la renderización.
  */
  void 
  setTextures(vector<Texture> textures) {
    m_textures = textures;
  }

  /**
   * @brief Devuelve el nombre del Actor.
   * @return Cadena que representa el nombre del Actor.
   */
  string
  getName() {
    return m_name;
  }

  /*
  * @brief Recupera un componente específico del Actor mediante el tipo indicado.
  */
  template<typename T>
  EngineUtilities::TSharedPointer<T>
  getComponent();

private:
  vector<MeshComponent> m_meshes;
  vector<Texture> m_textures;
  vector<Buffer> m_vertexBuffers;
  vector<Buffer> m_indexBuffers;
  vector<Buffer> m_buffers;

  Buffer m_modelBuffer;
  SamplerState m_sampler;
  CBChangesEveryFrame m_changeEveryFrame;
  string m_name = "Actor";
};

/*
  * The purpose of this function is to search for and return a specific component of an actor using the specific component type as template arguments.
  * actor using the type of the specific component as template arguments.
  * If the component is not found, the function returns nullptr.
  */
template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
  for (auto& component : m_components) {
    EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
    if (specificComponent) {
      return specificComponent;
    }
  }
  // Returns an empty TSharedPointer if the component is not found.
  return EngineUtilities::TSharedPointer<T>();
}