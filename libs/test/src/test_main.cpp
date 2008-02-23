#include <unittest++/src/UnitTest++.h>

// All test applications use the same entry point. For now, this is wrapped in 
// the library to minimize test app setup. If needed, this could be moved to a 
// 'you must manually include the file in your project' pattern instead.

// TODO: What macro should be used instead of cdecl?
int __cdecl main(int, char*)
{
    int failures = UnitTest::RunAllTests();

	// Return an error to enable command line error detection (for example, 
	// using %errorlevel% in DOS)
    return ((failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
}
