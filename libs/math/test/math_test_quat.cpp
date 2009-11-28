// Copyright 2009 Brian Legge

#include "secondpylon/math/math_quat.h"
#include "unittest++/src/UnitTest++.h"
#include "secondpylon/test/test_utils.h"

namespace {

using secondpylon::math::quat;

template <typename TStorage>
UnitTest::MemoryOutStream& operator<<(UnitTest::MemoryOutStream& stream
                                      , const quat<TStorage>& q) {
    stream << "("
        << q.q[quat<TStorage>::kW]
        << "," << q.q[quat<TStorage>::kX]
        << "," << q.q[quat<TStorage>::kY]
        << "," << q.q[quat<TStorage>::kZ
        ] << ")";
    return stream;
}
}  // namespace

namespace secondpylon {
namespace math {
namespace test {

SUITE(quat) {
    typedef math::quat<float> quatf;

    TEST(ConstructFromComponents) {
        quatf q(1.0F, 0.0F, 0.0F, 0.0F);
        CHECK_EQUAL(quatf::GetIdentity(), q);
    }

    TEST(ConjugateIdentityIsIdentity) {
        quatf conj = quatf::GetIdentity().Conjugate();
        CHECK_EQUAL(quatf::GetIdentity(), conj);
    }
}

}  //  namespace secondpylon
}  //  namespace math
}  //  namespace test
