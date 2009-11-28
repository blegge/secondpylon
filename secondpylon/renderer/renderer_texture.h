// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_RENDERER_RENDERER_TEXTURE_H_
#define SECONDPYLON_RENDERER_RENDERER_TEXTURE_H_

#include "secondpylon/math/math_vec2.h"
#include "secondpylon/plat/plat_crt.h"

struct IDirect3DTexture9;

namespace secondpylon {
namespace renderer {

class Texture {
public:
    // Takes ownership of the passed in texture object.
    Texture(IDirect3DTexture9* texture, const math::vec2<plat::uint32>& dims);
    ~Texture();

    // Dynamic texture updating
    plat::uint32* Lock();

    // Pointer to the previously data retreived from this Texture with a call 
    // to Lock. Once Unlocked, this pointer is invalid.
    void Unlock(plat::uint32* lock_pointer);

private:
    SPUNCOPYABLE(Texture);

    IDirect3DTexture9* texture_;
    math::vec2<plat::uint32> size_;
    plat::uint32* locked_;
};

}  // namespace renderer
}  // namespace secondpylon

#endif  // SECONDPYLON_RENDERER_RENDERER_TEXTURE_H_
