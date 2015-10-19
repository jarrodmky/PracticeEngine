#ifndef IncludedMathGraphH
#define IncludedMathGraphH

//===========================================================================
// Filename:	Graph.h
// Author:		Jarrod MacKay
// Description:	Provides a general graph structure.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>

//===========================================================================
// Classes
//===========================================================================

namespace Abstracts
{

class Graph
{
//Definitions
public:

	class Node
	{
		static const int kMaxNeighbours = 8;

	//Operations
	public:

		Node();

	//Methods
	public:

		void AddNeighbour(Node* p_Node);

		u32 GetNumberOfNeighbours() const;

		Node* GetNeighbour(const u32 p_Index);

		const Node* GetNeighbour(const u32 p_Index) const;

		u32 GetIndex() const {return m_Index;}

	//Attributes
	private:

		friend class Graph;

		u32 m_Index;

		u32 m_NumberOfNeighbours;

		Node* m_Neighbours[kMaxNeighbours];
	};

//Operations
public:

	Graph();
	~Graph();

	NonCopyable(Graph);

//Methods
public:

	void Allocate(const u32 p_NumberOfNodes);

	void Free();

	u32 GetNumberOfNodes() const;

	Node& GetNode(const u32 p_Index);

	const Node& GetNode(const u32 p_Index) const;

//Attributes
private:

	u32 m_NumberOfNodes;

	Node* m_Nodes;
};

} // namespace Abstracts 

#endif // #ifndef IncludedMathGraphH