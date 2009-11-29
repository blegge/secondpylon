// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_PLAT_PLAT_CRT_INL_H_
#define SECONDPYLON_PLAT_PLAT_CRT_INL_H_

namespace secondpylon {

template <typename T, size_t kSize>
size_t ArraySize(T (&)[kSize]) {
  return kSize;
}

// @todo Implement the error handling
SPPLAT_INLINE void StringCopy(
  char* SPPLAT_RESTRICT dest
  , const char* SPPLAT_RESTRICT source
  , size_t dest_length) {
  // Verify the string fits.
  size_t sourceLength = strlen(source);
  if (sourceLength + 1 > dest_length) {
    dest[0] = '\0';
    // SPDIAG_ERROR((""));
    return;
  }

  // Verify the ranges don't overlap by checking the boundaries.
  // SPDIAG_ASSERT(source > dest+dest_length
  //  || source+sourceLength+1 < dest);

  // Copy and terminate the string.
  memcpy(dest, source, sourceLength*sizeof(dest[0]));
  dest[sourceLength] = '\0';
}

SPPLAT_INLINE bool StringEquals(const char* string0, const char* string1) {
  return (0 == strcmp(string0, string1));
}

SPPLAT_INLINE bool StringIEquals(const char* string0, const char* string1) {
  return (0 == _stricmp(string0, string1));
}

// @todo Add a compile time assert to insure the source and dest are of
// the same size.
template <typename TDest, typename TSource>
TDest StrictCast(TSource source) {
  union Converter {
    TSource source;
    TDest dest;
  };

  Converter converter;
  converter.source = source;
  return converter.dest;
};

}  // namespace secondpylon

#endif  // SECONDPYLON_PLAT_PLAT_CRT_INL_H_
