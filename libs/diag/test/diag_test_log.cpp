#include <secondpylon/diag/diag_log.h>
#include <secondpylon/plat/plat_compiler.h>
#include <unittest++/src/UnitTest++.h>

using namespace secondpylon;

namespace 
{
    class StoringLogListener : public diag::ILogListener
    {
        SPUNCOPYABLE(StoringLogListener);

        enum { kStorageSize = 80 };

    public:
        StoringLogListener()
        {
            m_Message[0] = '\0';
        }

        virtual void OnMessage(const char* message)
        {
            strncpy(m_Message, message, kStorageSize);
            m_Message[kStorageSize-1] = '\0';
        }

        const char* GetMessage() const { return m_Message; }
    private:
        char m_Message[kStorageSize];
    };
}

TEST(LogAddListener)
{
    const char* msg = "test";

    diag::Log testLog;
    StoringLogListener listener;
    testLog.AddListener(listener);
    testLog.Message(msg);
    testLog.RemoveListener(listener);

    CHECK_EQUAL(msg, listener.GetMessage());
}

TEST(LogLogMessage)
{
    const char* msg = "test";

    diag::Log testLog;
    StoringLogListener listener;
    testLog.AddListener(listener);
    RSDIAG_LOG(testLog, msg);
    testLog.RemoveListener(listener);

    CHECK_EQUAL(msg, listener.GetMessage());
}
