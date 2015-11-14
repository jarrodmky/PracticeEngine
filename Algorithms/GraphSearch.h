#ifndef IncludedAlgoGraphSearchH
#define IncludedAlgoGraphSearchH

//===========================================================================
// Filename:	GraphSearch.h
// Author:		Jarrod MacKay
// Description:	Main entry point into the AI engine.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Abstracts.h>
#include "SearchContext.h"

//===========================================================================
// Definition
//===========================================================================

namespace Algorithms
{

template <typename t_Policy>
class GraphSearch
{
public:
	static void Run(const Abstracts::Graph& p_Graph, SearchContext<t_Policy>& p_Context)
	{
		//Until goal reached or graph completely searched
		//while(!p_Context.HaveFinished && !p_Context.OpenList.IsEmpty())
		while(!p_Context.HaveFinished && !p_Context.OpenList.empty())
		{
			//pick next node
			u32 next = t_Policy::Next(p_Context);

			//check if node is our goal
			if(next == p_Context.EndIndex)
			{
				p_Context.HaveFinished = true;
				p_Context.HaveFound = true;
			}
			else
			{
				//Expand node
				const Abstracts::Graph::Node& node = p_Graph.GetNode(next);
				for(u32 i = 0; i < node.GetNumberOfNeighbours(); ++i)
				{
					u32 neighbour = node.GetNeighbour(i).GetIndex();
					if(!p_Context.HaveClosed[neighbour] &&
					   !p_Context.HaveOpened[neighbour] &&
					   p_Context.Filter(next, neighbour))
					{
						t_Policy::Open(p_Context, next, neighbour);
						p_Context.Parents[neighbour] = next;
					}
				}
			}

			//add node to closed list
			p_Context.ClosedList.push_back(next);
			p_Context.HaveClosed[next] = true;
		}
	}

	static void GetPath(SearchContext<t_Policy>& p_Context, std::vector<u32>& p_Path)
	{
		p_Path.clear();

		u32 next = p_Context.EndIndex;
		while(next != INFINITE)
		{
			p_Path.push_back(next);
			next = p_Context.Parents[next];
		}
	}
};

}

#endif //#ifndef IncludedAlgoGraphSearchH