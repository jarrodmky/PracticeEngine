#ifndef IncludedAbstListH
#define IncludedAbstListH

//===========================================================================
// Filename:	List.h
// Author:		Jarrod MacKay
// Description:	Defines a resizable array of unordered elements (think std::vector).
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>

//===========================================================================
// Templates
//===========================================================================

namespace Abstracts
{

	template<typename t_Type>
	class List
	{
	//Attributes
	private:

		u32 m_NumberOfElements;

		u32 m_Capacity;

		std::unique_ptr<t_Type[]> m_Array;

	//Operators
	public:

		List(const u32 p_Capacity = 4)
			: m_NumberOfElements(0)
			, m_Capacity(p_Capacity)
			, m_Array(std::make_unique<t_Type[]>(p_Capacity))
		{}

		List(const u32 p_FillToSize, const t_Type& p_InitialValue)
			: m_NumberOfElements(0)
			, m_Capacity(p_FillToSize)
			, m_Array(std::make_unique<t_Type[]>(p_FillToSize))
		{
			Fill(p_InitialValue);
		}

		//rule of 5
		~List() 
		{
			Assert(IsDestroyed(), "List not destroyed!");
		}

		List(const List& p_Other)
			: m_NumberOfElements(p_Other.m_NumberOfElements)
			, m_Capacity(p_Other.m_Capacity)
			, m_Array(std::make_unique<t_Type[]>(p_Other.m_Capacity))
		{
			for(u32 i = 0; i < m_NumberOfElements; ++i)
			{
				m_Array[i] = p_Other.m_Array[i];
			}
		}

		List(const List&& p_Other)
			: m_NumberOfElements(p_Other.m_NumberOfElements)
			, m_Capacity(p_Other.m_Capacity)
			, m_Array(std::move(p_Other.m_Array))
		{}
		
		List& operator=(const List& p_Other)
		{
			m_Capacity = p_Lhs.m_Capacity;
			m_NumberOfElements = p_Lhs.m_NumberOfElements;

			m_Array.reset(std::make_unique<t_Type[]>(*p_Other.m_Array));
			return *this,
		}

		List& operator=(List&& p_Other)
		{
			m_Capacity = p_Lhs.m_Capacity;
			m_NumberOfElements = p_Lhs.m_NumberOfElements;

			m_Array = std::move(p_Other.m_Array);
			return *this,
		}

		inline const t_Type& operator()(const u32 p_Index) const
		{
			Assert(0 <= p_Index && p_Index < m_NumberOfElements, "Index out of bounds!");
			return m_Array[p_Index];
		}

		inline t_Type& operator()(const u32 p_Index)
		{
			Assert(0 <= p_Index && p_Index < m_NumberOfElements, "Index out of bounds!");
			return m_Array[p_Index];
		}

	//Methods
	public:

		//raw array access
		inline t_Type* GetPointer() const
		{
			return m_Array.get();
		}

		//single value assignment
		inline void Fill(const t_Type& p_Value = t_Type())
		{
			std::fill(m_Array.get(), (m_Array.get() + m_Capacity), p_Value);
			m_NumberOfElements = m_Capacity;
		}

		inline void Clear()
		{
			m_NumberOfElements = 0;
		}

		inline void Destroy()
		{
			m_NumberOfElements = 0;
			m_Capacity = 0;
			m_Array.reset(nullptr);
		}

		inline void Shrink()
		{
			Reserve(m_NumberOfElements);
		}

		inline void Add(const t_Type& p_Value)
		{
			if (IsFull())
			{
				DoubleCapacity();
			}

			m_Array[m_NumberOfElements] = p_Value;
			++m_NumberOfElements;
		}

		inline bool Remove(t_Type& p_Value)
		{
			return Remove(m_NumberOfElements - 1, p_Value);
		}

		inline bool Peek(const u32 p_Index, t_Type& p_Value) const
		{
			Assert(p_Index < m_NumberOfElements, "Index out of bounds!");
			if (IsEmpty())
			{
				return false;
			}
			p_Value = m_Array[p_Index];
			return true;
		}

		void Reserve(const u32 p_NewCapacity)
		{
			//make new list and copy in values
			Assert(p_NewCapacity >= m_NumberOfElements, "Not enough room!");
			List newList(p_NewCapacity);

			m_Capacity = p_NewCapacity;

			//move to new array
			memcpy(newList.m_Array.get(), m_Array.get(), m_NumberOfElements);

			m_Array.swap(newList.m_Array);

			newList.Destroy();
		}

		void Resize(const t_Type* p_NewData, const u32 p_Size)
		{
			//make new list and copy in values
			List newList(p_Size);
			memcpy(newList.m_Array.get(), p_NewData, p_Size);

			m_Array.swap(newList.m_Array);

			newList.Destroy();

			m_Capacity = p_Size;
			m_NumberOfElements = p_Size;
		}

		void Resize(const u32 p_Size, const t_Type& p_Value = t_Type())
		{
			Reserve(p_Size);
			Fill(p_Value);
		}

		inline u32 GetNumberOfElements() const
		{
			return m_NumberOfElements;
		}

		inline u32 GetCapacity() const
		{
			return m_Capacity;
		}

		inline bool IsEmpty() const
		{
			return (m_NumberOfElements == 0);
		}

		inline bool IsFull() const
		{
			return (m_Capacity == m_NumberOfElements);
		}

		inline bool IsDestroyed() const
		{
			return (m_Capacity == 0 && m_Array == nullptr);
		}

	private:

		inline bool Remove(const u32 p_Index, t_Type& p_Value)
		{
			if(!Peek(p_Index, p_Value))
			{
				return false;
			}
			--m_NumberOfElements;
			m_Array[p_Index] = m_Array[m_NumberOfElements];
			return true;
		}

		inline void DoubleCapacity()
		{
			Reserve((m_Capacity == 0) ? (1) : (m_Capacity << 1));
		}
	};
} // namespace Abstracts
#endif // #ifndef IncludedAbstListH