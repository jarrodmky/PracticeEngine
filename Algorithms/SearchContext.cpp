#include "Precompiled.h"
#include "SearchContext.h"

using namespace Algorithms;

SearchContext::SearchContext()
: StartIndex(0)
, EndIndex(0)
, HaveFinished(false)
, HaveFound(false)
, OpenList(0)
, ClosedList(0)
, Parents(0)
, HaveOpened(0)
, HaveClosed(0)
{}

void SearchContext::Initialize(const u32 p_NumberOfNodes, const u32 p_Start, const u32 p_Goal)
{
	StartIndex = p_Start;
	EndIndex = p_Goal;
	HaveFinished = false;
	HaveFound = false;
	OpenList.reserve(p_NumberOfNodes);
	ClosedList.reserve(p_NumberOfNodes);
	Parents.resize(p_NumberOfNodes, INFINITE);
	HaveOpened.resize(p_NumberOfNodes, false);
	HaveClosed.resize(p_NumberOfNodes, false);
}