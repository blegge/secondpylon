#ifndef SPRENDERER_DEVICE_H
#define SPRENDERER_DEVICE_H

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/math/math_vec2.h>
#include <secondpylon/data/data_memstorage.h>
#include <secondpylon/data/data_bytepacker.h>
#include <secondpylon/data/data_instream.h>

#include <windows.h>

struct IDirect3D9;
struct IDirect3DDevice9;
struct IDirect3DVertexShader9;
struct IDirect3DPixelShader9;
struct IDirect3DIndexBuffer9;
struct IDirect3DVertexBuffer9;
struct IDirect3DVertexDeclaration9;

namespace secondpylon {
namespace renderer {

    class DynamicMesh;
    class Material;
    class Color;
    class Texture;

    struct SDeviceParameters
    {
        HWND parent_window;
        math::vec2<plat::uint32> dims;
        bool vsync;
        UINT adapter;
    };

    // An entity with mesh and material generates SSubMeshRenderRequests which describe both objects.
    struct SSubMeshRenderRequest
    {
        SSubMeshRenderRequest() : 
            m_pVertexShader(NULL)
            , m_pPixelShader(NULL)
            , m_pIndexBuffer(NULL)
            , m_pVertexBuffer(NULL)
            , m_pVertexDeclaration(NULL)
            , m_nVertexStride(0)
            , m_nVertexCount(0)
            , m_nIndexCount(0)
        {
        }

        // Material state
        IDirect3DVertexShader9* m_pVertexShader;
        IDirect3DPixelShader9* m_pPixelShader;

        // Mesh state
        IDirect3DIndexBuffer9* m_pIndexBuffer;
        IDirect3DVertexBuffer9* m_pVertexBuffer;
        IDirect3DVertexDeclaration9* m_pVertexDeclaration;
        plat::uint32 m_nVertexStride;
        plat::uint32 m_nVertexCount;
        plat::uint32 m_nIndexCount;
    };

    class Device
    {
    public:
        typedef data::InStream<data::MemStorage, data::SBytePacker> TInMemoryStream;

        Device(const SDeviceParameters& params);
        ~Device();

        DynamicMesh* CreateDynamicMesh(plat::uint32 nVertexCount, plat::uint32 nIndexCount);
        Material* CreateMaterial(TInMemoryStream& pixelShader, TInMemoryStream& vertexShader);
        Texture* CreateTexture(const math::vec2<plat::uint32>& size);

        void Draw(const SSubMeshRenderRequest& request);

        void Clear(const Color& clearColor);
        bool BeginScene();
        void EndScene();
        void Flip();

    private:
        SPUNCOPYABLE(Device);

        IDirect3D9* m_pD3D;
        IDirect3DDevice9* m_pDevice;

        // Debug value tracking if we are in a BeginScene/EndScene block.
        bool m_bInScene;
    };

}
}

#endif // SPRENDERER_DEVICE_H
