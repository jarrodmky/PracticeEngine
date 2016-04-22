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
// structes
//===========================================================================

namespace Mathematics
{
	template <typename t_Series>
	struct Series
	{
		inline static const u64 Integer()
		{
			return t_Series::m_Value;
		}

		inline static const f64 Float()
		{
			return static_cast<f64>(t_Series::m_Value);
		}
	};

#define MetaFor(Class, Iteration, N)\
 friend Iteration<N + 1>;\
 friend Class<Iteration<N> >

	//==========
	//  Triangular
	//==========

	template <u8 t_N>
	class Triangular : public Series<Triangular<t_N> >
	{
		MetaFor(Series, Triangular, t_N);
		static const u64 m_Value = Triangular<t_N - 1>::m_Value + t_N;
	};

	template <>
	class Triangular<0> : public Series<Triangular<0> >
	{
		MetaFor(Series, Triangular, 0);
		static const u64 m_Value = 0;
	};

	//==========
	//  Factorial
	//==========

	template <u8 t_N>
	class Factorial : public Series<Factorial<t_N> >
	{
		MetaFor(Series, Factorial, t_N);
		static const u64 m_Value = Factorial<t_N - 1>::m_Value * t_N;
	};

	template <>
	class Factorial<0> : public Series<Factorial<0> >
	{
		MetaFor(Series, Factorial, 0);
		static const u64 m_Value = 1;
	};


	//==========
	//  Fibonacci
	//==========

#define MetaForFib(Class, Iteration, N)\
 friend Iteration<N + 1>;\
 friend Iteration<N + 2>;\
 friend Class<Iteration<N> >

	//returns the Nth fibonacci series based on seeds Fib(0) = 0, Fib(1) = 1
	template <u8 t_N>
	class Fibonacci : public Series<Fibonacci<t_N> >
	{
		MetaForFib(Series, Fibonacci, t_N);
		static const u64 m_Value = Fibonacci<t_N - 1>::m_Value + Fibonacci<t_N - 2>::m_Value;
	};

	template <>
	class Fibonacci<1> : public Series<Fibonacci<1> >
	{
		MetaForFib(Series, Fibonacci, 1);
		static const u64 m_Value = 1;
	};

	template <>
	class Fibonacci<0> : public Series<Fibonacci<0> >
	{
		MetaForFib(Series, Fibonacci, 0);
		static const u64 m_Value = 0;
	};

	//==========
	//  Combinations
	//==========

#define MetaFor2(Class, Iteration, M, N)\
	friend Iteration<M + 1, N + 1>;\
	friend Iteration<M + 1, N>;\
	friend Iteration<M, N + 1>;\
	 friend Class<Iteration<M, N> >

	template <u8 t_N, u8 t_K>
	class Combinations : public Series<Combinations<t_N, t_K> >
	{
		MetaFor2(Series, Combinations, t_N, t_K);
		static const u64 m_Value = Combinations<t_N - 1, t_K - 1>::m_Value
			+ Combinations<t_N - 1, t_K>::m_Value;
	};

	template <u8 t_N>
	class Combinations<t_N, 0> : public Series<Combinations<t_N, 0> >
	{
		MetaFor2(Series, Combinations, t_N, 0);
		static const u64 m_Value = 1;
	};

	template <u8 t_N>
	class Combinations<t_N, t_N> : public Series<Combinations<t_N, t_N> >
	{
		MetaFor2(Series, Combinations, t_N, t_N);
		static const u64 m_Value = 1;
	};

	template <>
	class Combinations<0, 0> : public Series<Combinations<0, 0> >
	{
		MetaFor2(Series, Combinations, 0, 0);
		static const u64 m_Value = 1;
	};
} // namespace Mathematics

#endif //#ifndef IncludedMathSeriesH