#ifndef IncludedAlgoSearchContextH
#define IncludedAlgoSearchContextH

//===========================================================================
// Filename:	SearchContext.h
// Author:		Jarrod MacKay
// Description:	Utility struct for use in graph search algorithms.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>

//===========================================================================
// Definition
//===========================================================================

namespace Algorithms
{

template <typename t_Policy>
class SearchContext;

class DepthFirst
{
public:
	typedef Abstracts::Stack<u32> Collector;

	static u32 Next(SearchContext<DepthFirst>& p_Context);

	static void Open(SearchContext<DepthFirst>& p_Context, const u32 p_Index, const u32 p_Parent);
};

class BreadthFirst
{
public:
	typedef std::vector<u32> Collector;

	static u32 Next(SearchContext<BreadthFirst>& p_Context);

	static void Open(SearchContext<BreadthFirst>& p_Context, const u32 p_Index, const u32 p_Parent);
};

class Dijkstra
{
public:
	typedef std::vector<u32> Collector;

	static u32 Next(SearchContext<Dijkstra>& p_Context);

	static void Open(SearchContext<Dijkstra>& p_Context, const u32 p_Index, const u32 p_Parent);
};

class A_Star
{
public:
	typedef std::vector<u32> Collector;

	static u32 Next(SearchContext<A_Star>& p_Context);

	static void Open(SearchContext<A_Star>& p_Context, const u32 p_Index, const u32 p_Parent);
};



template <typename t_Policy>
class SearchContext
{
public:

	//Attributes
	u32 StartIndex;
	u32 EndIndex;

	bool HaveFinished;
	bool HaveFound;

	typename t_Policy::Collector OpenList;
	std::vector<u32> ClosedList;
	std::vector<u32> Parents;
	std::vector<bool> HaveOpened;
	std::vector<bool> HaveClosed;
	std::vector<f32> g;
	std::vector<f32> h;

	std::function<bool(u32, u32)> Filter;
	std::function<f32(u32, u32)> GetG;
	std::function<f32(u32, u32)> GetH;

	//Operations
	SearchContext()
	: StartIndex(0)
	, EndIndex(0)
	, HaveFinished(false)
	, HaveFound(false)
	, OpenList(0)
	, ClosedList(0)
	, Parents(0)
	, HaveOpened(0)
	, HaveClosed(0)
	, g(0)
	, h(0)
	, Filter(nullptr)
	, GetG(nullptr)
	, GetH(nullptr)
	{}

	//Methods
	void Initialize(const u32 p_NumberOfNodes, const u32 p_Start, const u32 p_Goal)
	{
		StartIndex = p_Start;
		EndIndex = p_Goal;
		HaveFinished = false;
		HaveFound = false;
		//OpenList.Reserve(p_NumberOfNodes);
		OpenList.reserve(p_NumberOfNodes);
		ClosedList.reserve(p_NumberOfNodes);
		Parents.resize(p_NumberOfNodes, INFINITE);
		HaveOpened.resize(p_NumberOfNodes, false);
		HaveClosed.resize(p_NumberOfNodes, false);
		g.resize(p_NumberOfNodes, FLT_MAX);
		h.resize(p_NumberOfNodes, FLT_MAX);

		//start search
		//OpenList.Push(p_Start);
		OpenList.push_back(p_Start);
		HaveOpened[p_Start] = true;
		Parents[p_Start] = INFINITE;
	}
};

}

#endif //#ifndef IncludedAlgoSearchContextH