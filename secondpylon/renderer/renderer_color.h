#ifndef SPRENDERER_COLOR_H
#define SPRENDERER_COLOR_H

#include <secondpylon/plat/plat_types.h>

namespace secondpylon {
namespace renderer {

    // Renderer internal color representation.  This class insures colors can be configured at runtime in a consistent
    // way, regardless of how they are actually handled to the renderer.
    class Color
    {
    public:
        Color();

        plat::uint32 GetEncodedColor() const { return m_EncodedColor; }

        void Encode(plat::uint8 r, plat::uint8 g, plat::uint8 b, plat::uint8 a);
        void Decode(plat::uint8& r, plat::uint8& g, plat::uint8& b, plat::uint8& a) const;

        bool operator==(const Color& rhs) const { return m_EncodedColor == rhs.m_EncodedColor; }
        bool operator!=(const Color& rhs) const  { return *this != rhs; }

    private:
        plat::uint32 m_EncodedColor;
    };

}
}

#endif // SPRENDERER_COLOR_H
