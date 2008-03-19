#include <viewscene_renderutils.h>
#include "d3dx9.h"		// Header File For DirectX 3D
#include "d3d9.h"		// Header File For DirectX 3D

RenderUtils::RenderDevice::RenderDevice() : 
    m_pD3D(NULL)
    , m_pDevice(NULL)
{
}

RenderUtils::RenderDevice::~RenderDevice()
{
    SPDIAG_ASSERT(NULL == m_pD3D);
    SPDIAG_ASSERT(NULL == m_pDevice);
}



void RenderUtils::CreateDevice(RenderDevice& device, const DeviceParameters& parameters)
{
    SPDIAG_ASSERT(NULL == device.m_pDevice);

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
        SPDIAG_ASSERT(hr == S_OK);
        SPDIAG_UNREFERENCED(hr);
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

void RenderUtils::DestroyDevice(RenderDevice& device)
{
    device.m_pDevice->Release();
    device.m_pDevice = NULL;

    device.m_pD3D->Release();
    device.m_pD3D = NULL;
}
