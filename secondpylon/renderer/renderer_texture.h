#ifndef SPRENDERER_TEXTURE_H
#define SPRENDERER_TEXTURE_H

#include <secondpylon/math/math_vec2.h>
#include <secondpylon/plat/plat_crt.h>

struct IDirect3DTexture9;

namespace secondpylon {
namespace renderer {

    class Texture
    {
    public:
        // Takes ownership of the passed in texture object.
        Texture(IDirect3DTexture9& texture, const math::vec2<plat::uint32>& dims);
        ~Texture();

        // Dynamic texture updating
        plat::uint32* Lock();
        void Unlock(plat::uint32*&);

    private:
        SPUNCOPYABLE(Texture);

        IDirect3DTexture9* m_pTexture;
        math::vec2<plat::uint32> m_Size;
        plat::uint32* m_pLocked;
    };
 
}
}

#endif // SPRENDERER_TEXTURE_H
