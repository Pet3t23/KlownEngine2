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
   * @param bindFlag Indicador que especifica si el b�fer es de v�rtices o �ndices.
   * @return Resultado de la operaci�n.
   */
  HRESULT
  init(Device& device, MeshComponent& mesh, unsigned int bindFlag);

  /**
   * @brief Inicializa los b�feres constantes.
   * @param device Referencia al dispositivo.
   * @param ByteWidth Tama�o del b�fer en bytes.
   */
  HRESULT
  init(Device& device, unsigned int ByteWidth);

  /**
   * @brief Actualiza la l�gica de los b�feres constantes en cada fotograma.
   * @param DstSubresource �ndice del subrecurso.
   * @param pDstBox Puntero de la regi�n a actualizar.
   * @param pSrcData Puntero a los datos de origen.
   * @param SrcRowPitch Tama�o de la de datos.
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
   * @brief Configura y vincula los b�feres de v�rtices, �ndices y constantes para la renderizaci�n.
   * @param deviceContext Referencia al contexto del dispositivo.
   * @param StartSlot �ndice inicial para la vinculaci�n del b�fer.
   * @param NumBuffers N�mero de b�feres a vincular.
   * @param setPixelShader Si es true, el b�fer se vincula al sombreador de p�xeles.
   * @param format Formato del b�fer de �ndice (por defecto es desconocido).
   */
  void
  render(DeviceContext& deviceContext, 
         unsigned int StartSlot, 
         unsigned int NumBuffers,
         bool setPixelShader = false,
         DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN
         );

  /**
   * @brief Libera los recursos del b�fer.
   */
  void
  destroy();

private:
  /**
   * @brief Crea un b�fer D3D11.
   * @param device Referencia al dispositivo utilizado para la creaci�n del b�fer.
   * @param desc Estructura que describe las propiedades del b�fer.
   * @param initData Puntero a los datos iniciales del b�fer.
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