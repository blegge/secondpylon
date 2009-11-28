// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_DATA_DATA_MEMSTORAGE_H_
#define SECONDPYLON_DATA_DATA_MEMSTORAGE_H_

/* This is a bootstrap/reference implementation of a stream memory storage
    implementation. This very is extremely inefficient for even moderate sized
    streams as it pushes data into a std::vector byte by byte. A more ideal
    version would operate operate on page chunks to reduce the cost of
    individual byte writes. A version like this could largely be inlined.

// @todo Compare performance to a paged based allocation, as this impacts the
//      class API. Paged based access couldn't return a pointer to the start
//      of the buffer as it may span multiple non-contiguous pages.

// @todo Implement fixed size memory buffer storage for optimal throughput.
//      Profile against the dynamic memory case to
//      determine if it is a useful avenue to explore as it impacts client
//      requirements.

*/

#pragma warning(push)
#pragma warning(disable:4702)

// Disable the 'exceptions used' warning due to the use of a standard container.
#pragma warning(disable:4530)
#include <vector>
#pragma warning(pop)

#include "secondpylon/plat/plat_types.h"
#include "secondpylon/plat/plat_compiler.h"
#include "secondpylon/diag/diag_assert.h"

namespace secondpylon {
namespace data {

    class MemStorage {
    public:
        enum EUsage {
            kRead
            , kWrite
            , kUnused
        };

        MemStorage();
        MemStorage(const plat::byte* data, plat::uint32 dataSize);

        // Access to the raw underlying memory storage.
        const plat::byte* GetData() const;
        plat::uint32 GetDataSize() const;

        //
        // Stream API functions
        //
        void SetUsage(EUsage currentUsage);

        // Adds bytes of data to the stream. Read can only be called when this
        // object is locked for writing.
        void Write(plat::byte* data, plat::uint32 bytes);

        // Fills the passed in buffer with size bytes from storage. Read can
        // only be called when this object is locked for reading. Behavior is
        // undefined when reading bytes reads beyond the end of storage.
        void Read(plat::byte* data, plat::uint32 bytes);

        // Advances the stream forward by bytes. Read can only be called when
        // this object is locked for reading. Behavior is undefined if
        // advancing by bytes advances beyond the end of storage.
        void Advance(plat::uint32 bytes);

    private:
        EUsage Usage_;
        plat::uint32 ReadOffset_;
        std::vector<plat::byte> Storage_;
    };

}  // namespace data
}  // namespace secondpylon

#include "secondpylon/data/data_memstorage-inl.h"

#endif  // SECONDPYLON_DATA_DATA_MEMSTORAGE_H_
