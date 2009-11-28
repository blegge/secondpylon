// Copyright 2009 Brian Legge

#include "secondpylon/renderer/renderer_dynamicmesh.h"
#include <d3d9.h>
#include "secondpylon/diag/diag_assert.h"
#include "./renderer_utils.h"

namespace secondpylon {
namespace renderer {

DynamicMesh::DynamicMesh()
    : VertexBuffer_(NULL)
    , IndexBuffer_(NULL)
    , pVertexDeclaration_(NULL)
    , nVertexCount_(0)
    , nIndexCount_(0) {
}

DynamicMesh::~DynamicMesh() {
    SafeRelease(VertexBuffer_);
    SafeRelease(IndexBuffer_);
    SafeRelease(pVertexDeclaration_);
}

// Create is separate from the constructor as it can fail. The alternative is
// to either have an 'IsValid' function which complicates the API and would
// tempt people to call it when not needed or to make the operations that can
// fail external - which would distribute the responsibility of this module.
bool DynamicMesh::Create(IDirect3DDevice9* device
                         , plat::uint32 nVertexCount
                         , plat::uint32 nIndexCount) {
    SPDIAG_ASSERT(
        VertexBuffer_ == NULL
        && IndexBuffer_ == NULL
        && pVertexDeclaration_ == NULL
        , "DynamicMesh components already initialized.");

    nVertexCount_ = nVertexCount;
    nIndexCount_ = nIndexCount;

    // @todo How do we want to handle the vertex declaration? Do we want a
    // single version for now or a few preset variations? This is more of a
    // mesh attribute than a material attribute, though the material depends on
    // it.
    const D3DVERTEXELEMENT9 decl[] = {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        D3DDECL_END()
    };
    device->CreateVertexDeclaration(decl, &pVertexDeclaration_);

    SP_DXVERIFY(device->CreateVertexBuffer(
        nVertexCount * GetVertexStride()
        , D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY
        , 0
        , D3DPOOL_DEFAULT
        , &VertexBuffer_
        , NULL));

    // Create the index buffer using 32 bit indices. This simplifies alignment
    // issues on platforms where 16 bit aligns reads are expensive as they
    // require reading back from non-write combined memory. This does use more
    // memory/GPU bandwidth but indices aren't expected to be the primary
    // bottleneck here. Consider making this per platform in the future if
    // needed.
    plat::uint32 nIndexSize = 4;
    SP_DXVERIFY(device->CreateIndexBuffer(
        nIndexCount * nIndexSize
        , D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY
        , D3DFMT_INDEX32
        , D3DPOOL_DEFAULT
        , &IndexBuffer_
        , NULL));

    return (VertexBuffer_ && IndexBuffer_ && pVertexDeclaration_);
}

plat::uint32* DynamicMesh::LockIndices(plat::uint32 nIndices) {
    void* pData = NULL;
    IndexBuffer_->Lock(0, sizeof(plat::uint32)*nIndices, &pData, 0);
    return StrictCast<plat::uint32*>(pData);
}

void DynamicMesh::UnlockIndices() {
    IndexBuffer_->Unlock();
}

plat::uint32* DynamicMesh::LockVertices(plat::uint32 nVertexCount) {
    void* pData = NULL;
    plat::uint32 nBytesToLock = nVertexCount * GetVertexStride();
    VertexBuffer_->Lock(0, nBytesToLock, &pData, 0);
    return StrictCast<plat::uint32*>(pData);
}

void DynamicMesh::UnlockVertices() {
    VertexBuffer_->Unlock();
}

IDirect3DVertexDeclaration9* DynamicMesh::GetVertexDecl() const {
    return pVertexDeclaration_;
}

plat::uint32 DynamicMesh::GetVertexCount() const {
    return nVertexCount_;
}

plat::uint32 DynamicMesh::GetIndexCount() const {
    return nIndexCount_;
}

plat::uint32 DynamicMesh::GetVertexStride() const {
    return sizeof(SVertex);
}

}  // namespace renderer
}  // namespace secondpylon
