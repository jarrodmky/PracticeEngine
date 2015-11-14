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
		
		inline Interval(const scalar p_Min, const scalar p_Max);

		//equality
		inline const bool operator ==(const Interval& p_Rhs) const;
		inline const bool operator !=(const Interval& p_Rhs) const;

		//arithmetic
		inline Interval& operator +=(const Interval& p_Rhs);
		inline const Interval operator +(const Interval& p_Rhs) const;
		inline Interval& operator -=(const Interval& p_Rhs);
		inline const Interval operator -(const Interval& p_Rhs) const;
		inline Interval& operator /=(const Interval& p_Rhs);
		inline const Interval operator /(const Interval p_Rhs) const;
		inline Interval& operator *=(const Interval& p_Rhs);
		inline const Interval operator *(const Interval& p_Rhs) const;

	//Methods
	public:

		//maniplators
		inline void ProjectLower(t_Type& p_Value);
		inline void ProjectHigher(t_Type& p_Value);
		inline Interval<t_Type>& Bisect();

		//queries
		inline bool HasElement(const t_Type& p_Value) const;
		inline bool HasNoElement(const t_Type& p_Value) const;
	};
} // namespace Mathematics

#include "Interval.inl"

#endif //#ifndef IncludedMathIntervalH