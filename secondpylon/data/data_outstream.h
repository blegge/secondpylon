#ifndef SPDATA_OUTSTREAM_H
#define SPDATA_OUTSTREAM_H

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/plat/plat_crt.h>
#include <secondpylon/data/data_bytepacker.h>

namespace secondpylon {
namespace data {

    template <typename TStorage, template <typename> class Packer = SBytePacker >
    class OutStream
    {
        SPUNCOPYABLE(OutStream);
        typedef typename Packer<typename TStorage>::TPacker TPacker;

    public:
        OutStream(TStorage& storage);
        ~OutStream();

        void Write(plat::uint8 i) { TPacker::Write(m_Storage, i); }
        void Write(plat::uint16 i) { TPacker::Write(m_Storage, i); }
        void Write(plat::uint32 i) { TPacker::Write(m_Storage, i); }

        void Write(plat::sint8 i) { TPacker::Write(m_Storage, i); }
        void Write(plat::sint16 i) { TPacker::Write(m_Storage, i); }
        void Write(plat::sint32 i) { TPacker::Write(m_Storage, i); }

        void Write(plat::float32 f) { TPacker::Write(m_Storage, f); }

        void Write(plat::bool8 b) { TPacker::Write(m_Storage, b); }

        void Write(const char* pszString);

    private:
        TStorage& m_Storage;
    };

    //
    // Inline functions
    //

    template <typename TStorage, template <typename> class  Packer>
    OutStream<TStorage, Packer>::OutStream(TStorage& storage) : m_Storage(storage) 
    { 
        storage.SetUsage(TStorage::kWrite); 
    }
    
    template <typename TStorage, template <typename> class  Packer>
    OutStream<TStorage, Packer>::~OutStream() 
    { 
        m_Storage.SetUsage(TStorage::kUnused); 
    }

    template <typename TStorage, template <typename> class  Packer>
    void OutStream<TStorage, Packer>::Write(const char* pszString) 
    {
        plat::uint32 len = strlen(pszString);
        Write(len);
        TPacker::Write(m_Storage, pszString, len);
    }

}
}

#endif // SPDATA_OUTSTREAM_H
