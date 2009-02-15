#ifndef SPDATA_BYTESWAPPACKER_H
#define SPDATA_BYTESWAPPACKER_H

#include <secondpylon/plat/plat_types.h>

namespace secondpylon {
namespace data {

struct SSwapUtil
{
    static plat::uint16 Swap16(plat::uint16 data)
    {
        return ((data & 0xff00) >> 8) 
            | ((data & 0x00ff) << 8);
    }

    static plat::uint32 Swap32(plat::uint32 data)
    {
        return (data & 0xff000000)    >> 24
            | (data & 0x00ff0000)  >> 8
            | (data & 0x0000ff00)  << 8
            | (data & 0x000000ff)  << 24;
    }
};


// This class is used as a template policy to stream interfaces. This class swaps the endianness when writing data.
// This can be useful when attempting to pack data to a native format.
template <typename TStorage>
class ByteSwapPacker
{
public:
    static void Write(TStorage& storage, plat::uint8 data) { storage.Write((plat::byte*)&data, sizeof(uint8)); }
    static void Write(TStorage& storage, plat::sint8 data) { storage.Write((plat::byte*)&data, sizeof(sint8)); }
    static void Write(TStorage& storage, plat::bool8 data) { storage.Write((plat::byte*)&data, sizeof(bool8)); }

    static void Write(TStorage& storage, plat::uint16 data) { Write16(storage, data); }
    static void Write(TStorage& storage, plat::sint16 data) { Write16(storage, StrictCast<plat::uint16>(data)); }

    static void Write(TStorage& storage, plat::uint32 data) { Write32(storage, data); }
    static void Write(TStorage& storage, plat::sint32 data) { Write32(storage, StrictCast<plat::uint32>(data)); }
    static void Write(TStorage& storage, plat::float32 data) { Write32(storage, StrictCast<plat::uint32>(data)); }

    template <typename T>
    static void Write(TStorage& storage, const T* data, size_t arrayLen)
    {
        storage.Write((plat::byte*)data, arrayLen*sizeof(T));
    }

private:
    static void Write16(TStorage& storage, plat::uint16 data)
    {
        plat::uint16 swapped = SSwapUtil::Swap16(data);
        storage.Write((plat::byte*)&swapped, 2);
    }

    static void Write32(TStorage& storage, plat::uint32 data)
    {
        plat::uint32 swapped = SSwapUtil::Swap32(data);
        storage.Write((plat::byte*)&swapped, 4);
    }
};


// This class is used as a template policy to stream interfaces. This class swaps the endianness on read. It can be
// useful when reading data produced in another endian. For example, data always written as little endian may need to
// be swapped on read for big endian platforms. This has more runtime cost than swapping on data write use of
// ByteSwapPacker is prefered.
template <typename TStorage>
class ByteSwapUnpacker
{
public: 
    static void Read(TStorage& storage, plat::uint8& data) { storage.Read((plat::byte*)&data, sizeof(uint8)); }
    static void Read(TStorage& storage, plat::sint8& data) { storage.Read((plat::byte*)&data, sizeof(sint8)); }
    static void Read(TStorage& storage, plat::bool8& data) { storage.Read((plat::byte*)&data, sizeof(bool8)); }

    static void Read(TStorage& storage, plat::uint16& data) { Read16(storage, data); }
    static void Read(TStorage& storage, plat::sint16& data) { Read16(storage, StrictCast<plat::uint16>(data)); }

    static void Read(TStorage& storage, plat::uint32& data) { Read32(storage, data); }
    static void Read(TStorage& storage, plat::sint32& data) { Read32(storage, StrictCast<plat::uint32>(data)); }
    static void Read(TStorage& storage, plat::float32& data) { Read32(storage, StrictCast<plat::uint32>(data)); }

    template <typename T>
    static void Read(TStorage& storage, const T* data, size_t arrayLen)
    {
        storage.Read((plat::byte*)data, arrayLen*sizeof(T));
    }

private:
    static void Read16(TStorage& storage, plat::uint16& data)
    {
        plat::uint16 raw = 0;
        storage.Read((plat::byte*)&raw, 2);
        data = SSwapUtil::Swap16(raw);
    }

    static void Read32(TStorage& storage, plat::uint32& data)
    {
        plat::uint32 raw;
        storage.Read((plat::byte*)&raw, 4);
        data = SSwapUtil::Swap32(raw);
    }
};

template <typename TStorage>
struct SByteSwapPacker
{
    typedef ByteSwapPacker<TStorage> TPacker;
    typedef ByteSwapUnpacker<TStorage> TUnpacker;
};

}
}

#endif // SPDATA_BYTESWAPPACKER_H
