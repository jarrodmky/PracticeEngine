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

#include "List.h"

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

		List<t_Type> m_List;

	//Operators
	public:

		Stack(const u32 p_Capacity = 4)
			: m_List(p_Capacity)
		{}

		~Stack() {}

		Stack(const Stack& p_Other)
			: m_List(p_Other.m_List)
		{}

		Stack& operator = (const Stack& p_Lhs)
		{
			m_List = p_Lhs.m_List;
			return *this;
		}

	//Methods
	public:

		inline void Clear()
		{
			m_List.Clear();
		}

		inline void Destroy()
		{
			m_List.Destroy();
		}

		inline void Push(const t_Type& p_Value)
		{
			m_List.Add(p_Value);
		}

		inline bool Pop(t_Type& p_Value)
		{
			return m_List.Remove(p_Value);
		}

		inline bool Peek(t_Type& p_Value) const
		{
			return m_List.Peek(GetNumberOfElements() - 1, p_Value);
		}

		inline void Reserve(const u32 p_NewCapacity)
		{
			m_List.Reserve(p_NewCapacity);
		}

		inline u32 GetNumberOfElements() const
		{
			return m_List.GetNumberOfElements();
		}

		inline bool IsEmpty() const
		{
			return m_List.IsEmpty();
		}
	};
} // namespace Abstracts
#endif // #ifndef IncludedAbstStackH