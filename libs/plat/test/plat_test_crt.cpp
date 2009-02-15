#include <secondpylon/plat/plat_crt.h>
#include <unittest++/src/UnitTest++.h>

using namespace secondpylon;

namespace 
{
    class TestClass {};

}

SUITE(CRT)
{
    TEST(GetArraySizeAtRuntime)
    {
        TestClass testList[4];
        CHECK_EQUAL(size_t(4), ArraySize(testList));
    }

    TEST(AliasSafeTypeConversion)
    {
        char* source = "test";
        intptr_t dest = StrictCast<intptr_t>(source);
        char* roundtrip = StrictCast<char*>(dest);

        // Verify that source and roundtrip point at the same address.
        CHECK_EQUAL(source, roundtrip);
    }

    TEST(CopyAString)
    {
        char dest[5];
        StringCopy(dest, "test", ArraySize(dest));
        CHECK_EQUAL(dest, "test");
    }

    TEST(CopyAStringToUndersizedBuffer)
    {
        char dest[4];
        dest[0] = '\0';
        StringCopy(dest, "test", ArraySize(dest));
        CHECK_EQUAL(dest, "");
    }

    TEST(StringEqualityTests)
    {
        char* baseCase = "test";
        char* sameCase = "test";
        CHECK_EQUAL(true, StringEquals(baseCase, sameCase));
        CHECK_EQUAL(true, StringIEquals(baseCase, sameCase));

        char* caseDiff = "tesT";
        CHECK_EQUAL(false, StringEquals(baseCase, caseDiff));
        CHECK_EQUAL(true, StringIEquals(baseCase, caseDiff));

        char* caseDifferent = "tset";
        CHECK_EQUAL(false, StringEquals(baseCase, caseDifferent));
        CHECK_EQUAL(false, StringEquals(baseCase, caseDifferent));
    }
}
