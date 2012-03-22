// Copyright 2009 Brian Legge

#include "secondpylon/data/data_memstorage.h"

namespace secondpylon {
namespace data {

MemStorage::MemStorage(const plat::byte* data, plat::uint64 dataSize)
  : read_offset_(0)
  , usage_(kUnused) {
  storage_.reserve((plat::uint32)dataSize);
  for (plat::uint32 element = 0; element < dataSize; ++element) {
    storage_.push_back(data[element]);
  }
}

void MemStorage::Write(plat::byte* data, plat::uint64 size) {
  SPDIAG_ASSERT(kWrite == usage_,
    "memstorage usage must be write to call Write.");

  for (plat::uint32 element = 0; element < size; ++element) {
    storage_.push_back(data[element]);
  }
}

void MemStorage::Read(plat::byte* data, plat::uint64 size) {
  SPDIAG_ASSERT(kRead == usage_,
    "memstorage usage must be read to call Read");

  if (read_offset_ + size <= storage_.size()) {
    for (plat::uint64 element = 0; element < size; ++element) {
      data[element] = storage_[(plat::uint32)(read_offset_++)];
    }
  } else {
    SPDIAG_ERROR("Reading beyond the end of storage.");

    read_offset_ = storage_.size();
    for (plat::uint32 element = 0; element < size; ++element) {
      data[element] = 0;
    }
  }
}

}  // namespace data
}  // namespace secondpylon
