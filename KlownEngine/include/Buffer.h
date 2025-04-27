#pragma once
#include "Prerequisites.h"

// Forward Declations
class Device;
class DeviceContext;
class MeshComponent;

class 
Buffer {
public:
  Buffer() = default;
  ~Buffer() = default;

  /**
   * @brief Inicializa los buffers index y vertex.
   * @param device Referencia al dispositivo.
   * @param mesh Referencia a la malla.
   * @param bindFlag Indicador que especifica si el búfer es de vértices o índices.
   * @return Resultado de la operación.
   */
  HRESULT
  init(Device& device, MeshComponent& mesh, unsigned int bindFlag);

  /**
   * @brief Inicializa los búferes constantes.
   * @param device Referencia al dispositivo.
   * @param ByteWidth Tamaño del búfer en bytes.
   */
  HRESULT
  init(Device& device, unsigned int ByteWidth);

  /**
   * @brief Actualiza la lógica de los búferes constantes en cada fotograma.
   * @param DstSubresource Índice del subrecurso.
   * @param pDstBox Puntero de la región a actualizar.
   * @param pSrcData Puntero a los datos de origen.
   * @param SrcRowPitch Tamaño de la de datos.
   * @param SrcDepthPitch Capa de datos en la profundidad.
   */
  void
  update(DeviceContext& deviceContext,
         unsigned int DstSubresource,
         const D3D11_BOX* pDstBox,
         const void* pSrcData,
         unsigned int SrcRowPitch,
         unsigned int SrcDepthPitch);

  /**
   * @brief Configura y vincula los búferes de vértices, índices y constantes para la renderización.
   * @param deviceContext Referencia al contexto del dispositivo.
   * @param StartSlot Índice inicial para la vinculación del búfer.
   * @param NumBuffers Número de búferes a vincular.
   * @param setPixelShader Si es true, el búfer se vincula al sombreador de píxeles.
   * @param format Formato del búfer de índice (por defecto es desconocido).
   */
  void
  render(DeviceContext& deviceContext, 
         unsigned int StartSlot, 
         unsigned int NumBuffers,
         bool setPixelShader = false,
         DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN
         );

  /**
   * @brief Libera los recursos del búfer.
   */
  void
  destroy();

private:
  /**
   * @brief Crea un búfer D3D11.
   * @param device Referencia al dispositivo utilizado para la creación del búfer.
   * @param desc Estructura que describe las propiedades del búfer.
   * @param initData Puntero a los datos iniciales del búfer.
   */
  HRESULT
  createBuffer(Device& device,
                 D3D11_BUFFER_DESC& desc,
                 D3D11_SUBRESOURCE_DATA* initData);

  ID3D11Buffer* m_buffer = nullptr;
  unsigned int m_bindFlag = 0;
  unsigned int m_stride = 0;
  unsigned int m_offset = 0;
};