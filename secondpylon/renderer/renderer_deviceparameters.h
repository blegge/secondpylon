#ifndef SPRENDERER_DEVICEPARAMETERS_H
#define SPRENDERER_DEVICEPARAMETERS_H

#include <secondpylon/math/math_vec2.h>
#include <windows.h>

namespace secondpylon {
namespace renderer {

    struct SDeviceParameters
    {
        HWND parent_window;
        math::vec2<plat::uint32> dims;
        bool vsync;
        UINT adapter;
    };

}
}

#endif // SPRENDERER_DEVICEPARAMETERS_H
