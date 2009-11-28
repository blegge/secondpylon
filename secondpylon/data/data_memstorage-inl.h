// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_DATA_DATA_MEMSTORAGE_INL_H_
#define SECONDPYLON_DATA_DATA_MEMSTORAGE_INL_H_

namespace secondpylon {
namespace data {

SPPLAT_INLINE MemStorage::MemStorage()
    : m_ReadOffset(0)
    , m_Usage(kUnused) {
}

SPPLAT_INLINE void MemStorage::SetUsage(EUsage currentUsage) {
    SPDIAG_ASSERT(currentUsage == kUnused || kUnused == m_Usage,
        "Storage going between two invalid states (%d->%d)"
        , m_Usage, currentUsage);
    m_Usage = currentUsage;
}

SPPLAT_INLINE void MemStorage::Advance(plat::uint32 bytes) {
  SPDIAG_ASSERT(
    kRead == m_Usage,
    "Reading is only permitted when the memstorage usage is set to reading.");

  SPDIAG_ASSERT(m_ReadOffset+bytes < m_Storage.size()
      , "Advancing beyond the end of the storage buffer.");

  m_ReadOffset += bytes;
}

SPPLAT_INLINE const plat::byte* MemStorage::GetData() const {
    return &m_Storage[0];
}

SPPLAT_INLINE plat::uint32 MemStorage::GetDataSize() const {
    return m_Storage.size();
}

}  // namespace data
}  // namespace secondpylon

#endif  // SECONDPYLON_DATA_DATA_MEMSTORAGE_INL_H_

