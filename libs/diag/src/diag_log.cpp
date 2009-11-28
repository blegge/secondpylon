// Copyright 2009 Brian Legge

#include "secondpylon/diag/diag_log.h"

namespace secondpylon {
namespace diag {

  void Log::AddListener(ILogListener* listener) {
    listener_list_.push_back(listener);
  }

  void Log::RemoveListener(ILogListener* listener) {
    listener_list_.remove(listener);
  }

  void Log::Message(const char* message) {
    std::list<ILogListener*>::iterator each = listener_list_.begin();
    std::list<ILogListener*>::iterator end = listener_list_.end();
    for (;each != end; ++each) {
      (*each)->OnMessage(message);
    }
  }

}  // namespace diag
}  // namespace secondpylon
