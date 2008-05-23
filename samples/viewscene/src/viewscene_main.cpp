// This is a simple application demonstrating the use of secondpylon to build a basic little renderering. Note that this
// is meant for a simple, one-off application window. Subwindows within another application and full screen window
// support is more complex.

#include <windows.h>
#include <secondpylon/plat/plat_types.h>
#include <secondpylon/diag/diag_assert.h>
#include <secondpylon/math/math_vec2.h>
#include <secondpylon/math/math_vec3.h>
#include <secondpylon/renderer/renderer_color.h>
#include <secondpylon/renderer/renderer_device.h>
#include <secondpylon/renderer/renderer_mesh.h>
#include <secondpylon/renderer/renderer_material.h>
#include <viewscene_windowutils.h>
#include <viewscene_applicationutils.h>
#include <viewscene_renderutils.h>

using namespace secondpylon;
using namespace secondpylon::plat;


// --
// http://www.codesampler.com/d3dbook/chapter_04/chapter_04.htm

#include "d3dx9.h"		// Header File For DirectX 3D
#include "d3d9.h"		// Header File For DirectX 3D

static renderer::Device* g_device = NULL;

// http://docendo.bai.nu/img/kapitel/0735616531.htm
IDirect3DVertexShader9* LoadVertexShader(IDirect3DDevice9* device, const char* shader)
{
	ID3DXBuffer* pShaderBuffer = NULL;
	ID3DXBuffer* pErrorBuffer = NULL;

	HRESULT hr = D3DXCompileShader(
		shader
		, (UINT)strlen(shader)
		, NULL	// no defines
		, NULL	// no includes
		, "entry"
		, "vs_1_1"
		, D3DXSHADER_DEBUG 
		, &pShaderBuffer
		, &pErrorBuffer
		, NULL	// no constant table
	);

	IDirect3DVertexShader9* pShader = NULL;
	if (hr != S_OK)
	{
//		RSCONTENT_ERROR(
//			const char* szError = (const char*)pErrorBuffer->GetBufferPointer();
//			RSPlatform::Services()->Error("Shader Error: Failed to load '%s': %s", "<default>", szError);
//		);
	}

	if (S_OK == hr)
	{
		hr = device->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &pShader);
	}

	if (pErrorBuffer)
		pErrorBuffer->Release();
	if (pShaderBuffer)
		pShaderBuffer->Release();

	return pShader;
}


void renderpoly()
{
    // Create a mesh and fill in a few verts
    renderer::Mesh* pMesh = g_device->CreateDynamicMesh(renderer::Mesh::kVertexStride, 3, 3);

    {
        plat::uint32* pIndices = pMesh->LockIndices(3);
        pIndices[0] = 0;
        pIndices[1] = 1;
        pIndices[2] = 2;
        pMesh->UnlockIndices();
    }

    {
        math::vec3<float>* pVertex = (math::vec3<float>*)pMesh->LockVertices(3, renderer::Mesh::kVertexStride);
        pVertex[0] = math::vec3<float>(0,0,0);
        pVertex[1] = math::vec3<float>(0,1,0);
        pVertex[2] = math::vec3<float>(0,1,1);
        pMesh->UnlockVertices();
    }

    renderer::Material mat;
    g_device->Draw(*pMesh, mat);

    pMesh->Release();
    pMesh = NULL;


		// Load the shaders
	//const char vShader[] = 
	//	"float4 entry(float4 inPos : POSITION) : POSITION	\
	//	{	\
	//		return inPos;	\
	//	}";
	//IDirect3DVertexShader9* basicVertexShader = LoadVertexShader(g_device->m_pDevice, vShader);
}

void render()
{
    renderer::Color clearColor;
    clearColor.Encode(0, 255, 255, 255);
    g_device->Clear(clearColor);

    if (g_device->BeginScene())
    {
        renderpoly();
        g_device->EndScene();
        g_device->Flip();
    }
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
    WindowUtils::create_window(app_window, instance, L"viewscene", vec2i(128, 128));

    RenderUtils::RenderDevice device;

    renderer::SDeviceParameters params;
    params.adapter = 0;
    params.dims = vec2i(128, 128);
    params.parent_window = app_window.m_window;
    params.vsync = false;

    {
        renderer::Device device(params);
        g_device = &device;
	    ApplicationUtils::run_app();
        g_device = NULL;
    }
    
    WindowUtils::destroy_window(app_window);
    WindowUtils::unregister_classes(instance);

    return 0;
}
