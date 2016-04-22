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
	void CreateStaticBuffer(ID3D11Buffer*& p_Buffer
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
		, ID3D11DeviceContext* p_Context
		, D3D11_BIND_FLAG p_Desc
		, const t_Type* p_InitialData
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

		if (p_InitialData != nullptr)
		{
			MapDynamicBuffer(p_Buffer, p_Context, p_InitialData, p_NumberOfElements, p_ElementSize);
		}

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

	void SetTopology(ID3D11DeviceContext* p_Context, Mathematics::TopologyIndexing p_Topology)
	{
		using namespace Mathematics;
		switch (p_Topology)
		{
		case TopologyIndexing::PointList:
			p_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			break;
		case TopologyIndexing::LineList:
			p_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			break;
		case TopologyIndexing::LineStrip:
			p_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
			break;
		case TopologyIndexing::TriangleList:
			p_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			break;
		case TopologyIndexing::TriangleStrip:
			p_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			break;
		default:
			Halt("Topology is not set properly!");
			break;
		}
	}
}

//==========
// Abstract Graphics API Buffer
//==========

template <typename t_BufferedType>
GraphicsBuffer<t_BufferedType>::GraphicsBuffer(System& p_System)
	: m_System(p_System)
	, m_Buffer(nullptr)
	, m_Size(-1)
{}

//---------------------------------------------------------------------------

template <typename t_BufferedType>
GraphicsBuffer<t_BufferedType>::~GraphicsBuffer()
{
	Assert(-1 != m_Size, "Never allocated!");
	Assert(nullptr == m_Buffer && m_Size == 0, "Not released!");
}

//---------------------------------------------------------------------------

template <typename t_BufferedType>
void GraphicsBuffer<t_BufferedType>::Free()
{
	ProperlyRelease(m_Buffer);
	m_Size = 0;
}

//---------------------------------------------------------------------------

template <typename t_BufferedType>
const u32 GraphicsBuffer<t_BufferedType>::Size()
{
	return m_Size;
}

//==========
// Vertex Buffer
//==========

