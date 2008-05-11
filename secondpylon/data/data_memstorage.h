#ifndef SPDATA_MEMSTORAGE_H
#define SPDATA_MEMSTORAGE_H

/* This is a bootstrap/reference implementation of a stream memory storage implementation. This very is extremely inefficient for even moderate sized streams as it pushes data into a std::vector byte by byte. A more ideal version would operate operate on page chunks to reduce the cost of individual byte writes. A version like this could largely be inlined.
*/

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/plat/plat_compiler.h>
#include <secondpylon/diag/diag_assert.h>

#pragma warning(push)
#pragma warning(disable:4702)
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

        void SetUsage(EUsage currentUsage);
        EUsage GetUsage() const;

        // Read functions
        void Read(plat::byte* data, plat::uint32 size);
        void Advance(plat::uint32 bytes);

        // Write functions
        void Write(plat::byte* data, plat::uint32 size);

        // Access to the raw underlying memory storage.
        const plat::byte* GetData() const;
        plat::uint32 GetDataSize() const;

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
        SPDIAG_ASSERT(currentUsage == kUnused || kUnused == m_Usage);
        m_Usage = currentUsage; 
    }

    SPPLAT_INLINE MemStorage::EUsage MemStorage::GetUsage() const 
    { 
        return m_Usage; 
    }

    SPPLAT_INLINE void MemStorage::Advance(plat::uint32 bytes)
    { 
        SPDIAG_ASSERT(kRead == m_Usage);
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
