#ifndef SPTEST_UTILS_H
#define SPTEST_UTILS_H

namespace secondpylon {
namespace test {

}
}

#define SPTEST_UNIMPLEMENTED() (void)testResults_

// @todo implement this test once the assert library is filled out. Until then, use this assert to wrap unit test 
#define SPTEST_CHECKASSERTS_BEGIN() SPTEST_UNIMPLEMENTED(); do  { if (0)
#define SPTEST_CHECKASSERTS_END() } while (0);

#endif // SPTEST_UTILS_H
