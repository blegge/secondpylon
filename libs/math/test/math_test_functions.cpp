#include <secondpylon/math/math_functions.h>
#include <secondpylon/test/test_utils.h>
#include <unittest++/src/UnitTest++.h>

using namespace secondpylon;

TEST(Sqrt)
{
    CHECK_EQUAL(2.0f, math::Functions::Sqrt(4.0f));
}

TEST(SqrtNegative)
{
    SPTEST_CHECKASSERTS_BEGIN()
    {
        math::Functions::Sqrt(-4.0f);
    }
    SPTEST_CHECKASSERTS_END()
}
