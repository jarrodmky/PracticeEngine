#include "Precompiled.h"
#include "Shader.h"
#include "Vertex.h"

using namespace Visualization;

	//==========
	// Shader
	//==========

Shader::Shader(System& p_System, const LPCSTR p_EntryName, const LPCSTR p_ShaderLevel, const LPCWSTR p_FileName)
: m_System(p_System)
, m_EntryName(p_EntryName)
, m_ShaderLevel(p_ShaderLevel)
, m_FileName(p_FileName)
{
	Assert(m_EntryName.size() > 0, "Empty entry name!");
}

Shader::~Shader() {}

void Shader::Compile()
{
	ID3DBlob* shaderBlob = nullptr;

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile
		(m_FileName.c_str()
		, nullptr
		, nullptr
		, m_EntryName.c_str()
		, m_ShaderLevel.c_str()
		, shaderFlags
		, 0
		, &shaderBlob
		, &errorBlob);

	Assert(SUCCEEDED(hr), "Could not compile the shader! Error: %s", (char*)(errorBlob->GetBufferPointer()));
	ProperlyRelease(errorBlob);

	SetSpecificShader(shaderBlob);

	ProperlyRelease(shaderBlob);
}

	//==========
	// Geometry Shader
	//==========

GeometryShader::GeometryShader(System& p_System, const LPCWSTR p_FileName)
: Shader(p_System, "GS", "gs_5_0", p_FileName)
, m_ShaderPointer(nullptr)
{
}

GeometryShader::~GeometryShader()
{
	Assert(nullptr == m_ShaderPointer, "Not released!");
}

void GeometryShader::Release()
{
	ProperlyRelease(m_ShaderPointer);
}

void GeometryShader::Bind() const
{
	m_System.GetContext()->GSSetShader(m_ShaderPointer, nullptr, 0);
}

void GeometryShader::Unbind() const
{
	m_System.GetContext()->GSSetShader(nullptr, nullptr, 0);
}

void GeometryShader::SetSpecificShader(ID3DBlob* p_Blob)
{
	m_System.GetDevice()->CreateGeometryShader
		(p_Blob->GetBufferPointer()
		, p_Blob->GetBufferSize()
		, nullptr
		, &m_ShaderPointer);
}

	//==========
	// Pixel Shader
	//==========

PixelShader::PixelShader(System& p_System, const LPCWSTR p_FileName)
: Shader(p_System, "PS", "ps_5_0", p_FileName)
, m_ShaderPointer(nullptr)
{
}

PixelShader::~PixelShader()
{
	Assert(nullptr == m_ShaderPointer, "Not released!");
}

void PixelShader::Release()
{
	ProperlyRelease(m_ShaderPointer);
}

void PixelShader::Bind() const
{
	m_System.GetContext()->PSSetShader(m_ShaderPointer, nullptr, 0);
}

void PixelShader::Unbind() const
{
	m_System.GetContext()->PSSetShader(nullptr, nullptr, 0);
}

void PixelShader::SetSpecificShader(ID3DBlob* p_Blob)
{
	m_System.GetDevice()->CreatePixelShader
		(p_Blob->GetBufferPointer()
		, p_Blob->GetBufferSize()
		, nullptr
		, &m_ShaderPointer);
}