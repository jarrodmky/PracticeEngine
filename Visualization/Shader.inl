//===========================================================================
// Filename:	Shaders.inl
// Author:		Jarrod MacKay
//===========================================================================

template <typename t_VertexType>
VertexShader<t_VertexType>::VertexShader(System& p_System, const LPCWSTR p_FileName)
: Shader(p_System, "VS", "vs_5_0", p_FileName)
, m_InputLayout(nullptr)
, m_ShaderPointer(nullptr)
{}

template <typename t_VertexType>
VertexShader<t_VertexType>::~VertexShader()
{
	Assert(nullptr == m_ShaderPointer && nullptr == m_InputLayout, "Not released!");
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

template <typename t_VertexType>
void VertexShader<t_VertexType>::Unbind() const
{
	m_System.GetContext()->IASetInputLayout(nullptr);
	m_System.GetContext()->VSSetShader(nullptr, nullptr, 0);
}

template <typename t_VertexType>
void VertexShader<t_VertexType>::SetSpecificShader(ID3DBlob* p_Blob)
{
	m_System.GetDevice()->CreateVertexShader
	( p_Blob->GetBufferPointer()
	, p_Blob->GetBufferSize()
	, nullptr
	, &m_ShaderPointer);

	MeshUtil::LayoutVector layout;
	MeshUtil::CreateVertexLayout(t_VertexType::Format, layout);

	m_System.GetDevice()->CreateInputLayout
		(&layout[0]
		, layout.size()
		, p_Blob->GetBufferPointer()
		, p_Blob->GetBufferSize()
		, &m_InputLayout);

	Assert(m_InputLayout != nullptr, "Input assembly failed!");
}