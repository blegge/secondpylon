#include <secondpylon/math/math_vec2.h>
#include <unittest++/src/UnitTest++.h>
#include <secondpylon/test/test_utils.h>

using namespace secondpylon;

UnitTest::MemoryOutStream& operator<<(UnitTest::MemoryOutStream& stream, const math::vec2f& v)
{
    stream << "(" << v.x << "," << v.y << ")";
    return stream;
}

SUITE(vec2)
{

    TEST(Construct)
    {
        math::vec2f v(1.0F, 2.0F);
        CHECK_EQUAL(1.0F, v.x);
        CHECK_EQUAL(2.0F, v.y);
    }

    TEST(Equality)
    {
        math::vec2f v(1.0F, 2.0F);
        CHECK_EQUAL(math::vec2f(1.0F, 2.0F), v);
    }

    TEST(EqualityTolerance)
    {
        math::vec2f base(1.0F, 1.0F);

        CHECK(true == base.Equals(math::vec2f(1.0F, 1.9F), 1.0F));
        CHECK(false == math::vec2f(2.0F, 1.0F).Equals(math::vec2f(1.0F, 2.0F), 1.0F));
        CHECK(true == base.Equals(math::vec2f(1.99F, 1.99f), 1.0F));
    }

    TEST(Inequality)
    {
        CHECK(math::vec2f(1.0F, 1.0F) != math::vec2f(1.0F, 2.0F));
        CHECK(!(math::vec2f(1.0F, 1.0F) != math::vec2f(1.0F, 1.0F)));
    }

    TEST(Copy)
    {
        math::vec2f v(1.0F, 2.0F);
        math::vec2f v2(v);
        CHECK_EQUAL(v, v2);
    }

    TEST(Assignment)
    {
        math::vec2f v(1.0F, 2.0F);
        math::vec2f v2 = v;
        CHECK_EQUAL(v, v2);
    }

    TEST(Negate)
    {
        math::vec2f v(1.0F, 2.0F);
        v = -v;
        CHECK_EQUAL(math::vec2f(-1, -2), v);
    }

    TEST(Positive)
    {
        math::vec2f v(1.0F, 2.0F);
        v = +v;
        CHECK_EQUAL(math::vec2f(1, 2), v);
    }

    TEST(Length)
    {
        CHECK_EQUAL(2.0F, math::vec2f(0, 2).Length());
        CHECK_EQUAL(3.0F, math::vec2f(3, 0).Length());
        CHECK_EQUAL(math::Utils::Sqrt(5.0F), math::vec2f(-2, 1).Length());
    }

    TEST(Normal)
    {
        CHECK_EQUAL(math::vec2f(1.0, 0.0F), math::vec2f(3.0F, 0.0F).Normal());

        plat::float32 length = 1.0F / math::Utils::Sqrt(2);
        CHECK_EQUAL(math::vec2f(length, length), math::vec2f(1.0F, 1.0F).Normal());

        CHECK_EQUAL(1.0F, math::vec2f(100.0F, -10000.0F).Normal().Length());
    }

    TEST(Minus)
    {
        CHECK_EQUAL(math::vec2f(2.0F, -0.5F), math::vec2f(1.0F, 2.5F) - math::vec2f(-1.0F, 3.0F));
    }

    TEST(Plus)
    {
        CHECK_EQUAL(math::vec2f(0.0F, 5.5F), math::vec2f(1.0F, 2.5F) + math::vec2f(-1.0F, 3.0F));
    }

    TEST(Times)
    {
        CHECK_EQUAL(math::vec2f(2.0F, 5.0F), math::vec2f(1.0F, 2.5F) * 2.0f);
    }

    TEST(Divide)
    {
        CHECK_EQUAL(math::vec2f(1.0F, 2.5F), math::vec2f(2.0F, 5.0F) / 2.0f);
    }

    TEST(MinusEqual)
    {
        SPTEST_UNIMPLEMENTED();
    }

    TEST(PlusEqual)
    {
        SPTEST_UNIMPLEMENTED();
    }

    TEST(TimesEqual)
    {
        SPTEST_UNIMPLEMENTED();
    }

    TEST(DivEqual)
    {
        SPTEST_UNIMPLEMENTED();
    }

    TEST(DivEqualOutOfRange)
    {
        SPTEST_CHECKASSERTS_BEGIN()
        {
            math::vec2f base(2.0F, 2.0F);
            base /= 0.0F;
        }
        SPTEST_CHECKASSERTS_END()
    }

    TEST(DotProduct)
    {
        // Test using the dot product to project a point onto a line.

        math::vec2f p(10.0F, 5.0F);
        CHECK_EQUAL(5.0F, math::vec2f::DotProduct(p, math::vec2f(0.0F, 1.0F)));
        CHECK_EQUAL(10.0F, math::vec2f::DotProduct(p, math::vec2f(1.0F, 0.0F)));
    }

    TEST(Interpolate)
    {
        CHECK_EQUAL(math::vec2f(0,0), math::vec2f::Interpolate(math::vec2f(0,0), math::vec2f(1,1), 0));
        CHECK_EQUAL(math::vec2f(0.5F,0.5F), math::vec2f::Interpolate(math::vec2f(0,0), math::vec2f(1,1), 0.5f));
        CHECK_EQUAL(math::vec2f(1,1), math::vec2f::Interpolate(math::vec2f(0,0), math::vec2f(1,1), 1));
    }

    TEST(InterpolateOutOfRange)
    {
        SPTEST_CHECKASSERTS_BEGIN()
        {
            math::vec2f::Interpolate(math::vec2f(0,0), math::vec2f(1,1), -0.0F);
        }
        SPTEST_CHECKASSERTS_END()

        SPTEST_CHECKASSERTS_BEGIN()
        {
            math::vec2f::Interpolate(math::vec2f(0,0), math::vec2f(1,1), 1.0F+1E-6f);
        }
        SPTEST_CHECKASSERTS_END()
    }
}
