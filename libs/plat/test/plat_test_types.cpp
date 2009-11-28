// Copyright 2009 Brian Legge

#include "secondpylon/plat/plat_types.h"
#include "unittest++/src/UnitTest++.h"

namespace secondpylon {
namespace plat {
namespace test {

TEST(VerifySize) {
    CHECK_EQUAL(size_t(1), sizeof(plat::uint8));
    CHECK_EQUAL(size_t(2), sizeof(plat::uint16));
    CHECK_EQUAL(size_t(4), sizeof(plat::uint32));
    CHECK_EQUAL(size_t(1), sizeof(plat::sint8));
    CHECK_EQUAL(size_t(2), sizeof(plat::sint16));
    CHECK_EQUAL(size_t(4), sizeof(plat::sint32));

    CHECK_EQUAL(size_t(4), sizeof(plat::float32));

    CHECK_EQUAL(size_t(1), sizeof(plat::byte));

    CHECK_EQUAL(size_t(1), sizeof(plat::bool8));
}

TEST(VerifyBool) {
    plat::bool8 true_value = true;
    CHECK_EQUAL(true, true_value);

    plat::bool8 false_value = false;
    CHECK_EQUAL(false, false_value);

    CHECK_EQUAL(true, true_value != false_value);
}

TEST(VerifySign) {
    CHECK(static_cast<plat::uint8>(0xff) > 0);
    CHECK(static_cast<plat::uint16>(0xffff) > 0);
    CHECK(static_cast<plat::uint32>(0xffffffff) > 0);
    CHECK(static_cast<plat::sint8>(-1) < 0);
    CHECK(static_cast<plat::sint16>(-1) < 0);
    CHECK(static_cast<plat::sint32>(-1) < 0);

    // Byte is always unsigned
    CHECK(static_cast<plat::byte>(0xff) > 0);
}

}  // namespace secondpylon
}  // namespace plat
}  // namespace test
