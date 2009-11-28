// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_RENDERER_RENDERER_DEVICE_H_
#define SECONDPYLON_RENDERER_RENDERER_DEVICE_H_

#include "secondpylon/plat/plat_types.h"
#include "secondpylon/math/math_vec2.h"
#include "secondpylon/data/data_memstorage.h"
#include "secondpylon/data/data_bytepacker.h"
#include "secondpylon/data/data_instream.h"


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
struct SDeviceParameters;

// An entity with mesh and material generates SSubMeshRenderRequests which
// describe both objects.
struct SSubMeshRenderRequest {
    SSubMeshRenderRequest() :
        pVertexShader_(NULL)
        , pPixelShader_(NULL)
        , pIndexBuffer_(NULL)
        , pVertexBuffer_(NULL)
        , pVertexDeclaration_(NULL)
        , nVertexStride_(0)
        , nVertexCount_(0)
        , nIndexCount_(0) {
    }

    // Material state
    IDirect3DVertexShader9* pVertexShader_;
    IDirect3DPixelShader9* pPixelShader_;

    // Mesh state
    IDirect3DIndexBuffer9* pIndexBuffer_;
    IDirect3DVertexBuffer9* pVertexBuffer_;
    IDirect3DVertexDeclaration9* pVertexDeclaration_;
    plat::uint32 nVertexStride_;
    plat::uint32 nVertexCount_;
    plat::uint32 nIndexCount_;
};

class Device {
public:
    typedef data::InStream<data::MemStorage, data::SBytePacker> TInMemoryStream;

    explicit Device(const SDeviceParameters& params);
    ~Device();

    // Returns a DynamicMesh with the requested number of vertices and
    // indices. This function may return NULL if the DynamicMesh cannot be
    // created. The DynamicMesh must be deleted with a call to
    // DynamicMesh::Destroy.
    DynamicMesh* CreateDynamicMesh(
        plat::uint32 nVertexCount
        , plat::uint32 nIndexCount);

    Material* CreateMaterial(
        TInMemoryStream* pixelShader
        , TInMemoryStream* vertexShader);

    Texture* CreateTexture(const math::vec2<plat::uint32>& size);

    void Draw(const SSubMeshRenderRequest& request);

    void Clear(const Color& clearColor);
    bool BeginScene();
    void EndScene();
    void Flip();

private:
    SPUNCOPYABLE(Device);

    IDirect3D9* pD3D_;
    IDirect3DDevice9* pDevice_;

    // Debug value tracking if we are in a BeginScene/EndScene block.
    bool bInScene_;
};

}  // namespace renderer
}  // namespace secondpylon

#endif  // SECONDPYLON_RENDERER_RENDERER_DEVICE_H_
