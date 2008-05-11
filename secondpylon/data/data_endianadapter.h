#ifndef SPDATA_ENDIANADAPTER_H
#define SPDATA_ENDIANADAPTER_H

#include <secondpylon/plat/plat_types.h>

namespace secondpylon {
namespace data {

// This class is used as a template policy to stream interfaces. This class swaps the endianness when writing data.
// This can be useful when attempting to pack data to a native format.
template <typename TStorage>
class EndianAdapter
{
public:
    static void Write(TStorage& storage, plat::uint8 data) { storage.Write((plat::byte*)&data, sizeof(uint8)); }
    static void Write(TStorage& storage, plat::sint8 data) { storage.Write((plat::byte*)&data, sizeof(sint8)); }
    static void Write(TStorage& storage, plat::bool8 data) { storage.Write((plat::byte*)&data, sizeof(bool8)); }

    static void Write(TStorage& storage, plat::uint16 data) { Write16(storage, *(plat::uint16*)&data); }
    static void Write(TStorage& storage, plat::sint16 data) { Write16(storage, *(plat::uint16*)&data); }

    static void Write(TStorage& storage, plat::uint32 data) { Write32(storage, *(plat::uint32*)&data); }
    static void Write(TStorage& storage, plat::sint32 data) { Write32(storage, *(plat::uint32*)&data); }
    static void Write(TStorage& storage, plat::float32 data) { Write32(storage, *(plat::uint32*)&data); }

    template <typename T>
    static void Write(TStorage& storage, const T* data, size_t arrayLen)
    {
        storage.Write((plat::byte*)data, arrayLen*sizeof(T));
    }

private:
    static void Write16(TStorage& storage, plat::uint16 data)
    {
        plat::uint16 swapped = ((data & 0xff00) >> 8) | ((data & 0x00ff) << 8);
        storage.Write((plat::byte*)&swapped, 2);
    }

    static void Write32(TStorage& storage, plat::uint32 data)
    {
        plat::uint32 swapped = (data & 0xff000000) >> 24
            | (data & 0x00ff0000) >> 8
            | (data & 0x0000ff00) << 8
            | (data & 0x000000ff) << 24;

        storage.Write((plat::byte*)&swapped, 4);
    }
};

}
}

#endif // SPDATA_ENDIANADAPTER_H
