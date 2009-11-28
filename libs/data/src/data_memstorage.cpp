// Copyright 2009 Brian Legge

#include "secondpylon/data/data_memstorage.h"

namespace secondpylon {
namespace data {

MemStorage::MemStorage(const plat::byte* data, plat::uint32 dataSize)
    : ReadOffset_(0)
    , Usage_(kUnused) {
    Storage_.reserve(dataSize);
    for (plat::uint32 i = 0; i < dataSize; ++i) {
        Storage_.push_back(data[i]);
    }
}

void MemStorage::Write(plat::byte* data, plat::uint32 size) {
    SPDIAG_ASSERT(kWrite == Usage_,
        "memstorage usage must be write to call Write.");

    for (plat::uint32 i = 0; i < size; ++i) {
        Storage_.push_back(data[i]);
    }
}

void MemStorage::Read(plat::byte* data, plat::uint32 size) {
    SPDIAG_ASSERT(kRead == Usage_,
        "memstorage usage must be read to call Read");

    if (ReadOffset_ + size <= Storage_.size()) {
        for (plat::uint32 i = 0; i < size; ++i) {
            data[i] = Storage_[ReadOffset_++];
        }
    } else {
        SPDIAG_ERROR("Reading beyond the end of storage.");

        ReadOffset_ = Storage_.size();
        for (plat::uint32 i = 0; i < size; ++i) {
            data[i] = 0;
        }
    }
}

}  // namespace data
}  // namespace secondpylon
