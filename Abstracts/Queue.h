#ifndef IncludedAbstQueueH
#define IncludedAbstQueueH

//===========================================================================
// Filename:	Queue.h
// Author:		Jarrod MacKay
// Description:	Defines a resizable array of ordered elements.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "LinkedList.h"

//===========================================================================
// Templates
//===========================================================================

namespace Abstracts
{

	template<typename t_Type>
	class Queue
	{

	//Attributes
	private:

		LinkedList<t_Type> m_List;

	//Operators
	public:

		Queue(const u32 p_Capacity = 4)
			: m_List(p_Capacity)
		{}

		~Queue() {}

		Queue(const Queue& p_Other)
			: m_List(p_Other.m_List)
		{}

		inline Queue& operator =(const Queue& p_Lhs)
		{
			m_List = p_Lhs.m_List;
			return *this;
		}

	//Methods
	public:

		inline void Clear()
		{
		}

		inline void Push(const t_Type& p_Value)
		{
		}

		inline bool Pop(t_Type& p_Value)
		{
			return false;
		}

		inline bool Peek(t_Type& p_Value) const
		{
			return false;
		}

		void Reserve(const u32 p_NewCapacity)
		{
			m_List.Reserve(p_NewCapacity);
		}

		inline u32 GetNumberOfElements() const
		{
			return 0;
		}

		inline bool IsEmpty() const
		{
			return false;
		}
	};
} // namespace Abstracts
#endif // #ifndef IncludedAbstQueueH