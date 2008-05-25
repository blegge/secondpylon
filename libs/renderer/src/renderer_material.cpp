#include <secondpylon/renderer/renderer_material.h>
#include "d3d9.h"
#include "d3dx9shader.h"

// TODO: How do we want to handle pixel shader versions? Using the Effect framework would be one option for the PC.
// Depends mostly on required scalability. For now, just use the native version. Note that the pixel and vertex shaders need to be in sync.

static IDirect3DPixelShader9* LoadPixelShader(IDirect3DDevice9& device, const char* shader)
{
	ID3DXBuffer* pShaderBuffer = NULL;
	ID3DXBuffer* pErrorBuffer = NULL;

	const char* psProfilename = D3DXGetPixelShaderProfile(&device);

    HRESULT hr = D3DXCompileShader(
		shader
		, (UINT)strlen(shader)
		, NULL	// no defines
		, NULL	// no includes
		, "entry"
		, psProfilename
		, D3DXSHADER_DEBUG 
		, &pShaderBuffer
		, &pErrorBuffer
		, NULL	// no constant table
	);

	IDirect3DPixelShader9* pShader = NULL;
	if (hr != S_OK)
	{
        const char* pszError  = (const char*)pErrorBuffer->GetBufferPointer();
        (pszError);
//		RSCONTENT_ERROR(
//			const char* szError = (const char*)pErrorBuffer->GetBufferPointer();
//			RSPlatform::Services()->Error("Shader Error: Failed to load '%s': %s", "<default>", szError);
//		);
	}

	if (S_OK == hr)
	{
		hr = device.CreatePixelShader((DWORD*)pShaderBuffer->GetBufferPointer(), &pShader);
	}

	if (pErrorBuffer)
		pErrorBuffer->Release();
	if (pShaderBuffer)
		pShaderBuffer->Release();

	return pShader;
}

static IDirect3DVertexShader9* LoadVertexShader(IDirect3DDevice9& device, const char* shader)
{
	ID3DXBuffer* pShaderBuffer = NULL;
	ID3DXBuffer* pErrorBuffer = NULL;

    const char* psProfilename = D3DXGetVertexShaderProfile(&device);

	HRESULT hr = D3DXCompileShader(
		shader
		, (UINT)strlen(shader)
		, NULL	// no defines
		, NULL	// no includes
		, "entry"
		, psProfilename
		, D3DXSHADER_DEBUG 
		, &pShaderBuffer
		, &pErrorBuffer
		, NULL	// no constant table
	);

	IDirect3DVertexShader9* pShader = NULL;
	if (hr != S_OK)
	{
//		RSCONTENT_ERROR(
//			const char* szError = (const char*)pErrorBuffer->GetBufferPointer();
//			RSPlatform::Services()->Error("Shader Error: Failed to load '%s': %s", "<default>", szError);
//		);
	}

	if (S_OK == hr)
	{
		hr = device.CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &pShader);
	}

	if (pErrorBuffer)
		pErrorBuffer->Release();
	if (pShaderBuffer)
		pShaderBuffer->Release();

	return pShader;
}

IDirect3DVertexDeclaration9* CreateVertexDeclaration(IDirect3DDevice9& device)
{
	const D3DVERTEXELEMENT9 decl[] = 
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		D3DDECL_END()
	};

    IDirect3DVertexDeclaration9* pDecl = NULL;
    device.CreateVertexDeclaration(decl, &pDecl);

    return pDecl;
}

namespace secondpylon {
namespace renderer {

Material::Material(IDirect3DDevice9& device)
{
    // Load the a test shaders
    const char vertexShader[] = 
	    "float4 entry(float4 inPos : POSITION) : POSITION	\
	    {	\
		    return inPos;	\
	    }";

    const char pixelShader[] = "\
        float4 entry() : COLOR \
        { \
            return float4 (1, 0, 0, 1); \
        }";

    m_pVertexShader = LoadVertexShader(device, vertexShader);
    m_pVertexDeclaration = CreateVertexDeclaration(device);
    m_pPixelShader = LoadPixelShader(device, pixelShader);
}

Material::~Material()
{
    m_pVertexDeclaration->Release();
    m_pVertexDeclaration = NULL;

    m_pVertexShader->Release();
    m_pVertexShader = NULL;

    m_pPixelShader->Release();
    m_pPixelShader = NULL;
}

IDirect3DVertexDeclaration9* Material::GetVertexDecl() const
{
    return m_pVertexDeclaration;
}

IDirect3DVertexShader9* Material::GetVertexShader() const 
{ 
    return m_pVertexShader; 
}

IDirect3DPixelShader9* Material::GetPixelShader() const 
{ 
    return m_pPixelShader;
}

void Material::Destroy()
{ 
    delete this;
}

}
}
