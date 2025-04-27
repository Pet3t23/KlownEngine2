#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

class 
InputLayout {
public:
  InputLayout() = default;
  ~InputLayout() = default;

  /**
   * @brief Utiliza la configuraci�n del dispositivo para ingresar el dise�o,
   * Ingrese una descripci�n del dise�o y los datos del sombreador de v�rtices.
   * @param dispositivo Una referencia al dispositivo utilizado para crear el dise�o de entrada.
   * @param Vector de dise�o de una estructura D3D11_INPUT_ELEMENT_DESC que describe el dise�o de entrada.
   * @param VertexShaderData Puntero a datos del sombreador de v�rtices.
   */
  HRESULT
  init(Device& device,
      std::vector<D3D11_INPUT_ELEMENT_DESC>& Layout,
      ID3DBlob* VertexShaderData);

  /**
   * @brief Actualiza el Input Layout
   */
  void
  update();

  /**
   * @brief Vincula el InputLayouta al pipeline.
   */
  void
  render(DeviceContext& deviceContext);

  /**
   * @brief Libera los recursos del layout
   */
  void
  destroy();

public:
  ID3D11InputLayout* m_inputLayout = nullptr;
};