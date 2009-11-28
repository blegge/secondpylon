// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_RENDERER_RENDERER_UTILS_H_
#define SECONDPYLON_RENDERER_RENDERER_UTILS_H_

namespace secondpylon {
namespace renderer {

// The SP_DXVERIFY macro wraps DirectX calls which can fail. This is similar to
// an assert only it doesn't compile out when asserts are disabled.
#if defined(_DEBUG)
  #define SP_DXVERIFY(x) \
    SPDIAG_ASSERT((x) == S_OK, \
    "DirectX call returned an unexpected result.")
#else
  #define SP_DXVERIFY(x) (x)
#endif

// DirectX helper function to handle conditionally releasing DX resources and
// nullifying the referencing pointer. This avoids the very common
// if (resource) resource->Release(); resource = NULL; pattern.
template <typename T>
void SafeRelease(T*& resource) {
  if (resource) {
    resource->Release();
    resource = NULL;
  }
}

}  // namespace renderer
}  // namespace secondpylon

#endif  // SECONDPYLON_RENDERER_RENDERER_UTILS_H_
