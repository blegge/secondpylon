#ifndef SPDIAG_LOG
#define SPDIAG_LOG

#include <secondpylon/plat/plat_crt.h>

#pragma warning(push)
#pragma warning(disable:4530) // Disable exception warnings
#pragma warning(disable:4702)
#include <list>

//#pragma warning(disable:4511)
//#pragma warning(disable:4512)
#pragma warning(pop)

namespace secondpylon {
namespace diag {

    class ILogListener
    {
        SPUNCOPYABLE(ILogListener);

    public:
        ILogListener() {}
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

    // Logging is enabled by default if there is the user does not explicitly configure logging.
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
