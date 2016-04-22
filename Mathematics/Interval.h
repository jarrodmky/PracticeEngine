#ifndef IncludedMathIntervalH
#define IncludedMathIntervalH

//===========================================================================
// Filename:	Interval.h
// Author:		Jarrod MacKay
// Description:	Requires classes that have defined operators : <, >, <=,
//				>=, ==, !=.  Defines an one-dimensional closed interval.
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
	template <typename t_Type>
	class Interval
	{
	//Attributes
	private:

		t_Type m_Minimum;
		t_Type m_Maximum;

	//Operators
	public:
		
		inline Interval(const t_Type& p_Min, const t_Type& p_Max)
			: m_Minimum(p_Min)
			, m_Maximum(p_Max)
		{
			Assert(p_Max > p_Min, "Interval is invalid!");
		}

		//equality
		inline const bool operator ==(const Interval& p_Rhs) const;
		inline const bool operator !=(const Interval& p_Rhs) const;

		//arithmetic
		inline Interval& operator +=(const Interval& p_Rhs);
		inline const Interval operator +(const Interval& p_Rhs) const;
		inline Interval& operator -=(const Interval& p_Rhs);
		inline const Interval operator -(const Interval& p_Rhs) const;
		inline Interval& operator /=(const Interval& p_Rhs);
		inline const Interval operator /(const Interval& p_Rhs) const;
		inline Interval& operator *=(const Interval& p_Rhs);
		inline const Interval operator *(const Interval& p_Rhs) const;

	//Methods
	public:

		//maniplators
		inline void ExtendLower(const t_Type& p_Value);
		inline void ExtendHigher(const t_Type& p_Value);
		inline Interval<t_Type>& Bisect();

		//queries
		inline t_Type MinValue() const {return m_Minimum;}
		inline t_Type MaxValue() const {return m_Maximum;}
		inline bool HasElement(const t_Type& p_Value) const;

		//projections
		inline t_Type ProjectWrapping(const t_Type& p_Value) const;
		inline t_Type ProjectMirroring(const t_Type& p_Value) const;
		inline t_Type ProjectClamping(const t_Type& p_Value) const;
	};

	typedef Interval<scalar> RealInterval;

	template <u32 t_Dimensions>
	using VectorInterval = Interval< RealVector<t_Dimensions> >;

	inline const scalar Midpoint(const RealInterval& p_Interval)
	{
		return (p_Interval.MaxValue() + p_Interval.MinValue()) * 0.5f;
	}
} // namespace Mathematics

#endif //#ifndef IncludedMathIntervalH