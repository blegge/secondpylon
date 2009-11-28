// Copyright 2009 Brian Legge

#include "secondpylon/plat/plat_compiler.h"
#include "secondpylon/plat/plat_types.h"
#include "secondpylon/plat/plat_crt.h"
#include "unittest++/src/UnitTest++.h"

namespace secondpylon {
namespace plat {
namespace test {

SPPLAT_INLINE bool TrueInline() { return true; }
SPPLAT_NOINLINE bool TrueNoInline() { return true; }

// This function is normally inlined, which prohibits us from actually testing
// the SPPLAT_RESTRICT behavior.
SPPLAT_NOINLINE void RestrictCopy(plat::uint32* SPPLAT_RESTRICT source
                                  , plat::uint32* SPPLAT_RESTRICT destlist
                                  , plat::uint32 count) {
    for (plat::uint32 i = 0; i < count; ++i) {
        destlist[i] = *source;
    }
}

SUITE(Compiler) {
    TEST(Inline) {
        CHECK(TrueInline());
    }

    TEST(NoInline) {
        CHECK(TrueNoInline());
    }

    // This doesn't actually test the restrict behavior, but throwing a
    // breakpoint in can help verify that we don't do a load per write on
    // platforms that support restrict.
    TEST(RestrictCopy) {
        plat::uint32 value = 3;
        plat::uint32 outputList[5];
        RestrictCopy(&value, &outputList[0], ArraySize(outputList));
        for (plat::uint32 i = 0; i < ArraySize(outputList); ++i) {
            CHECK_EQUAL(value, outputList[i]);
        }
    }
}

}  // namespace secondpylon
}  // namespace plat
}  // namespace test
