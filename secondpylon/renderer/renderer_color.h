// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_RENDERER_RENDERER_COLOR_H_
#define SECONDPYLON_RENDERER_RENDERER_COLOR_H_

#include "secondpylon/plat/plat_types.h"

namespace secondpylon {
namespace renderer {

    // Renderer internal color representation.  This class insures colors can
    // be configured at runtime in a consistent way, regardless of how they are
    // actually handled to the renderer.
    class Color {
    public:
        Color();

        plat::uint32 GetEncodedColor() const { return encoded_color_; }

        void Encode(plat::uint8 r, plat::uint8 g, plat::uint8 b, plat::uint8 a);

        void Decode(
            plat::uint8* r
            , plat::uint8* g
            , plat::uint8* b
            , plat::uint8* a) const;

        bool operator==(const Color& rhs) const
        { return encoded_color_ == rhs.encoded_color_; }

        bool operator!=(const Color& rhs) const  { return *this != rhs; }

    private:
        plat::uint32 encoded_color_;
    };

}  // namespace renderer
}  // namespace secondpylon

#endif  // SECONDPYLON_RENDERER_RENDERER_COLOR_H_
