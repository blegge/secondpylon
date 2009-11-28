// Copyright 2009 Brian Legge

#include "./viewscene_windowutils.h"
#include "secondpylon/diag/diag_assert.h"

namespace secondpylon {
namespace viewscene {

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_CLOSE:
      PostQuitMessage(0);
      return 0;
  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

static wchar_t* g_window_class_name = L"secondpylon_example_viewscene_window";

void WindowUtils::register_classes(HINSTANCE instance) {
  WNDCLASSW wc = {
    0, WndProc, 0, 0, instance, LoadIcon(0, IDI_APPLICATION),
    LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH), 0,
    g_window_class_name };

  ATOM result = RegisterClassW(&wc);
  SPDIAG_ASSERT(result != 0, "Failed to register clss");
  SPDIAG_UNREFERENCED(result);
}

void WindowUtils::unregister_classes(HINSTANCE instance) {
  BOOL result = UnregisterClassW(g_window_class_name, instance);
  SPDIAG_ASSERT(result != 0, "Failed to unregister class.");
  SPDIAG_UNREFERENCED(result);
}

void WindowUtils::create_window(WindowUtils::window* window_result
                , HINSTANCE instance
                , const wchar_t* window_name
                , vec2i dims) {
  SPDIAG_ASSERT(window_result->window_ == 0
    , "Output parameter already has a window specified.");

  DWORD window_style =
    (WS_POPUP
    | WS_CLIPSIBLINGS
    | WS_CLIPCHILDREN
    | WS_CAPTION
    | WS_SYSMENU
    | WS_MINIMIZEBOX);

  HWND new_window = CreateWindowExW(
    0,             // Extended Window Style
    g_window_class_name,  // Registered Class Name
    window_name,    // Window Name
    window_style,    // Window Style
    0,             // Horiz. Position of Window
    0,              // Vert. Position of Window
    dims.x,          // Window Width
    dims.y,          // Window Height
    NULL,          // Parent Window
    NULL,          // Menu
    instance,        // App Instance
    NULL);         // Window Creation Data
  SPDIAG_ASSERT(new_window != 0, "Failed to create a window");

  ShowWindow(new_window, SW_SHOWNORMAL);

  // Store the results now that everything completed successfully.
  window_result->window_ = new_window;
}

void WindowUtils::destroy_window(WindowUtils::window* target) {
  DestroyWindow(target->window_);
  target->window_ = 0;
}

}  // namespace viewscene
}  // namespace secondpylon
