// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_DIAG_DIAG_LOG_H_
#define SECONDPYLON_DIAG_DIAG_LOG_H_

#pragma warning(push)
#pragma warning(disable:4530)  // Disable exception warnings
#pragma warning(disable:4702)
#include <list>
#pragma warning(pop)

#include "secondpylon/plat/plat_crt.h"

namespace secondpylon {
namespace diag {

  class LogListenerInterface {
    SPUNCOPYABLE(LogListenerInterface);

  public:
    LogListenerInterface() {}
    virtual ~LogListenerInterface() = 0 {}
    virtual void OnMessage(const char* message) = 0;
  };

  class Log {
  public:
    void AddListener(LogListenerInterface* listener);
    void RemoveListener(LogListenerInterface* listener);

    void Message(const char* message);

  private:
    std::list<LogListenerInterface*> listener_list_;
  };

  // Logging is enabled by default if there is the user does not explicitly
  // configure logging.
  #ifndef RSDIAG_ENABLE_LOG
    #define RSDIAG_ENABLE_LOG 1
  #endif

  #if RSDIAG_ENABLE_LOG
    #define RSDIAG_LOG(log, message) log.Message(message);
  #else
    #define RSDIAG_LOG(log, message)
  #endif

}  // namespace diag
}  // namespace secondpylon

#endif  // SECONDPYLON_DIAG_DIAG_LOG_H_
