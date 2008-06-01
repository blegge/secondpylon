#include <secondpylon/renderer/renderer_device.h>
#include <secondpylon/renderer/renderer_dynamicmesh.h>
#include <secondpylon/renderer/renderer_material.h>
#include <secondpylon/renderer/renderer_color.h>
#include <secondpylon/renderer/renderer_texture.h>
#include "renderer_utils.h"

#include <d3dx9.h>
#include <d3d9.h>

namespace secondpylon {
namespace renderer {

Device::Device(const SDeviceParameters& deviceParams) : 
    m_pD3D(NULL)
    , m_pDevice(NULL)
    , m_bInScene(false)
{
    // Create D3D and the rendering device.
    IDirect3D9* pD3D = Direct3DCreate9( D3D_SDK_VERSION );
    if (pD3D)
    {
        D3DPRESENT_PARAMETERS internal_params;
        internal_params.Windowed = TRUE;
        internal_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
   		internal_params.EnableAutoDepthStencil	= TRUE;
        internal_params.AutoDepthStencilFormat = D3DFMT_D16;
        internal_params.hDeviceWindow = deviceParams.parent_window;
        internal_params.BackBufferWidth = deviceParams.dims.x;
        internal_params.BackBufferHeight = deviceParams.dims.y;
		
        // Assume 16 bit color. Use D3DFMT_X8R8G8B8 if 32 isn't supported
        internal_params.BackBufferFormat = D3DFMT_R5G6B5; 
        
		internal_params.MultiSampleType = D3DMULTISAMPLE_NONE;
		internal_params.MultiSampleQuality = 0;
        internal_params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
        internal_params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
        internal_params.Flags = 0;

        if (deviceParams.vsync)
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
        VERIFY(pD3D->CheckDeviceFormat( 
            deviceParams.adapter
            , device_type
            , internal_params.BackBufferFormat
            , D3DUSAGE_DEPTHSTENCIL
            , D3DRTYPE_SURFACE
            , internal_params.AutoDepthStencilFormat ));

//        pD3D->CheckDepthStencilMatch(parameters.adapter, D3DDEVTYPE_HAL, , internal_params. );
//        pD3D->CheckDeviceFormat();
//        pD3D->CheckDeviceFormatConversion();
//        pD3D->CheckDeviceMultiSampleType();
//        pD3D->CheckDeviceType();

        IDirect3DDevice9* pD3DDevice = NULL;
        VERIFY(pD3D->CreateDevice(
            deviceParams.adapter
            , device_type
            , deviceParams.parent_window
            , D3DCREATE_HARDWARE_VERTEXPROCESSING
            , &internal_params
            , &pD3DDevice));

        if (pD3DDevice)
        {
            // Assign the output parameters once we've cleared all potential failure points.
            m_pD3D = pD3D;
            m_pDevice = pD3DDevice;
        }
        else
        {
            SafeRelease(pD3D);
        }
    }
}

Device::~Device()
{
    SPDIAG_ASSERT(!m_bInScene);
    SafeRelease(m_pD3D);
    SafeRelease(m_pDevice);
}

DynamicMesh* Device::CreateDynamicMesh(plat::uint32 nVertexCount, plat::uint32 nIndexCount)
{
    // @todo We need to handle the possibility tht the mesh isn't valid (the vb/ib allocations failed. We could check
    //       the mesh to verify that it is valid before returning it. That would mean adding a slightly ugly 'is valid'
    //       type function, but without exceptions (which we couldn't throw from the constructor anyway) this wouldn't
    //       work.
    DynamicMesh* pMesh = new DynamicMesh(*m_pDevice, nVertexCount, nIndexCount);
    if (!pMesh->IsValid())
    {
        delete pMesh;
        pMesh = NULL;
    }
    return pMesh;
}

Material* Device::CreateMaterial(TInMemoryStream& pixelShaderBuffer, TInMemoryStream& vertexShaderBuffer)
{
    return new Material(*m_pDevice, pixelShaderBuffer, vertexShaderBuffer);
}

Texture* Device::CreateTexture(const math::vec2<plat::uint32>& size)
{
    IDirect3DTexture9* pTexture = NULL;
    m_pDevice->CreateTexture(size.x, size.y, 0, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, 
        D3DPOOL_SYSTEMMEM, &pTexture, NULL);
    return new Texture(*pTexture, size);
}

void Device::Draw(const renderer::SSubMeshRenderRequest& request)
{
    // @todo This doesn't do any sorting or redundancy filtering. This needs either needs to be added here (with draws
    // batched externally) or we need to add internal checks (which would be less efficient but simpler from an API
    // standpoint.)
 	VERIFY(m_pDevice->SetVertexShader(request.m_pVertexShader));
	VERIFY(m_pDevice->SetPixelShader(request.m_pPixelShader));

    VERIFY(m_pDevice->SetVertexDeclaration(request.m_pVertexDeclaration));
    VERIFY(m_pDevice->SetStreamSource(0, request.m_pVertexBuffer, 0, DynamicMesh::kVertexStride));
    VERIFY(m_pDevice->SetIndices(request.m_pIndexBuffer));

    VERIFY(m_pDevice->DrawIndexedPrimitive(
        D3DPT_TRIANGLELIST, 0, 0, request.m_nVertexCount, 0, request.m_nIndexCount));

   	VERIFY(m_pDevice->SetStreamSource(0, NULL, 0, 0));
	VERIFY(m_pDevice->SetVertexShader(NULL));
	VERIFY(m_pDevice->SetPixelShader(NULL));
}

void Device::Clear(const renderer::Color& clearColor)
{
    VERIFY(m_pDevice->Clear(0, NULL, 
        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clearColor.GetEncodedColor(), 1.0f, 0));
}

void Device::Flip()
{
    VERIFY(m_pDevice->Present(NULL, NULL, NULL, NULL));
}

bool Device::BeginScene()
{
    SPDIAG_ASSERT(!m_bInScene);
    m_bInScene = (S_OK == m_pDevice->BeginScene());
    return m_bInScene;
}

void Device::EndScene()
{
    SPDIAG_ASSERT(m_bInScene);
    VERIFY(m_pDevice->EndScene());
    m_bInScene = false;
}

}
}
