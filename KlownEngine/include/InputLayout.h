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
   * @brief Utiliza la configuración del dispositivo para ingresar el diseño,
   * Ingrese una descripción del diseño y los datos del sombreador de vértices.
   * @param dispositivo Una referencia al dispositivo utilizado para crear el diseño de entrada.
   * @param Vector de diseño de una estructura D3D11_INPUT_ELEMENT_DESC que describe el diseño de entrada.
   * @param VertexShaderData Puntero a datos del sombreador de vértices.
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