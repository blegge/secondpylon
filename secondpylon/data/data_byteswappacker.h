// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_DATA_DATA_BYTESWAPPACKER_H_
#define SECONDPYLON_DATA_DATA_BYTESWAPPACKER_H_

#include "secondpylon/plat/plat_types.h"

namespace secondpylon {
namespace data {

struct SSwapUtil {
    static plat::uint16 Swap16(plat::uint16 data) {
        return ((data & 0xff00) >> 8)
            | ((data & 0x00ff) << 8);
    }

    static plat::uint32 Swap32(plat::uint32 data) {
        return (data & 0xff000000)    >> 24
            | (data & 0x00ff0000)  >> 8
            | (data & 0x0000ff00)  << 8
            | (data & 0x000000ff)  << 24;
    }
};


// This class is used as a template policy to stream interfaces. This class
// swaps the endianness when writing data. This can be useful when attempting to
// pack data to a native format.
template <typename TStorage>
class ByteSwapPacker {
public:
    static void Write(TStorage* pStorage, plat::uint8 data) {
        pStorage->Write(StrictCast<plat::byte*>(&data), sizeof(uint8));
    }

    static void Write(TStorage* pStorage, plat::sint8 data) {
        pStorage->Write(StrictCast<plat::byte*>(&data), sizeof(sint8));
    }

    static void Write(TStorage* pStorage, plat::bool8 data) {
        pStorage->Write(StrictCast<plat::byte*>(&data), sizeof(bool8));
    }

    static void Write(TStorage* pStorage, plat::uint16 data) {
        Write16(pStorage, data);
    }

    static void Write(TStorage* pStorage, plat::sint16 data) {
        Write16(pStorage, StrictCast<plat::uint16>(data));
    }

    static void Write(TStorage* pStorage, plat::uint32 data) {
        Write32(pStorage, data);
    }

    static void Write(TStorage* pStorage, plat::sint32 data) {
        Write32(pStorage, StrictCast<plat::uint32>(data));
    }

    static void Write(TStorage* pStorage, plat::float32 data) {
        Write32(pStorage, StrictCast<plat::uint32>(data));
    }

    template <typename T>
    static void Write(TStorage* pStorage, T* data, size_t arrayLen) {
        pStorage->Write(StrictCast<plat::byte*>(data), arrayLen*sizeof(T));
    }

private:
    static void Write16(TStorage* pStorage, plat::uint16 data) {
        plat::uint16 swapped = SSwapUtil::Swap16(data);
        pStorage->Write(StrictCast<plat::byte*>(&swapped), 2);
    }

    static void Write32(TStorage* pStorage, plat::uint32 data) {
        plat::uint32 swapped = SSwapUtil::Swap32(data);
        pStorage->Write(StrictCast<plat::byte*>(&swapped), 4);
    }
};


// This class is used as a template policy to stream interfaces. This class
// swaps the endianness on read. It can be useful when reading data produced in
// another endian. For example, data always written as little endian may need to
// be swapped on read for big endian platforms. This has more runtime cost than
// swapping on data write use of ByteSwapPacker is prefered.
template <typename TStorage>
class ByteSwapUnpacker {
public:
    static void Read(TStorage* pStorage, plat::uint8* pData) {
        pStorage->Read(pData, sizeof(uint8));
    }

    static void Read(TStorage* pStorage, plat::sint8* pData) {
        pStorage->Read(pData, sizeof(sint8));
    }

    static void Read(TStorage* pStorage, plat::bool8* pData) {
        pStorage->Read(pData, sizeof(bool8));
    }

    static void Read(TStorage* pStorage, plat::uint16* pData) {
        Read16(pStorage, pData);
    }

    static void Read(TStorage* pStorage, plat::sint16* pData) {
        Read16(pStorage, pData);
    }

    static void Read(TStorage* pStorage, plat::uint32* pData) {
        Read32(pStorage, pData);
    }

    static void Read(TStorage* pStorage, plat::sint32* pData) {
        Read32(pStorage, pData);
    }

    static void Read(TStorage* pStorage, plat::float32* pData) {
        uint32 nTemp;
        Read32(storage, &nTemp);
        *pData = StrictCast<float>(nTemp);
    }

    template <typename T>
    static void Read(TStorage* pStorage, const T* data, size_t arrayLen) {
        pStorage->Read(StrictCast<plat::byte*>(data), arrayLen*sizeof(T));
    }

private:
    static void Read16(TStorage* pStorage, plat::uint16* pData) {
        plat::uint16 raw = 0;
        pStorage->Read(reinterpret_cast<plat::byte*>(&raw), 2);
        *pData = SSwapUtil::Swap16(raw);
    }

    static void Read32(TStorage* pStorage, plat::uint32* pData) {
        plat::uint32 raw;
        pStorage->Read(reinterpret_cast<plat::byte*>(&raw), 4);
        *pData = SSwapUtil::Swap32(raw);
    }
};

template <typename TStorage>
struct SByteSwapPacker {
    typedef ByteSwapPacker<TStorage> TPacker;
    typedef ByteSwapUnpacker<TStorage> TUnpacker;
};

}  // namespace data
}  // namespace secondpylon

#endif  // SECONDPYLON_DATA_DATA_BYTESWAPPACKER_H_
