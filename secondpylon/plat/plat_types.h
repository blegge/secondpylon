// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_PLAT_PLAT_TYPES_H_
#define SECONDPYLON_PLAT_PLAT_TYPES_H_

// What compiler guards will enable us to use this instead?
// #include <inttypes.h>

// Assume that char could be either signed or unsigned - don't do integer
// comparisons against it. This header originally defined a 'uchar' to be
// explicit, but this caused more compiler headaches than it resolved.

namespace secondpylon {
namespace plat {
  // Define basic types. These defines may need to vary by platform, as C/C++
  // type definitions are more general than we need here. Using these types
  // simplify serialization and general file io. For simplicity, these types
  // should be used at all times.

  typedef unsigned char uint8;
  typedef unsigned short uint16;
  typedef unsigned int uint32;
  typedef unsigned long long uint64;
  typedef signed char sint8;
  typedef signed short sint16;
  typedef signed int sint32;
  typedef signed long long sint64;

  typedef float float32;

  typedef unsigned char byte;

  typedef bool bool8;

  // Types which may vary in size. Ideally, these types should not be used in
  // for any persistent storage. Their use is required by the C++ spec however
  // so they can't be entirely avoided.
  // ptrdiff_t, size_t, intptr_t

}  // namespace plat
}  // namespace secondpylon

#endif  // SECONDPYLON_PLAT_PLAT_TYPES_H_
