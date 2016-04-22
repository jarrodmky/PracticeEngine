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

	template <typename t_BufferedType>
	class GraphicsBuffer
	{
	//Attributes
	protected:

		using BufferedType = t_BufferedType;

		System& m_System;
		ID3D11Buffer* m_Buffer;
		u32 m_Size;

	//Operations
	public:

		GraphicsBuffer(System& p_System);
		virtual ~GraphicsBuffer();

	private:

		NonCopyable(GraphicsBuffer<t_BufferedType>);

	//Methods
	public:

		virtual void Allocate(const t_BufferedType* p_BufferedObject, const u32 p_Size) = 0;

		virtual void Free();
		
		inline const u32 Size();
	};

	template <typename t_VertexType>
	class VertexBuffer : public GraphicsBuffer<t_VertexType>
	{
	//Attributes
	public:

		using VertexType = t_VertexType;

	//Operations
	public:

		VertexBuffer(System& p_System);
		virtual ~VertexBuffer() {}

	//Methods
	public:

		virtual void Allocate(const t_VertexType* p_Array, const u32 p_Size) override;

		virtual void Draw(const Mathematics::TopologyIndexing p_Topology) const;

		void Bind() const;
	};

	//---------------------------------------------------------------------------

	template <typename t_VertexType>
	class DynamicVertexBuffer : public VertexBuffer<t_VertexType>
	{
	//Attributes
	private:

		Abstracts::Stack<t_VertexType> m_VertexStack;

	//Operations
	public:

		DynamicVertexBuffer(System& p_System);
		virtual ~DynamicVertexBuffer() {}

		inline const t_VertexType operator[](const u32 p_Index) const;
		inline t_VertexType& operator[](const u32 p_Index);

	//Methods
	public:

		virtual void Allocate(const t_VertexType* p_Array, const u32 p_MaxSize) override;

		virtual void Free() override;

		virtual void Draw(const Mathematics::TopologyIndexing p_Topology) const override;

		void Update();

		void Add(const t_VertexType& p_Value);

		void Clear();

		bool IsFull() const;
	};

//---------------------------------------------------------------------------
	
	template <typename t_IndexType>
	class IndexBuffer : public GraphicsBuffer<t_IndexType>
	{
	//Operations
	public:

		IndexBuffer(System& p_System);
		virtual ~IndexBuffer() {}

	//Methods
	public:

		void Allocate(const t_IndexType* p_Array = nullptr, const u32 p_Size = 0) override;

		void Draw(const Mathematics::TopologyIndexing p_Topology) const;
	};

	//---------------------------------------------------------------------------

	template <typename t_ConstantType>
	class ConstantBuffer : public GraphicsBuffer<t_ConstantType>
	{
	//Attributes
	public:

		t_ConstantType Data;

	//Operations
	public:

		ConstantBuffer(System& p_System);
		virtual ~ConstantBuffer() {}

	//Methods
	public:

		void Allocate(const t_ConstantType* p_Array = nullptr, const u32 p_Size = 1) override;
		
		void BindToVertexShader(u32 p_Slot) const;
		void BindToGeometryShader(u32 p_Slot) const;
		void BindToPixelShader(u32 p_Slot) const;
		void BindToComputeShader(u32 p_Slot) const;

		void Update() const;

	private:

		u32 GetPaddedSize() const;
	};

	#include "Buffer.inl"
	#include "ShaderBuffers.inl"
}

#endif // #ifndef IncludedVisuBufferH