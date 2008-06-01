#ifndef SPRENDERER_UTIL_H
#define SPRENDERER_UTIL_H

namespace secondpylon {
namespace renderer {

    #if NDEBUG == 1
        #define VERIFY(x) SPDIAG_ASSERT((x) == S_OK);
    #else
        #define VERIFY(x) (x);
    #endif

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
