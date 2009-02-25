#include <secondpylon/plat/plat_compiler.h>
#include <secondpylon/plat/plat_types.h>
#include <unittest++/src/UnitTest++.h>

using namespace secondpylon;

SPPLAT_INLINE bool TrueInline() { return true; }
SPPLAT_NOINLINE bool TrueNoInline() { return true; }

// This function is normally inlined, which prohibits us from actually testing the SPPLAT_RESTRICT behavior.
SPPLAT_NOINLINE void RestrictCopy(plat::uint32* SPPLAT_RESTRICT source, plat::uint32* SPPLAT_RESTRICT destlist, plat::uint32 count)
{
    for (plat::uint32 i = 0; i < count; ++i)
    {
        destlist[i] = *source;
    }
}

SUITE(Compiler)
{
    TEST(Inline)
    {
        CHECK(TrueInline());
    }

    TEST(NoInline)
    {
        CHECK(TrueNoInline());
    }

    // This doesn't actually test the restrict behavior, but throwing a breakpoint in can help verify that we don't do a
    // load per write on platforms that support restrict.
    TEST(RestrictCopy)
    {
        const plat::uint32 count = 5;
        plat::uint32 value = 3;
        plat::uint32 outputList[count];
        RestrictCopy(&value, &outputList[0], count);
        for (plat::uint32 i = 0; i < count; ++i)
        {
            CHECK_EQUAL(value, outputList[i]);
        }
    }
}
