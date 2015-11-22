#ifndef IncludedMathSeriesH
#define IncludedMathSeriesH

//===========================================================================
// Filename:	Series.h
// Author:		Jarrod MacKay
// Description:	Implementation of template recursive series
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include "MathBase.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	//returns the Nth factorial
	template <u32 t_N>
	class Factorial
	{
		static u64 Generate()
		{
			return Factorial<t_N - 1>::Generate() * t_N;
		}
	};

	template <>
	class Factorial<0>
	{
		static u64 Generate()
		{
			return 1;
		}
	};


	//returns the Nth fibonacci series based on seeds
	template <u32 t_N, u64 t_N0, u64 t_N1>
	class Fibonacci
	{
		static u64 Generate()
		{
			return Fibonacci<t_N - 1, t_N0, t_N1>::Generate() + Fibonacci<t_N - 2, t_N0, t_N1>::Generate();
		}
	};

	template <u64 t_N0, u64 t_N1>
	class Fibonacci<1, t_N0, t_N1>
	{
		static u64 Generate()
		{
			return t_N1;
		}
	};

	template <u64 t_N0, u64 t_N1>
	class Fibonacci<0, t_N0, t_N1>
	{
		static u64 Generate()
		{
			return t_N0;
		}
	};
} // namespace Mathematics

#endif //#ifndef IncludedMathSeriesH