// Copyright 2009 Brian Legge

#include "secondpylon/math/math_vec3.h"
#include "unittest++/src/UnitTest++.h"
#include "secondpylon/test/test_utils.h"

template <typename T>
UnitTest::MemoryOutStream& operator<<(UnitTest::MemoryOutStream& stream
                                      , const secondpylon::math::vec3<T>& v) {
    stream << "(" << v.x << "," << v.y << "," << v.z << ")";
    return stream;
}

namespace secondpylon {
namespace math {
namespace test {

typedef vec3<plat::float32> vec3f;

SUITE(vec3) {
    TEST(ConstructFromComponents) {
        vec3f v(1.0F, 2.0F, 3.0F);
        CHECK_EQUAL(1.0F, v.x);
        CHECK_EQUAL(2.0F, v.y);
        CHECK_EQUAL(3.0F, v.z);
    }

    TEST(Interpolate) {
        CHECK_EQUAL(vec3f(0, 0, 0),
            vec3f::Interpolate(vec3f(0, 0, 0), vec3f(1, 1, 1), 0));

        CHECK_EQUAL(vec3f(0.5F, 0.5F, 0.5F),
            vec3f::Interpolate(vec3f(0, 0, 0), vec3f(1, 1, 1), 0.5f));

        CHECK_EQUAL(vec3f(1, 1, 1),
            vec3f::Interpolate(vec3f(0, 0, 0), vec3f(1, 1, 1), 1));
    }
}

}  // namespace secondpylon
}  // namespace math
}  // namespace test
