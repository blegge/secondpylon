#ifndef SPDIAG_LOG
#define SPDIAG_LOG

#include <secondpylon/plat/plat_types.h>

#pragma warning(disable:4530) // Disable exception warnings
#pragma warning(disable:4702)
#include <list>

#pragma warning(disable:4511)
#pragma warning(disable:4512)

namespace secondpylon {
namespace diag {

    // Trait class to flag a class as uncopyable. Ideally classes could aggregate this instead of deriving from it.
    // Unfortunately, aggregation has a cost as it has to be possible to take the address of this object even though it
    // doesn't have any data.
    class Uncopyable
    {
    public:
        Uncopyable() {}

    private:
        Uncopyable(Uncopyable&);
        Uncopyable& operator=(Uncopyable&);
    };

    class ILogListener : public Uncopyable
    {
    public:
        virtual ~ILogListener() = 0 {}
        virtual void OnMessage(const char* message) = 0;
    };

    class Log
    {
    public:
        void AddListener(ILogListener&);
        void RemoveListener(ILogListener&);

        void Message(const char* message);

    private:
        std::list<ILogListener*> m_ListenerList;
    };

    // By default, enabIf there is no explicitly configured behavior, enable the logging system by default.
    #ifndef RSDIAG_ENABLE_LOG
        #define RSDIAG_ENABLE_LOG 1
    #endif

    #if RSDIAG_ENABLE_LOG
        #define RSDIAG_LOG(log, message) log.Message(message);
    #else
        #define RSDIAG_LOG(log, message)
    #endif

}
}

#endif // SPDIAG_LOG
