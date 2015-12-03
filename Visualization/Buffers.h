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

//===========================================================================
// Classes
//===========================================================================

	template <typename t_VertexType>
	class VertexBuffer
	{
	//Attributes
	private:

		System& m_System;
		ID3D11Buffer* m_Buffer;

	//Operations
	public:

		VertexBuffer(System& p_System);

		~VertexBuffer();

	private:

		NonCopyable(VertexBuffer<t_VertexType>);

	//Methods
	public:

		void Allocate(const t_VertexType* p_Array, const u32 p_Size);

		void Free();

		void Bind() const;
	};

//---------------------------------------------------------------------------

	template <typename t_IndexType>
	class IndexBuffer
	{
	//Attributes
	private:
		
		System& m_System;
		ID3D11Buffer* m_Buffer;
		IndexTopology m_Topology;

	//Operations
	public:

		IndexBuffer(System& p_System);

		~IndexBuffer();

	private:

		NonCopyable(IndexBuffer<t_IndexType>);

	//Methods
	public:

		void Allocate(const t_IndexType* p_Array, const u32 p_Size, const IndexTopology p_Topology);

		void Free();

		void Bind() const;
	};

#include "Buffers.inl"
}

#endif // #ifndef IncludedVisuBufferH