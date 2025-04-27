#include "Prerequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Swapchain.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "MeshComponent.h"
#include "Buffer.h"
#include "SamplerState.h"
#include "UserInterface.h"
#include "ModelLoader.h"
#include "ECS/Actor.h"

class
  BaseApp {
public:
  /**
   * @brief Constructores por fefecto
   */
  BaseApp() = default;
  ~BaseApp() = default;

  /**
   * @brief Inicia la ventana con todos los recursos
   */
  HRESULT
    init();

  /**
   * @brief Actualiza la lógica de la ventana en cada frame
   */
  void
    update();

  /**
   * @brief Renderiza la ventana
   */
  void
    render();

  /**
   * @brief Libera los recursos
   */
  void
    destroy();

  /**
   * @brief Reajusta el tamaño de la pantalla
   */
  HRESULT
    ResizeWindow(HWND hWnd, LPARAM lParam);

  /**
  * @brief Maneja los inputs actions para el movimiento del cubo y la cámara
  */
  void
    inputActionMap(float deltaTime);

  /**
  * @brief  Actualiza la matriz de la cámara
  */
  void
    UpdateCamera();

  /**
  * @brief Rota la cámara dependiendo de la última posición del mouse.
  */
  void
    RotateCamera(int mouseX, int mouseY);

  /**
   * @brief Corre la aplicación
   */
  int
    run(HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      LPWSTR lpCmdLine,
      int nCmdShow,
      WNDPROC wndproc);

public:
  Window                              m_window;
  Device                              m_device;
  DeviceContext                       m_deviceContext;
  SwapChain                           m_swapchain;
  Texture                             m_backBuffer;
  Texture                             m_depthStencil;
  RenderTargetView                    m_renderTargetView;
  DepthStencilView                    m_depthStencilView;
  Viewport                            m_viewport;
  ShaderProgram                       m_shaderProgram;
  Buffer                              m_neverChanges;
  Buffer                              m_changeOnResize;
  Buffer                              m_changesEveryFrame;
  CBNeverChanges cbNeverChanges;
  CBChangeOnResize cbChangesOnResize;
  UserInterface                       m_ui;

  ModelLoader                            m_loader;
  EngineUtilities::TSharedPointer<Actor> AInvincible;
  std::vector<Texture>                   m_texturesInvincible;

  ModelLoader                            m_loader3;
  EngineUtilities::TSharedPointer<Actor> AInvincible2;
  std::vector<Texture>                   m_texturesInvincible2;

  ModelLoader                            m_loader2;
  EngineUtilities::TSharedPointer<Actor> AIkon;
  std::vector<Texture>                   m_texturesIkon;

  XMMATRIX                            m_View;
  XMMATRIX                            m_Projection;
  std::vector<EngineUtilities::TSharedPointer<Actor>> m_actors;
  Camera m_camera;

  bool keys[256] = { false };
  int lastX;
  int lastY;
  float sensitivity = 0.01f;
  bool mouseLeftDown = false;
};