//--------------------------------------------------------------------------------------
// File: KlownEngine.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "BaseApp.h"
#include "UserInterface.h"

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
BaseApp m_app;

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK
WndProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;

  if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    return true;

  switch (message) {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

  case WM_SIZE:
    m_app.ResizeWindow(hWnd, lParam);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  case WM_KEYDOWN:
    m_app.keys[wParam] = true;
    break;

  case WM_KEYUP:
    m_app.keys[wParam] = false;
    break;

  case WM_RBUTTONDOWN:
    m_app.mouseLeftDown = true;
    break;

  case WM_RBUTTONUP:
    m_app.mouseLeftDown = false;
    break;

  case WM_MOUSEMOVE:
    if (m_app.mouseLeftDown) {
      int x = LOWORD(lParam);
      int y = HIWORD(lParam);
      m_app.RotateCamera(x, y);
    }
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
  return m_app.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
}