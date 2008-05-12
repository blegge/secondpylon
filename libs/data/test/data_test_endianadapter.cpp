#include <secondpylon/data/data_instream.h>
#include <secondpylon/data/data_outstream.h>
#include <secondpylon/data/data_memstorage.h>
#include <secondpylon/data/data_byteswappacker.h>
#include <unittest++/src/UnitTest++.h>

using namespace secondpylon;

// @todo Endian adapters need testing. Right nowe have only testing required to insure they compile.

SUITE(SByteSwapPacker)
{
    TEST(RoundTripStream)
    {
        data::MemStorage storage;
        data::OutStream<data::MemStorage, data::SByteSwapPacker > out(storage);
        {
            out.Write("test");
            out.Write(plat::uint16(0x1234));
            out.Write(plat::uint32(0x0a1a2a3a));        
        }

        CHECK(1);
    }
}
