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
   * @brief Configura el SamplerState, que controla el muestreo de texturas en la renderizaci�n.
   * @param device Dispositivo gr�fico utilizado para la inicializaci�n.
   */
  HRESULT
  init(Device& device);

  /**
   * @briefActualiza los par�metros del SamplerState si es necesario.
   */
  void
  update();

  /**
   * @brief Aplica el SamplerState al pipeline gr�fico para su uso en el muestreo de texturas.
   @param deviceContext Contexto del dispositivo donde se aplicar� el SamplerState.
   * @param StartSlot �ndice del primer slot donde se vincular� el SamplerState.
   * @param numSamplers N�mero total de SamplerStates a configurar.
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