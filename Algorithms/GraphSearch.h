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

class GraphSearch
{
	static void Run(const Abstracts::Graph& p_Graph, SearchContext& p_Context)
	{
		//Until goal reached or graph completely searched
		while(!p_Context.HaveFinished && !p_Context.OpenList.empty())
		{
			//pick next node
			u32 next = p_Context.OpenList.front();
			p_Context.OpenList.erase(p_Context.OpenList.begin());

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
					u32 neighbour = node.GetNeighbour(i)->GetIndex();
					if(!p_Context.HaveClosed[neighbour] &&
					   !p_Context.HaveOpened[neighbour])
					{
						p_Context.OpenList.push_back(neighbour);
						p_Context.HaveOpened[neighbour] = true;
						p_Context.Parents[neighbour] = next;
					}
				}
			}

			//add node to closed list
			p_Context.ClosedList.push_back(next);
			p_Context.HaveClosed[next] = true;
		}


	}

	static void GetPath(SearchContext& p_Context, std::vector<u32>& p_Path)
	{
		p_Path.clear();

		u32 next = p_Context.EndIndex;
		while(next != -1)
		{

		}
	}
};

}

#endif //#ifndef IncludedAlgoGraphSearchH