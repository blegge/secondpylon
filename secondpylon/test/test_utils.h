#ifndef SPTEST_UTILS_H
#define SPTEST_UTILS_H

#include <secondpylon/diag/diag_assert.h>
#include <unittest++/src/UnitTest++.h>

namespace secondpylon {
namespace test {

class AssertCheck : public secondpylon::diag::IAssertHandler
{
public:
	AssertCheck(UnitTest::TestResults& testResults_, UnitTest::TestDetails& details) : 
	  m_TestResults(testResults_)
	  , m_Details(details)
	  , m_AssertCount(0)
	  , m_pPreviousHandler(NULL)
	{
		m_pPreviousHandler = secondpylon::diag::AssertSystem::SetAssertHandler(this);
	}

	~AssertCheck()
	{
		secondpylon::diag::AssertSystem::SetAssertHandler(m_pPreviousHandler);
		if (m_AssertCount == 0)
		{
			m_TestResults.OnTestFailure(m_Details, "Failed to report error");
		}
	}

	virtual secondpylon::diag::AssertSystem::EAssertAction OnAssert(const char* /*error*/, const char* /*message*/)
	{
		++m_AssertCount;
		return secondpylon::diag::AssertSystem::kContinue;
	}

private:
	secondpylon::diag::IAssertHandler* m_pPreviousHandler;
	UnitTest::TestResults& m_TestResults;
	UnitTest::TestDetails& m_Details;
	int m_AssertCount;


	AssertCheck& operator=(AssertCheck&);
};
}
}

#define SPTEST_UNIMPLEMENTED() (void)testResults_

// @todo implement this test once the assert library is filled out. Until then, use this assert to wrap unit test 
#define SPTEST_CHECKASSERTS_BEGIN() do { \
	secondpylon::test::AssertCheck check(testResults_, UnitTest::TestDetails(m_details, __LINE__));

#define SPTEST_CHECKASSERTS_END() } while (0);

#endif // SPTEST_UTILS_H
