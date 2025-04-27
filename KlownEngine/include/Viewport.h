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
   * @brief Inicializa la ventana gráfica utilizando una instancia de Windows.
   * @param window Una referencia al objeto Window.
   */
  HRESULT
  init(const Window& window);

  /**
   * @brief Inicialice la ventana gráfica con dimensiones específicas.
   * @param width El ancho de la ventana gráfica.
   * @param height La altura de la ventana gráfica.
   */
  HRESULT
  init(unsigned int width, unsigned int height);

  /**
   * @brief Actualice la configuración de la ventana gráfica cuando sea necesario cambiar sus dimensiones.
   */
  void
  update();

  /**
   * @brief Representa la ventana gráfica utilizando el contexto del dispositivo proporcionado.
   * @param deviceContext Una referencia al DeviceContext utilizado para la representación.
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