// Copyright 2009 Brian Legge

#include "secondpylon/renderer/renderer_texture.h"
#include <d3d9.h>
#include "secondpylon/plat/plat_crt.h"
#include "./renderer_utils.h"

namespace secondpylon {
namespace renderer {

Texture::Texture(IDirect3DTexture9* texture
                 , const math::vec2<plat::uint32>& size)
                 : m_pTexture(texture)
                 , m_Size(size)
                 , m_pLocked(NULL) {
}

Texture::~Texture() {
    SafeRelease(m_pTexture);
}

plat::uint32* Texture::Lock() {
    SPDIAG_ASSERT(NULL == m_pLocked, "Only unlocked texture may be locked.");
    D3DLOCKED_RECT rect;
    m_pTexture->LockRect(0, &rect, NULL, D3DLOCK_DISCARD);

    // This assumes the texture block is 4 byte aligned.
    SPDIAG_ASSERT((uintptr_t)rect.pBits % sizeof(plat::uint32) == 0
        , "Texture block must be 4 byte aligned (%d)"
        , (uintptr_t)rect.pBits % sizeof(plat::uint32));

    m_pLocked = StrictCast<plat::uint32*>(rect.pBits);
    return m_pLocked;
}

void Texture::Unlock(plat::uint32*& pLockPointer) {
    SPDIAG_ASSERT(NULL != m_pLocked, "Texture must be locked to call Unlock");

    SPDIAG_ASSERT(pLockPointer == m_pLocked
        , "Passing an invalid pointer to pLockPointer");

    m_pTexture->UnlockRect(0);
    m_pLocked = NULL;
    pLockPointer = NULL;
}

}  // namespace renderer
}  // namespace secondpylon
