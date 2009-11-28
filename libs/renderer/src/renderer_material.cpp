// Copyright 2009 Brian Legge

#include "secondpylon/renderer/renderer_material.h"
#include <d3d9.h>
#include <d3dx9shader.h>
#include "secondpylon/plat/plat_crt.h"
#include "./renderer_utils.h"

// TODO(brianlegge) How do we want to handle pixel shader versions? Using the
// Effect framework would be one option for the PC. Depends mostly on required
// scalability. For now, just use the native version. Note that the pixel and
// vertex shaders need to be in sync.

static IDirect3DPixelShader9* LoadPixelShader(IDirect3DDevice9* device
                        , const char* shader_data) {
  ID3DXBuffer* shader_buffer = NULL;
  ID3DXBuffer* error_buffer = NULL;

  const char* profile_name = D3DXGetPixelShaderProfile(device);

  HRESULT hr = D3DXCompileShader(
    shader_data
    , (UINT)strlen(shader_data)
    , NULL  // no defines
    , NULL  // no includes
    , "entry"
    , profile_name
    , D3DXSHADER_DEBUG
    , &shader_buffer
    , &error_buffer
    , NULL);  // no constant table

  IDirect3DPixelShader9* shader = NULL;
  if (hr != S_OK) {
    const char* pszError  = (const char*)error_buffer->GetBufferPointer();
    (pszError);
//  RSCONTENT_ERROR(
//  const char* szError = (const char*)error_buffer->GetBufferPointer();
// RSPlatform::Services()->Error(
// "Shader Error: Failed to load '%s': %s", "<default>", szError);
// );
  }

  if (S_OK == hr) {
    hr = device->CreatePixelShader(
      reinterpret_cast<DWORD*>(shader_buffer->GetBufferPointer())
      , &shader);
  }

  secondpylon::renderer::SafeRelease(error_buffer);
  secondpylon::renderer::SafeRelease(shader_buffer);

  return shader;
}

static IDirect3DVertexShader9* LoadVertexShader(
  IDirect3DDevice9* device
  , const char* shader_data) {
  ID3DXBuffer* shader_buffer = NULL;
  ID3DXBuffer* error_buffer = NULL;

  const char* profile_name = D3DXGetVertexShaderProfile(device);

  HRESULT hr = D3DXCompileShader(
    shader_data
    , (UINT)strlen(shader_data)
    , NULL  // no defines
    , NULL  // no includes
    , "entry"
    , profile_name
    , D3DXSHADER_DEBUG
    , &shader_buffer
    , &error_buffer
    , NULL);  // no constant table

  IDirect3DVertexShader9* shader = NULL;
  if (hr != S_OK) {
// RSCONTENT_ERROR(
// const char* szError = (const char*)error_buffer->GetBufferPointer();
// RSPlatform::Services()->Error(
// "Shader Error: Failed to load '%s': %s", "<default>", szError);
//  );
  }

  if (S_OK == hr) {
    hr = device->CreateVertexShader(
      reinterpret_cast<DWORD*>(shader_buffer->GetBufferPointer())
      , &shader);
  }

  secondpylon::renderer::SafeRelease(error_buffer);
  secondpylon::renderer::SafeRelease(shader_buffer);

  return shader;
}

namespace secondpylon {
namespace renderer {

Material::Material(IDirect3DDevice9* device
           , TInMemoryStream* pixel_shader_stream
           , TInMemoryStream* vertex_shader_stream) {
  // @todo We don't want to create a shader per material instance. We don't
  // yet know how we want to expose this functionality - do we need to expose
  // manual creation externally? Lets put off the decision a bit longer.

  // @todo We need a more graceful way of handling the variable data size we
  // could hit here. This will fail semi-gracefully - it won't overrun the
  // state - but the pointers we later assume to be valid will be NULL. This
  // is just a bootstrapping attempt to push data into the material.
  char vertex_shader_data[1024];
  vertex_shader_stream->Read(
    &vertex_shader_data[0]
    , ArraySize(vertex_shader_data));
  vertex_shader_ = LoadVertexShader(device, vertex_shader_data);

  char pixel_shader_data[1024];
  pixel_shader_stream->Read(
    &pixel_shader_data[0]
    , ArraySize(pixel_shader_data));
  pixel_shader_ = LoadPixelShader(device, pixel_shader_data);
}

Material::~Material() {
  SafeRelease(vertex_shader_);
  SafeRelease(pixel_shader_);
}

IDirect3DVertexShader9* Material::GetVertexShader() const {
  return vertex_shader_;
}

IDirect3DPixelShader9* Material::GetPixelShader() const {
  return pixel_shader_;
}

void Material::Destroy() {
  delete this;
}

}  // namespace renderer
}  // secondpylon
