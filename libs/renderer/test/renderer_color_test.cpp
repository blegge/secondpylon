#include <unittest++/src/UnitTest++.h>
#include <secondpylon/renderer/renderer_color.h>
#include <cstdio>

using namespace secondpylon;

namespace {

    struct ColorFixture
    {
        ColorFixture() : 
            m_red(0)
            , m_green(64)
            , m_blue(128)
            , m_alpha(255)
        {
            m_color.Encode(m_red, m_green, m_blue, m_alpha);
        }

        plat::uint8 m_red;
        plat::uint8 m_green;
        plat::uint8 m_blue;
        plat::uint8 m_alpha;

        renderer::Color m_color;
    };

    UnitTest::MemoryOutStream& operator<<(UnitTest::MemoryOutStream& stream, const renderer::Color& c)
    {
        char txt[32];
        sprintf_s(txt, "Color:%x", c.GetEncodedColor());
        stream << txt;
        return stream;
    }
}

TEST_FIXTURE(ColorFixture, Initialization)
{
    renderer::Color uninitialized;
    renderer::Color white;
    white.Encode(0, 0, 0, 255);

    CHECK_EQUAL(white, uninitialized);
}

TEST_FIXTURE(ColorFixture, Decode)
{
    plat::uint8 red, blue, green, alpha;
    m_color.Decode(red, green, blue, alpha);
    CHECK_EQUAL(m_red, red);
    CHECK_EQUAL(m_green, green);
    CHECK_EQUAL(m_blue, blue);
    CHECK_EQUAL(m_alpha, alpha);
}
