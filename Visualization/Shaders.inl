//===========================================================================
// Filename:	Shaders.inl
// Author:		Jarrod MacKay
//===========================================================================

namespace Visualization
{

template <typename t_VertexType>
VertexShader<t_VertexType>::VertexShader(System& p_System)
: m_System(p_System)
, m_InputLayout(nullptr)
, m_ShaderPointer(nullptr)
{}

template <typename t_VertexType>
VertexShader<t_VertexType>::~VertexShader()
{
	Assert(nullptr == m_ShaderPointer && nullptr == m_InputLayout, "Not released!");
}

template <typename t_VertexType>
void VertexShader<t_VertexType>::Compile(LPCWSTR p_FileName, LPCSTR p_EntryName, LPCSTR p_ShaderLevel)
{
	ID3DBlob* shaderBlob = nullptr;	
	
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile
	( p_FileName
	, nullptr
	, nullptr
	, p_EntryName
	, p_ShaderLevel
	, shaderFlags
	, 0
	, &shaderBlob
	, &errorBlob);

	Assert(SUCCEEDED(hr), "Could not compile vertex shader! %s", (char*)errorBlob->GetBufferPointer());
	ProperlyRelease(errorBlob);

	m_System.GetDevice()->CreateVertexShader
	( shaderBlob->GetBufferPointer()
	, shaderBlob->GetBufferSize()
	, nullptr
	, &m_ShaderPointer);

	MeshUtil::LayoutVector layout;
	MeshUtil::CreateVertexLayout(t_VertexType::Format, layout);

	m_System.GetDevice()->CreateInputLayout
		(&layout[0]
		, layout.size()
		, shaderBlob->GetBufferPointer()
		, shaderBlob->GetBufferSize()
		, &m_InputLayout);

	ProperlyRelease(shaderBlob);
}

template <typename t_VertexType>
void VertexShader<t_VertexType>::Release()
{
	ProperlyRelease(m_ShaderPointer);
	ProperlyRelease(m_InputLayout);
}

template <typename t_VertexType>
void VertexShader<t_VertexType>::Bind() const
{
	m_System.GetContext()->IASetInputLayout(m_InputLayout);
	m_System.GetContext()->VSSetShader(m_ShaderPointer, nullptr, 0);
}
}