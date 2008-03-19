#include <secondpylon/contr/contr_array.h>

// The only down size to using the boost array implementation is its dependency on exceptions. While this is generally
// a great solution, it does violate our requirements. As a very similar implementation will be added to the C++0x, we
// are ignoring that for now.
