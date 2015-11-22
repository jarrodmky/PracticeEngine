#include "Precompiled.h"
#include "Shaders.h"
#include "Vertices.h"

using namespace Visualization;

void PixelShader::Compile(LPCWSTR p_FileName, ID3D11Device* p_Device)
{
	ID3DBlob* shaderBlob = nullptr;

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile
	( p_FileName
	, nullptr
	, nullptr
	,  "PS"
	, "ps_5_0"
	, shaderFlags
	, 0
	, &shaderBlob
	, &errorBlob);

	Assert(SUCCEEDED(hr), "Could not compile pixel shader! %s", (char*)errorBlob->GetBufferPointer());
	ProperlyRelease(errorBlob);

	p_Device->CreatePixelShader
	( shaderBlob->GetBufferPointer()
	, shaderBlob->GetBufferSize()
	, nullptr
	, &m_ShaderPointer);

	ProperlyRelease(shaderBlob);
}

void PixelShader::Release()
{
	ProperlyRelease(m_ShaderPointer);
}

void PixelShader::Bind(ID3D11DeviceContext* p_Context) const
{
	p_Context->PSSetShader(m_ShaderPointer, nullptr, 0);
}