#ifndef SPPLAT_TYPES_H
#define SPPLAT_TYPES_H

// Assume that char could be either signed or unsigned - don't do integer comparisons against it. This header
// originally defined a 'uchar' to be explicit, but this caused more compiler headaches than it resolved.

namespace secondpylon {
namespace plat {

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
