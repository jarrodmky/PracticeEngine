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

	SetMooreNeighbourhood();
}

void Grid::Free()
{
	m_Graph.Free();

	m_NumberOfColumns = 0;
	m_NumberOfRows = 0;
}

const u32 Grid::GetIndex(const u32 p_X, const u32 p_Y) const
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

void Grid::SetMooreNeighbourhood()
{
	//set horizontal laterals
	for (u32 i = 0; i < m_NumberOfRows; ++i)
	{
		for (u32 j = 0; j < m_NumberOfColumns - 1; ++j)
		{
			m_Graph.ConnectNodes(GetIndex(i, j), GetIndex(i, j + 1));
		}
	}

	//set horizontal laterals
	for (u32 j = 0; j < m_NumberOfColumns; ++j)
	{
		for (u32 i = 0; i < m_NumberOfRows - 1; ++i)
		{
			m_Graph.ConnectNodes(GetIndex(i, j), GetIndex(i + 1, j));
		}
	}

	//set diagonals
	for (u32 i = 0; i < m_NumberOfRows - 1; ++i)
	{
		for (u32 j = 0; j < m_NumberOfColumns - 1; ++j)
		{
			m_Graph.ConnectNodes(GetIndex(i, j), GetIndex(i + 1, j + 1));
			m_Graph.ConnectNodes(GetIndex(i + 1, j), GetIndex(i, j + 1));
		}
	}
}