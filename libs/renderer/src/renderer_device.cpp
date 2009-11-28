// Copyright 2009 Brian Legge

#include "secondpylon/renderer/renderer_device.h"

#include <d3dx9.h>
#include <d3d9.h>

#include "secondpylon/renderer/renderer_dynamicmesh.h"
#include "secondpylon/renderer/renderer_material.h"
#include "secondpylon/renderer/renderer_color.h"
#include "secondpylon/renderer/renderer_texture.h"
#include "secondpylon/renderer/renderer_deviceparameters.h"

#include "./renderer_utils.h"

namespace secondpylon {
namespace renderer {

Device::Device(const DeviceParameters& deviceParams)
  : d3d_(NULL)
  , device_(NULL)
  , in_scene_(false) {
  // Create D3D and the rendering device.
  IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);
  if (d3d) {
    D3DPRESENT_PARAMETERS internal_params;
    internal_params.Windowed = TRUE;
    internal_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
    internal_params.EnableAutoDepthStencil = TRUE;
    internal_params.AutoDepthStencilFormat = D3DFMT_D16;
    internal_params.hDeviceWindow = deviceParams.parent_window;
    internal_params.BackBufferWidth = deviceParams.dims.x;
    internal_params.BackBufferHeight = deviceParams.dims.y;

    // Assume 16 bit color. Use D3DFMT_X8R8G8B8 if 32 isn't supported
    internal_params.BackBufferFormat = D3DFMT_R5G6B5;

    internal_params.MultiSampleType = D3DMULTISAMPLE_NONE;
    internal_params.MultiSampleQuality = 0;
    internal_params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    internal_params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    internal_params.Flags = 0;

    if (deviceParams.vsync) {
      internal_params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
      internal_params.BackBufferCount = 2;
    } else {
      internal_params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
      internal_params.BackBufferCount = 1;
    }

    // TODO(brianlegge) Handle graceful fallbacks based on the checks below?
    D3DDEVTYPE device_type = D3DDEVTYPE_HAL;
    SP_DXVERIFY(d3d->CheckDeviceFormat(
      deviceParams.adapter
      , device_type
      , internal_params.BackBufferFormat
      , D3DUSAGE_DEPTHSTENCIL
      , D3DRTYPE_SURFACE
      , internal_params.AutoDepthStencilFormat));

    // Other possible checks include, CheckDepthStencilMatch,
    // CheckDeviceFormat, CheckDeviceFormatConversion,
    // CheckDeviceMultiSampleType,  CheckDeviceType

    IDirect3DDevice9* pD3DDevice = NULL;
    SP_DXVERIFY(d3d->CreateDevice(
      deviceParams.adapter
      , device_type
      , deviceParams.parent_window
      , D3DCREATE_HARDWARE_VERTEXPROCESSING
      , &internal_params
      , &pD3DDevice));

    if (pD3DDevice) {
      // Assign the output parameters once we've cleared all potential
      // failure points.
      d3d_ = d3d;
      device_ = pD3DDevice;
    } else {
      SafeRelease(d3d);
    }
  }
}

Device::~Device() {
  SPDIAG_ASSERT(!in_scene_,
    "Must end a scene before destroying a render device.");

  SafeRelease(d3d_);
  SafeRelease(device_);
}

DynamicMesh* Device::CreateDynamicMesh(plat::uint32 vertex_count
                     , plat::uint32 index_count) {
  DynamicMesh* mesh = new DynamicMesh;
  if (!mesh->Create(device_, vertex_count, index_count)) {
    delete mesh;
    mesh = NULL;
  }
  return mesh;
}

Material* Device::CreateMaterial(TInMemoryStream* pixel_shader_buffer
                 , TInMemoryStream* vertex_shader_buffer) {
  return new Material(device_, pixel_shader_buffer, vertex_shader_buffer);
}

Texture* Device::CreateTexture(const math::vec2<plat::uint32>& size) {
  IDirect3DTexture9* texture = NULL;
  device_->CreateTexture(size.x, size.y, 0, D3DUSAGE_DYNAMIC,
    D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &texture, NULL);
  return new Texture(texture, size);
}

void Device::Draw(const renderer::SubMeshRenderRequest& request) {
  // @todo This doesn't do any sorting or redundancy filtering. This needs
  // either needs to be added here (with draws batched externally) or we need
  // to add internal checks (which would be less efficient but simpler from
  // an API standpoint).
  SP_DXVERIFY(device_->SetVertexShader(request.vertex_shader_));
  SP_DXVERIFY(device_->SetPixelShader(request.pixel_shader_));

  SP_DXVERIFY(device_->SetVertexDeclaration(request.vertex_declaration_));
  SP_DXVERIFY(
    device_->SetStreamSource(0, request.vertex_buffer_,
      0, request.vertex_stride_));
  SP_DXVERIFY(device_->SetIndices(request.index_buffer_));

  SP_DXVERIFY(
    device_->DrawIndexedPrimitive(
      D3DPT_TRIANGLELIST, 0, 0, request.vertex_count_,
      0, request.index_count_));

  SP_DXVERIFY(device_->SetStreamSource(0, NULL, 0, 0));
  SP_DXVERIFY(device_->SetVertexShader(NULL));
  SP_DXVERIFY(device_->SetPixelShader(NULL));
}

void Device::Clear(const renderer::Color& clearColor) {
  SP_DXVERIFY(
    device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
            , clearColor.GetEncodedColor(), 1.0f, 0));
}

void Device::Flip() {
  SP_DXVERIFY(device_->Present(NULL, NULL, NULL, NULL));
}

bool Device::BeginScene() {
  SPDIAG_ASSERT(
    !in_scene_
    , "Device must call EndScene to complete the current scene before"
    " calling BeginScene again.");
  in_scene_ = (S_OK == device_->BeginScene());
  return in_scene_;
}

void Device::EndScene() {
  SPDIAG_ASSERT(in_scene_
    , "Device must being a scene before calling EndScene");
  SP_DXVERIFY(device_->EndScene());
  in_scene_ = false;
}

}  // namespace renderer
}  // namespace secondpylon
