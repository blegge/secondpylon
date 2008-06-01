#include <secondpylon/renderer/renderer_dynamicmesh.h>
#include "renderer_utils.h"
#include <d3d9.h>


static IDirect3DVertexDeclaration9* CreateVertexDeclaration(IDirect3DDevice9& device)
{
	const D3DVERTEXELEMENT9 decl[] = 
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		D3DDECL_END()
	};

    IDirect3DVertexDeclaration9* pDecl = NULL;
    device.CreateVertexDeclaration(decl, &pDecl);

    return pDecl;
}

namespace secondpylon {
namespace renderer {

    DynamicMesh::DynamicMesh(IDirect3DDevice9& device, plat::uint32 nVertexCount, plat::uint32 nIndexCount) :
        m_nVertexCount(nVertexCount)
        , m_nIndexCount(nIndexCount)
    {
            // @todo How do we want to handle the vertex declaration? Do we want a single version for now or a few preset
            //       variations? This is more of a mesh attribute than a material attribute, though the material depends on it.
        m_pVertexDeclaration = CreateVertexDeclaration(device);

	    VERIFY(device.CreateVertexBuffer(
            nVertexCount * kVertexStride
		    , D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY
		    , 0
		    , D3DPOOL_DEFAULT
		    , &m_VertexBuffer
		    , NULL));

        // Create the index buffer using 32 bit indices. This simplifies alignment issues on platforms where 16 bit
        // aligns reads are expensive as they require reading back from non-write combined memory. This does use more
        // memory/GPU bandwidth but indices aren't expected to be the primary bottleneck here. Consider making this per
        // platform in the future if needed.
        plat::uint32 nIndexSize = 4;
	    VERIFY(device.CreateIndexBuffer(
		    nIndexCount * nIndexSize
		    , D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY
		    , D3DFMT_INDEX32
		    , D3DPOOL_DEFAULT
		    , &m_IndexBuffer
		    , NULL));
    }

    DynamicMesh::~DynamicMesh()
    {
        SafeRelease(m_VertexBuffer);
        SafeRelease(m_IndexBuffer);
        SafeRelease(m_pVertexDeclaration);
    }

    plat::uint32* DynamicMesh::LockIndices(plat::uint32 nIndices)
    {
        void* pData = NULL;
        m_IndexBuffer->Lock(0, sizeof(plat::uint32)*nIndices, &pData, 0);
        return StrictCast<plat::uint32*>(pData);
    }

    void DynamicMesh::UnlockIndices()
    {
        m_IndexBuffer->Unlock();
    }

    plat::uint32* DynamicMesh::LockVertices(plat::uint32 nVertexCount, plat::uint32 nVertexSize)
    {
        void* pData = NULL;
        plat::uint32 nBytesToLock = nVertexCount * nVertexSize;
        m_VertexBuffer->Lock(0, nBytesToLock, &pData, 0);
        return StrictCast<plat::uint32*>(pData);
    }

    void DynamicMesh::UnlockVertices()
    {
        m_VertexBuffer->Unlock();
    }

    IDirect3DVertexDeclaration9* DynamicMesh::GetVertexDecl() const
    {
        return m_pVertexDeclaration;
    }

    plat::uint32 DynamicMesh::GetVertexCount() const
    {
        return m_nVertexCount;
    }

    plat::uint32 DynamicMesh::GetIndexCount() const
    {
        return m_nIndexCount;
    }

}
}
