#include "BaseApp.h"

HRESULT
BaseApp::init() {
  HRESULT hr = S_OK;

  // Create Swapchain and BackBuffer
  hr = m_swapchain.init(m_device, m_deviceContext, m_backBuffer, m_window);
  if (FAILED(hr)) {
    return hr;
  }

  hr = m_renderTargetView.init(m_device,
    m_backBuffer,
    DXGI_FORMAT_R8G8B8A8_UNORM);
  if (FAILED(hr)) {
    return hr;
  }

  // Create a Depth Stencil texture
  hr = m_depthStencil.init(m_device,
    m_window.m_width,
    m_window.m_height,
    DXGI_FORMAT_D24_UNORM_S8_UINT,
    D3D11_BIND_DEPTH_STENCIL, 4, 0);
  if (FAILED(hr)) {
    return hr;
  }

  hr = m_depthStencilView.init(m_device,
    m_depthStencil,
    DXGI_FORMAT_D24_UNORM_S8_UINT);
  if (FAILED(hr)) {
    return hr;
  }

  m_viewport.init(m_window);

  std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

  D3D11_INPUT_ELEMENT_DESC position;
  position.SemanticName = "POSITION";
  position.SemanticIndex = 0;
  position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
  position.InputSlot = 0;
  position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*0*/;
  position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  position.InstanceDataStepRate = 0;
  Layout.push_back(position);

  D3D11_INPUT_ELEMENT_DESC texcoord;
  texcoord.SemanticName = "TEXCOORD";
  texcoord.SemanticIndex = 0;
  texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
  texcoord.InputSlot = 0;
  texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
  texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  texcoord.InstanceDataStepRate = 0;
  Layout.push_back(texcoord);

  // Create the Shader Program
  hr = m_shaderProgram.init(m_device, "KerberosEngine.fx", Layout);
  if (FAILED(hr)) {
    return hr;
  }

  // Create the constant buffers
  hr = m_neverChanges.init(m_device, sizeof(CBNeverChanges));
  if (FAILED(hr))
    return hr;

  hr = m_changeOnResize.init(m_device, sizeof(CBChangeOnResize));
  if (FAILED(hr))
    return hr;

  // Initialize the view matrix
  XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
  XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  m_View = XMMatrixLookAtLH(Eye, At, Up);

  m_ui.init(m_window.m_hWnd, m_device.m_device, m_deviceContext.m_deviceContext);

  // Load FBX model
  Texture body;
  body.init(m_device, "Texturas/atomeve_df.png", ExtensionType::PNG);

  m_texturesInvincible.push_back(body);

  m_loader.LoadFBXModel("Modelos/Model_AtomEve.fbx");
  AInvincible = EngineUtilities::MakeShared<Actor>(m_device);
  if (!AInvincible.isNull()) {
    // Init Transform
    AInvincible->getComponent<Transform>()->setTransform(EngineUtilities::Vector3(1.0f, -0.5f, -2.0f),
      EngineUtilities::Vector3(XM_PI / -2.0f, 1.4f, XM_PI / 2.0f),
      EngineUtilities::Vector3(2.0f, 2.0f, 2.0f));
    // Init Actor Mesh
    AInvincible->setMesh(m_device, m_loader.meshes);
    // Init Actor Textures
    AInvincible->setTextures(m_texturesInvincible);

    std::string msg = AInvincible->getName() + "Actor accessed successfully.";
    MESSAGE("Actor", "AInvincible", msg.c_str());
  }
  else {
    MESSAGE("Actor", "AInvincible", "Actor resource not found")
  }
  m_actors.push_back(AInvincible);

  // Load FBX model
  Texture cara;
  cara.init(m_device, "Texturas/cara.png", ExtensionType::PNG);
  Texture cuerpo;
  cuerpo.init(m_device, "Texturas/cuerpo.png", ExtensionType::PNG);
  Texture pelo;
  pelo.init(m_device, "Texturas/pelo.png", ExtensionType::PNG);

  m_texturesInvincible2.push_back(pelo);
  m_texturesInvincible2.push_back(cuerpo);
  m_texturesInvincible2.push_back(cara);

  m_loader3.LoadFBXModel("Modelos/invincible blackyblue.fbx");
  AInvincible2 = EngineUtilities::MakeShared<Actor>(m_device);
  if (!AInvincible2.isNull()) {
    // Init Transform
    AInvincible2->getComponent<Transform>()->setTransform(EngineUtilities::Vector3(2.7f, -0.5f, -2.0f),
      EngineUtilities::Vector3(XM_PI / -2.0f, 2.2f, XM_PI / 2.0f),
      EngineUtilities::Vector3(2.0f, 2.0f, 2.0f));
    // Init Actor Mesh
    AInvincible2->setMesh(m_device, m_loader3.meshes);
    // Init Actor Textures
    AInvincible2->setTextures(m_texturesInvincible2);

    std::string msg = AInvincible->getName() + "Actor accessed successfully.";
    MESSAGE("Actor", "AInvincible2", msg.c_str());
  }
  else {
    MESSAGE("Actor", "AInvincible2", "Actor resource not found")
  }
  m_actors.push_back(AInvincible2);

  // Load OBJ model
  m_loader2.LoadOBJ_model("Modelos/Gun.obj");

  m_texturesIkon.clear();

  Texture gun;
  gun.init(m_device, "Texturas/GAP_Examen_Gun_albedo_DriesDeryckere.tga.png", PNG);

  Texture grip;
  grip.init(m_device, "Texturas/Grip_Tex_A.tga.png", PNG);

  Texture scope;
  scope.init(m_device, "Texturas/Scope_Tex_A.tga.png", PNG);

  m_texturesIkon.push_back(scope);
  m_texturesIkon.push_back(gun);
  m_texturesIkon.push_back(grip);

  AIkon = EngineUtilities::MakeShared<Actor>(m_device);
  if (!AIkon.isNull()) {
    // Init Transform
    AIkon->getComponent<Transform>()->setTransform(EngineUtilities::Vector3(-4.0, -1.0f, 1.1f),
      EngineUtilities::Vector3(0.0f, 1.3f, 0.0f),
      EngineUtilities::Vector3(0.1f, 0.1f, 0.1f));
    // Init Actor Mesh
    AIkon->setMesh(m_device, m_loader2.meshes);
    // Init Actor Textures
    AIkon->setTextures(m_texturesIkon);

    MESSAGE("Actor", "AIkon", (AIkon->getName() + " - Actor accessed successfully.").c_str());
  }
  else {
    ERROR("Actor", "AobAIkoni", "Failed to create actor.");
  }
  m_actors.push_back(AIkon);

  return S_OK;
}

