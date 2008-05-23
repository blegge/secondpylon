#include <secondpylon/data/data_instream.h>
#include <secondpylon/data/data_outstream.h>
#include <secondpylon/data/data_memstorage.h>
#include <secondpylon/data/data_byteswappacker.h>
#include <unittest++/src/UnitTest++.h>

using namespace secondpylon;

// @todo Endian adapters need testing. Right now have only surface testing

SUITE(SByteSwapPacker)
{
    TEST(RoundTripStream)
    {
        data::MemStorage storage;
        {
            data::OutStream<data::MemStorage, data::SByteSwapPacker > out(storage);
            out.Write("test");
            out.Write(plat::uint16(0x1234));
            out.Write(plat::uint32(0x0a1a2a3a));        
        }

        char buffer[16];
        plat::uint16 n16;
        plat::uint32 n32;

        {
            data::InStream<data::MemStorage, data::SByteSwapPacker > in(storage);
            in.Read(buffer, ArraySize(buffer));
            in.Read(n16);
            in.Read(n32);
        }

        CHECK_EQUAL("test", buffer);
        CHECK_EQUAL(plat::uint16(0x1234), n16);
        CHECK_EQUAL(plat::uint32(0x0a1a2a3a), n32);
    }
}
