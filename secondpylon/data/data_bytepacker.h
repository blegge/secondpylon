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
        static void Read(TStorage* pStorage, T* pData) {
            pStorage->Read(reinterpret_cast<plat::byte*>(pData), sizeof(T));
        }

        template <typename T>
        static void Read(TStorage* pStorage, T* pData, size_t arrayLen) {
            pStorage->Read(
                reinterpret_cast<plat::byte*>(pData)
                , arrayLen*sizeof(T));
        }
    };

    template <typename TStorage>
    class BytePacker {
    public:
        template <typename T>
            static void Write(TStorage* pStorage, T data) {
            pStorage->Write(StrictCast<plat::byte*>(&data), sizeof(T));
        }

        template <typename T>
        static void Write(TStorage* pStorage, const T* data, size_t arrayLen) {
            pStorage->Write(StrictCast<plat::byte*>(data), arrayLen*sizeof(T));
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
