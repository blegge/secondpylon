// Copyright 2009 Brian Legge

#include "secondpylon/renderer/renderer_dynamicmesh.h"
#include <d3d9.h>
#include "secondpylon/diag/diag_assert.h"
#include "./renderer_utils.h"

namespace secondpylon {
namespace renderer {

DynamicMesh::DynamicMesh()
    : vertex_buffer_(NULL)
    , index_buffer_(NULL)
    , vertex_declaration_(NULL)
    , vertex_count_(0)
    , index_count_(0) {
}

DynamicMesh::~DynamicMesh() {
    SafeRelease(vertex_buffer_);
    SafeRelease(index_buffer_);
    SafeRelease(vertex_declaration_);
}

// Create is separate from the constructor as it can fail. The alternative is
// to either have an 'IsValid' function which complicates the API and would
// tempt people to call it when not needed or to make the operations that can
// fail external - which would distribute the responsibility of this module.
bool DynamicMesh::Create(IDirect3DDevice9* device
                         , plat::uint32 vertex_count
                         , plat::uint32 index_count) {
    SPDIAG_ASSERT(
        vertex_buffer_ == NULL
        && index_buffer_ == NULL
        && vertex_declaration_ == NULL
        , "DynamicMesh components already initialized.");

    vertex_count_ = vertex_count;
    index_count_ = index_count;

    // @todo How do we want to handle the vertex declaration? Do we want a
    // single version for now or a few preset variations? This is more of a
    // mesh attribute than a material attribute, though the material depends on
    // it.
    const D3DVERTEXELEMENT9 decl[] = {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        D3DDECL_END()
    };
    device->CreateVertexDeclaration(decl, &vertex_declaration_);

    SP_DXVERIFY(device->CreateVertexBuffer(
        vertex_count * GetVertexStride()
        , D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY
        , 0
        , D3DPOOL_DEFAULT
        , &vertex_buffer_
        , NULL));

    // Create the index buffer using 32 bit indices. This simplifies alignment
    // issues on platforms where 16 bit aligns reads are expensive as they
    // require reading back from non-write combined memory. This does use more
    // memory/GPU bandwidth but indices aren't expected to be the primary
    // bottleneck here. Consider making this per platform in the future if
    // needed.
    plat::uint32 nIndexSize = 4;
    SP_DXVERIFY(device->CreateIndexBuffer(
        index_count * nIndexSize
        , D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY
        , D3DFMT_INDEX32
        , D3DPOOL_DEFAULT
        , &index_buffer_
        , NULL));

    return (vertex_buffer_ && index_buffer_ && vertex_declaration_);
}

plat::uint32* DynamicMesh::LockIndices(plat::uint32 nIndices) {
    void* data = NULL;
    index_buffer_->Lock(0, sizeof(plat::uint32)*nIndices, &data, 0);
    return StrictCast<plat::uint32*>(data);
}

void DynamicMesh::UnlockIndices() {
    index_buffer_->Unlock();
}

plat::uint32* DynamicMesh::LockVertices(plat::uint32 vertex_count) {
    void* data = NULL;
    plat::uint32 bytes_to_lock = vertex_count * GetVertexStride();
    vertex_buffer_->Lock(0, bytes_to_lock, &data, 0);
    return StrictCast<plat::uint32*>(data);
}

void DynamicMesh::UnlockVertices() {
    vertex_buffer_->Unlock();
}

IDirect3DVertexDeclaration9* DynamicMesh::GetVertexDecl() const {
    return vertex_declaration_;
}

plat::uint32 DynamicMesh::GetVertexCount() const {
    return vertex_count_;
}

plat::uint32 DynamicMesh::GetIndexCount() const {
    return index_count_;
}

plat::uint32 DynamicMesh::GetVertexStride() const {
    return sizeof(SVertex);
}

}  // namespace renderer
}  // namespace secondpylon
