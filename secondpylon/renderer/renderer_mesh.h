#ifndef SPRENDERER_MESH_H
#define SPRENDERER_MESH_H

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/plat/plat_crt.h>

struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;

namespace secondpylon {
namespace renderer {

    class Mesh
    {
    public:

        enum 
        {
            // @todo We need a long term way to handle vertex declarations/strides. We need more use cases first to
            //       understand what interface is practical.
            kVertexStride = sizeof(float)*3
        };

        Mesh(IDirect3DVertexBuffer9& vertexBuffer, IDirect3DIndexBuffer9& indexBuffer) :
          m_VertexBuffer(&vertexBuffer)
          , m_IndexBuffer(&indexBuffer)
        {
        }

        ~Mesh();

        plat::uint32* LockIndices(plat::uint32 nIndices);
        void UnlockIndices();
        IDirect3DVertexBuffer9* GetVertices() { return m_VertexBuffer; }

        plat::uint32* LockVertices(plat::uint32 nVertexCount, plat::uint32 nVertexSize);
        void UnlockVertices();
        IDirect3DIndexBuffer9* GetIndices() { return m_IndexBuffer; }

        void Release() { delete this; }

    private:
    	SPUNCOPYABLE(Mesh);

        IDirect3DVertexBuffer9* m_VertexBuffer;
        IDirect3DIndexBuffer9* m_IndexBuffer;
    };

}
}

#endif // SPRENDERER_MESH_H
