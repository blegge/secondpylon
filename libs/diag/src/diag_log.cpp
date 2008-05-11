#include <secondpylon/diag/diag_log.h>
#include <secondpylon/diag/diag_assert.h>


namespace secondpylon {
namespace diag {

void Log::AddListener(ILogListener&) {}
void Log::RemoveListener(ILogListener&) {}
void Log::Message(const char* message) 
{
    SPDIAG_UNREFERENCED(message);
}

}
}

