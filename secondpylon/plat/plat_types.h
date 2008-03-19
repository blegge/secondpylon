#ifndef SPPLAT_TYPES_H
#define SPPLAT_TYPES_H

// Assume that char could be either signed or unsigned - don't do integer comparisons against it. This header
// originally defined a 'uchar' to be explicit, but this caused more compiler headaches than it resolved.

namespace secondpylon {
namespace plat {

    // Define basic types. These defines may need to vary by platform, as C/C++ type definitions are more general than
    // we need here. Using these types simplify serialization and general file io. For simplicity, these types shoulse
    // be used at all times.

    typedef unsigned char uint8;
    typedef unsigned short uint16;
    typedef unsigned int uint32;
    typedef signed char sint8;
    typedef signed short sint16;
    typedef signed int sint32;

    typedef float float32;

    typedef unsigned char byte;
    
    typedef bool bool8;

}
}

#endif // SPPLAT_TYPES_H
