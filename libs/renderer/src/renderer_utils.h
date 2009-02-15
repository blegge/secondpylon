#ifndef SPRENDERER_UTIL_H
#define SPRENDERER_UTIL_H

namespace secondpylon {
namespace renderer {

    // The SP_DXVERIFY macro wraps DirectX calls which can fail. This is similar to an assert only it doesn't compile
    // out when asserts are disabled.
    #if NDEBUG == 1
        #define SP_DXVERIFY(x) SPDIAG_ASSERT((x) == S_OK);
    #else
        #define SP_DXVERIFY(x) (x);
    #endif

    // DirectX helper function to handle conditionally releasing DX resources and nullifying the referencing pointer.
    // This avoids the very common if (pResource) pResource->Release(); pResource = NULL; pattern.
    template <typename T>
    void SafeRelease(T*& pResource)
    {
        if (pResource)
        {
            pResource->Release();
            pResource = NULL;
        }
    }

}
}

#endif // SPRENDERER_UTIL_H