void
BaseApp::update() {
  m_ui.update();

  m_ui.AllActorsGUI(m_actors);

  // Update our time
  static float t = 0.0f;
  if (m_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE)
  {
    t += (float)XM_PI * 0.0125f;
  }
  else {
    static DWORD dwTimeStart = 0;
    DWORD dwTimeCur = GetTickCount();
    if (dwTimeStart == 0)
      dwTimeStart = dwTimeCur;
    t = (dwTimeCur - dwTimeStart) / 1000.0f;
  }

  inputActionMap(t);

  // Initialize the projection matrix
  float FOV = XMConvertToRadians(90.0f);
  m_Projection = XMMatrixPerspectiveFovLH(FOV, m_window.m_width / (float)m_window.m_height, 0.01f, 10000.0f);

  UpdateCamera();

  AInvincible->update(0, m_deviceContext);
  AInvincible2->update(0, m_deviceContext);
  AIkon->update(0, m_deviceContext);

  cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
  m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

}

void
BaseApp::render() {
  // Clear the back buffer
  float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha

  // Set Viewport
  m_viewport.render(m_deviceContext);

  // Set Render Target View
  m_renderTargetView.render(m_deviceContext, m_depthStencilView, 1, ClearColor);

  // Set Depth Stencil View
  m_depthStencilView.render(m_deviceContext);

  // Render the cube
  // Set Buffers and Shaders for pipeline
  m_shaderProgram.render(m_deviceContext);
  m_deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  // Set Constant Buffers and asign Shaders
  // g_deviceContext.m_deviceContext->VSSetShader(g_pVertexShader, NULL, 0);
  m_neverChanges.render(m_deviceContext, 0, 1);
  m_changeOnResize.render(m_deviceContext, 1, 1);
  m_changesEveryFrame.render(m_deviceContext, 2, 1);

  m_changesEveryFrame.render(m_deviceContext, 2, 1, true);

  // Render the UI
  m_ui.render();

  // Present our back buffer to our front buffer
  m_swapchain.present();

  AInvincible->render(m_deviceContext);
  AInvincible2->render(m_deviceContext);
  AIkon->render(m_deviceContext);
}

void
BaseApp::destroy() {
  if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();
  AInvincible->destroy();
  AInvincible2->destroy();
  AIkon->destroy();
  m_changeOnResize.destroy();
  m_changesEveryFrame.destroy();
  m_neverChanges.destroy();
  m_shaderProgram.destroy();
  m_depthStencil.destroy();
  m_depthStencilView.destroy();
  m_renderTargetView.destroy();
  m_swapchain.destroy();
  m_deviceContext.destroy();
  m_device.destroy();
  m_ui.destroy();
}

