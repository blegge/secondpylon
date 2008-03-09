// This is a simple application demonstrating the use of secondpylon to build a basic little renderering. Note that this
// is meant for a simple, one-off application window. Subwindows within another application and full screen window
// support is more complex.

#include <windows.h>
#include <secondpylon/plat/plat_types.h>
#include <secondpylon/error/error_assert.h>
#include <secondpylon/math/math_vec2.h>
#include <viewscene_windowutils.h>
#include <viewscene_applicationutils.h>

using namespace secondpylon;
using namespace secondpylon::plat;


// --
// http://www.codesampler.com/d3dbook/chapter_04/chapter_04.htm

#include "d3dx9.h"		// Header File For DirectX 3D
#include "d3d9.h"		// Header File For DirectX 3D

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

struct RenderUtils
{
    struct RenderDevice
    {
        RenderDevice() : 
            m_pD3D(NULL)
            , m_pDevice(NULL)
        {
        }

        ~RenderDevice()
        {
            SPERROR_ASSERT(NULL == m_pD3D);
            SPERROR_ASSERT(NULL == m_pDevice);
        }

        IDirect3D9* m_pD3D;
        IDirect3DDevice9* m_pDevice;
    };

    struct DeviceParameters
    {
        HWND parent_window;
        math::vec2i dims;
        bool vsync;
        UINT adapter;
    };

    static void CreateDevice(RenderDevice& device, const DeviceParameters& parameters)
    {
        SPERROR_ASSERT(NULL == device.m_pDevice);

        // Create D3D and the rendering device.
        IDirect3D9* pD3D = Direct3DCreate9( D3D_SDK_VERSION );
        if (pD3D)
        {
            D3DPRESENT_PARAMETERS internal_params;
            internal_params.Windowed = TRUE;
            internal_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
   		    internal_params.EnableAutoDepthStencil	= TRUE;
            internal_params.AutoDepthStencilFormat = D3DFMT_D16;
            internal_params.hDeviceWindow = parameters.parent_window;
            internal_params.BackBufferWidth = parameters.dims.x;
            internal_params.BackBufferHeight = parameters.dims.y;
		    internal_params.BackBufferFormat = D3DFMT_R5G6B5; // Assume 16 bit color. Use D3DFMT_X8R8G8B8 if 32 isn't supported
		    internal_params.MultiSampleType = D3DMULTISAMPLE_NONE;
		    internal_params.MultiSampleQuality = 0;
            internal_params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
            internal_params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
            internal_params.Flags = 0;

            if (parameters.vsync)
            {
                internal_params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
                internal_params.BackBufferCount	 = 2;
            }
            else
            {
                internal_params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
                internal_params.BackBufferCount	 = 1;
            }

            // TODO: Handle graceful fallbacks based on the checks below?
            D3DDEVTYPE device_type = D3DDEVTYPE_HAL;
            HRESULT hr = pD3D->CheckDeviceFormat( 
                parameters.adapter
                , device_type
                , internal_params.BackBufferFormat
                , D3DUSAGE_DEPTHSTENCIL
                , D3DRTYPE_SURFACE
                , internal_params.AutoDepthStencilFormat );
            SPERROR_ASSERT(hr == S_OK);
            SPERROR_UNREFERENCED(hr);
    //        pD3D->CheckDepthStencilMatch(parameters.adapter, D3DDEVTYPE_HAL, , internal_params. );
    //        pD3D->CheckDeviceFormat();
    //        pD3D->CheckDeviceFormatConversion();
    //        pD3D->CheckDeviceMultiSampleType();
    //        pD3D->CheckDeviceType();

            IDirect3DDevice9* pD3DDevice = NULL;
            pD3D->CreateDevice(
                parameters.adapter
                , device_type
                , parameters.parent_window
                , D3DCREATE_HARDWARE_VERTEXPROCESSING
                , &internal_params
                , &pD3DDevice);

            if (pD3DDevice)
            {
                // Assign the output parameters once we've cleared all potential failure points.
                device.m_pD3D = pD3D;
                device.m_pDevice = pD3DDevice;
            }
            else
            {
                pD3D->Release();
                pD3D = NULL;
            }
        }
    }

    static void DestroyDevice(RenderDevice& device)
    {
        device.m_pDevice->Release();
        device.m_pDevice = NULL;

        device.m_pD3D->Release();
        device.m_pD3D = NULL;
    }
};

RenderUtils::RenderDevice* g_device;
void render_clear()
{
    g_device->m_pDevice->Clear(
        0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255,255,255), 1.0f, 0);

    g_device->m_pDevice->BeginScene();
    g_device->m_pDevice->EndScene();

    g_device->m_pDevice->Present(NULL, NULL, NULL, NULL);
}

int main(int /*args*/, char* /*argv*/)
{
    // Normal entrypoint would use WinMain, which wouldn't require this.
    HMODULE instance = GetModuleHandle(NULL);

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
