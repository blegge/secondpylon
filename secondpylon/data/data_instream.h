// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_DATA_DATA_INSTREAM_H_
#define SECONDPYLON_DATA_DATA_INSTREAM_H_

// Note that InStream does not contain a technique for arbitrary seeking or
// backward seeking. This is intentional this operation is problematic for some
// storage types such as compressed data or data on a disc that is not designed
// for random seeks.
//
// @todo Add a method to insure that reads and writes are synced. This may be
//      as simple as an accumulator we optionally write to the stream in
//      particular configurations that tracks writes by type.

#include "secondpylon/plat/plat_crt.h"
#include "secondpylon/plat/plat_types.h"
#include "secondpylon/plat/plat_compiler.h"
#include "secondpylon/data/data_bytepacker.h"
#include "secondpylon/diag/diag_assert.h"

namespace secondpylon {
namespace data {

    // This class loads data from the provided storage using the specified
    // unpacker. The syntax used to specify the DefaultUnpacker may be a bit
    // unfamiliar - it is a 'template template parameter'. The expanded end
    // user version would look like:
    // 'InStream<MemStorage, EndianAdapter<MemStorage> >'.
    // Using template template syntax, we can eliminate the redundant
    // MemStorage specification and simplify this to:
    // 'InStream<MemStorage, EndianAdapter>'
    template <
        typename TStorage
        , template <typename> class Packer = SBytePacker
    >
    class InStream {
        SPUNCOPYABLE(InStream);
        typedef typename Packer<typename TStorage>::TUnpacker TUnpacker;

    public:
        explicit InStream(TStorage* storage);
        ~InStream();

        void Read(plat::uint8* i) { TUnpacker::Read(&m_Storage, i); }
        void Read(plat::uint16* i) { TUnpacker::Read(&m_Storage, i); }
        void Read(plat::uint32* i) { TUnpacker::Read(&m_Storage, i); }

        void Read(plat::sint8* i) { TUnpacker::Read(&m_Storage, i); }
        void Read(plat::sint16* i) { TUnpacker::Read(&m_Storage, i); }
        void Read(plat::sint32* i) { TUnpacker::Read(&m_Storage, i); }

        void Read(plat::float32* f) { TUnpacker::Read(&m_Storage, f); }
        void Read(plat::bool8* b) { TUnpacker::Read(&m_Storage, b); }

        void Read(char* pszString, plat::uint32 capacity);

    private:
        TStorage& m_Storage;
    };

    //
    // Inline functions
    //

    template <typename TStorage, template <typename> class Unpacker >
    InStream<TStorage, Unpacker>::InStream(TStorage* storage) :
        m_Storage(*storage) {
        m_Storage.SetUsage(TStorage::kRead);
    }

    template <typename TStorage, template <typename> class Unpacker >
    InStream<TStorage, Unpacker>::~InStream() {
        m_Storage.SetUsage(TStorage::kUnused);
    }

    template <typename TStorage, template <typename> class Unpacker >
    void InStream<TStorage, Unpacker>::Read(
        char* pszString
        , plat::uint32 capacity) {
        plat::uint32 size = 0;
        Read(&size);

        if (size >= capacity) {
            // The buffer is too small. This should probably be considered a
            // fatal error as this would have completely unpredictable results.
            // Skip the string to avoid misaligning our next read.
            m_Storage.Advance(sizeof(pszString[0])*size);
            SPDIAG_ERROR("Attempting to read beyond the end of stream");
        } else {
            TUnpacker::Read(&m_Storage, pszString, size);
            pszString[size] = '\0';
        }
    }

}  // namespace data
}  // namespace secondpylon

#endif  // SECONDPYLON_DATA_DATA_INSTREAM_H_
