#include "Precompiled.h"
#include "Grid.h"

using namespace Abstracts;

Grid::Grid()
: m_NumberOfColumns(0)
, m_NumberOfRows(0)
, m_Graph()
{}

Grid::~Grid(){}

void Grid::Initialize(u32 p_NumberOfRows, u32 p_NumberOfColumns)
{
	m_NumberOfColumns = p_NumberOfColumns;
	m_NumberOfRows = p_NumberOfRows;

	m_Graph.Allocate(p_NumberOfRows * p_NumberOfColumns);

	MooreNeighbourhood();
}

void Grid::Terminate()
{
	m_Graph.Free();

	m_NumberOfColumns = 0;
	m_NumberOfRows = 0;
}

const u32 Grid::GetNodeIndex(const u32 p_X, const u32 p_Y) const
{	
	Assert(p_X < m_NumberOfRows, "Invalid Coordinates");
	Assert(p_Y < m_NumberOfColumns, "Invalid Coordinates");

	return (p_X * m_NumberOfColumns) + p_Y;
}

const u32 Grid::GetX(const u32 p_Index) const
{
	Assert(p_Index < m_Graph.GetNumberOfNodes(), "Invalid Index.");
	return p_Index / m_NumberOfColumns;
}

const u32 Grid::GetY(const u32 p_Index) const
{
	Assert(p_Index < m_Graph.GetNumberOfNodes(), "Invalid Index.");
	return p_Index % m_NumberOfColumns;
}

const Graph::Node& Grid::GetNode(const u32 p_Index) const
{
	return m_Graph.GetNode(p_Index);
}

void Grid::MooreNeighbourhood()
{
	//Graph::Node UpN(nullptr);
	//Graph::Node* UpRightN(nullptr);
	//Graph::Node* RightN(nullptr);
	//Graph::Node* LowRightN(nullptr);
	//Graph::Node* LowN(nullptr);
	//Graph::Node* LowLeftN(nullptr);
	//Graph::Node* LeftN(nullptr);
	//Graph::Node* UpLeftN(nullptr);

	//for(u32 i = 1; i <= m_NumberOfRows; ++i)
	//{
	//	for(u32 j = 1; j <= m_NumberOfColumns; ++j)
	//	{
	//		Graph::Node& currentNode(m_Graph.GetNode(GetNodeIndex(i, j)));

	//		//UpN = GetNode(i - 1, j);
	//		//UpRightN = GetNode(i - 1, j + 1);
	//		//RightN = GetNode(i, j + 1);
	//		//LowRightN = GetNode(i + 1, j + 1);
	//		//LowN = GetNode(i + 1, j);
	//		//LowLeftN = GetNode(i + 1, j - 1);
	//		//LeftN = GetNode(i, j - 1);
	//		//UpLeftN = GetNode(i - 1, j - 1);

	//		if(UpN) currentNode.AddNeighbour(UpN);
	//		if(UpRightN) currentNode.AddNeighbour(UpRightN);
	//		if(RightN) currentNode.AddNeighbour(RightN);
	//		if(LowRightN) currentNode.AddNeighbour(LowRightN);
	//		if(LowN) currentNode.AddNeighbour(LowN);
	//		if(LowLeftN) currentNode.AddNeighbour(LowLeftN);
	//		if(LeftN) currentNode.AddNeighbour(LeftN);
	//		if(UpLeftN) currentNode.AddNeighbour(UpLeftN);
	//	}
	//}
}