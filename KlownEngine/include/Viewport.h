#pragma once
#include "Prerequisites.h"

class Window;
class DeviceContext;

class
Viewport {
public:
  Viewport() = default;
  ~Viewport() = default;

  /**
   * @brief Inicializa la ventana gr�fica utilizando una instancia de Windows.
   * @param window Una referencia al objeto Window.
   */
  HRESULT
  init(const Window& window);

  /**
   * @brief Inicialice la ventana gr�fica con dimensiones espec�ficas.
   * @param width El ancho de la ventana gr�fica.
   * @param height La altura de la ventana gr�fica.
   */
  HRESULT
  init(unsigned int width, unsigned int height);

  /**
   * @brief Actualice la configuraci�n de la ventana gr�fica cuando sea necesario cambiar sus dimensiones.
   */
  void
  update();

  /**
   * @brief Representa la ventana gr�fica utilizando el contexto del dispositivo proporcionado.
   * @param deviceContext Una referencia al DeviceContext utilizado para la representaci�n.
   */
  void
  render(DeviceContext& deviceContext);

  /**
   * @brief Libera los recursos asociados al viewport.
   */
  void
  destroy();

private:
  D3D11_VIEWPORT m_viewport;
};