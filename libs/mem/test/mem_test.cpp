// Copyright 2009 Brian Legge

// This file is currently a stub for experimenting with different memory 
// allocators, error trapping and logging schemes. Long term this will become
// either a base allocator for the secondpylon libraries or an implementation
// of an allocator interface (to permit the hosts to specify their own 
// allocators if so desired)

#include "unittest++/src/UnitTest++.h"
#include "secondpylon/test/test_utils.h"
#include "secondpylon/plat/plat_types.h"

//  -- API --

namespace {

  class ClassWithConstructor {
  public:
    explicit ClassWithConstructor(secondpylon::plat::uint32  i)
      : i_(i) {
    }

  private:
    secondpylon::plat::uint32 i_;
  };

}  // namespace

#define SPNEW() new(__FILE__, __LINE__)

typedef size_t TAllocationSizeType;

struct AllocationDescriptor {
  const char* filename_;
  secondpylon::plat::uint16 line_;
  TAllocationSizeType size_;
};

struct AllocationHeader {
  // descriptor associated with this allocation
  AllocationDescriptor description_;

  // linked list of allocations
  AllocationHeader* next_;
  AllocationHeader* previous_;

  secondpylon::plat::uint32 data_;  //  Hash of the header + allocator info
};

struct AllocationFooter {
  secondpylon::plat::uint32 hash_;  //  Hash of the header + allocator info
};

void* operator new(size_t size
           , const char* /*filename*/
           , secondpylon::plat::uint32 /*linenumber*/) {
  void* buffer = malloc(size);
  return buffer;

  // Write the header
  // Write the footer
  // Fill the memory
}

void operator delete(void* mem
           , const char* /*filename*/
           , secondpylon::plat::uint32 /*linenumber*/) {
  // check header
  // Fill the memory
  free(mem);
}
/*
void Checkallocationconsistency()
{
  for each allocation
  {
    calculate the hash
    compare to the header
    compare to the footer
  }
}
*/
//  ----

namespace secondpylon {
namespace mem {
namespace test {

TEST(SimpleAlloc) {
  plat::uint8* alloc = SPNEW() plat::uint8;
  CHECK(alloc != NULL);
  delete alloc;
}

TEST(SimpleAllocConstructor) {
  ClassWithConstructor* alloc = SPNEW() ClassWithConstructor(5);
  CHECK(alloc != NULL);
  delete alloc;
}

TEST(ArrayAlloc) {
  plat::uint8* alloc = SPNEW() plat::uint8[10];
  CHECK(alloc != NULL);
  delete [] alloc;
}

// This should throw!
TEST(AllocatorMismatch) {
  plat::uint8* alloc = SPNEW() plat::uint8[10];
  SPTEST_CHECKASSERTS_BEGIN();
  delete alloc;
  SPTEST_CHECKASSERTS_END();
}

// This should throw!
TEST(AllocatorMismatchArray) {
  plat::uint8* alloc = SPNEW() plat::uint8;
  SPTEST_CHECKASSERTS_BEGIN();
  delete [] alloc;
  SPTEST_CHECKASSERTS_END();
}

// This should throw!
TEST(AllocatorDoubleDelete) {
  plat::uint8* alloc = SPNEW() plat::uint8;
  delete alloc;
  SPTEST_CHECKASSERTS_BEGIN();
  delete alloc;
  SPTEST_CHECKASSERTS_END();
}

// This should throw!
TEST(AllocatorDoubleDeleteArray) {
  plat::uint8* alloc = SPNEW() plat::uint8[5];
  delete [] alloc;
  SPTEST_CHECKASSERTS_BEGIN()
  SPTEST_CHECKASSERTS_END()
}

}  // namespace secondpylon
}  // namespace mem
}  // namespace test
