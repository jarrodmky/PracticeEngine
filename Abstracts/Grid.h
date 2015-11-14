#ifndef IncludedMathGridH
#define IncludedMathGridH

//===========================================================================
// Filename:	Grid.h
// Author:		Jarrod MacKay
// Description:	Provides a graph that has fixed width and height of nodes.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Graph.h"

//===========================================================================
// Classes
//===========================================================================

namespace Abstracts
{

class Grid
{
//Operations
public:

	Grid();
	~Grid();

//Methods
public:

	void Initialize(u32 p_NumberOfRows, u32 p_NumberOfColumns);

	void Free();

	const u32 GetIndex(const u32 p_X, const u32 p_Y) const;

	const u32 GetX(const u32 p_Index) const;

	const u32 GetY(const u32 p_Index) const;

	const Graph& GetGraph() {return m_Graph;}

private:

	const Graph::Node& GetNode(const u32 p_Index) const;

	void SetMooreNeighbourhood();

//Attributes
private:

	u32 m_NumberOfColumns;

	u32 m_NumberOfRows;

	Graph m_Graph;
};

} // namespace Abstracts

#endif // #ifndef IncludedMathGridH