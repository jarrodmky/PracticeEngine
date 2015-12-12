//===========================================================================
// Filename:	Buffers.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Class Definitions
//===========================================================================

namespace
{
	template <typename t_Type>
	void CreateStaticBuffer( ID3D11Buffer*& p_Buffer
					 , ID3D11Device* p_Device
					 , D3D11_BIND_FLAG p_Desc
					 , const t_Type* p_InitialData
					 , const u32 p_NumberOfElements
					 , const u32 p_ElementSize = sizeof(t_Type))
	{
		Assert(p_Buffer == nullptr, "Buffer previously allocated!");

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = p_NumberOfElements * p_ElementSize;
		bd.BindFlags = p_Desc;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA subresourceData;
		D3D11_SUBRESOURCE_DATA* subresourceDataPtr = nullptr;
		if (p_InitialData != nullptr)
		{
			ZeroMemory(&subresourceData, sizeof(subresourceData));
			subresourceData.pSysMem = p_InitialData;
			subresourceDataPtr = &subresourceData;
		}

		p_Device->CreateBuffer(&bd, subresourceDataPtr, &p_Buffer);
		Assert(p_Buffer != nullptr, "Could not create buffer!");
	}

	template <typename t_Type>
	void CreateDynamicBuffer(ID3D11Buffer*& p_Buffer
		, ID3D11Device* p_Device
		, D3D11_BIND_FLAG p_Desc
		, const u32 p_NumberOfElements
		, const u32 p_ElementSize = sizeof(t_Type))
	{
		Assert(p_Buffer == nullptr, "Buffer previously allocated!");

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = p_NumberOfElements * p_ElementSize;
		bd.BindFlags = p_Desc;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;

		p_Device->CreateBuffer(&bd, nullptr, &p_Buffer);
		Assert(p_Buffer != nullptr, "Could not create buffer!");
	}

