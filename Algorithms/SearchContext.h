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

struct SearchContext
{
	//Attributes
	u32 StartIndex;
	u32 EndIndex;

	bool HaveFinished;
	bool HaveFound;

	std::vector<u32> OpenList;
	std::vector<u32> ClosedList;
	std::vector<u32> Parents;
	std::vector<bool> HaveOpened;
	std::vector<bool> HaveClosed;

	//Operations
	SearchContext();

	//Methods
	void Initialize(const u32 p_NumberOfNodes, const u32 p_Start, const u32 p_Goal);
};

}

#endif //#ifndef IncludedAlgoSearchContextH