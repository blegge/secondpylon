#ifndef SPDATA_BYTEPACKER_H
#define SPDATA_BYTEPACKER_H

#include <secondpylon/plat/plat_types.h>

namespace secondpylon {
namespace data {

    template <typename TStorage>
    class ByteUnpacker
    {
    public:
        template <typename T>
        static void Read(TStorage& storage, T& data)
        {
            storage.Read((plat::byte*)&data, sizeof(T));
        }

        template <typename T>
        static void Read(TStorage& storage, const T* data, size_t arrayLen)
        {
            storage.Read((plat::byte*)data, arrayLen*sizeof(T));
        }
    };

    template <typename TStorage>
    class BytePacker
    {
    public:
        template <typename T>
            static void Write(TStorage& storage, T data)
        {
            storage.Write((plat::byte*)&data, sizeof(T));
        }

        template <typename T>
            static void Write(TStorage& storage, const T* data, size_t arrayLen)
        {
            storage.Write((plat::byte*)data, arrayLen*sizeof(T));
        }
    };

    template <typename TStorage>
    struct SBytePacker
    {
        typedef BytePacker<TStorage> TPacker;
        typedef ByteUnpacker<TStorage> TUnpacker;
    };
}
}

#endif // SPDATA_BYTEPACKER_H
