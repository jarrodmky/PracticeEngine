#ifndef IncludedCoreMetaprogrammingH
#define IncludedCoreMetaprogrammingH

//===========================================================================
// Filename:	Metaprogramming.h
// Author:		Jarrod MacKay
// Description:	Metaprogramming templates for reference
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Types.h"
#include "Common.h"

namespace Core
{

	//===========================================================================
	// Branch
	//===========================================================================
	
	template <bool t_Condition, typename t_TrueResultType, typename t_FalseResultType>
	class Branch;

	template <typename t_TrueResultType, typename t_FalseResultType>
	struct Branch<true, t_TrueResultType, t_FalseResultType>
	{
		typedef t_TrueResultType result;
	};

	template <typename t_TrueResultType, typename t_FalseResultType>
	struct Branch<false, t_TrueResultType, t_FalseResultType>
	{
		typedef t_FalseResultType result;
	};

	//example

	//	typename Branch<true, int, void*>::result number(3);
	//	typename Branch<false, int, void*>::result pointer(&number);
	//
	//	typedef typename Branch<(sizeof(void *) > sizeof(uint32_t)), uint64_t, uint32_t > ::result
	//		integral_ptr_t;
	//
	//	integral_ptr_t converted_pointer = reinterpret_cast<integral_ptr_t>(pointer);
	//
	
	template <bool t_Condition, typename t_ResultType>
	class LargerOf;

	template <typename t_ResultType>
	struct LargerOf<true, t_ResultType>
	{
		typedef t_ResultType result;
	};

	template <typename t_ResultType>
	struct LargerOf<false, t_ResultType>
	{
		typedef t_ResultType result;
	};
	
	template<u32 t_LeftHand, u32 t_RightHand>
	typename LargerOf<true, u32>::result right(t_RightHand);
	
	template<u32 t_LeftHand, u32 t_RightHand>
	typename LargerOf<false, u32>::result left(t_LeftHand);

	template<u32 t_LeftHand, u32 t_RightHand>
	typedef typename LargerOf<(t_LeftHand < t_RightHand), u32>::result Larger;

	//===========================================================================
	// Iterative
	//===========================================================================

}
#endif //#ifndef IncludedCoreMetaprogrammingH