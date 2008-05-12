#include <secondpylon/data/data_instream.h>
#include <secondpylon/data/data_outstream.h>
#include <secondpylon/data/data_memstorage.h>
#include <unittest++/src/UnitTest++.h>
#include <secondpylon/plat/plat_architecture.h>
#include <secondpylon/plat/plat_crt.h>

using namespace secondpylon;

namespace 
{

struct SStreamTestCase
{
    SStreamTestCase() :
        m_bool(true)
        , m_uint8(0xfd)
        , m_uint32(0x1234)
        , m_uint16(0xab)
        , m_float32(0.6764556980453310f)
        , m_sint8(-94)
        , m_sint32(-1239057)
        , m_sint16(-1234)
    {
        StringCopy(m_szString, "Test", ArraySize(m_szString));
    }

    bool operator==(const SStreamTestCase& rhs) const
    {
        return (
            m_bool == rhs.m_bool
            && m_uint8 == rhs.m_uint8
            && m_uint32 == rhs.m_uint32
            && m_uint16 == rhs.m_uint16
            && m_float32 == rhs.m_float32
            && m_sint8 == rhs.m_sint8
            && m_sint32 == rhs.m_sint32
            && m_sint16 == rhs.m_sint16
            );
    }

    void Write(data::OutStream<data::MemStorage>& stream)
    {
        stream.Write(m_bool);
        stream.Write(m_uint8);
        stream.Write(m_uint32);
        stream.Write(m_uint16);
        stream.Write(m_float32);
        stream.Write(m_sint8);
        stream.Write(m_sint32);
        stream.Write(m_sint16);
        stream.Write(m_szString);
    }

    void Read(data::InStream<data::MemStorage>& stream)
    {
        stream.Read(m_bool);
        stream.Read(m_uint8);
        stream.Read(m_uint32);
        stream.Read(m_uint16);
        stream.Read(m_float32);
        stream.Read(m_sint8);
        stream.Read(m_sint32);
        stream.Read(m_sint16);
        stream.Read(m_szString, ArraySize(m_szString));
    }

    plat::bool8 m_bool;
    plat::uint8 m_uint8;
    plat::uint32 m_uint32;
    plat::uint16 m_uint16;
    plat::float32 m_float32;
    plat::sint8 m_sint8;
    plat::sint32 m_sint32;
    plat::sint16 m_sint16;
    char m_szString[48];
};

}

TEST(TestSStreamTestCaseEquality)
{
    CHECK(SStreamTestCase() == SStreamTestCase());
}

TEST(WriteStreamAtomic)
{
    data::MemStorage storage;
    {
        data::OutStream<data::MemStorage> out(storage);
        out.Write(plat::bool8(true));
        out.Write(plat::uint16(0xa0a1));
        out.Write(plat::bool8(false));
        out.Write("ab");
        out.Write(plat::uint32(0xf0f1f2f3));
    }

    plat::uint32 dataSize = storage.GetDataSize();
    const plat::byte* data = storage.GetData();

#if defined(SPPLAT_LITTLEENDIAN)

    plat::byte block[] = { 
        0x01 // bool8(true)
        , 0xa1, 0xa0  // plat::uint16(0xa0a1)
        , 0x00 // bool8(false)
        , 0x2, 0x00, 0x00, 0x00  // size of string
        , 'a', 'b' //string contents
        , 0xf3, 0xf2, 0xf1, 0xf0   // uint32(0xf0f1f2f3)
    };

#elif defined(SPPLAT_BIGENDIAN)

    plat::byte block[] = { 
        0x01 // bool8(true)
        , 0xa0, 0xa1,   // plat::uint16(0xa0a1)
        , 0x00 // bool8(false)
        , 0x00, 0x00, 0x00, 0x2  // size of string
        , 'a', 'b' //string contents
        , 0xf0, 0xf1, 0xf2, 0xf3,     // uint32(0xf0f1f2f3)
    };

#else

    #error Platform does not define byte ordering

#endif

    plat::uint32 blockSize = ArraySize(block);
    CHECK_EQUAL(blockSize, dataSize);
    CHECK(0 == memcmp(block, data, blockSize));
}

TEST(RoundTripStream)
{
    data::MemStorage storage;
    SStreamTestCase test;
    {
        data::OutStream<data::MemStorage> out(storage);
        test.Write(out);
    }

    SStreamTestCase test2;
    data::InStream<data::MemStorage> in(storage);
    test2.Read(in);

    CHECK(test == test2);
}

TEST(StringReadCapacity)
{
    data::MemStorage storage;
    {
        data::OutStream<data::MemStorage> out(storage);
        out.Write("test");
        out.Write(plat::uint32(0x0a1a2a3a));
    }

    char szTooSmall[4];
    plat::uint32 nNextRead = 0;

    szTooSmall[0] = '\0';
    data::InStream<data::MemStorage> in(storage);
    in.Read(szTooSmall, 4);
    in.Read(nNextRead);

    CHECK_EQUAL("", szTooSmall);
    CHECK_EQUAL(plat::uint32(0x0a1a2a3a), nNextRead);
}

// What enables this behavior? We don't want it to be required, as that would add a sizeable amount of overhead to the file operations. Unless perhaps each read/write changed an accumulator, which would avoid size overhead.
TEST(MismatchedStreamRead)
{
    data::MemStorage storage;
    {
        data::OutStream<data::MemStorage> out(storage);
        out.Write(plat::uint32(0xfdfdfdfd));
        out.Write(plat::uint16(0xabab));
        out.Write(plat::uint16(0xcdcd));
    }

    plat::uint32 nGoodRead = 0;
    plat::uint32 nBadRead = 0;
    data::InStream<data::MemStorage> in(storage);
    in.Read(nGoodRead);
    in.Read(nBadRead);

    CHECK_EQUAL(0xfdfdfdfd, nGoodRead);
    CHECK_EQUAL(plat::uint32(0), nBadRead);
}
