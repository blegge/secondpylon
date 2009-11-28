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
                                              , const char* shader) {
    ID3DXBuffer* pShaderBuffer = NULL;
    ID3DXBuffer* pErrorBuffer = NULL;

    const char* psProfilename = D3DXGetPixelShaderProfile(device);

    HRESULT hr = D3DXCompileShader(
        shader
        , (UINT)strlen(shader)
        , NULL    // no defines
        , NULL    // no includes
        , "entry"
        , psProfilename
        , D3DXSHADER_DEBUG
        , &pShaderBuffer
        , &pErrorBuffer
        , NULL);    // no constant table

    IDirect3DPixelShader9* pShader = NULL;
    if (hr != S_OK) {
        const char* pszError  = (const char*)pErrorBuffer->GetBufferPointer();
        (pszError);
//  RSCONTENT_ERROR(
//  const char* szError = (const char*)pErrorBuffer->GetBufferPointer();
// RSPlatform::Services()->Error(
// "Shader Error: Failed to load '%s': %s", "<default>", szError);
// );
    }

    if (S_OK == hr) {
        hr = device->CreatePixelShader(
            reinterpret_cast<DWORD*>(pShaderBuffer->GetBufferPointer())
            , &pShader);
    }

    secondpylon::renderer::SafeRelease(pErrorBuffer);
    secondpylon::renderer::SafeRelease(pShaderBuffer);

    return pShader;
}

static IDirect3DVertexShader9* LoadVertexShader(
    IDirect3DDevice9* device
    , const char* shader) {
    ID3DXBuffer* pShaderBuffer = NULL;
    ID3DXBuffer* pErrorBuffer = NULL;

    const char* psProfilename = D3DXGetVertexShaderProfile(device);

    HRESULT hr = D3DXCompileShader(
        shader
        , (UINT)strlen(shader)
        , NULL    // no defines
        , NULL    // no includes
        , "entry"
        , psProfilename
        , D3DXSHADER_DEBUG
        , &pShaderBuffer
        , &pErrorBuffer
        , NULL);    // no constant table

    IDirect3DVertexShader9* pShader = NULL;
    if (hr != S_OK) {
// RSCONTENT_ERROR(
// const char* szError = (const char*)pErrorBuffer->GetBufferPointer();
// RSPlatform::Services()->Error(
// "Shader Error: Failed to load '%s': %s", "<default>", szError);
//  );
    }

    if (S_OK == hr) {
        hr = device->CreateVertexShader(
            reinterpret_cast<DWORD*>(pShaderBuffer->GetBufferPointer())
            , &pShader);
    }

    secondpylon::renderer::SafeRelease(pErrorBuffer);
    secondpylon::renderer::SafeRelease(pShaderBuffer);

    return pShader;
}

namespace secondpylon {
namespace renderer {

Material::Material(IDirect3DDevice9* device
                   , TInMemoryStream* pixelShaderStream
                   , TInMemoryStream* vertexShaderStream) {
    // @todo We don't want to create a shader per material instance. We don't
    // yet know how we want to expose this functionality - do we need to expose
    // manual creation externally? Lets put off the decision a bit longer.

    // @todo We need a more graceful way of handling the variable data size we
    // could hit here. This will fail semi-gracefully - it won't overrun the
    // state - but the pointers we later assume to be valid will be NULL. This
    // is just a bootstrapping attempt to push data into the material.
    char szVertexShaderData[1024];
    vertexShaderStream->Read(
        &szVertexShaderData[0]
        , ArraySize(szVertexShaderData));
    pVertexShader_ = LoadVertexShader(device, szVertexShaderData);

    char szPixelShaderData[1024];
    pixelShaderStream->Read(
        &szPixelShaderData[0]
        , ArraySize(szPixelShaderData));
    pPixelShader_ = LoadPixelShader(device, szPixelShaderData);
}

Material::~Material() {
    SafeRelease(pVertexShader_);
    SafeRelease(pPixelShader_);
}

IDirect3DVertexShader9* Material::GetVertexShader() const {
    return pVertexShader_;
}

IDirect3DPixelShader9* Material::GetPixelShader() const {
    return pPixelShader_;
}

void Material::Destroy() {
    delete this;
}

}  // namespace renderer
}  // secondpylon
