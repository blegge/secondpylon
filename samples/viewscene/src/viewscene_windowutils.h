// Copyright 2009 Brian Legge

#ifndef SAMPLES_VIEWSCENE_SRC_VIEWSCENE_WINDOWUTILS_H_
#define SAMPLES_VIEWSCENE_SRC_VIEWSCENE_WINDOWUTILS_H_

#include <windows.h>
#include "secondpylon/plat/plat_types.h"
#include "./viewscene_common.h"

namespace secondpylon {
namespace viewscene {

struct WindowUtils {
    struct window {
        window() :
            m_window(0) {
        }

        HWND m_window;
    };

    static void register_classes(HINSTANCE instance);
    static void unregister_classes(HINSTANCE instance);

    static void create_window(
        window* window_result
        , HINSTANCE instance
        , const wchar_t* window_name
        , vec2i dims);

    static void destroy_window(window* target);
};

}  // namespace viewscene
}  // namespace secondpylon

#endif  // SAMPLES_VIEWSCENE_SRC_VIEWSCENE_WINDOWUTILS_H_
