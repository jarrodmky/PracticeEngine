template <typename t_VertexType>
void Visualization::VertexShader<t_VertexType>::Compile(LPCWSTR p_FileName, ID3D11Device* p_Device)
{
	ID3DBlob* shaderBlob = nullptr;	
	
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile
	( p_FileName
	, nullptr
	, nullptr
	,  "VS"
	, "vs_5_0"
	, shaderFlags
	, 0
	, &shaderBlob
	, &errorBlob);

	Assert(SUCCEEDED(hr), "Could not compile vertex shader! %s", (char*)errorBlob->GetBufferPointer());
	ProperlyRelease(errorBlob);

	p_Device->CreateVertexShader
	( shaderBlob->GetBufferPointer()
	, shaderBlob->GetBufferSize()
	, nullptr
	, &m_ShaderPointer);

	Visualization::MeshUtil::LayoutVector layout;
	Visualization::MeshUtil::CreateVertexLayout(t_VertexType::Format, layout);

	p_Device->CreateInputLayout
		(&layout[0]
		, layout.size()
		, shaderBlob->GetBufferPointer()
		, shaderBlob->GetBufferSize()
		, &m_InputLayout);

	ProperlyRelease(shaderBlob);
}

template <typename t_VertexType>
void Visualization::VertexShader<t_VertexType>::Release()
{
	ProperlyRelease(m_ShaderPointer);
	ProperlyRelease(m_InputLayout);
}

template <typename t_VertexType>
void Visualization::VertexShader<t_VertexType>::Bind(ID3D11DeviceContext* p_Context) const
{
	p_Context->IASetInputLayout(m_InputLayout);
	p_Context->VSSetShader(m_ShaderPointer, nullptr, 0);
}