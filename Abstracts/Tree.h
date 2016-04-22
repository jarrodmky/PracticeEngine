#ifndef IncludedAbstTreeH
#define IncludedAbstTreeH

//===========================================================================
// Filename:	Tree.h
// Author:		Jarrod MacKay
// Description:	A k-ary tree
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

	template<u32 t_Degree, typename t_LeafType, typename t_ForkType>
	class Tree
	{
	//Attributes
	private:

	//Operators
	public:

		Tree(const u32 p_Capacity = 4)
			: m_NumberOfElements(0)
			, m_Capacity(p_Capacity)
			, m_Array(std::make_unique<t_Type[]>(p_Capacity))
		{}

		//rule of 5
		~Tree() 
		{
			Assert(IsDestroyed(), "Tree not destroyed!");
		}

		Tree(const Tree& p_Other)
			: m_NumberOfElements(p_Other.m_NumberOfElements)
			, m_Capacity(p_Other.m_Capacity)
			, m_Array(std::make_unique<t_Type[]>(p_Other.m_Capacity))
		{
			for(u32 i = 0; i < m_NumberOfElements; ++i)
			{
				m_Array[i] = p_Other.m_Array[i];
			}
		}

		Tree(const Tree&& p_Other)
			: m_NumberOfElements(p_Other.m_NumberOfElements)
			, m_Capacity(p_Other.m_Capacity)
			, m_Array(std::move(p_Other.m_Array))
		{}
		
		Tree& operator=(const Tree& p_Other)
		{
			m_Capacity = p_Lhs.m_Capacity;
			m_NumberOfElements = p_Lhs.m_NumberOfElements;

			m_Array.reset(std::make_unique<t_Type[]>(*p_Other.m_Array));
			return *this,
		}

		Tree& operator=(Tree&& p_Other)
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

	private:
	};

	template <typename t_NodeType>
	using BinaryTree<t_NodeType> = Tree<2, t_NodeType, t_NodeType>;
} // namespace Abstracts
#endif // #ifndef IncludedAbstTreeH