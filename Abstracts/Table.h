#ifndef IncludedAbstTableH
#define IncludedAbstTableH

//===========================================================================
// Filename:	Table.h
// Author:		Jarrod MacKay
// Description:	Defines a dynamic 2 dimensional array
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include "List.h"

//===========================================================================
// Templates
//===========================================================================

namespace Abstracts
{

	template<typename t_Type>
	class Table
	{
		//Attributes
	private:

		u32 m_NumberOfElements;

		u32 m_Capacity;

		List m_Array;

		//Operators
	public:

		Table(const u32 p_Capacity = 4)
			: m_NumberOfElements(0)
			, m_Capacity(p_Capacity)
			, m_Array(std::make_unique<t_Type[]>(p_Capacity))
		{}

		Table(const u32 p_FillToSize, const t_Type& p_InitialValue)
			: m_NumberOfElements(0)
			, m_Capacity(p_FillToSize)
			, m_Array(std::make_unique<t_Type[]>(p_FillToSize))
		{
			Fill(p_InitialValue);
		}

		~Table() {}

		Table(const Table& p_Other)
			: m_NumberOfElements(p_Other.m_NumberOfElements)
			, m_Capacity(p_Other.m_Capacity)
			, m_Array(std::make_unique<t_Type[]>(p_Other.m_Capacity))
		{
			CopyFrom(p_Other);
		}

		Table& operator = (const Table& p_Lhs)
		{
			m_Capacity = p_Lhs.m_Capacity;
			m_NumberOfElements = p_Lhs.m_NumberOfElements;

			m_Array.reset(std::make_unique<t_Type[]>(p_Other.m_Capacity));

			CopyFrom(p_Lhs);

			return *this;
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

		inline void Allocate(const t_Type& p_Value = t_Type())
		{
			std::fill(m_Array, (m_Array + m_Capacity), p_Value);
			m_NumberOfElements = m_Capacity;
		}

		inline void Free()
		{
			m_Array.resset(nullptr);

		}

		inline void Clear()
		{
			m_NumberOfElements = 0;
		}

		void Reserve(const u32 p_NewCapacity)
		{
		}

		inline u32 GetNumberOfElements() const
		{
			return m_NumberOfElements;
		}

	private:

		void CopyFrom(const Table& p_Source)
		{
			Assert(m_Capacity >= p_Source.m_NumberOfElements
				&& m_NumberOfElements == p_Source.m_NumberOfElements, "No room!");
			std::copy(p_Source.m_Array.get(), p_Source.m_Array.get() + m_NumberOfElements, m_Array);
		}
	};
} // namespace Abstracts
#endif // #ifndef IncludedAbstTableH