#pragma once
#include "Prerequisites.h"
#include "InputLayout.h"

class Device;
class DeviceContext;

class 
ShaderProgram {
public:
  ShaderProgram() = default;
  ~ShaderProgram() = default;

  /**
   * @brief Se encarga de iniciar y establecer las configuraciones del programa de sombreado. 
   * @param device Referencia al dispositivo. * @param fileName Nombre del archivo de sombreado. 
   * @param Layout Vector que tiene la explicaci�n del dise�o de entrada.
   */
  HRESULT
  init(Device& device,
      const std::string& fileName,
      std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /**
   * @brief Actualiza el Shader Program
   */
  void
  update();

  /**
   * @brief Establece el layout, el VertextShader y el Pixel Shader en el contexto del dispositivo.
   */
  void
  render(DeviceContext& DeviceContext);

  /**
   * @brief Destruye el programa y libera recursos
   */
  void
  destroy();

  /**
   * @brief Crea el layout utilizando el dispositivo y la descripci�n del mismo proporcionados.
   * @param device Referencia al dispositivo.
   * @param Layout Vector que contiene la descripci�n del dise�o de entrada.
   */
  HRESULT
  CreateInputLayout(Device& device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /**
   * @brief  Crea un shader de v�rtices o uno de p�xeles seg�n se especifique
   */
  HRESULT
  CreateShader(Device& device, ShaderType type);

  /**
   * @brief Compila el shader mediante un punto de entrada.
   */
  HRESULT
  CompileShaderFromFile(char* szFileName,
                        LPCSTR szEntryPoint,
                        LPCSTR szShaderModel,
                        ID3DBlob** ppBlobOut);

  ID3D11VertexShader* m_VertexShader = nullptr;
  ID3D11PixelShader* m_PixelShader = nullptr;
  InputLayout m_inputLayout;

private:
  std::string m_shaderFileName;
  ID3DBlob* m_vertexShaderData = nullptr;
  ID3DBlob* m_pixelShaderData = nullptr;
};