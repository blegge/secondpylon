#ifndef SPRENDERER_RENDERTARGET_H
#define SPRENDERER_RENDERTARGET_H

namespace secondpylon {
namespace renderer {

    // Rendertargets are the 'surface' to which we render. This may be the main screen or a texture render target. Once
    // a render target is resolved, its contents are undefined. More specifically, the following has undefined
    // behavior:
    //
    // 1) Render primitives to RenderTarget A
    // 2) Resolve RenderTarget A
    // 3) Render more primitives to RenderTarget A
    //
    // At the start of step 3, the contents of RenderTarget A are undefined.

    class IRenderTarget {};
    class BackbufferRenderTarget : public IRenderTarget {};
    class TextureRenderTarget : public IRenderTarget {};
 
}
}

#endif // SPRENDERER_RENDERTARGET_H
