#include <secondpylon/math/math_utils.h>
#include <secondpylon/test/test_utils.h>
#include <unittest++/src/UnitTest++.h>

using namespace secondpylon;

TEST(Sqrt)
{
    CHECK_EQUAL(2.0F, math::Utils::Sqrt(4.0f));
}

TEST(SqrtNegative)
{
    SPTEST_CHECKASSERTS_BEGIN()
    {
        math::Utils::Sqrt(-4.0f);
    }
    SPTEST_CHECKASSERTS_END()
}


TEST(Abs)
{
    CHECK_EQUAL(4.0F, math::Utils::Abs(-4.0F));
    CHECK_EQUAL(4.0F, math::Utils::Abs(4.0F));
}

//TEST(PI)
//{
//  plat::float32 PI() { return 3.1415926535897931F; }
//}

TEST(DegreeToRadian)
{
    CHECK_EQUAL((2.0F*math::Utils::PI())/4.0F, math::Utils::DegreeToRadian(90.0F));
}

TEST(RadianToDegree)
{
    CHECK_EQUAL(90.0F, math::Utils::RadianToDegree((2.0F*math::Utils::PI()) / 4.0F));
}
