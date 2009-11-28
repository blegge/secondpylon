#ifndef SECONDPYLON_DATA_DATA_STREAM_H_
#define SECONDPYLON_DATA_DATA_STREAM_H_

/*
#include "data_instream.h"
#include "data_outstream.h"

namespace secondpylon {
namespace data {

class Stream
{
  struct StreamTypeMask
  {
    enum Enum
    {
      kWriteBool8    = 1<<0
      , kWriteUInt8    = 1<<1
      , kWriteUInt16  = 1<<2
      , kWriteUInt32  = 1<<3
      , kWriteSInt8    = 1<<4
      , kWriteSInt16  = 1<<5
      , kWriteSInt32  = 1<<6
      , kWriteFloat32   = 1<<7
    };
  };

  struct VerificationPolicy
  {
    static void Read(InStream& stream, StreamTypeMask::Enum e)
    {
    }

    static void Write(InStream& stream, StreamTypeMask::Enum e)
    {
    }
  };

public:
  //
  //
  //
  static void Read(InStream& stream, plat::uint8& i)
  {
    VerificationPolicy::Read(stream, kWriteBool8);
    stream.Read(StrictCast<plat::byte*>(&i), sizeof(i));
  }


  //
  //
  //

};

}
}
*/

#endif   // SECONDPYLON_DATA_DATA_STREAM_H_
