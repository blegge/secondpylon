#ifndef SPRENDERER_DEVICE_H
#define SPRENDERER_DEVICE_H

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/math/math_vec2.h>
#include <windows.h>

struct IDirect3D9;
struct IDirect3DDevice9;

namespace secondpylon {
namespace renderer {

    class Mesh;
    class Material;
    class Color;

    class SDeviceParameters
    {
    public:
        HWND parent_window;
        math::vec2<plat::uint32> dims;
        bool vsync;
        UINT adapter;
    };

    class Device
    {
    public:
        Device(const SDeviceParameters& params);
        ~Device();

        Mesh* CreateDynamicMesh(plat::uint32 nVertexSize, plat::uint32 nVertexCount, plat::uint32 nIndexCount);
        Material* CreateMaterial();

        void Draw(Mesh& mesh, Material& mat);

        void Clear(const Color& clearColor);
        bool BeginScene();
        void EndScene();
        void Flip();

    private:
        IDirect3D9* m_pD3D;
        IDirect3DDevice9* m_pDevice;

        // Debug value tracking if we are in a BeginScene/EndScene block.
        bool m_bInScene;
    };

}
}

#endif // SPRENDERER_DEVICE_H