template <typename t_VertexType>
VertexBuffer<t_VertexType>::VertexBuffer(System& p_System)
	: GraphicsBuffer<t_VertexType>(p_System)
{}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void VertexBuffer<t_VertexType>::Allocate(const t_VertexType* p_Array, const u32 p_Size)
{
	m_Size = p_Size;
	CreateStaticBuffer(m_Buffer, m_System.GetDevice(), D3D11_BIND_VERTEX_BUFFER, p_Array, p_Size);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void VertexBuffer<t_VertexType>::Bind() const
{
	UINT stride = sizeof(t_VertexType);
	UINT offset = 0;
	m_System.GetContext()->IASetVertexBuffers(0, 1, &m_Buffer, &stride, &offset);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void VertexBuffer<t_VertexType>::Draw(const Mathematics::TopologyIndexing p_Topology) const
{
	SetTopology(m_System.GetContext(), p_Topology);
	m_System.GetContext()->Draw(m_Size, 0);
}

//==========
// Dynamic Buffer
//==========

template <typename t_VertexType>
DynamicVertexBuffer<t_VertexType>::DynamicVertexBuffer(System& p_System)
	: VertexBuffer<t_VertexType>(p_System)
	, m_VertexStack(0)
{}

//---------------------------------------------------------------------------

template <typename t_VertexType>
const t_VertexType DynamicVertexBuffer<t_VertexType>::operator[](const u32 p_Index) const
{
	return m_VertexStack[p_Index];
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
t_VertexType& DynamicVertexBuffer<t_VertexType>::operator[](const u32 p_Index)
{
	return m_VertexStack[p_Index];
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void DynamicVertexBuffer<t_VertexType>::Allocate(const t_VertexType* p_Array, const u32 p_MaxSize)
{
	m_Size = p_MaxSize;
	m_VertexStack.Reserve(m_Size);
	if (p_Array != nullptr)
	{
		m_VertexStack.Push(p_Array, m_Size);
	}
	CreateDynamicBuffer<t_VertexType>(m_Buffer, m_System.GetDevice(), m_System.GetContext()
		, D3D11_BIND_VERTEX_BUFFER, p_Array, m_Size);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void DynamicVertexBuffer<t_VertexType>::Free()
{
	m_VertexStack.Destroy();
	GraphicsBuffer<t_VertexType>::Free();
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void DynamicVertexBuffer<t_VertexType>::Draw(const Mathematics::TopologyIndexing p_Topology) const
{
	SetTopology(m_System.GetContext(), p_Topology);
	m_System.GetContext()->Draw(m_VertexStack.Size(), 0);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void DynamicVertexBuffer<t_VertexType>::Update()
{
	Assert(m_VertexStack.Capacity() == m_Size, "Allocation mismatch!");
	MapDynamicBuffer(m_Buffer, m_System.GetContext(), m_VertexStack.Array(), m_Size);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void DynamicVertexBuffer<t_VertexType>::Add(const t_VertexType& p_Vertex)
{
	Assert(!IsFull(), "No room on buffer!");
	m_VertexStack.Push(p_Vertex);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void DynamicVertexBuffer<t_VertexType>::Clear()
{
	m_VertexStack.Clear();
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
bool DynamicVertexBuffer<t_VertexType>::IsFull() const
{
	return m_VertexStack.Size() == m_Size;
}

//==========
// Index Buffer
//==========

template <typename t_IndexType>
IndexBuffer<t_IndexType>::IndexBuffer(System& p_System)
	: GraphicsBuffer<t_IndexType>(p_System)
{}

//---------------------------------------------------------------------------

template <typename t_IndexType>
void IndexBuffer<t_IndexType>::Allocate(const t_IndexType* p_Array, const u32 p_Size)
{
	m_Size = p_Size;
	CreateStaticBuffer(m_Buffer, m_System.GetDevice(), D3D11_BIND_INDEX_BUFFER, p_Array, p_Size);
}

//---------------------------------------------------------------------------

template <typename t_IndexType>
void IndexBuffer<t_IndexType>::Draw(const Mathematics::TopologyIndexing p_Topology) const
{
	using namespace Mathematics;
	ID3D11DeviceContext* context = m_System.GetContext();

	SetTopology(context, p_Topology);

	switch (sizeof(t_IndexType))
	{
	case 1:
		context->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R8_UINT, 0);
		break;
	case 2:
		context->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R16_UINT, 0);
		break;
	case 4:
		context->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R32_UINT, 0);
		break;
	default:
		Halt("Index is invalid!");
		break;
	}
	context->DrawIndexed(m_Size, 0, 0);
}

//==========
// Constant Buffer
//==========

template <typename t_ConstantType>
ConstantBuffer<t_ConstantType>::ConstantBuffer(System& p_System)
	: GraphicsBuffer<t_ConstantType>(p_System)
	, Data()
{}

//---------------------------------------------------------------------------

template <typename t_ConstantType>
void ConstantBuffer<t_ConstantType>::Allocate(const t_ConstantType* p_Array, const u32 p_Size)
{
	m_Size = p_Size;
	if(p_Array != nullptr)
	{
		Data = *p_Array;
	}
	CreateStaticBuffer(m_Buffer, m_System.GetDevice(), D3D11_BIND_CONSTANT_BUFFER, p_Array, p_Size, GetPaddedSize());
}

//---------------------------------------------------------------------------

template <typename t_ConstantType>
void ConstantBuffer<t_ConstantType>::BindToVertexShader(u32 p_Slot) const
{
	m_System.GetContext()->VSSetConstantBuffers(p_Slot, 1, &m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_ConstantType>
void ConstantBuffer<t_ConstantType>::BindToGeometryShader(u32 p_Slot) const
{
	m_System.GetContext()->GSSetConstantBuffers(p_Slot, 1, &m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_ConstantType>
void ConstantBuffer<t_ConstantType>::BindToPixelShader(u32 p_Slot) const
{
	m_System.GetContext()->PSSetConstantBuffers(p_Slot, 1, &m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_ConstantType>
void ConstantBuffer<t_ConstantType>::BindToComputeShader(u32 p_Slot) const
{
	m_System.GetContext()->CSSetConstantBuffers(p_Slot, 1, &m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_ConstantType>
void ConstantBuffer<t_ConstantType>::Update() const
{
	Assert(m_Buffer != nullptr, "Buffer was not initialized!");
	m_System.GetContext()->UpdateSubresource(m_Buffer, 0, nullptr, static_cast<const void*>(&Data), 0, 0);
}

//---------------------------------------------------------------------------

template <typename t_ConstantType>
u32 ConstantBuffer<t_ConstantType>::GetPaddedSize() const
{
	const u32 typeSize = sizeof(t_ConstantType);
	const u32 bufferSize = (typeSize % 16) ? ((typeSize / 16) + 1) * 16 : typeSize;
	return bufferSize;
}