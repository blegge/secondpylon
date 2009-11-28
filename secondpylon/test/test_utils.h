// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_TEST_TEST_UTILS_H_
#define SECONDPYLON_TEST_TEST_UTILS_H_

#include "secondpylon/diag/diag_assert.h"
#include "unittest++/src/UnitTest++.h"

namespace secondpylon {
namespace test {

class AssertCheck : public secondpylon::diag::IAssertHandler {
public:
    AssertCheck(UnitTest::TestResults* testResults,
        const UnitTest::TestDetails& details)
        : TestResults_(testResults)
        , Details_(details)
        , AssertCount_(0)
        , pPreviousHandler_(NULL) {
        pPreviousHandler_ =
            secondpylon::diag::AssertSystem::SetAssertHandler(this);
    }

    ~AssertCheck() {
        secondpylon::diag::AssertSystem::SetAssertHandler(pPreviousHandler_);
        if (AssertCount_ == 0) {
            TestResults_->OnTestFailure(Details_, "Failed to report error");
        }
    }

    virtual secondpylon::diag::AssertSystem::EAssertAction OnAssert(
        const char* error, const char* message) {
        SPDIAG_UNREFERENCED(error);
        SPDIAG_UNREFERENCED(message);
        ++AssertCount_;
        return secondpylon::diag::AssertSystem::kContinue;
    }

private:
    SPUNCOPYABLE(AssertCheck);

    secondpylon::diag::IAssertHandler* pPreviousHandler_;

    UnitTest::TestResults* TestResults_;

    const UnitTest::TestDetails& Details_;

    int AssertCount_;
};

}  // namespace secondpylon
}  // namespace secondpylon

#define SPTEST_UNIMPLEMENTED() (void)testResults_

// @todo implement this test once the assert library is filled out. Until then,
// use this assert to wrap unit test
#define SPTEST_CHECKASSERTS_BEGIN() \
    do { \
        secondpylon::test::AssertCheck \
            check(&testResults_, UnitTest::TestDetails(m_details, __LINE__)); \
        try {

#define SPTEST_CHECKASSERTS_END() \
        } \
        catch(...) { \
            check.OnAssert("", ""); \
        } \
    } while (0);

#endif  // SECONDPYLON_TEST_TEST_UTILS_H_
