#include <secondpylon/renderer/renderer_mesh.h>
#include "d3d9.h"

namespace secondpylon {
namespace renderer {

    Mesh::~Mesh()
    {
        m_VertexBuffer->Release();
        m_VertexBuffer = NULL;

        m_IndexBuffer->Release();
        m_IndexBuffer = NULL;
    }

    plat::uint32* Mesh::LockIndices(plat::uint32 nIndices)
    {
        void* pData = NULL;
        m_IndexBuffer->Lock(0, sizeof(plat::uint32)*nIndices, &pData, 0);
        return StrictCast<plat::uint32*>(pData);
    }

    void Mesh::UnlockIndices()
    {
        m_IndexBuffer->Unlock();
    }

    plat::uint32* Mesh::LockVertices(plat::uint32 nVertexCount, plat::uint32 nVertexSize)
    {
        void* pData = NULL;
        plat::uint32 nBytesToLock = nVertexCount * nVertexSize;
        m_VertexBuffer->Lock(0, nBytesToLock, &pData, 0);
        return StrictCast<plat::uint32*>(pData);
    }

    void Mesh::UnlockVertices()
    {
        m_VertexBuffer->Unlock();
    }

}
}
