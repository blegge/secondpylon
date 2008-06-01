#ifndef SPRENDERER_MESH_H
#define SPRENDERER_MESH_H

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/plat/plat_crt.h>
#include <secondpylon/math/math_vec3.h>

struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
struct IDirect3DVertexDeclaration9;
struct IDirect3DDevice9;

namespace secondpylon {
namespace renderer {

    class DynamicMesh
    {
    public:
        // @todo Long term, the Vertex implementation will probably be externalized (template parameter or dynamic
        //       binding?) so that we can have different mesh formats.
        struct SVertex
        {
            // Vertex implementations provide a 'Write' function to insure writes are ordered. This avoids penalties on
            // platforms where out of order writes to video memory cause penalties.
            void Write(const math::vec3<float>& position)
            {
                m_Position = position;
            }

            math::vec3<float> m_Position;
        };

        DynamicMesh();
        ~DynamicMesh();

        bool Create(IDirect3DDevice9& device, plat::uint32 nVertexCount, plat::uint32 nIndexCount);

        plat::uint32* LockIndices(plat::uint32 nIndices);
        void UnlockIndices();
        IDirect3DVertexBuffer9* GetVertices() { return m_VertexBuffer; }

        plat::uint32* LockVertices(plat::uint32 nVertexCount);
        void UnlockVertices();
        IDirect3DIndexBuffer9* GetIndices() { return m_IndexBuffer; }

        IDirect3DVertexDeclaration9* GetVertexDecl() const;

        plat::uint32 GetVertexStride() const;
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
