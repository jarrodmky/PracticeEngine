#include "Precompiled.h"
#include "Graph.h"

using namespace Abstracts;

//Node implementation
Graph::Node::Node()
: m_Index(0)
, m_NumberOfNeighbours(0)
{
	memset(m_Neighbours, 0, LengthOf(m_Neighbours));
}

void Graph::Node::AddNeighbour(Node* p_Node)
{
	Assert(p_Node != nullptr, "A new neighbour must be non-null!")
	Assert(m_NumberOfNeighbours < kMaxNeighbours, "Too many neighbours!");
	m_Neighbours[m_NumberOfNeighbours++] = p_Node;
}

u32 Graph::Node::GetNumberOfNeighbours() const
{
	return m_NumberOfNeighbours;
}

Graph::Node* Graph::Node::GetNeighbour(const u32 p_Index)
{
	Assert(p_Index >= 0 && p_Index < kMaxNeighbours, "Node index is out of bounds!");
	return m_Neighbours[p_Index];
}

const Graph::Node* Graph::Node::GetNeighbour(const u32 p_Index) const
{
	Assert(p_Index >= 0 && p_Index < kMaxNeighbours, "Node index is out of bounds!");
	return m_Neighbours[p_Index];
}

//Graph implementation
Graph::Graph()
: m_NumberOfNodes(0)
, m_Nodes(nullptr)
{}

Graph::~Graph()
{
	Assert(m_Nodes == nullptr, "Graph nodes were not freed!");
}

void Graph::Allocate(const u32 p_NumberOfNodes)
{
	Assert(m_Nodes == nullptr, "Graph nodes already exist!");
	Assert(p_NumberOfNodes > 0, "[graph.cpp] Need a valid number of nodes!");
	m_NumberOfNodes = p_NumberOfNodes;
	m_Nodes = new Node[m_NumberOfNodes];

	for(u32 i = 0; i < m_NumberOfNodes; ++i)
	{
		m_Nodes[i].m_Index = i;
	}
}

void Graph::Free()
{
	ProperlyDeleteArray(m_Nodes);
	m_NumberOfNodes = 0;
}

u32 Graph::GetNumberOfNodes() const
{
	return m_NumberOfNodes;
}

Graph::Node& Graph::GetNode(const u32 p_Index)
{
	Assert(p_Index < m_NumberOfNodes, "Invalid index!");
	return m_Nodes[p_Index];
}

const Graph::Node& Graph::GetNode(const u32 p_Index) const
{
	Assert(p_Index < m_NumberOfNodes, "Invalid index!");
	return m_Nodes[p_Index];
}