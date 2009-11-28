// Copyright 2009 Brian Legge

#include "./viewscene_applicationutils.h"
#include <windows.h>

void ApplicationUtils::run_app(RenderCallback render_callback) {
  bool quit_posted = false;
  while (!quit_posted) {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) {
        quit_posted = true;
      }

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    (*render_callback)();
    Sleep(1);  // Sleep a bit to relinquish the timeslice.
  }

  // clean up any pending messages posted after WM_QUIT
  {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}
