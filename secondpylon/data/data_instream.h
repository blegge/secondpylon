#ifndef SPDATA_INSTREAM_H
#define SPDATA_INSTREAM_H

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/plat/plat_compiler.h>

namespace secondpylon {
namespace data {
    
    template <typename TStorage>
    class DefaultUnpacker
    {
    public:
        template <typename T>
        static void Read(TStorage& storage, T& data)
        {
            storage.Read((plat::byte*)&data, sizeof(T));
        }

        template <typename T>
        static void Read(TStorage& storage, const T* data, size_t arrayLen)
        {
            storage.Read((plat::byte*)data, arrayLen*sizeof(T));
        }
    };

    // This class loads data from the provided storage using the specified unpacker. The syntax used to specify the
    // DefaultUnpacker may be a bit unfamiliar - it is a 'template template parameter'. The expanded end user versiou
    // would look like 'InStream<MemStorage, EndianAdapter<MemStorage> >'. Using template template syntax, we can
    // eliminate the redundant MemStorage specification and simplify this to 'InStream<MemStorage, EndianAdapter>'
    template <typename TStorage, template <typename> class  Unpacker = DefaultUnpacker >
    class InStream
    {
        SPPLAT_UNCOPYABLE(InStream);
        typedef Unpacker<typename TStorage> TUnpacker;

    public:
        InStream(TStorage& storage);
        ~InStream();

        void Read(plat::uint8& i) { TUnpacker::Read(m_Storage, i); }
        void Read(plat::uint16& i) { TUnpacker::Read(m_Storage, i); }
        void Read(plat::uint32& i) { TUnpacker::Read(m_Storage, i); }

        void Read(plat::sint8& i) { TUnpacker::Read(m_Storage, i); }
        void Read(plat::sint16& i) { TUnpacker::Read(m_Storage, i); }
        void Read(plat::sint32& i) { TUnpacker::Read(m_Storage, i); }

        void Read(plat::float32& f) { TUnpacker::Read(m_Storage, f); }
        void Read(plat::bool8& b) { TUnpacker::Read(m_Storage, b); }

        void Read(char* pszString, plat::uint32 capacity);

    private:
        TStorage& m_Storage;
    };

    //
    // Inline functions
    //

    template <typename TStorage, template <typename> class Unpacker >
    InStream<TStorage, Unpacker>::InStream(TStorage& storage) : 
        m_Storage(storage)
    {
        storage.SetUsage(TStorage::kRead);
    }

    template <typename TStorage, template <typename> class Unpacker >
    InStream<TStorage, Unpacker>::~InStream() 
    { 
        m_Storage.SetUsage(TStorage::kUnused); 
    }

    template <typename TStorage, template <typename> class Unpacker >
    void InStream<TStorage, Unpacker>::Read(char* pszString, plat::uint32 capacity)
    { 
        plat::uint32 size = 0;
        Read(size);

        if (size >= capacity)
        {
            // Skip the string to avoid misaligning our next read
            m_Storage.Advance(sizeof(char)*size);
            // TODO: issue an error? Policy?
        }
        else
        {
            TUnpacker::Read(m_Storage, pszString, size);
            pszString[size] = '\0';
        }
    }

}
}

#endif // SPDATA_INSTREAM_H
