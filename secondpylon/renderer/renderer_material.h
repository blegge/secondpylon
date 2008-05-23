#ifndef SPRENDERER_MATERIAL_H
#define SPRENDERER_MATERIAL_H

struct IDirect3DVertexShader9;
struct IDirect3DPixelShader9;

namespace secondpylon {
namespace renderer {

    // Materials define how primitives are rendered. This includes texture info, shader info, constants, etc.
    class Material
    {
        // Effect
            // Vertex shader
            // Pixel shader
        // Constants
    public:
        IDirect3DVertexShader9* GetVertexShader() const { return NULL; }
        IDirect3DPixelShader9* GetPixelShader() const { return NULL; }
    };
 
}
}

#endif // SPRENDERER_MATERIAL_H
