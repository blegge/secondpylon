#include <secondpylon/diag/diag_assert.h>

namespace 
{
	secondpylon::diag::AssertSystem::EAssertAction DefaultHandler(const char* error, const char* message)
	{
		return secondpylon::diag::AssertSystem::kBreak;
	}
}


namespace secondpylon {
namespace diag {

AssertSystem::pfnAssertHandler AssertSystem::sm_Handler = &DefaultHandler;

AssertSystem::EAssertAction AssertSystem::HandleAssert(const char* pszAssert, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	char message[1024];
	size_t size = _vsnprintf_s(message, ArraySize(message), ArraySize(message), format, args);
	va_end(args);

	return (*sm_Handler)(pszAssert, message);
}

void AssertSystem::SetAssertHandler(pfnAssertHandler pfnNewHandler)
{
	sm_Handler = pfnNewHandler;
}


}
}


