#ifndef IncludedAbstStackH
#define IncludedAbstStackH

//===========================================================================
// Filename:	Stack.h
// Author:		Jarrod MacKay
// Description:	Defines a traditional stack
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "DynamicArray.h"
#define INIT_CAP 8


//===========================================================================
// Templates
//===========================================================================

namespace Abstracts
{

	template<typename t_Type>
	class Stack
	{
		//Attributes
	private:

		DynamicArray<t_Type> m_Array;

		u32 m_Size;

		//Operators
	public:

		inline Stack(const u32 p_Capacity = INIT_CAP)
			: m_Size(0)
			, m_Array(t_Type(), p_Capacity)
		{}

		inline ~Stack() {}

		inline Stack(const Stack& p_Other)
			: m_Size(p_Other.m_Size)
			, m_Array(p_Other.m_Array)
		{}

		inline Stack& operator = (const Stack& p_Other)
		{
			m_Size = p_Other.m_Size;
			m_Array = p_Other.m_Array;
			return *this;
		}

		inline t_Type& operator [](const u32 p_Index)
		{
			Assert(p_Index < m_Size, "Invalid index!");
			return m_Array[p_Index];
		}

		inline const t_Type& operator [](const u32 p_Index) const
		{
			Assert(p_Index < m_Size, "Invalid index!");
			return m_Array[p_Index];
		}

		//Methods
	public:

		inline void Clear()
		{
			m_Size = 0;
		}

		inline void Destroy()
		{
			m_Size = 0;
			m_Array.Resize(INIT_CAP);
		}

		inline const t_Type* const Array() const
		{
			return m_Array.Raw();
		}

		void Push(const t_Type& p_Value)
		{
			if (IsFull())
			{
				Reserve(m_Array.Size() << 1);
			}
			m_Array[m_Size++] = p_Value;
		}

		void Push(const t_Type* p_Values, const u32 p_Size)
		{
			const u32 totalSize = Size() + p_Size;
			if (Capacity() < totalSize)
			{
				Reserve(totalSize << 1);
			}
			m_Array.Store(p_Values, p_Size, m_Size);
			m_Size = totalSize;
		}

		inline const t_Type Peek() const
		{
			Assert(!IsEmpty(), "Peeking into empty stack!");
			return m_Array[m_Size - 1];
		}

		inline void Peek(t_Type& p_Value) const
		{
			p_Value = Peek();
		}

		inline const t_Type Pull()
		{
			t_Type ret = Peek();
			--m_Size;
			return ret;
		}

		inline const void Pull(t_Type& p_Value)
		{
			p_Value = Pull();
		}

		inline void Reserve(const u32 p_NewCapacity)
		{
			Assert(m_Size <= p_NewCapacity, "Invalid capacity!");
			m_Array.Resize(p_NewCapacity);
		}

		inline void Shrink()
		{
			Reserve(m_Size);
		}

		inline const u32 Size() const
		{
			return m_Size;
		}

		inline const u32 Capacity() const
		{
			return m_Array.Size();
		}

		inline const bool IsEmpty() const
		{
			return Size() == 0;
		}

		inline const bool IsFull() const
		{
			return Size() == Capacity();
		}
	};
} // namespace Abstracts
#undef INIT_CAP
#endif // #ifndef IncludedAbstStackH