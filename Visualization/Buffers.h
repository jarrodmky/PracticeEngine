#ifndef IncludedVisuBufferH
#define IncludedVisuBufferH

//===========================================================================
// Filename:	Buffer.h
// Author:		Jarrod MacKay
// Description:	Abstracts a data buffer
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include "System.h"

namespace Visualization
{
//===========================================================================
// Definitions
//===========================================================================

	enum IndexTopology
	{
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip
	};

//===========================================================================
// Classes
//===========================================================================

	template <typename t_VertexType>
	class VertexBuffer
	{
	//Attributes
	private:
		ID3D11Buffer* m_Buffer;
		ID3D11Device* m_RenderDevice;

	//Operations
	public:

		VertexBuffer();

		~VertexBuffer();

	private:

		NonCopyable(VertexBuffer<t_VertexType>);

	//Methods
	public:

		void Allocate(const t_VertexType* p_Array, const u32 p_Size, ID3D11Device* p_Device);

		void Free();

		void Bind(ID3D11DeviceContext* p_Context) const;
	};

//---------------------------------------------------------------------------

	template <typename t_IndexType>
	class IndexBuffer
	{
	//Attributes
	private:

		ID3D11Buffer* m_Buffer;
		ID3D11Device* m_RenderDevice;
		IndexTopology m_Topology;

	//Operations
	public:

		IndexBuffer();

		~IndexBuffer();

	private:

		NonCopyable(IndexBuffer<t_IndexType>);

	//Methods
	public:

		void Allocate(const t_IndexType* p_Array, const u32 p_Size, ID3D11Device* p_Device, const IndexTopology p_Topology);

		void Free();

		void Bind(ID3D11DeviceContext* p_Context) const;
	};

#include "Buffers.inl"
}

#endif // #ifndef IncludedVisuBufferH