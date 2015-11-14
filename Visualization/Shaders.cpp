#include "Precompiled.h"
#include "Shaders.h"
#include "Vertices.h"


namespace
{
	void CompileFileIntoShader(ID3DBlob*& p_ShaderBlob, LPCWSTR p_FileName, LPCSTR p_EntryPoint, LPCSTR p_Target)
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
		ID3DBlob* errorBlob = nullptr;
		HRESULT hr = D3DCompileFromFile
		( p_FileName
		, nullptr
		, nullptr
		, p_EntryPoint
		, p_Target
		, shaderFlags
		, 0
		, &p_ShaderBlob
		, &errorBlob);

		Assert(SUCCEEDED(hr), "Could not compile vertex shader! %s", (char*)errorBlob->GetBufferPointer());
		ProperlyRelease(errorBlob);
	}
}



using namespace Visualization;

void VertexShader::Compile(LPCWSTR p_FileName, ID3D11Device* p_Device)
{
	ID3DBlob* shaderBlob = nullptr;
	CompileFileIntoShader(shaderBlob, p_FileName, "VS", "vs_5_0");

	p_Device->CreateVertexShader
	( shaderBlob->GetBufferPointer()
	, shaderBlob->GetBufferSize()
	, nullptr
	, &m_ShaderPointer);

	p_Device->CreateInputLayout
		( BasicVertex::Layout
		, BasicVertex::NumberOfComponents
		, shaderBlob->GetBufferPointer()
		, shaderBlob->GetBufferSize()
		, &m_InputLayout);

	ProperlyRelease(shaderBlob);
}

void VertexShader::Release()
{
	ProperlyRelease(m_ShaderPointer);
	ProperlyRelease(m_InputLayout);
}

void VertexShader::Bind(ID3D11DeviceContext* p_Context) const
{
	p_Context->IASetInputLayout(m_InputLayout);
	p_Context->VSSetShader(m_ShaderPointer, nullptr, 0);
}

void PixelShader::Compile(LPCWSTR p_FileName, ID3D11Device* p_Device)
{
	ID3DBlob* shaderBlob = nullptr;
	CompileFileIntoShader(shaderBlob, p_FileName, "PS", "ps_5_0");

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