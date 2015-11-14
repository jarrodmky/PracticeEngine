#ifndef IncludedMathBaseH
#define IncludedMathBaseH

//===========================================================================
// Filename:	MathBase.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 3 dimensional vector
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"

//===========================================================================
// Typedefs
//===========================================================================

namespace Mathematics
{
	typedef f32	scalar;
	typedef std::pair<scalar, scalar> scalarPair;
	typedef std::complex<scalar> complex;
	
	//TODO: define literal some general unit suffix e.g. (1.0s)

	#ifdef max
	#undef max
	#endif
	#ifdef min
	#undef min
	#endif
	
	namespace ConstantScalars
	{
		const static scalar Zero				= 0.0f;
		const static scalar Unity				= 1.0f;
		const static scalar Epsilon				= std::numeric_limits<scalar>::epsilon();
		const static scalar Infinity			= std::numeric_limits<scalar>::infinity();
		const static scalar NegativeInfinity	= -Infinity;
		const static scalar NotANumber			= std::numeric_limits<scalar>::signaling_NaN();
		const static scalar Maximum				= std::numeric_limits<scalar>::max();
		const static scalar Minimum				= std::numeric_limits<scalar>::min();
		const static scalar Pi					= 3.141592653589793238462643383279f;
		const static scalar TwoPi				= 6.28318530717958647692528676656f;
		const static scalar PiSquared			= 9.869604401089358618834f;
		const static scalar OneOverPi			= 0.3183098861837906715378f;
		const static scalar OneOverTwoPi		= 0.1591549430918953357689f;
		const static scalar DegsPerRad			= 57.2957795130823208768f;
		const static scalar RadsPerDeg			= 0.01745329251994329576924f;
	}
	
	namespace ConstantIntegers
	{
		const static u8 MaxU8					= 0xffui8;
		const static u16 MaxU16					= 0xffffui16;
		const static u32 MaxU32					= 0xffffffffui32;
		const static u64 MaxU64					= 0xffffffffffffffffui64;
	}

	inline void DropSign(scalar& p_Scalar)
	{
		p_Scalar = (p_Scalar > ConstantScalars::Zero) ? (p_Scalar) : (-p_Scalar);
	}

	inline const scalar AbsoluteValue(const scalar p_Scalar)
	{
		scalar temp(p_Scalar);
		DropSign(temp);
		return temp;
	}

	inline bool EquivalentToEachOther(const scalar p_LHS, const scalar p_RHS)
	{
		return (AbsoluteValue(p_LHS - p_RHS) < ConstantScalars::Epsilon);
	}

	inline bool EquivalentToZero(const scalar p_Scalar)
	{
		return (AbsoluteValue(p_Scalar) < ConstantScalars::Epsilon);
	}

	inline bool IsFinite(const scalar p_Scalar)
	{
		return !EquivalentToEachOther(ConstantScalars::Infinity, p_Scalar) 
			&& !EquivalentToEachOther(ConstantScalars::NegativeInfinity, p_Scalar);
	}

	inline bool IsInfinite(const scalar p_Scalar)
	{
		return !IsFinite(p_Scalar);
	}
	
	inline bool IsANumber(const scalar p_Scalar)
	{
		return (ConstantScalars::NotANumber != p_Scalar);
	}
	
	inline void Invert(scalar& p_Scalar)
	{
		Assert(EquivalentToZero(p_Scalar), "Tried a division by zero!");
		p_Scalar = ConstantScalars::Unity / p_Scalar;
	}

	inline const scalar Inverse(const scalar p_Scalar)
	{
		scalar temp(p_Scalar);
		Invert(temp);
		return temp;
	}

	inline void InvertAfterSquaring(scalar& p_Scalar)
	{
		Invert(p_Scalar *= p_Scalar);
	}

	inline const scalar InverseSquare(const scalar p_Scalar)
	{
		scalar temp(p_Scalar);
		InverseSquare(temp);
		return temp;
	}

	inline const scalar ClampInclusive(const scalar p_Value, const scalar p_Min, const scalar p_Max)
	{
		scalar temp(p_Value);
		temp = (p_Value > p_Max) ? (p_Max) : (p_Value);
		temp = (p_Value < p_Min) ? (p_Min) : (p_Value);
		return temp;
	}

	//void RaiseExponentially(scalar& p_Base, const scalar p_Exponent)
	//{
	//}
	//scalar GetExponentiation(const scalar p_Base, const scalar p_Exponent)
	//{
	//}

	//TODO wrap trig functions!
	//TODO calc sine cos at same time function
}

#endif // #ifndef IncludedMathBaseH