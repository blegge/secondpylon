#ifndef SPCONTR_ARRAY_H
#define SPCONTR_ARRAY_H

#pragma warning(disable:4530)

//#define BOOST_ENABLE_ASSERT_HANDLER

//#include <boost/array.hpp>
#include <array>

namespace secondpylon {
namespace contr {

    // We use boost::array for the array implementation. Long term (ie C++0x), we will be using the standard library
    // array in the place of boost. This is the best replacement at this time.
    //using boost::array;

	template <typename T, int Count>
	using array = std::array<T, Count>;
}
}

#endif // SPCONTR_ARRAY_H
