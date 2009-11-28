// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_DATA_DATA_MEMSTORAGE_INL_H_
#define SECONDPYLON_DATA_DATA_MEMSTORAGE_INL_H_

namespace secondpylon {
namespace data {

SPPLAT_INLINE MemStorage::MemStorage()
    : ReadOffset_(0)
    , Usage_(kUnused) {
}

SPPLAT_INLINE void MemStorage::SetUsage(EUsage currentUsage) {
    SPDIAG_ASSERT(currentUsage == kUnused || kUnused == Usage_,
        "Storage going between two invalid states (%d->%d)"
        , Usage_, currentUsage);
    Usage_ = currentUsage;
}

SPPLAT_INLINE void MemStorage::Advance(plat::uint32 bytes) {
  SPDIAG_ASSERT(
    kRead == Usage_,
    "Reading is only permitted when the memstorage usage is set to reading.");

  SPDIAG_ASSERT(ReadOffset_+bytes < Storage_.size()
      , "Advancing beyond the end of the storage buffer.");

  ReadOffset_ += bytes;
}

SPPLAT_INLINE const plat::byte* MemStorage::GetData() const {
    return &Storage_[0];
}

SPPLAT_INLINE plat::uint32 MemStorage::GetDataSize() const {
    return Storage_.size();
}

}  // namespace data
}  // namespace secondpylon

#endif  // SECONDPYLON_DATA_DATA_MEMSTORAGE_INL_H_

