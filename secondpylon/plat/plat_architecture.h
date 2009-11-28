// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_PLAT_PLAT_ARCHITECTURE_H_
#define SECONDPYLON_PLAT_PLAT_ARCHITECTURE_H_

// Define the byte ordering for this platform.
#include <boost/detail/endian.hpp>
#if defined(BOOST_BIG_ENDIAN)

  #define SPPLAT_BIGENDIAN

#elif defined(BOOST_LITTLE_ENDIAN)

  #define SPPLAT_LITTLEENDIAN

#else

  #error Byte ordering is not defined

#endif

#endif  // SECONDPYLON_PLAT_PLAT_ARCHITECTURE_H_
