// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_DATA_DATA_MEMSTORAGE_INL_H_
#define SECONDPYLON_DATA_DATA_MEMSTORAGE_INL_H_

namespace secondpylon {
namespace data {

SPPLAT_INLINE MemStorage::MemStorage()
  : read_offset_(0)
  , usage_(kUnused) {
}

SPPLAT_INLINE void MemStorage::SetUsage(EUsage currentUsage) {
  SPDIAG_ASSERT(currentUsage == kUnused || kUnused == usage_,
    "Storage going between two invalid states (%d->%d)"
    , usage_, currentUsage);
  usage_ = currentUsage;
}

SPPLAT_INLINE void MemStorage::Advance(plat::uint64 bytes) {
  SPDIAG_ASSERT(
  kRead == usage_,
  "Reading is only permitted when the memstorage usage is set to reading.");

  SPDIAG_ASSERT(read_offset_+bytes < storage_.size()
    , "Advancing beyond the end of the storage buffer.");

  read_offset_ += bytes;
}

SPPLAT_INLINE const plat::byte* MemStorage::GetData() const {
  return &storage_[0];
}

SPPLAT_INLINE size_t MemStorage::GetDataSize() const {
  return storage_.size();
}

}  // namespace data
}  // namespace secondpylon

#endif  // SECONDPYLON_DATA_DATA_MEMSTORAGE_INL_H_

