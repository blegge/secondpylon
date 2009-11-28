// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_RENDERER_RENDERER_DEVICEPARAMETERS_H_
#define SECONDPYLON_RENDERER_RENDERER_DEVICEPARAMETERS_H_

#include <windows.h>
#include "secondpylon/math/math_vec2.h"

namespace secondpylon {
namespace renderer {

  struct DeviceParameters {
    HWND parent_window;
    math::vec2<plat::uint32> dims;
    bool vsync;
    UINT adapter;
  };

}  // namespace renderer
}  // namespace secondpylon

#endif  // SECONDPYLON_RENDERER_RENDERER_DEVICEPARAMETERS_H_
