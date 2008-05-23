#include <secondpylon/renderer/renderer_device.h>
#include <secondpylon/renderer/renderer_mesh.h>
#include <secondpylon/renderer/renderer_material.h>
#include <secondpylon/renderer/renderer_color.h>

#include "d3dx9.h"
#include "d3d9.h"

#define VERIFY(x) SPDIAG_ASSERT((x) == S_OK);

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
            pD3D->Release();
            pD3D = NULL;
        }
    }
}

Mesh* Device::CreateDynamicMesh(plat::uint32 nVertexSize, plat::uint32 nVertexCount, plat::uint32 nIndexCount)
{
    IDirect3DVertexBuffer9* pVertexBuffer = NULL;
	VERIFY(m_pDevice->CreateVertexBuffer(
		nVertexCount * nVertexSize
		, D3DUSAGE_DYNAMIC
		, 0
		, D3DPOOL_DEFAULT
		, &pVertexBuffer
		, NULL));

    // Create the index buffer using 32 bit indices. This simplifies alignment issues on platforms where 16 bit aligns
    // reads are expensive as they require reading back from non-write combined memory. This does use more memory/GPU
    // bandwidth but indices aren't expected to be the primary bottleneck here. Consider making this per platform in
    // the future if needed.
    plat::uint32 nIndexSize = 4;
    IDirect3DIndexBuffer9* pIndexBuffer = NULL;
	VERIFY(m_pDevice->CreateIndexBuffer(
		nIndexCount * nIndexSize
		, D3DUSAGE_DYNAMIC
		, D3DFMT_INDEX32
		, D3DPOOL_DEFAULT
		, &pIndexBuffer
		, NULL));

    if (pVertexBuffer && pIndexBuffer)
    {
        return new Mesh(*pVertexBuffer, *pIndexBuffer);
    }
    else
    {
        if (pIndexBuffer)
        {
            pIndexBuffer->Release();
            pIndexBuffer = NULL;
        }

        if (pVertexBuffer)
        {
            pVertexBuffer->Release();
            pVertexBuffer = NULL;
        }
    
        return NULL;
    }
}

void Device::Draw(Mesh& mesh, Material& mat)
{
	// @todo We need to determine who should own the vertex declaration. This depends on the number of formats we
    //       support at runtime.
	const D3DVERTEXELEMENT9 decl[] = 
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		D3DDECL_END()
	};
    IDirect3DVertexDeclaration9* basicVertexDecl = NULL;
	VERIFY(m_pDevice->CreateVertexDeclaration(&decl[0], &basicVertexDecl));

    // @todo This doesn't do any sorting or redundancy filtering. This needs either needs to be added here (with draws
    // batched externally) or we need to add internal checks (which would be less efficient but simpler from an API
    // standpoint.)
 	VERIFY(m_pDevice->SetVertexShader(mat.GetVertexShader()));
	VERIFY(m_pDevice->SetPixelShader(mat.GetPixelShader()));

    VERIFY(m_pDevice->SetVertexDeclaration(basicVertexDecl));

    VERIFY(m_pDevice->SetStreamSource(0, mesh.GetVertices(), 0, Mesh::kVertexStride));
    VERIFY(m_pDevice->SetIndices(mesh.GetIndices()));

    VERIFY(m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 3, 0, 1));

   	VERIFY(m_pDevice->SetStreamSource(0, NULL, 0, 0));
	VERIFY(m_pDevice->SetVertexShader(NULL));
	VERIFY(m_pDevice->SetPixelShader(NULL));

    basicVertexDecl->Release();
    basicVertexDecl = NULL;
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
