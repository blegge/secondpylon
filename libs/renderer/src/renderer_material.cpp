#include <secondpylon/renderer/renderer_material.h>
#include "d3d9.h"
#include "d3dx9shader.h"


// http://docendo.bai.nu/img/kapitel/0735616531.htm
IDirect3DVertexShader9* LoadVertexShader(IDirect3DDevice9& device, const char* shader)
{
	ID3DXBuffer* pShaderBuffer = NULL;
	ID3DXBuffer* pErrorBuffer = NULL;

	HRESULT hr = D3DXCompileShader(
		shader
		, (UINT)strlen(shader)
		, NULL	// no defines
		, NULL	// no includes
		, "entry"
		, "vs_1_1"
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
    const char vShader[] = 
	    "float4 entry(float4 inPos : POSITION) : POSITION	\
	    {	\
		    return inPos;	\
	    }";

    m_pVertexShader = LoadVertexShader(device, vShader);
    m_pVertexDeclaration = CreateVertexDeclaration(device);
}

Material::~Material()
{
    m_pVertexDeclaration->Release();
    m_pVertexDeclaration = NULL;

    m_pVertexShader->Release();
    m_pVertexShader = NULL;
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
    return NULL; 
}

void Material::Destroy()
{ 
    delete this;
}

}
}
