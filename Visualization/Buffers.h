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
#include "DataStructures.h"

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

	template <typename t_VertexType>
	class DynamicVertexBuffer
	{
	//Attributes
	private:

		System& m_System;
		ID3D11Buffer* m_GPUBuffer;
		Abstracts::List<t_VertexType> m_CPUBuffer;

	//Operations
	public:

		DynamicVertexBuffer(System& p_System);
		~DynamicVertexBuffer();

		inline const t_VertexType operator[](const u32 p_Index) const;
		inline t_VertexType& operator[](const u32 p_Index);

	private:

		NonCopyable(DynamicVertexBuffer<t_VertexType>);

	//Methods
	public:

		void Allocate(const u32 p_Size);

		inline const u32 GetCapacity() const;
		inline const u32 GetNumberOfVertices() const;

		void Add(const t_VertexType& p_Value);

		void Clear();

		void Free();

		void Bind();
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

	//---------------------------------------------------------------------------

	template <typename t_Type>
	class ConstantBuffer
	{
	//Attributes
	private:

		System& m_System;
		ID3D11Buffer* m_Buffer;

	//Operations
	public:

		ConstantBuffer(System& p_System);
		~ConstantBuffer();

	private:

		NonCopyable(ConstantBuffer<t_Type>);

	//Methods
	public:

		void Allocate(const t_Type* p_Object = nullptr);

		void Set(const t_Type* p_Object);

		void Free();

		void BindToVertexShader(u32 p_Slot = 0) const;
		void BindToGeometryShader(u32 p_Slot = 0) const;
		void BindToPixelShader(u32 p_Slot = 0) const;
		void BindToComputeShader(u32 p_Slot = 0) const;

	private:

		u32 GetPaddedSize() const;
	};

	#include "Buffers.inl"
}

#endif // #ifndef IncludedVisuBufferH