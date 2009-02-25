#include <secondpylon/data/data_memstorage.h>

namespace secondpylon {
namespace data {

MemStorage::MemStorage(const plat::byte* data, plat::uint32 dataSize) : 
    m_ReadOffset(0)
    , m_Usage(kUnused)
{
    m_Storage.reserve(dataSize);
    for (plat::uint32 i = 0; i < dataSize; ++i)
    {
        m_Storage.push_back(data[i]);
    }
}

void MemStorage::Write(plat::byte* data, plat::uint32 size) 
{
    SPDIAG_ASSERT(kWrite == m_Usage, "memstorage usage must be write to call Write.");

    for (plat::uint32 i = 0; i < size; ++i)
    {
        m_Storage.push_back(data[i]);
    }
}


void MemStorage::Read(plat::byte* data, plat::uint32 size) 
{
    SPDIAG_ASSERT(kRead == m_Usage, "memstorage usage must be read to call Read");

    if (m_ReadOffset + size <= m_Storage.size())
    {
        for (plat::uint32 i = 0; i < size; ++i)
        {
            data[i] = m_Storage[m_ReadOffset++];
        }
    }
    else
    {
        SPDIAG_ERROR("Reading beyond the end of storage.");

        m_ReadOffset = m_Storage.size();
        for (plat::uint32 i = 0; i < size; ++i)
        {
            data[i] = 0;
        }
    }
}

}
}