	template <typename t_Type>
	void MapDynamicBuffer(ID3D11Buffer*& p_Buffer
		, ID3D11DeviceContext* p_Device
		, const t_Type* p_Data
		, const u32 p_NumberOfElements
		, const u32 p_ElementSize = sizeof(t_Type))
	{
		D3D11_MAPPED_SUBRESOURCE mappedRes;
		p_Device->Map(p_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
		memcpy(mappedRes.pData, p_Data, p_NumberOfElements * p_ElementSize);
		p_Device->Unmap(p_Buffer, 0);
	}
}

//==========
// Vertex Buffer
//==========

template <typename t_VertexType>
VertexBuffer<t_VertexType>::VertexBuffer(System& p_System)
	: m_System(p_System)
	, m_Buffer(nullptr)
{}

//---------------------------------------------------------------------------

template <typename t_VertexType>
VertexBuffer<t_VertexType>::~VertexBuffer()
{
	Assert(nullptr == m_Buffer, "Not released!");
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void VertexBuffer<t_VertexType>::Allocate(const t_VertexType* p_Array, const u32 p_Size)
{
	CreateStaticBuffer(m_Buffer, m_System.GetDevice(), D3D11_BIND_VERTEX_BUFFER, p_Array, p_Size);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void VertexBuffer<t_VertexType>::Free()
{
	ProperlyRelease(m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void VertexBuffer<t_VertexType>::Bind() const
{
	UINT stride = sizeof(t_VertexType);
	UINT offset = 0;
	m_System.GetContext()->IASetVertexBuffers(0, 1, &m_Buffer, &stride, &offset);
}

//==========
// Dynamic Buffer
//==========

template <typename t_VertexType>
DynamicVertexBuffer<t_VertexType>::DynamicVertexBuffer(System& p_System)
	: m_System(p_System)
	, m_GPUBuffer(nullptr)
	, m_CPUBuffer()
{}

//---------------------------------------------------------------------------

template <typename t_VertexType>
DynamicVertexBuffer<t_VertexType>::~DynamicVertexBuffer()
{
	Assert(nullptr == m_GPUBuffer, "Not released!");
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
const t_VertexType DynamicVertexBuffer<t_VertexType>::operator[](const u32 p_Index) const
{
	return m_CPUBuffer(p_Index);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
t_VertexType& DynamicVertexBuffer<t_VertexType>::operator[](const u32 p_Index)
{
	return m_CPUBuffer(p_Index);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void DynamicVertexBuffer<t_VertexType>::Allocate(const u32 p_Size)
{
	m_CPUBuffer.Reserve(p_Size);
	CreateDynamicBuffer<t_VertexType>(m_GPUBuffer, m_System.GetDevice(), D3D11_BIND_VERTEX_BUFFER, p_Size);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
const u32 DynamicVertexBuffer<t_VertexType>::GetCapacity() const
{
	return m_CPUBuffer.GetCapacity();
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
const u32 DynamicVertexBuffer<t_VertexType>::GetNumberOfVertices() const
{
	return m_CPUBuffer.GetNumberOfElements();
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void DynamicVertexBuffer<t_VertexType>::Add(const t_VertexType& p_Vertex)
{
	m_CPUBuffer.Add(p_Vertex);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void DynamicVertexBuffer<t_VertexType>::Clear()
{
	m_CPUBuffer.Clear();
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void DynamicVertexBuffer<t_VertexType>::Free()
{
	ProperlyRelease(m_GPUBuffer);
	m_CPUBuffer.Destroy();
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void DynamicVertexBuffer<t_VertexType>::Bind()
{
	u32 numElements(m_CPUBuffer.GetNumberOfElements());
	u32 stride = sizeof(t_VertexType);
	u32 offset = 0;

	MapDynamicBuffer(m_GPUBuffer, m_System.GetContext(), m_CPUBuffer.GetPointer(), numElements, stride);

	m_System.GetContext()->IASetVertexBuffers(0, 1, &m_GPUBuffer, &stride, &offset);
}

//==========
// Index Buffer
//==========

template <typename t_IndexType>
IndexBuffer<t_IndexType>::IndexBuffer(System& p_System)
	: m_System(p_System)
	, m_Buffer(nullptr)
	, m_Topology(PointList)
{}

//---------------------------------------------------------------------------

template <typename t_IndexType>
IndexBuffer<t_IndexType>::~IndexBuffer()
{
	Assert(nullptr == m_Buffer, "Not released!");
}

//---------------------------------------------------------------------------

template <typename t_IndexType>
void IndexBuffer<t_IndexType>::Allocate(const t_IndexType* p_Array, const u32 p_Size, const IndexTopology p_Topology)
{
	m_Topology = p_Topology;
	CreateStaticBuffer(m_Buffer, m_System.GetDevice(), D3D11_BIND_INDEX_BUFFER, p_Array, p_Size);
}

//---------------------------------------------------------------------------

template <typename t_IndexType>
void IndexBuffer<t_IndexType>::Free()
{
	ProperlyRelease(m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_IndexType>
void IndexBuffer<t_IndexType>::Bind() const
{
	ID3D11DeviceContext* context = m_System.GetContext();

	//set primitive topology
	switch (m_Topology)
	{
	case Visualization::PointList:
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case Visualization::LineList:
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case Visualization::LineStrip:
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		break;
	case Visualization::TriangleList:
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case Visualization::TriangleStrip:
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	default:
		Assert(false, "Topology is not set properly!");
		break;
	}
	
	context->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R32_UINT, 0); //TODO:: only good if u32 used...
}

//==========
// Constant Buffer
//==========

template <typename t_Type>
ConstantBuffer<t_Type>::ConstantBuffer(System& p_System)
	: m_System(p_System)
	, m_Buffer(nullptr)
{}

//---------------------------------------------------------------------------

template <typename t_Type>
ConstantBuffer<t_Type>::~ConstantBuffer()
{
	Assert(nullptr == m_Buffer, "Not released!");
}

//---------------------------------------------------------------------------

template <typename t_Type>
void ConstantBuffer<t_Type>::Allocate(const t_Type* p_Object)
{
	CreateStaticBuffer(m_Buffer, m_System.GetDevice(), D3D11_BIND_CONSTANT_BUFFER, p_Object, 1, GetPaddedSize());
}

//---------------------------------------------------------------------------

template <typename t_Type>
void ConstantBuffer<t_Type>::Set(const t_Type* p_Object)
{
	m_System.GetContext()->UpdateSubresource(m_Buffer, 0, nullptr, static_cast<const void*>(p_Object), 0, 0);
}

//---------------------------------------------------------------------------

template <typename t_Type>
void ConstantBuffer<t_Type>::Free()
{
	ProperlyRelease(m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_Type>
void ConstantBuffer<t_Type>::BindToVertexShader(u32 p_Slot) const
{
	m_System.GetContext()->VSSetConstantBuffers(p_Slot, 1, &m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_Type>
void ConstantBuffer<t_Type>::BindToGeometryShader(u32 p_Slot) const
{
	m_System.GetContext()->GSSetConstantBuffers(p_Slot, 1, &m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_Type>
void ConstantBuffer<t_Type>::BindToPixelShader(u32 p_Slot) const
{
	m_System.GetContext()->PSSetConstantBuffers(p_Slot, 1, &m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_Type>
void ConstantBuffer<t_Type>::BindToComputeShader(u32 p_Slot) const
{
	m_System.GetContext()->CSSetConstantBuffers(p_Slot, 1, &m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_Type>
u32 ConstantBuffer<t_Type>::GetPaddedSize() const
{
	const u32 typeSize = sizeof(t_Type);
	const u32 bufferSize = (typeSize % 16) ? ((typeSize / 16) + 1) * 16 : typeSize;
	return bufferSize;
}