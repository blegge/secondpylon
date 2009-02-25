#ifndef SPDATA_MEMSTORAGE_H
#define SPDATA_MEMSTORAGE_H


/* This is a bootstrap/reference implementation of a stream memory storage implementation. This very is extremely inefficient for even moderate sized streams as it pushes data into a std::vector byte by byte. A more ideal version would operate operate on page chunks to reduce the cost of individual byte writes. A version like this could largely be inlined.

// @todo Compare performance to a paged based allocation, as this impacts the class API. Paged based access couldn't
//       return a pointer to the start of the buffer as it may span multiple non-contiguous pages.

// @todo Implement fixed size memory buffer storage for optimal throughput. Profile against the dynamic memory case to
//       determine if it is a useful avenue to explore as it impacts client requirements.

*/

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/plat/plat_compiler.h>
#include <secondpylon/diag/diag_assert.h>

#pragma warning(push)
#pragma warning(disable:4702)
#pragma warning(disable:4530) // Disable the 'exceptions used' warning due to the use of a standard container.
#include <vector>
#pragma warning(pop)

namespace secondpylon {
namespace data {

    class MemStorage
    {
    public:
        enum EUsage
        {
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

        // Adds bytes of data to the stream. Read can only be called when this object is locked
        // for writing. 
        void Write(plat::byte* data, plat::uint32 bytes);

        // Fills the passed in buffer with size bytes from storage. Read can only be called when this object is locked
        // for reading. Behavior is undefined when reading bytes reads beyond the end of storage.
        void Read(plat::byte* data, plat::uint32 bytes);

        // Advances the stream forward by bytes. Read can only be called when this object is locked for reading.
        // Behavior is undefined if advancing by bytes advances beyond the end of storage.
        void Advance(plat::uint32 bytes);

    private:
        EUsage m_Usage;
        plat::uint32 m_ReadOffset;
        std::vector<plat::byte> m_Storage;
    };


    //
    // Inline functions
    //

    SPPLAT_INLINE MemStorage::MemStorage() : 
        m_ReadOffset(0)
        , m_Usage(kUnused)
    {
    }

    SPPLAT_INLINE void MemStorage::SetUsage(EUsage currentUsage)
    {
        SPDIAG_ASSERT(currentUsage == kUnused || kUnused == m_Usage, "Storage going between two invalid states (%d->%d)", m_Usage, currentUsage);
        m_Usage = currentUsage; 
    }

    SPPLAT_INLINE void MemStorage::Advance(plat::uint32 bytes)
    { 
        SPDIAG_ASSERT(kRead == m_Usage, "Reading is only permitted when the memstorage usage is set to reading.");
        SPDIAG_ASSERT(m_ReadOffset+bytes < m_Storage.size(), "Advancing beyond the end of the storage buffer.");
        m_ReadOffset += bytes; 
    }

    SPPLAT_INLINE const plat::byte* MemStorage::GetData() const 
    { 
        return &m_Storage[0]; 
    }
    
    SPPLAT_INLINE plat::uint32 MemStorage::GetDataSize() const
    { 
        return m_Storage.size(); 
    }

}
}

#endif // SPDATA_MEMSTORAGE_H
