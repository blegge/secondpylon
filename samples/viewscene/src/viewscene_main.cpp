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
#include <secondpylon/renderer/renderer_dynamicmesh.h>
#include <secondpylon/renderer/renderer_material.h>
#include <viewscene_windowutils.h>
#include <viewscene_applicationutils.h>
#include <secondpylon/data/data_outstream.h>

#include <d3dx9.h>
#include <d3d9.h>

using namespace secondpylon;
using namespace secondpylon::plat;


static renderer::Device* g_device = NULL;

#include <cstdio>
float Random(int min, int max)
{
    return (float)(min + ((float)max-(float)min)* ((float)rand() / (float)RAND_MAX));
}

void renderpoly()
{
    // Create a mesh and fill in a few verts
    renderer::DynamicMesh* pMesh = g_device->CreateDynamicMesh(3, 3);

    {
        plat::uint32* pIndices = pMesh->LockIndices(3);
        pIndices[0] = 0;
        pIndices[1] = 1;
        pIndices[2] = 2;
        pMesh->UnlockIndices();
    }

    {
        math::vec3<float>* pVertex = (math::vec3<float>*)pMesh->LockVertices(3, renderer::DynamicMesh::kVertexStride);
        pVertex[0] = math::vec3<float>(Random(-1, 1),Random(-1, 1),0);
        pVertex[1] = math::vec3<float>(Random(-1, 1),Random(-1, 1),0);
        pVertex[2] = math::vec3<float>(Random(-1, 1),Random(-1, 1),0);
        pMesh->UnlockVertices();
    }

    const char vertexShader[] = 
	    "float4 entry(float4 inPos : POSITION) : POSITION	\
	    {	\
		    return inPos;	\
	    }";

    const char pixelShader[] = "\
        float4 entry() : COLOR \
        { \
            return float4 (1, 0, 0, 1); \
        }";

    typedef data::OutStream<data::MemStorage, data::SBytePacker> TOutMemoryStream;
    typedef data::InStream<data::MemStorage, data::SBytePacker> TInMemoryStream;

    data::MemStorage vertexShaderBuffer;
    {
        TOutMemoryStream vertexShaderStream(vertexShaderBuffer);
        vertexShaderStream.Write(vertexShader);
    }

    data::MemStorage pixelShaderBuffer;
    {
        TOutMemoryStream pixelShaderStream(pixelShaderBuffer);
        pixelShaderStream.Write(pixelShader);
    }

    TInMemoryStream pixelShaderInStream(pixelShaderBuffer);
    TInMemoryStream vertexShaderInStream(vertexShaderBuffer);
    renderer::Material* pMat = g_device->CreateMaterial(pixelShaderInStream, vertexShaderInStream);

    // @todo We need to add references here to avoid the resources getting released before rendering. We also don't
    //       have a way to handle possibly in-place modifications before rendering occurs. This will be simplest to
    //       handle at the source end. Consider updating resources to get released prior to write and recreated.
    renderer::SSubMeshRenderRequest polyRequest;
    polyRequest.m_pPixelShader = pMat->GetPixelShader();
    polyRequest.m_pVertexShader = pMat->GetVertexShader();
    polyRequest.m_pIndexBuffer = pMesh->GetIndices();
    polyRequest.m_pVertexBuffer = pMesh->GetVertices();
    polyRequest.m_pVertexDeclaration = pMesh->GetVertexDecl();
    polyRequest.m_nVertexStride = renderer::DynamicMesh::kVertexStride;
    polyRequest.m_nVertexCount = pMesh->GetVertexCount();
    polyRequest.m_nIndexCount = pMesh->GetIndexCount();

    g_device->Draw(polyRequest);

    pMesh->Destroy();
    pMesh = NULL;

    pMat->Destroy();
    pMat = NULL;
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
