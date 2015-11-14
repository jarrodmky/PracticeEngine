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
	void CreateBuffer( ID3D11Buffer*& p_Buffer
					 , const t_Type* p_Array
					 , const u32 p_Size
					 , ID3D11Device* p_Device
					 , D3D11_BIND_FLAG p_Desc)
	{
		Assert(p_Buffer == nullptr, "Buffer previously allocated!");

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = p_Size * sizeof(t_Type);
		bd.BindFlags = p_Desc;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));
		initData.pSysMem = p_Array;

		p_Device->CreateBuffer(&bd, &initData, &p_Buffer);
		Assert(p_Buffer != nullptr, "Could not create buffer!");
	}
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
VertexBuffer<t_VertexType>::VertexBuffer()
	: m_Buffer()
	, m_RenderDevice()
{}

//---------------------------------------------------------------------------

template <typename t_VertexType>
VertexBuffer<t_VertexType>::~VertexBuffer()
{
	Assert(nullptr == m_Buffer, "Not released!");
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void VertexBuffer<t_VertexType>::Allocate(const t_VertexType* p_Array, const u32 p_Size, ID3D11Device* p_Device)
{
	CreateBuffer(m_Buffer, p_Array, p_Size, p_Device, D3D11_BIND_VERTEX_BUFFER);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void VertexBuffer<t_VertexType>::Free()
{
	ProperlyRelease(m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_VertexType>
void VertexBuffer<t_VertexType>::Bind(ID3D11DeviceContext* p_Context) const
{
	UINT stride = sizeof(t_VertexType);
	UINT offset = 0;
	p_Context->IASetVertexBuffers(0, 1, &m_Buffer, &stride, &offset);
}

//---------------------------------------------------------------------------

template <typename t_IndexType>
IndexBuffer<t_IndexType>::IndexBuffer()
	: m_Buffer()
	, m_RenderDevice()
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
void IndexBuffer<t_IndexType>::Allocate(const t_IndexType* p_Array, const u32 p_Size, ID3D11Device* p_Device, const IndexTopology p_Topology)
{
	m_Topology = p_Topology;
	CreateBuffer(m_Buffer, p_Array, p_Size, p_Device, D3D11_BIND_INDEX_BUFFER);
}

//---------------------------------------------------------------------------

template <typename t_IndexType>
void IndexBuffer<t_IndexType>::Free()
{
	ProperlyRelease(m_Buffer);
}

//---------------------------------------------------------------------------

template <typename t_IndexType>
void IndexBuffer<t_IndexType>::Bind(ID3D11DeviceContext* p_Context) const
{
	//set primitive topology
	switch (m_Topology)
	{
	case Visualization::PointList:
		p_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case Visualization::LineList:
		p_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case Visualization::LineStrip:
		p_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		break;
	case Visualization::TriangleList:
		p_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case Visualization::TriangleStrip:
		p_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	default:
		Assert(false, "Topology is not set properly!");
		break;
	}
	
	p_Context->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R32_UINT, 0); //TODO:: only good if u32 used...
}