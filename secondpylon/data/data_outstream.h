// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_DATA_DATA_OUTSTREAM_H_
#define SECONDPYLON_DATA_DATA_OUTSTREAM_H_

#include "secondpylon/plat/plat_types.h"
#include "secondpylon/plat/plat_crt.h"
#include "secondpylon/data/data_bytepacker.h"

namespace secondpylon {
namespace data {

    template <
        typename TStorage
        , template <typename> class Packer = SBytePacker >
    class OutStream {
        SPUNCOPYABLE(OutStream);
        typedef typename Packer<typename TStorage>::TPacker TPacker;

    public:
        explicit OutStream(TStorage* storage);

        ~OutStream();

        void Write(plat::uint8 i) { TPacker::Write(&Storage_, i); }
        void Write(plat::uint16 i) { TPacker::Write(&Storage_, i); }
        void Write(plat::uint32 i) { TPacker::Write(&Storage_, i); }

        void Write(plat::sint8 i) { TPacker::Write(&Storage_, i); }
        void Write(plat::sint16 i) { TPacker::Write(&Storage_, i); }
        void Write(plat::sint32 i) { TPacker::Write(&Storage_, i); }

        void Write(plat::float32 f) { TPacker::Write(&Storage_, f); }

        void Write(plat::bool8 b) { TPacker::Write(&Storage_, b); }

        void Write(const char* pszString);

    private:
        TStorage& Storage_;
    };

    //
    // Inline functions
    //

    template <typename TStorage, template <typename> class  Packer>
    OutStream<TStorage, Packer>::OutStream(TStorage* storage)
        : Storage_(*storage)  {
        Storage_.SetUsage(TStorage::kWrite);
    }

    template <typename TStorage, template <typename> class  Packer>
    OutStream<TStorage, Packer>::~OutStream() {
        Storage_.SetUsage(TStorage::kUnused);
    }

    template <typename TStorage, template <typename> class  Packer>
    void OutStream<TStorage, Packer>::Write(const char* pszString) {
        plat::uint32 len = strlen(pszString);
        Write(len);
        TPacker::Write(&Storage_, pszString, len);
    }

}  // namespace data
}  // namespace secondpylon

#endif  // SECONDPYLON_DATA_DATA_OUTSTREAM_H_
