// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_RENDERER_RENDERER_MATERIAL_H_
#define SECONDPYLON_RENDERER_RENDERER_MATERIAL_H_

#include "secondpylon/data/data_memstorage.h"
#include "secondpylon/data/data_bytepacker.h"
#include "secondpylon/data/data_instream.h"

struct IDirect3DVertexShader9;
struct IDirect3DPixelShader9;
struct IDirect3DDevice9;

namespace secondpylon {
namespace renderer {

// Materials define how primitives are rendered. This includes texture info,
// shader info, constants, etc.
class Material {
public:
    typedef data::InStream<data::MemStorage, data::SBytePacker> TInMemoryStream;

    Material(
        IDirect3DDevice9* device,
        TInMemoryStream* pixelShaderBuffer
        , TInMemoryStream* vertexShaderBuffer);

    ~Material();

    IDirect3DVertexShader9* GetVertexShader() const;
    IDirect3DPixelShader9* GetPixelShader() const;

    void Destroy();

private:
    SPUNCOPYABLE(Material);

    // @todo This needs to be a shared reference to the shader or an identifier
    // of some sort. This is a temp bootstrap setup.
    IDirect3DVertexShader9* pVertexShader_;
    IDirect3DPixelShader9* pPixelShader_;
};

}  // namespace renderer
}  // namespace secondpylon

#endif  // SECONDPYLON_RENDERER_RENDERER_MATERIAL_H_
