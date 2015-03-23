#include <secondpylon/contr/contr_array.h>
#include <secondpylon/test/test_utils.h>
#include <secondpylon/plat/plat_types.h>
#include "unittest++/src/UnitTest++.h"

using namespace secondpylon;
namespace {

    struct TestClass
    {
        TestClass() : 
            m_Counter(0)
        {
        }

        TestClass(plat::uint32 counter) : 
            m_Counter(counter)
        {
        }

        plat::uint32 m_Counter;
    };

}

TEST(ArraySize)
{
    contr::array<TestClass, 1> TestArray;
    CHECK_EQUAL(size_t(1), TestArray.size());
}

static plat::uint32 ReadCount(const contr::array<TestClass, 1>& array, size_t element)
{
    return array[element].m_Counter;
}

TEST(ArrayReadConstMethod)
{
    contr::array<TestClass, 1> TestArray;
    CHECK_EQUAL(plat::uint32(0), ReadCount(TestArray, 0));
}

TEST(ArrayWrite)
{
    contr::array<TestClass, 1> TestArray;
    TestArray[0] = TestClass(1);
    CHECK_EQUAL(plat::uint32(1), ReadCount(TestArray, 0));
}

/*
TEST(ArrayReadOutOfBounds)
{
    contr::array<TestClass, 1> TestArray;
     TestClass t = TestArray[1];
    CHECK_EQUAL(plat::uint32(1), ReadCount(TestArray, 0));
}
*/

// Required only when BOOST_ENABLE_ASSERT_HANDLER is defined. This function replaces the default boost assert hander.
//void boost::assertion_failed(char const * /*expr*/, char const * /*function*/, char const * /*file*/, long /*line*/)
//{
//}
