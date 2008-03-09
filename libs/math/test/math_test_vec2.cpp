#include <secondpylon\math\math_vec2.h>
#include <unittest++/src/UnitTest++.h>
#include <secondpylon\test\test_utils.h>

using namespace secondpylon;

typedef math::vec2<plat::float32> vec2f;

UnitTest::MemoryOutStream& operator<<(UnitTest::MemoryOutStream& stream, const vec2f& v)
{
    stream << "(" << v.x << "," << v.y << ")";
    return stream;
}

TEST(Construct)
{
    vec2f v(1.0f, 2.0f);
    CHECK_EQUAL(1.0f, v.x);
    CHECK_EQUAL(2.0f, v.y);
}

TEST(Equality)
{
    vec2f v(1.0f, 2.0f);
    CHECK_EQUAL(vec2f(1.0f, 2.0f), v);
}

TEST(EqualityTolerance)
{
    vec2f base(1.0f, 1.0f);

    CHECK(true == base.Equals(vec2f(1.0f, 2.0f), 1.0f));
    CHECK(false == vec2f(2.0f, 1.0f).Equals(vec2f(1.0f, 2.0f), 1.0f));
    CHECK(true == base.Equals(vec2f(1.99f, 1.99f), 1.0f));
}

TEST(Inequality)
{
    CHECK(vec2f(1.0f, 1.0f) != vec2f(1.0f, 2.0f));
    CHECK(!(vec2f(1.0f, 1.0f) != vec2f(1.0f, 1.0f)));
}

TEST(Copy)
{
    vec2f v(1.0f, 2.0f);
    vec2f v2(v);
    CHECK_EQUAL(v, v2);
}

TEST(Assignment)
{
    vec2f v(1.0f, 2.0f);
    vec2f v2 = v;
    CHECK_EQUAL(v, v2);
}

TEST(Negate)
{
    vec2f v(1.0f, 2.0f);
    v = -v;
    CHECK_EQUAL(vec2f(-1, -2), v);
}

TEST(Positive)
{
    vec2f v(1.0f, 2.0f);
    v = +v;
    CHECK_EQUAL(vec2f(1, 2), v);
}

TEST(Length)
{
    CHECK_EQUAL(2.0f, vec2f(0, 2).Length());
    CHECK_EQUAL(3.0f, vec2f(3, 0).Length());
    CHECK_EQUAL(math::Functions::Sqrt(5.0f), vec2f(-2, 1).Length());
}

TEST(Unit)
{
    CHECK_EQUAL(vec2f(1.0, 0.0f), vec2f(3.0f, 0.0f).Unit());
    //@todo define how close this is.
    plat::float32 sqrRootOne = math::Functions::Sqrt(1.0f);
    CHECK_EQUAL(vec2f(sqrRootOne, sqrRootOne), vec2f(1.0f, 1.0f).Unit());

    //@todo define how close this is.
    CHECK_CLOSE(1.0f, vec2f(1.0f, 1.0f).Unit().Length(), 0.001f);
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
