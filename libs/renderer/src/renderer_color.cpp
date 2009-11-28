// Copyright 2009 Brian Legge

#include "secondpylon/renderer/renderer_color.h"

// Encode and decode currently support only ARGB. Various platforms will have
// other requirements. To insulate us from this, Color should always be used to
// specify a color to the renderer. Eventually specialization will likely be
// resulted at link time.

namespace secondpylon {
namespace renderer {

Color::Color() {
    // Default to white. Consider making this a static function
    // (ie Color::White() { return Color c; c.Encode(0, 0, 0, 255); }
    Encode(0, 0, 0, 255);
}

void Color::Encode(plat::uint8 r, plat::uint8 g, plat::uint8 b
                   , plat::uint8 a) {
    encoded_color_ = (a << 24) | (r << 16) | (g << 8) | (b << 0);
}

void Color::Decode(plat::uint8* r, plat::uint8* g,
                   plat::uint8* b , plat::uint8* a) const {
    *a = static_cast<plat::uint8>((encoded_color_ >> 24) & 0xff);
    *r = static_cast<plat::uint8>((encoded_color_ >> 16) & 0xff);
    *g = static_cast<plat::uint8>((encoded_color_ >> 8) & 0xff);
    *b = static_cast<plat::uint8>((encoded_color_ >> 0) & 0xff);
}

}  // namespace renderer
}  // namespace secondpylon
