// Copyright 2009 Brian Legge

#include "secondpylon/math/math_utils.h"
#include "secondpylon/test/test_utils.h"
#include "unittest++/src/UnitTest++.h"

namespace secondpylon {
namespace math {
namespace test {

TEST(Sqrt) {
  CHECK_EQUAL(2.0F, math::Utils::Sqrt(4.0f));
}

TEST(SqrtNegative) {
  SPTEST_CHECKASSERTS_BEGIN() {
    math::Utils::Sqrt(-4.0f);
  }
  SPTEST_CHECKASSERTS_END()
}

TEST(Abs) {
  CHECK_EQUAL(4.0F, math::Utils::Abs(-4.0F));
  CHECK_EQUAL(4.0F, math::Utils::Abs(4.0F));
}

// TEST(PI) {
//  plat::float32 PI() { return 3.1415926535897931F; }
// }

TEST(DegreeToRadian) {
  float ninety_degrees_in_radians = math::Utils::DegreeToRadian(90.0F);
  float ninety_degrees_in_pi = (2.0F*math::Utils::PI())/4.0F;
  CHECK_EQUAL(ninety_degrees_in_pi, ninety_degrees_in_radians);
}

TEST(RadianToDegree) {
  float ninety_degrees_fropi_ =
    math::Utils::RadianToDegree((2.0F*math::Utils::PI()) / 4.0F);

  CHECK_EQUAL(90.0F, ninety_degrees_fropi_);
}

}  // namespace secondpylon
}  // namespace math
}  // namespace test
