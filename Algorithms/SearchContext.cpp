#include "Precompiled.h"
#include "SearchContext.h"

using namespace Algorithms;

u32 DepthFirst::Next(SearchContext<DepthFirst>& p_Context)
{
	return p_Context.OpenList.Pull();
}
	
void DepthFirst::Open(SearchContext<DepthFirst>& p_Context, const u32 p_Index)
{
	p_Context.OpenList.Push(p_Index);
	p_Context.HaveOpened[p_Index] = true;
}

u32 BreadthFirst::Next(SearchContext<BreadthFirst>& p_Context)
{
	u32 index = p_Context.OpenList.front();
	p_Context.OpenList.erase(p_Context.OpenList.begin());
	return index;
}

void BreadthFirst::Open(SearchContext<BreadthFirst>& p_Context, const u32 p_Index)
{
	p_Context.OpenList.push_back(p_Index);
	p_Context.HaveOpened[p_Index] = true;
}

u32 Dijkstra::Next(SearchContext<Dijkstra>& p_Context)
{
	u32 index = p_Context.OpenList.back();
	p_Context.OpenList.pop_back();
	return index;
}

void Dijkstra::Open(SearchContext<Dijkstra>& p_Context, const u32 p_Index, const u32 p_Parent)
{
	p_Context.OpenList.push_back(p_Index);
	p_Context.HaveOpened[p_Index] = true;

	p_Context.g[p_Index] = p_Context.GetG(p_Parent, p_Index) + p_Context.g[p_Parent];
	p_Context.h[p_Index] = p_Context.GetH(p_Index, p_Context.EndIndex);
}