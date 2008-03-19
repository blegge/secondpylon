// This is a simple application demonstrating the use of secondpylon to build a basic little renderering. Note that this
// is meant for a simple, one-off application window. Subwindows within another application and full screen window
// support is more complex.

#include <windows.h>
#include <secondpylon/plat/plat_types.h>
#include <secondpylon/diag/diag_assert.h>
#include <secondpylon/math/math_vec2.h>
#include <secondpylon/renderer/renderer_color.h>
#include <viewscene_windowutils.h>
#include <viewscene_applicationutils.h>
#include <viewscene_renderutils.h>

using namespace secondpylon;
using namespace secondpylon::plat;


// --
// http://www.codesampler.com/d3dbook/chapter_04/chapter_04.htm

#include "d3dx9.h"		// Header File For DirectX 3D
#include "d3d9.h"		// Header File For DirectX 3D

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

static RenderUtils::RenderDevice* g_device = NULL;

void render_clear()
{
    renderer::Color clearColor;
    clearColor.Encode(0, 255, 255, 255);
    g_device->m_pDevice->Clear(
        0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clearColor.GetEncodedColor(), 1.0f, 0);

    g_device->m_pDevice->BeginScene();
    g_device->m_pDevice->EndScene();

    g_device->m_pDevice->Present(NULL, NULL, NULL, NULL);
}

int WINAPI WinMain( HINSTANCE instance,
                    HINSTANCE /*hPrevInstance*/,
                    LPSTR     /*lpCmdLine*/,
                    int       /*nCmdShow*/)
{
    // Show the scene

    // Create Window and run the application
    WindowUtils::register_classes(instance);
    WindowUtils::window app_window;
    WindowUtils::create_window(app_window, instance, L"viewscene", math::vec2i(128, 128));

    RenderUtils::RenderDevice device;
    g_device = &device;

    RenderUtils::DeviceParameters params;
    params.adapter = 0;
    params.dims = math::vec2i(128, 128);
    params.parent_window = app_window.m_window;
    params.vsync = false;

    RenderUtils::CreateDevice(device, params);
	ApplicationUtils::run_app();
    RenderUtils::DestroyDevice(device);
    
    WindowUtils::destroy_window(app_window);
    WindowUtils::unregister_classes(instance);

    return 0;
}
