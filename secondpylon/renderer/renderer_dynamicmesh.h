#ifndef SPRENDERER_MESH_H
#define SPRENDERER_MESH_H

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/plat/plat_crt.h>

struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
struct IDirect3DVertexDeclaration9;
struct IDirect3DDevice9;

namespace secondpylon {
namespace renderer {

    class DynamicMesh
    {
    public:
        enum 
        {
            // @todo We need a long term way to handle vertex declarations/strides. We need more use cases first to
            //       understand what interface is practical.
            kVertexStride = sizeof(float)*3
        };

        DynamicMesh(IDirect3DDevice9& device, plat::uint32 nVertexCount, plat::uint32 nIndexCount);
        ~DynamicMesh();

        plat::uint32* LockIndices(plat::uint32 nIndices);
        void UnlockIndices();
        IDirect3DVertexBuffer9* GetVertices() { return m_VertexBuffer; }

        plat::uint32* LockVertices(plat::uint32 nVertexCount, plat::uint32 nVertexSize);
        void UnlockVertices();
        IDirect3DIndexBuffer9* GetIndices() { return m_IndexBuffer; }

        IDirect3DVertexDeclaration9* GetVertexDecl() const;

        plat::uint32 GetVertexCount() const;
        plat::uint32 GetIndexCount() const;

        void Destroy() { delete this; }

    private:
    	SPUNCOPYABLE(DynamicMesh);

        IDirect3DVertexBuffer9* m_VertexBuffer;
        IDirect3DIndexBuffer9* m_IndexBuffer;
        IDirect3DVertexDeclaration9* m_pVertexDeclaration;
        plat::uint32 m_nVertexCount;
        plat::uint32 m_nIndexCount;
    };

}
}

#endif // SPRENDERER_MESH_H
