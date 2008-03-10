#include <secondpylon/math/math_vec3.h>
#include <unittest++/src/UnitTest++.h>
#include <secondpylon/test/test_utils.h>

using namespace secondpylon;

UnitTest::MemoryOutStream& operator<<(UnitTest::MemoryOutStream& stream, const math::vec3f& v)
{
    stream << "(" << v.x << "," << v.y << "," << v.z << ")";
    return stream;
}

SUITE(vec3)
{
    TEST(Interpolate)
    {
        CHECK_EQUAL(math::vec3f(0,0,0), math::vec3f::Interpolate(math::vec3f(0,0,0), math::vec3f(1,1,1), 0));
        CHECK_EQUAL(math::vec3f(0.5F,0.5F,0.5F), math::vec3f::Interpolate(math::vec3f(0,0,0), math::vec3f(1,1,1), 0.5f));
        CHECK_EQUAL(math::vec3f(1,1,1), math::vec3f::Interpolate(math::vec3f(0,0,0), math::vec3f(1,1,1), 1));
    }
}
