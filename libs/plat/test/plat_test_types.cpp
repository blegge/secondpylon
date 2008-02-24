#include <unittest++/src/UnitTest++.h>
#include <secondpylon/plat/plat_types.h>

TEST(VerifySize)
{
    CHECK_EQUAL(size_t(1), sizeof(secondpylon::plat::uint8));
    CHECK_EQUAL(size_t(2), sizeof(secondpylon::plat::uint16));
    CHECK_EQUAL(size_t(4), sizeof(secondpylon::plat::uint32));
    CHECK_EQUAL(size_t(1), sizeof(secondpylon::plat::sint8));
    CHECK_EQUAL(size_t(2), sizeof(secondpylon::plat::sint16));
    CHECK_EQUAL(size_t(4), sizeof(secondpylon::plat::sint32));

    CHECK_EQUAL(size_t(4), sizeof(secondpylon::plat::float32));

    CHECK_EQUAL(size_t(1), sizeof(secondpylon::plat::byte));

    CHECK_EQUAL(size_t(1), sizeof(secondpylon::plat::bool8));

    CHECK_EQUAL(size_t(1), sizeof(secondpylon::plat::uchar));
}

TEST(VerifyBool)
{
    secondpylon::plat::bool8 bTrue = true;
    CHECK_EQUAL(true, bTrue);

    secondpylon::plat::bool8 bFalse = false;
    CHECK_EQUAL(false, bFalse);

    CHECK_EQUAL(true, bTrue != bFalse);
}

TEST(VerifySign)
{
    CHECK(secondpylon::plat::uint8(0xff) > 0);
    CHECK(secondpylon::plat::uint16(0xffff) > 0);
    CHECK(secondpylon::plat::uint32(0xffffffff) > 0);
    CHECK(secondpylon::plat::sint8(-1) < 0);
    CHECK(secondpylon::plat::sint16(-1) < 0);
    CHECK(secondpylon::plat::sint32(-1) < 0);
    
    // Byte is always unsigned
    CHECK(secondpylon::plat::byte(0xff) > 0);

    // char is always unsigned
    CHECK(secondpylon::plat::uchar(0xff) > 0);
}
