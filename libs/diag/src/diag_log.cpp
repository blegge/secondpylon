// Copyright 2009 Brian Legge

#include "secondpylon/diag/diag_log.h"

namespace secondpylon {
namespace diag {

    void Log::AddListener(ILogListener* listener) {
        ListenerList_.push_back(listener);
    }

    void Log::RemoveListener(ILogListener* listener) {
        ListenerList_.remove(listener);
    }

    void Log::Message(const char* message) {
        std::list<ILogListener*>::iterator each = ListenerList_.begin();
        std::list<ILogListener*>::iterator end = ListenerList_.end();
        for (;each != end; ++each) {
            (*each)->OnMessage(message);
        }
    }

}  // namespace diag
}  // namespace secondpylon
