#include <secondpylon/renderer/renderer_texture.h>
#include <secondpylon/plat/plat_crt.h>
#include "renderer_utils.h"
#include <d3d9.h>

namespace secondpylon {
namespace renderer {

Texture::Texture(IDirect3DTexture9& texture, const math::vec2<plat::uint32>& size) : 
    m_pTexture(&texture)
    , m_Size(size)
    , m_pLocked(NULL)
{
}

Texture::~Texture()
{
    SafeRelease(m_pTexture);
}

plat::uint32* Texture::Lock()
{
    SPDIAG_ASSERT(NULL == m_pLocked);
    D3DLOCKED_RECT rect;
    m_pTexture->LockRect(0, &rect, NULL, D3DLOCK_DISCARD);

    // This assumes the texture block is 4 byte aligned.
    SPDIAG_ASSERT((uintptr_t)rect.pBits % sizeof(plat::uint32) == 0);
    m_pLocked = StrictCast<plat::uint32*>(rect.pBits);
    return m_pLocked;
}

void Texture::Unlock(plat::uint32*& pLockPointer)
{
    SPDIAG_ASSERT(NULL != m_pLocked);
    SPDIAG_ASSERT(pLockPointer == m_pLocked);

    m_pTexture->UnlockRect(0);
    m_pLocked = NULL;
    pLockPointer = NULL;
}

}
}
