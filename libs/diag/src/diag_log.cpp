// Copyright 2009 Brian Legge

#include "secondpylon/diag/diag_log.h"

namespace secondpylon {
namespace diag {

    void Log::AddListener(ILogListener* listener) {
        m_ListenerList.push_back(listener);
    }

    void Log::RemoveListener(ILogListener* listener) {
        m_ListenerList.remove(listener);
    }

    void Log::Message(const char* message) {
        std::list<ILogListener*>::iterator each = m_ListenerList.begin();
        std::list<ILogListener*>::iterator end = m_ListenerList.end();
        for (;each != end; ++each) {
            (*each)->OnMessage(message);
        }
    }

}  // namespace diag
}  // namespace secondpylon
