// Copyright 2009 Brian Legge

#include "secondpylon/math/math_mat3.h"
#include "unittest++/src/UnitTest++.h"
#include "secondpylon/test/test_utils.h"

namespace {

template <typename T>
UnitTest::MemoryOutStream& operator<<(UnitTest::MemoryOutStream& stream
                    , const secondpylon::math::mat3<T>& mat) {
  typedef secondpylon::math::mat3<T> mat3f;
  stream << "\n("
    << mat.m[mat3f::k00]
    << "," << mat.m[mat3f::k01]
    << "," << mat.m[mat3f::k02]
    << ",\n"
    << mat.m[mat3f::k10]
    << "," << mat.m[mat3f::k11]
    << "," << mat.m[mat3f::k12]
    << ",\n"
    << mat.m[mat3f::k20]
    << "," << mat.m[mat3f::k21]
    << "," << mat.m[mat3f::k22]
    << ")";
  return stream;
}

}  // namespace

namespace secondpylon {
namespace math {
namespace test {

typedef math::mat3<float> mat3f;

TEST(Mat3ManualInitToIdentity) {
  mat3f test(
    1, 0, 0
    , 0, 1, 0
    , 0, 0, 1);

  mat3f identity;
  mat3f::Identity(&identity);
  CHECK_EQUAL(identity, test);
}

TEST(Mat3CopyIdentity) {
  mat3f identity;
  mat3f::Identity(&identity);
  mat3f identityCopy = identity;
  CHECK_EQUAL(identityCopy, identity);
}

/*
TEST(Mat3Multiply) {
}
*/
TEST(Mat3TransposeOfIdentity) {
  mat3f identity;
  mat3f::Identity(&identity);

  mat3f transpose;
  mat3f::Transpose(identity, &transpose);

  CHECK_EQUAL(identity, transpose);
}

/*
TEST(Mat3Inverse) {
}

TEST(Mat3Normalize) {
}
*/

}  // namespace secondpylon
}  // namespace math
}  //  namespace test
