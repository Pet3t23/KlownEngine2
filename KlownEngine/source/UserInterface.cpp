#include "UserInterface.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "BaseApp.h"
extern BaseApp m_app;

void
UserInterface::init(void* window,
  ID3D11Device* device,
  ID3D11DeviceContext* deviceContext) {
  IMGUI_CHECKVERSION(); // Check ImGUI version
  ImGui::CreateContext(); // Initialize the context
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // Setup GUI Style
  SetCSGOStyle();

  // / When viewports are enabled we tweak WindowRounding/WindoBg so platform windows can look identical to regular ones.
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform and Renderer bindings
  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX11_Init(device, deviceContext);

}

void
UserInterface::update() {
  // Start the Dear ImGui frame
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void
UserInterface::render() {
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  ImGuiIO& io = ImGui::GetIO();

  // Update and Render additional Platform Windows
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault(); // Update default platform for Windows
    //if (ImGui::DragFloat3("Posición", reinterpret_cast<float*>(&g_bApp.position), 0.1f)) {
  }
}

void
UserInterface::destroy() {
  // Cleanup
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

void 
UserInterface::SetCSGOStyle() {
  ImGuiStyle& style = ImGui::GetStyle();
  ImVec4* colors = style.Colors;

  // Colores inspirados en CS:GO
  colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

  colors[ImGuiCol_Border] = ImVec4(0.70f, 0.60f, 0.10f, 0.60f); // Dorado suave
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

  colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.60f, 0.40f, 0.10f, 1.00f); // Amarillo dorado
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.80f, 0.50f, 0.10f, 1.00f);

  colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);

  colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);

  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);

  colors[ImGuiCol_CheckMark] = ImVec4(0.85f, 0.65f, 0.00f, 1.00f); // Amarillo dorado

  colors[ImGuiCol_SliderGrab] = ImVec4(0.85f, 0.65f, 0.00f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.80f, 0.00f, 1.00f);

  colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.85f, 0.65f, 0.00f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.80f, 0.00f, 1.00f);

  colors[ImGuiCol_Header] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.85f, 0.65f, 0.00f, 1.00f);
  colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.80f, 0.00f, 1.00f);

  colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.70f, 0.60f, 0.10f, 1.00f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 0.80f, 0.00f, 1.00f);

  colors[ImGuiCol_ResizeGrip] = ImVec4(0.85f, 0.65f, 0.00f, 1.00f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 0.80f, 0.00f, 1.00f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.90f, 0.30f, 1.00f);

  colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.85f, 0.65f, 0.00f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(1.00f, 0.80f, 0.00f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.10f, 0.15f, 0.20f, 1.00f);

  colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.65f, 0.00f, 1.00f);
  colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.07f, 0.10f, 0.15f, 1.00f);

  // Ajustes generales de estilo
  style.WindowRounding = 4.0f;
  style.FrameRounding = 3.0f;
  style.PopupRounding = 3.0f;
  style.ScrollbarRounding = 3.0f;
  style.GrabRounding = 3.0f;
  style.TabRounding = 3.0f;
  style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
  style.FrameBorderSize = 1.0f;
  style.WindowBorderSize = 1.0f;
}

void 
UserInterface::AllActorsGUI(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
  ImGui::Begin("Actors Selection");
  int id = 0;

  for (size_t i = 0; i < actors.size(); ++i) {
    auto& actor = actors[i];
    if (!actor.isNull()) {
      // Poner el nombre de cada actor en un "Tree Node"
      std::string nodeName = "Actor " + std::to_string(i);

      id = i;
      if (ImGui::CollapsingHeader(nodeName.c_str())) {
        Transform& transform = *(actor->getComponent<Transform>());
        Position(transform, id); // Ya tienes esta función para un Transform individual
      }
    }
  }

  ImGui::End();
}

void 
UserInterface::Position(Transform& transform, int id) {

  ImGui::Begin(("Transform###Transform_" + std::to_string(id)).c_str());

  EngineUtilities::Vector3 position = transform.getPosition();
  EngineUtilities::Vector3 rotation = transform.getRotation();
  EngineUtilities::Vector3 scale = transform.getScale();

  if (ImGui::DragFloat3(("Position###Position_" + std::to_string(id)).c_str(), &position.x, 0.1f)) {
    transform.setPosition(position);
  }
  if (ImGui::DragFloat3(("Rotation###Rotation_" + std::to_string(id)).c_str(), &rotation.x, 0.1f)) {
    transform.setRotation(rotation);
  }
  if (ImGui::DragFloat3(("Scale###Scale_" + std::to_string(id)).c_str(), &scale.x, 0.1f)) {
    transform.setScale(scale);
  }

  ImGui::End();
}