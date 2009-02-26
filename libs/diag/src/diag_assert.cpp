#include <secondpylon/diag/diag_assert.h>
#include <stdio.h>
#include <stdarg.h>

namespace 
{
	class DefaultAssertHandler : public secondpylon::diag::IAssertHandler
	{
	public:
		secondpylon::diag::AssertSystem::EAssertAction OnAssert(const char* error, const char* message)
		{
			return secondpylon::diag::AssertSystem::kBreak;
		}
	};

}


namespace secondpylon {
namespace diag {

static DefaultAssertHandler s_DefaultHandler;
secondpylon::diag::IAssertHandler* AssertSystem::sm_pHandler = &s_DefaultHandler;

AssertSystem::EAssertAction AssertSystem::HandleAssert(const char* pszAssert, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	char message[1024];
	size_t size = _vsnprintf_s(message, ArraySize(message), ArraySize(message), format, args);
	va_end(args);

	return sm_pHandler->OnAssert(pszAssert, message);
}

secondpylon::diag::IAssertHandler* AssertSystem::SetAssertHandler(secondpylon::diag::IAssertHandler* pNewHandler)
{
	IAssertHandler* pPreviousHandler = sm_pHandler;
	sm_pHandler = pNewHandler;
	return pPreviousHandler;
}

}
}


