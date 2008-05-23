#include <secondpylon/math/math_quat.h>
#include <unittest++/src/UnitTest++.h>
#include <secondpylon/test/test_utils.h>

using namespace secondpylon;

template <typename TStorage>
UnitTest::MemoryOutStream& operator<<(UnitTest::MemoryOutStream& stream, const math::quat<TStorage>& q)
{
    stream << "(" 
        << q.q[math::quat<TStorage>::kW] 
        << "," << q.q[math::quat<TStorage>::kX]
        << "," << q.q[math::quat<TStorage>::kY]
        << "," << q.q[math::quat<TStorage>::kZ
        ] << ")";
    return stream;
}

SUITE(quat)
{
    typedef math::quat<float> quatf;

    TEST(ConstructFromComponents)
    {
        quatf q(1.0F, 0.0F, 0.0F, 0.0F);
        CHECK_EQUAL(quatf::GetIdentity(), q);
    }

    TEST(ConjugateIdentityIsIdentity)
    {
        quatf conj = quatf::GetIdentity().Conjugate();
        CHECK_EQUAL(quatf::GetIdentity(), conj);
    }
}
