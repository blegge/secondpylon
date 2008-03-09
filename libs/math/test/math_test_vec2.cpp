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

TEST(Construct)
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

    CHECK(true == base.Equals(vec2f(1.0F, 2.0F), 1.0F));
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
    CHECK_EQUAL(math::Functions::Sqrt(5.0F), vec2f(-2, 1).Length());
}

TEST(Unit)
{
    CHECK_EQUAL(vec2f(1.0, 0.0F), vec2f(3.0F, 0.0F).Unit());
    //@todo define how close this is.
    plat::float32 sqrRootOne = math::Functions::Sqrt(1.0F);
    CHECK_EQUAL(vec2f(sqrRootOne, sqrRootOne), vec2f(1.0F, 1.0F).Unit());

    //@todo define how close this is.
    CHECK_CLOSE(1.0F, vec2f(1.0F, 1.0F).Unit().Length(), 0.001F);
}

TEST(Normal)
{
    SPTEST_UNIMPLEMENTED();
}

TEST(Minus)
{
    SPTEST_UNIMPLEMENTED();
}

TEST(Plus)
{
    SPTEST_UNIMPLEMENTED();
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

TEST(DotProduct)
{
    SPTEST_UNIMPLEMENTED();
}

TEST(Interpolate)
{
    SPTEST_UNIMPLEMENTED();
}