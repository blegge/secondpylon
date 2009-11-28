// Copyright 2009 Brian Legge
#ifndef SAMPLES_VIEWSCENE_SRC_VIEWSCENE_RENDERUTILS_H_
#define SAMPLES_VIEWSCENE_SRC_VIEWSCENE_RENDERUTILS_H_

#include <windows.h>
#include "viewscene_common.h>"

struct IDirect3D9;
struct IDirect3DDevice9;

struct RenderUtils {
  struct RenderDevice {
    RenderDevice();
    ~RenderDevice();

    IDirect3D9* d3d_;
    IDirect3DDevice9* device_;
  };

  struct DeviceParameters {
    HWND parent_window;
    vec2i dims;
    bool vsync;
    UINT adapter;
  };

  static void CreateDevice(
    RenderDevice& device
    , const DeviceParameters& parameters);

  static void DestroyDevice(RenderDevice* device);
};

#endif  // SAMPLES_VIEWSCENE_SRC_VIEWSCENE_RENDERUTILS_H_
