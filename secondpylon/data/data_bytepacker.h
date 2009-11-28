// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_DATA_DATA_BYTEPACKER_H_
#define SECONDPYLON_DATA_DATA_BYTEPACKER_H_

#include "secondpylon/plat/plat_types.h"

namespace secondpylon {
namespace data {

    template <typename TStorage>
    class ByteUnpacker {
    public:
        template <typename T>
        static void Read(TStorage* storage, T* data) {
            storage->Read(reinterpret_cast<plat::byte*>(data), sizeof(T));
        }

        template <typename T>
        static void Read(TStorage* storage, T* data, size_t array_length) {
            storage->Read(
                reinterpret_cast<plat::byte*>(data)
                , array_length*sizeof(T));
        }
    };

    template <typename TStorage>
    class BytePacker {
    public:
        template <typename T>
            static void Write(TStorage* storage, T data) {
            storage->Write(StrictCast<plat::byte*>(&data), sizeof(T));
        }

        template <typename T>
        static void Write(TStorage* storage, const T* data, size_t array_length) {
            storage->Write(StrictCast<plat::byte*>(data), array_length*sizeof(T));
        }
    };

    template <typename TStorage>
    struct SBytePacker {
        typedef BytePacker<TStorage> TPacker;
        typedef ByteUnpacker<TStorage> TUnpacker;
    };

}  // namespace data
}  // namespace secondpylon

#endif  // SECONDPYLON_DATA_DATA_BYTEPACKER_H_
