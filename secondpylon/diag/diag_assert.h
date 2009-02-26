#ifndef SPDIAG_ASSERT_H
#define SPDIAG_ASSERT_H

#include <secondpylon/plat/plat_compiler.h>
#include <secondpylon/plat/plat_crt.h>

namespace secondpylon {
namespace diag {

	class AssertSystem
	{
	public:
		enum EAssertAction { kContinue, kBreak };

		typedef EAssertAction (*pfnAssertHandler)(const char* error, const char* message);

		static EAssertAction HandleAssert(const char* pszAssert, const char* format, ...);
		static void SetAssertHandler(pfnAssertHandler pfnNewHandler);

	private:
		static pfnAssertHandler sm_Handler;
	};

}
}

// Allow project level disabling of asserts through the SPDIAG_DISABLEASSERTS macro. 
// If it is defined, asserts will be disabled.
// TODO: What is the standard way of handling this?
#if !defined(SPDIAG_DISABLEASSERTS) && !defined(SPDIAG_ENABLEASSERTS)
	#define SPDIAG_ENABLEASSERTS
#endif

// Compile time assert, soon to be replaced by C++0x standard assert.
//
// Static asserst don't have any overhead - always use them. RSSTATIC_ASSERT
// attempts to create one of the two StaticAssertFailed types depending on the
// passed in value. Only a specialization of true will compile successfully -
// false will result in a compile time failure..
template <bool b> struct StaticAssertFailed;
template <> struct StaticAssertFailed<true>{};
#define SPDIAG_CTASSERT(x) StaticAssertFailed<x>();

// This is an internal macro to insure macros provided by secondpylon (and potentially compiled out in 
// different configurations) don't introduce flow control changes. The classic example is something like:
// if (bValue)
//		ASSERT(expression)
//  foo = 42;
//
// If ASSERT was compiled out completely, assigning 42 to foo would become conditional on bValue. This 
// macro insures that this doesn't happen.
#define SPDIAG_INTERNAL_MACRO(x) do { x } while (0);
#define SPDIAG_INTERNAL_MACRO_NULL() do { } while (0);

// Helper to invoke a crash in the case of a truly unrecoverable situation. A common use is forcing a crash to occur 
// early. This can be used to create a crash dump at a point with more information. For example, a NaN fed into a 
// physics system may cause a crash much later. Tracking the source back may be difficult. Asserts work on dev machines,
// but not if the bug only repros in the wild.
#define SPDIAG_FATAL(x) *(void*)0 = 0;

// Used to prevent 'unreference variable' warnings. Some variables may only be used in specific configurations. 
// This macro can be used to prevent these variables from generating warnings in other configurations. For example:
//
// bool bResult = DoWork();
// SPDIAG_ASSERT(bResult);
//
// in configurations with SPERROR_ASSERT compiled out, bResult would can generate an unreferenced variable warning. 
// SPDIAG_UNREFERENCED(bResult) can be used to prevent this warning.
#define SPDIAG_UNREFERENCED(x) (x)

#ifdef SPDIAG_ENABLEASSERTS

	#define SPDIAG_ASSERT(x, ...) SPDIAG_INTERNAL_MACRO(\
		if (!(x) && secondpylon::diag::AssertSystem::kBreak == secondpylon::diag::AssertSystem::HandleAssert(#x, __VA_ARGS__))\
		{\
			SPPLAT_BREAK();\
		}\
	)

	#define SPDIAG_ERROR(...) SPDIAG_INTERNAL_MACRO( \
		if (secondpylon::diag::AssertSystem::kBreak == secondpylon::diag::AssertSystem::HandleAssert("Error", __VA_ARGS__))\
		{\
			SPPLAT_BREAK();\
		}\
	)

#else

	#define SPDIAG_ASSERT(x, format, ...) SPDIAG_INTERNAL_MACRO_NULL()
	#define SPDIAG_ERROR(format, ...) SPDIAG_INTERNAL_MACRO_NULL()

#endif

#endif // SPDIAG_ASSERT_H
