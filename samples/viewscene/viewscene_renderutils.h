#include <windows.h>
#include <viewscene_common.h>

struct IDirect3D9;
struct IDirect3DDevice9;

struct RenderUtils
{
    struct RenderDevice
    {
        RenderDevice();
        ~RenderDevice();

        IDirect3D9* m_pD3D;
        IDirect3DDevice9* m_pDevice;
    };

    struct DeviceParameters
    {
        HWND parent_window;
        vec2i dims;
        bool vsync;
        UINT adapter;
    };

    static void CreateDevice(RenderDevice& device, const DeviceParameters& parameters);
    static void DestroyDevice(RenderDevice& device);
};