HRESULT
BaseApp::ResizeWindow(HWND hWnd, LPARAM lParam)
{
  // Validar que Swapchain exista
  if (m_swapchain.g_pSwapChain) {
    // Destruir los recursos anteriores del RTV, DS, DSV
    m_renderTargetView.destroy();
    m_depthStencil.destroy();
    m_depthStencilView.destroy();
    m_backBuffer.destroy();

    // Redimensionar los datos del ancho y alto de la ventana
    m_window.m_width = LOWORD(lParam);
    m_window.m_height = HIWORD(lParam);

    // Redimensionar el buffer del swapchain
    HRESULT hr = m_swapchain.g_pSwapChain->ResizeBuffers(0,
      m_window.m_width,
      m_window.m_height,
      DXGI_FORMAT_R8G8B8A8_UNORM,
      0);
    // Validación del HRESULT
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "SwapChain", "Failed to resize buffers");
      return hr;
    }

    // Recrear el backBuffer
    hr = m_swapchain.g_pSwapChain->GetBuffer(0,
      __uuidof(ID3D11Texture2D),
      reinterpret_cast<void**>(&m_backBuffer.m_texture));
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "ResizeWindow", "Failed to recreate back buffer");
      return hr;
    }

    // Recrear el render target view
    hr = m_renderTargetView.init(m_device,
      m_backBuffer,
      DXGI_FORMAT_R8G8B8A8_UNORM);
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "Render Target View", "Failed to create Render Target View");
      return hr;
    }

    // Recrear el depth stencil
    hr = m_depthStencil.init(m_device,
      m_window.m_width,
      m_window.m_height,
      DXGI_FORMAT_D24_UNORM_S8_UINT,
      D3D11_BIND_DEPTH_STENCIL,
      4,
      0);
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "Depth Stencil", "Failed to create Depth Stencil");
      return hr;
    }

    // Recrear el depth stencil view
    hr = m_depthStencilView.init(m_device,
      m_depthStencil,
      DXGI_FORMAT_D24_UNORM_S8_UINT);
    if (FAILED(hr)) {
      ERROR("ResizeWindow", "Depth Stencil View", "Failed to create new Depth Stencil View");
      return hr;
    }

    // Actualizar el viewport
    m_viewport.init(m_window);

    // Actualizar la proyección
    m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, m_window.m_width / (float)m_window.m_height, 0.01f, 100.0f);
    cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
    m_changeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
  }
}

void
BaseApp::inputActionMap(float deltaTime) {
  float speed = 0.001f;
  float moveSpeedCamera = 0.01f;

  XMVECTOR pos = XMLoadFloat3(&m_camera.position);
  XMVECTOR forward = XMLoadFloat3(&m_camera.forward);
  XMVECTOR right = XMLoadFloat3(&m_camera.right);
  XMStoreFloat3(&m_camera.position, pos);
}

void
BaseApp::UpdateCamera() {
  // Convertir la dirección a vectores normalizados
  XMVECTOR pos = XMLoadFloat3(&m_camera.position);
  XMVECTOR dir = XMLoadFloat3(&m_camera.forward);
  XMVECTOR up = XMLoadFloat3(&m_camera.up);

  // Calcular la nueva vista
  m_View = XMMatrixLookAtLH(pos, pos + dir, up);

  // Transponer y actualizar el buffer de la vista
  cbNeverChanges.mView = XMMatrixTranspose(m_View);
  m_neverChanges.update(m_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
}

void
BaseApp::RotateCamera(int mouseX, int mouseY) {
  float offsetX = (mouseX - lastX) * sensitivity;
  float offsetY = (mouseY - lastY) * sensitivity;
  lastX = mouseX;
  lastY = mouseY;

  m_camera.yaw += offsetX;
  m_camera.pitch += offsetY;

  // Limitar la inclinación de la cámara
  if (m_camera.pitch > 1.5f) m_camera.pitch = 1.5f;
  if (m_camera.pitch < -1.5f) m_camera.pitch = -1.5f;

  // Recalcular la dirección hacia adelante
  XMVECTOR forward = XMVectorSet(
    cosf(m_camera.yaw) * cosf(m_camera.pitch),
    sinf(m_camera.pitch),
    sinf(m_camera.yaw) * cosf(m_camera.pitch),
    0.0f
  );

  XMVECTOR right = XMVector3Cross(forward, XMLoadFloat3(&m_camera.up));

  XMStoreFloat3(&m_camera.forward, XMVector3Normalize(forward));
  XMStoreFloat3(&m_camera.right, XMVector3Normalize(right));
}

int
BaseApp::run(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPWSTR lpCmdLine,
  int nCmdShow,
  WNDPROC wndproc) {

  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  if (FAILED(m_window.init(hInstance, nCmdShow, wndproc)))
    return 0;

  if (FAILED(init())) {
    destroy();
    return 0;
  }

  // Main message loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message)
  {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else {
      update();
      render();
    }
  }

  destroy();

  return (int)msg.wParam;
}