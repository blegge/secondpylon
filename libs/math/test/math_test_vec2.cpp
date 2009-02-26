#include <secondpylon/math/math_vec2.h>
#include <unittest++/src/UnitTest++.h>
#include <secondpylon/test/test_utils.h>

using namespace secondpylon;

typedef math::vec2<plat::float32> vec2f;

UnitTest::MemoryOutStream& operator<<(UnitTest::MemoryOutStream& stream, const vec2f& v)
{
    stream << "(" << v.x << "," << v.y << ")";
    return stream;
}

SUITE(vec2)
{
    TEST(ConstructFromComponents)
    {
        vec2f v(1.0F, 2.0F);
        CHECK_EQUAL(1.0F, v.x);
        CHECK_EQUAL(2.0F, v.y);
    }

    TEST(Equality)
    {
        vec2f v(1.0F, 2.0F);
        CHECK_EQUAL(vec2f(1.0F, 2.0F), v);
    }

    TEST(EqualityTolerance)
    {
        vec2f base(1.0F, 1.0F);

        CHECK(true == base.Equals(vec2f(1.0F, 1.9F), 1.0F));
        CHECK(false == vec2f(2.0F, 1.0F).Equals(vec2f(1.0F, 2.0F), 1.0F));
        CHECK(true == base.Equals(vec2f(1.99F, 1.99f), 1.0F));
    }

    TEST(Inequality)
    {
        CHECK(vec2f(1.0F, 1.0F) != vec2f(1.0F, 2.0F));
        CHECK(!(vec2f(1.0F, 1.0F) != vec2f(1.0F, 1.0F)));
    }

    TEST(Copy)
    {
        vec2f v(1.0F, 2.0F);
        vec2f v2(v);
        CHECK_EQUAL(v, v2);
    }

    TEST(Assignment)
    {
        vec2f v(1.0F, 2.0F);
        vec2f v2 = v;
        CHECK_EQUAL(v, v2);
    }

    TEST(Negate)
    {
        vec2f v(1.0F, 2.0F);
        v = -v;
        CHECK_EQUAL(vec2f(-1, -2), v);
    }

    TEST(Positive)
    {
        vec2f v(1.0F, 2.0F);
        v = +v;
        CHECK_EQUAL(vec2f(1, 2), v);
    }

    TEST(Length)
    {
        CHECK_EQUAL(2.0F, vec2f(0, 2).Length());
        CHECK_EQUAL(3.0F, vec2f(3, 0).Length());
        CHECK_EQUAL(math::Utils::Sqrt(5.0F), vec2f(-2, 1).Length());
    }

    TEST(Normal)
    {
        CHECK_EQUAL(vec2f(1.0, 0.0F), vec2f(3.0F, 0.0F).Normal());

        plat::float32 length = 1.0F / math::Utils::Sqrt(2);
        CHECK_EQUAL(vec2f(length, length), vec2f(1.0F, 1.0F).Normal());

        CHECK_EQUAL(1.0F, vec2f(100.0F, -10000.0F).Normal().Length());
    }

    TEST(Minus)
    {
        CHECK_EQUAL(vec2f(2.0F, -0.5F), vec2f(1.0F, 2.5F) - vec2f(-1.0F, 3.0F));
    }

    TEST(Plus)
    {
        CHECK_EQUAL(vec2f(0.0F, 5.5F), vec2f(1.0F, 2.5F) + vec2f(-1.0F, 3.0F));
    }

    TEST(Times)
    {
        CHECK_EQUAL(vec2f(2.0F, 5.0F), vec2f(1.0F, 2.5F) * 2.0f);
    }

    TEST(Divide)
    {
        CHECK_EQUAL(vec2f(1.0F, 2.5F), vec2f(2.0F, 5.0F) / 2.0f);
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
            vec2f base(2.0F, 2.0F);
            base /= 0.0F;
        }
        SPTEST_CHECKASSERTS_END()
    }

    TEST(DotProduct)
    {
        // Test using the dot product to project a point onto a line.

        vec2f p(10.0F, 5.0F);
        CHECK_EQUAL(5.0F, vec2f::DotProduct(p, vec2f(0.0F, 1.0F)));
        CHECK_EQUAL(10.0F, vec2f::DotProduct(p, vec2f(1.0F, 0.0F)));
    }

    TEST(Interpolate)
    {
        CHECK_EQUAL(vec2f(0,0), vec2f::Interpolate(vec2f(0,0), vec2f(1,1), 0));
        CHECK_EQUAL(vec2f(0.5F,0.5F), vec2f::Interpolate(vec2f(0,0), vec2f(1,1), 0.5f));
        CHECK_EQUAL(vec2f(1,1), vec2f::Interpolate(vec2f(0,0), vec2f(1,1), 1));
    }

    TEST(InterpolateOutOfRange)
    {
        SPTEST_CHECKASSERTS_BEGIN()
        {
            vec2f::Interpolate(vec2f(0,0), vec2f(1,1), 0.0F-1E-6F);
        }
        SPTEST_CHECKASSERTS_END()

        SPTEST_CHECKASSERTS_BEGIN()
        {
            vec2f::Interpolate(vec2f(0,0), vec2f(1,1), 1.0F+1E-6F);
        }
        SPTEST_CHECKASSERTS_END()
    }
}
