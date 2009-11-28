// Copyright 2009 Brian Legge

#include "secondpylon/data/data_instream.h"
#include "secondpylon/data/data_outstream.h"
#include "secondpylon/data/data_memstorage.h"
#include "unittest++/src/UnitTest++.h"
#include "secondpylon/plat/plat_architecture.h"
#include "secondpylon/plat/plat_crt.h"
#include "secondpylon/test/test_utils.h"

namespace secondpylon {
namespace data {
namespace test {

struct StreamTestCase {
  StreamTestCase() :
    bool_(true)
    , uint8_(0xfd)
    , uint32_(0x1234)
    , uint16_(0xab)
    , float32_(0.6764556980453310f)
    , sint8_(-94)
    , sint32_(-1239057)
    , sint16_(-1234) {
    StringCopy(szString_, "Test", ArraySize(szString_));
  }

  bool operator==(const StreamTestCase& rhs) const {
    return (
      bool_ == rhs.bool_
      && uint8_ == rhs.uint8_
      && uint32_ == rhs.uint32_
      && uint16_ == rhs.uint16_
      && float32_ == rhs.float32_
      && sint8_ == rhs.sint8_
      && sint32_ == rhs.sint32_
      && sint16_ == rhs.sint16_);
  }

  void Write(data::OutStream<data::MemStorage, data::BytePacker>* pStream) {
    pStream->Write(bool_);
    pStream->Write(uint8_);
    pStream->Write(uint32_);
    pStream->Write(uint16_);
    pStream->Write(float32_);
    pStream->Write(sint8_);
    pStream->Write(sint32_);
    pStream->Write(sint16_);
    pStream->Write(szString_);
  }

  void Read(data::InStream<data::MemStorage, data::ByteUnpacker>* pStream) {
    pStream->Read(&bool_);
    pStream->Read(&uint8_);
    pStream->Read(&uint32_);
    pStream->Read(&uint16_);
    pStream->Read(&float32_);
    pStream->Read(&sint8_);
    pStream->Read(&sint32_);
    pStream->Read(&sint16_);
    pStream->Read(szString_, ArraySize(szString_));
  }

  plat::bool8 bool_;
  plat::uint8 uint8_;
  plat::uint32 uint32_;
  plat::uint16 uint16_;
  plat::float32 float32_;
  plat::sint8 sint8_;
  plat::sint32 sint32_;
  plat::sint16 sint16_;
  char szString_[48];
};

TEST(TestStreamTestCaseEquality) {
  CHECK(StreamTestCase() == StreamTestCase());
}

TEST(WriteStreamAtomic) {
  data::MemStorage storage;
  {
    data::OutStream<data::MemStorage, data::BytePacker> out(&storage);
    out.Write(plat::bool8(true));
    out.Write(plat::uint16(0xa0a1));
    out.Write(plat::bool8(false));
    out.Write("ab");
    out.Write(static_cast<plat::uint32>(0xf0f1f2f3));
  }

  plat::uint32 dataSize = storage.GetDataSize();
  const plat::byte* data = storage.GetData();

#if defined(SPPLAT_LITTLEENDIAN)

  plat::byte block[] = {
    0x01  // bool8(true)
    , 0xa1, 0xa0  // plat::uint16(0xa0a1)
    , 0x00  // bool8(false)
    , 0x2, 0x00, 0x00, 0x00  // size of string
    , 'a', 'b'  // string contents
    , 0xf3, 0xf2, 0xf1, 0xf0   // uint32(0xf0f1f2f3)
  };

#elif defined(SPPLAT_BIGENDIAN)

  plat::byte block[] = {
    0x01  // bool8(true)
    , 0xa0, 0xa1,   // plat::uint16(0xa0a1)
    , 0x00  // bool8(false)
    , 0x00, 0x00, 0x00, 0x2  // size of string
    , 'a', 'b'  // string contents
    , 0xf0, 0xf1, 0xf2, 0xf3,   // uint32(0xf0f1f2f3)
  };

#else

  #error Platform does not define byte ordering

#endif

  plat::uint32 blockSize = ArraySize(block);
  CHECK_EQUAL(blockSize, dataSize);
  CHECK(0 == memcmp(block, data, blockSize));
}

TEST(RoundTripStream) {
  data::MemStorage storage;
  StreamTestCase test;
  {
    data::OutStream<data::MemStorage, data::BytePacker> out(&storage);
    test.Write(&out);
  }

  StreamTestCase test2;
  data::InStream<data::MemStorage, data::ByteUnpacker> in(&storage);
  test2.Read(&in);

  CHECK(test == test2);
}

TEST(StringReadCapacity) {
  data::MemStorage storage;
  {
    data::OutStream<data::MemStorage, data::BytePacker> out(&storage);
    out.Write("test");
    out.Write(static_cast<plat::uint32>(0x0a1a2a3a));
  }

  char szTooSmall[4];
  plat::uint32 nNextRead = 0;

  szTooSmall[0] = '\0';
  data::InStream<data::MemStorage, data::ByteUnpacker> in(&storage);

  SPTEST_CHECKASSERTS_BEGIN();
  in.Read(szTooSmall, 4);
  SPTEST_CHECKASSERTS_END();

  in.Read(&nNextRead);

  CHECK_EQUAL("", szTooSmall);
  CHECK_EQUAL(static_cast<plat::uint32>(0x0a1a2a3a), nNextRead);
}

// What enables this behavior? We don't want it to be required, as that would
// add a sizeable amount of overhead to the file operations. Unless perhaps each
// read/write changed an accumulator, which would avoid size overhead.
/*

TODO: We need to figure out how to trap and report this error. We don't have
immediate plans to do so. We are

TEST(MismatchedStreamRead)
{
  data::MemStorage storage;
  {
    data::OutStream<data::MemStorage, data::BytePacker> out(storage);
    out.Write(plat::uint32(0xfdfdfdfd));
    out.Write(plat::uint16(0xabab));
    out.Write(plat::uint16(0xcdcd));
  }

  plat::uint32 nGoodRead = 0;
  plat::uint32 nBadRead = 0;
  data::InStream<data::MemStorage, data::BytePacker> in(storage);
  in.Read(nGoodRead);

  SPTEST_CHECKASSERTS_BEGIN();
  in.Read(nBadRead);
  SPTEST_CHECKASSERTS_END();

  CHECK_EQUAL(0xfdfdfdfd, nGoodRead);

  CHECK_EQUAL(plat::uint32(0), nBadRead);
}

*/

}  // namespace secondpylon
}  // namespace data
}  // namespace test
