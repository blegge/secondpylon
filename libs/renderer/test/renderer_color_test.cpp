// Copyright 2009 Brian Legge

#include <cstdio>
#include "unittest++/src/UnitTest++.h"
#include "secondpylon/renderer/renderer_color.h"

namespace {

UnitTest::MemoryOutStream& operator<<(UnitTest::MemoryOutStream& stream
                                  , const secondpylon::renderer::Color& c) {
    char txt[32];
    sprintf_s(txt, "Color:%x", c.GetEncodedColor());
    stream << txt;
    return stream;
}

}  // namespace

namespace secondpylon {
namespace renderer {
namespace test {

struct ColorFixture {
    ColorFixture() :
        red_(0)
        , green_(64)
        , blue_(128)
        , alpha_(255) {
        color_.Encode(red_, green_, blue_, alpha_);
    }

    plat::uint8 red_;
    plat::uint8 green_;
    plat::uint8 blue_;
    plat::uint8 alpha_;

    renderer::Color color_;
};

TEST_FIXTURE(ColorFixture, Initialization) {
    renderer::Color uninitialized;
    renderer::Color white;
    white.Encode(0, 0, 0, 255);

    CHECK_EQUAL(white, uninitialized);
}

TEST_FIXTURE(ColorFixture, Decode) {
    plat::uint8 red, blue, green, alpha;
    color_.Decode(&red, &green, &blue, &alpha);
    CHECK_EQUAL(red_, red);
    CHECK_EQUAL(green_, green);
    CHECK_EQUAL(blue_, blue);
    CHECK_EQUAL(alpha_, alpha);
}

}  // namespace secondpylon
}  // namespace renderer
}  // namespace test

