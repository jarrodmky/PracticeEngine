#ifndef IncludedAbstLinkedListH
#define IncludedAbstLinkedListH

//===========================================================================
// Filename:	LinkedList.h
// Author:		Jarrod MacKay
// Description:	Defines a resizable array of ordered elements.
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
	class LinkedList
	{
	//Definitions
	private:

		template<typename t_Type>
		class Node
		{
		//Attributes
		public:

			Node<t_Type>* Last;
			Node<t_Type>* Next;
			t_Type m_Data;

		//Operators
		public:

			Node()
			: Last(nullptr)
			, Next(nullptr)
			{}

			Node(const Node<t_Type>* p_LastNode, const Node<t_Type>* p_NextNode)
			: Last(p_LastNode)
			, Next(p_NextNode)
			{}

			~Node()
			{
				Last = nullptr;
				Next = nullptr;
			}
		};
		using DataNode = Node<t_Type>;
		using DataList = List<DataNode>;

	//Attributes
	private:

		DataNode m_Sentinal;

		DataList m_List;

	//Operators
	public:

		LinkedList(const u32 p_Capacity = 4)
			: m_Sentinal()
			, m_List(p_Capacity)
		{}

		~LinkedList() {}

	private:

		NonCopyable(LinkedList<t_Type>);

		//gets a pointer to the Nth list member
		DataNode* operator[](const u32 p_Index)
		{
			Assert(0 <= p_Index && p_Index < m_NumberOfElements, "Index out of bounds!");
			
			DataNode* cursor = m_Sentinal->Next;
			u32 count = 0;
			while (cursor != m_Sentinal && count != p_Index)
			{
				cursor = cursor->Next;
				++count;
			}

			return (cursor == m_Sentinal) ? (nullptr) : (cursor);
		}

	//Methods
	public:

		void Clear()
		{
			m_List.Clear();
			m_Sentinal.Last = nullptr;
			m_Sentinal.Next = nullptr;
		}

		void Shrink()
		{
			m_List.Reserve(m_List.GetNumberOfElements());
		}

		//Add element at index
		void Add(const u32 p_Index, const t_Type& p_Value)
		{
			//add element to the list
			Assert(p_Index <= m_List.GetNumberOfElements(), "Invalid index used to add node!");
			m_List.Add(p_Value);

			//find a pointer to the element at given index
			DataNode* cursor = m_List[p_Index];

			DataNode* lastElement = m_List[m_List.GetNumberOfElements()];

			//save point to the previous
			DataNode* lastNode = cursor->Last;

			//save pointer to next node
			DataNode* nextNode = cursor->Next;

			cursor->Next = cursor;

			cursor->Last = lastNode;
		}

		bool Remove(const u32 p_Index, t_Type& p_Value)
		{
			return ;
		}

		bool Peek(const u32 p_Index, t_Type& p_Value) const
		{
			return m_List(p_Value);
		}

		void Reserve(const u32 p_NewCapacity)
		{
			m_List.Reserve(p_NewCapacity);
		}

		inline DataNode& Front() const
		{
			return m_Sentinal.NextIndex;
		}

		inline DataNode& Back() const
		{
			return m_Sentinal.LastIndex;
		}

		inline u32 GetNumberOfElements() const
		{
			return m_List.GetNumberOfElements();
		}

		inline bool IsEmpty() const
		{
			return (m_List.GetNumberOfElements() == 0);
		}
	};
} // namespace Abstracts
#endif // #ifndef IncludedAbstLinkedListH