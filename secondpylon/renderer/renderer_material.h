#ifndef SPRENDERER_MATERIAL_H
#define SPRENDERER_MATERIAL_H

struct IDirect3DVertexShader9;
struct IDirect3DPixelShader9;
struct IDirect3DDevice9;
struct IDirect3DVertexDeclaration9;

namespace secondpylon {
namespace renderer {

    // Materials define how primitives are rendered. This includes texture info, shader info, constants, etc.
    class Material
    {
    public:
        Material(IDirect3DDevice9& device);
        ~Material();

        IDirect3DVertexDeclaration9* GetVertexDecl() const;
        IDirect3DVertexShader9* GetVertexShader() const;
        IDirect3DPixelShader9* GetPixelShader() const;

        void Destroy();

    private:
        // @todo This needs to be a shared reference to the shader or an identifier of some sort. This is a temp
        //       bootstrap setup.
        IDirect3DVertexShader9* m_pVertexShader;
        IDirect3DVertexDeclaration9* m_pVertexDeclaration;
    };
 
}
}

#endif // SPRENDERER_MATERIAL_H
