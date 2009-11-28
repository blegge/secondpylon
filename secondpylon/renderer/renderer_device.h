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
struct DeviceParameters;

// An entity with mesh and material generates SubMeshRenderRequests which
// describe both objects.
struct SubMeshRenderRequest {
  SubMeshRenderRequest() :
    vertex_shader_(NULL)
    , pixel_shader_(NULL)
    , index_buffer_(NULL)
    , vertex_buffer_(NULL)
    , vertex_declaration_(NULL)
    , vertex_stride_(0)
    , vertex_count_(0)
    , index_count_(0) {
  }

  // Material state
  IDirect3DVertexShader9* vertex_shader_;
  IDirect3DPixelShader9* pixel_shader_;

  // Mesh state
  IDirect3DIndexBuffer9* index_buffer_;
  IDirect3DVertexBuffer9* vertex_buffer_;
  IDirect3DVertexDeclaration9* vertex_declaration_;
  plat::uint32 vertex_stride_;
  plat::uint32 vertex_count_;
  plat::uint32 index_count_;
};

class Device {
public:
  typedef data::InStream<data::MemStorage, data::SBytePacker> TInMemoryStream;

  explicit Device(const DeviceParameters& params);
  ~Device();

  // Returns a DynamicMesh with the requested number of vertices and
  // indices. This function may return NULL if the DynamicMesh cannot be
  // created. The DynamicMesh must be deleted with a call to
  // DynamicMesh::Destroy.
  DynamicMesh* CreateDynamicMesh(
    plat::uint32 vertex_count
    , plat::uint32 index_count);

  Material* CreateMaterial(
    TInMemoryStream* pixelShader
    , TInMemoryStream* vertexShader);

  Texture* CreateTexture(const math::vec2<plat::uint32>& size);

  void Draw(const SubMeshRenderRequest& request);

  void Clear(const Color& clearColor);
  bool BeginScene();
  void EndScene();
  void Flip();

private:
  SPUNCOPYABLE(Device);

  IDirect3D9* d3d_;
  IDirect3DDevice9* device_;

  // Debug value tracking if we are in a BeginScene/EndScene block.
  bool in_scene_;
};

}  // namespace renderer
}  // namespace secondpylon

#endif  // SECONDPYLON_RENDERER_RENDERER_DEVICE_H_
