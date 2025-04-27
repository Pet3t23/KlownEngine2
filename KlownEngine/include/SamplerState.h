#pragma once
#include "Prerequisites.h"

// Forward declaraitons
class Device;
class DeviceContext;

class
SamplerState {
public:
  SamplerState() = default;
  ~SamplerState() = default;

  /**
   * @brief Configura el SamplerState, que controla el muestreo de texturas en la renderización.
   * @param device Dispositivo gráfico utilizado para la inicialización.
   */
  HRESULT
  init(Device& device);

  /**
   * @briefActualiza los parámetros del SamplerState si es necesario.
   */
  void
  update();

  /**
   * @brief Aplica el SamplerState al pipeline gráfico para su uso en el muestreo de texturas.
   @param deviceContext Contexto del dispositivo donde se aplicará el SamplerState.
   * @param StartSlot Índice del primer slot donde se vinculará el SamplerState.
   * @param numSamplers Número total de SamplerStates a configurar.
   * */
  void
  render(DeviceContext& deviceContext, 
           unsigned int StartSlot, 
           unsigned int numSamplers);

  /**
   * @brief Libera todos los recursos asignados al SamplerState.
   */
  void
  destroy();

private:
  ID3D11SamplerState* m_samplerState = nullptr;
};