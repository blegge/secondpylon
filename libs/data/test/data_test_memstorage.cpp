// Copyright 2009 Brian Legge

#include "secondpylon/data/data_memstorage.h"
#include "secondpylon/plat/plat_crt.h"
#include "unittest++/src/UnitTest++.h"

namespace secondpylon {
namespace data {
namespace test {

SUITE(MemStorage) {
    TEST(CreateReadMemStorage) {
        plat::uint32 source = 0x01020304;
        data::MemStorage storage(StrictCast<plat::byte*>(&source), sizeof(source));
        storage.SetUsage(data::MemStorage::kRead);

        plat::uint32 dest = 0;
        storage.Read(StrictCast<plat::byte*>(&dest), 4);

        CHECK_EQUAL(static_cast<plat::uint32>(0x01020304), dest);
    }

    // @todo We need a test figure out how we want to handle asserts at test
    // time. Verification that we assert on errors would be good - right now we
    // just abort the app.
    /*
    TEST(OverreadMemStorage)
    {
        plat::byte sourceData[] = { 1, 2, 3};
        data::MemStorage storage(sourceData, ArraySize(sourceData));
        storage.SetUsage(data::MemStorage::kRead);

        plat::uint32 dest = 0xffffffff;
        storage.Read(StrictCast<plat::byte*>(&dest), 4);

        CHECK_EQUAL(plat::uint32(0), dest);
    }
    */
}

}  // namespace secondpylon
}  // namespace data
}  // namespace test
