#ifndef SPRENDERER_MATERIAL_H
#define SPRENDERER_MATERIAL_H

#include <secondpylon/data/data_memstorage.h>
#include <secondpylon/data/data_bytepacker.h>
#include <secondpylon/data/data_instream.h>

struct IDirect3DVertexShader9;
struct IDirect3DPixelShader9;
struct IDirect3DDevice9;

namespace secondpylon {
namespace renderer {

    // Materials define how primitives are rendered. This includes texture info, shader info, constants, etc.
    class Material
    {
    public:
        typedef data::InStream<data::MemStorage, data::SBytePacker> TInMemoryStream;

        Material(
            IDirect3DDevice9& device, 
            TInMemoryStream& pixelShaderBuffer
            , TInMemoryStream& vertexShaderBuffer);

        ~Material();

        IDirect3DVertexShader9* GetVertexShader() const;
        IDirect3DPixelShader9* GetPixelShader() const;

        void Destroy();

    private:
    	SPUNCOPYABLE(Material);

        // @todo This needs to be a shared reference to the shader or an identifier of some sort. This is a temp
        //       bootstrap setup.
        IDirect3DVertexShader9* m_pVertexShader;
        IDirect3DPixelShader9* m_pPixelShader;
    };
 
}
}

#endif // SPRENDERER_MATERIAL_H
