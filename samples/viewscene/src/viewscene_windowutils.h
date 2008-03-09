#ifndef SPVIEWSCENE_WINDOWUTILS_H
#define SPVIEWSCENE_WINDOWUTILS_H

#include <windows.h>
#include <secondpylon\plat\plat_types.h>
#include <secondpylon\math\math_vec2.h>

struct WindowUtils
{
    struct window
    {
        window() :
	        m_window(0)
        {
        }

	    HWND m_window;
    };

    static void register_classes(HINSTANCE instance);
    static void unregister_classes(HINSTANCE instance);

    static void create_window(
        window& window_result
        , HINSTANCE instance
        , const wchar_t* window_name
        , secondpylon::math::vec2i dims);
    static void destroy_window(window& destroy);
};

#endif // SPVIEWSCENE_WINDOWUTILS_H
