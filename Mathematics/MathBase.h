#ifndef IncludedMathBaseH
#define IncludedMathBaseH

//===========================================================================
// Filename:	MathBase.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 3 dimensional vector
//===========================================================================

#include <Core.h>

//===========================================================================
// Typedefs
//===========================================================================

namespace Mathematics
{

	typedef f32	scalar;
	const scalar eps = 0.00001f;
	
	typedef std::complex<scalar> complex;
	typedef std::pair<scalar, scalar> ScalarPair;
	typedef std::pair<complex, complex> ComplexPair;

	//TODO: define literal some general unit suffix e.g. (1.0s)

	#ifdef max
	#undef max
	#endif
	#ifdef min
	#undef min
	#endif

	//===========================================================================
	// Constants
	//===========================================================================

	//TODO extern the constants so no multiple def

	const scalar Zero				= 0.0f;
	const scalar Unity				= 1.0f;
	const scalar Epsilon = eps;// std::numeric_limits<scalar>::epsilon();
	const scalar Infinity			= std::numeric_limits<scalar>::infinity();
	const scalar NegativeInfinity	= -Infinity;
	const scalar NotANumber			= std::numeric_limits<scalar>::signaling_NaN();
	const scalar Maximum			= std::numeric_limits<scalar>::max();
	const scalar Minimum			= std::numeric_limits<scalar>::min();
	const scalar PiOverTwo			= 1.570796326794896619231321691639f;
	const scalar Pi					= 3.141592653589793238462643383279f;
	const scalar TwoPi				= 6.28318530717958647692528676656f;
	const scalar PiSquared			= 9.869604401089358618834f;
	const scalar OneOverPi			= 0.3183098861837906715378f;
	const scalar OneOverTwoPi		= 0.1591549430918953357689f;
	const scalar DegsPerRad			= 57.2957795130823208768f;
	const scalar RadsPerDeg			= 0.01745329251994329576924f;
	const scalar RootTwo			= 1.41421356237309f;
	const scalar RootThree			= 1.73205080756887f;
	
	const static u8 MaxU8					= 0xffui8;
	const static u16 MaxU16					= 0xffffui16;
	const static u32 MaxU32					= 0xffffffffui32;
	const static u64 MaxU64					= 0xffffffffffffffffui64;

	//===========================================================================
	// Integer Functions
	//===========================================================================
	
	inline const u32 EulerCharacteristic(const u32 p_Vertices, const u32 p_Edges, const u32 p_Faces)
	{
		return p_Vertices - p_Edges + p_Faces;
	}

	//===========================================================================
	// Float Functions
	//===========================================================================

	inline const scalar AbsoluteValue(const scalar p_Scalar)
	{
		return (p_Scalar > Zero) ? (p_Scalar) : (-p_Scalar);
	}

	inline const scalar Signum(const scalar p_Scalar)
	{
		return (p_Scalar > Zero) ? (Unity) : (-Unity);
	}

	inline const scalar Signum(const scalar p_MagnitudeOf, const scalar p_SignOf)
	{
		return Signum(p_SignOf) * AbsoluteValue(p_MagnitudeOf);
	}

	//comparison to zero
	inline bool IsApproximatelyZero(const scalar p_Scalar, const scalar p_Tolerance)
	{
		return (AbsoluteValue(p_Scalar) <= p_Tolerance);
	}

	inline bool IsZero(const scalar p_Scalar)
	{
		return IsApproximatelyZero(p_Scalar, Epsilon);
	}

	//comparison to number
	inline bool Close(const scalar p_Scalar, const scalar p_Centre, const scalar p_Tolerance)
	{
		return IsApproximatelyZero(p_Scalar - p_Centre, p_Tolerance);
	}

	//absolute comparison to standard
	inline bool IsApproximatelyUnity(const scalar p_Scalar, const scalar p_Tolerance)
	{
		return Close(p_Scalar, Unity, p_Tolerance);
	}

	inline bool IsUnity(const scalar p_Scalar)
	{
		return IsApproximatelyUnity(p_Scalar, Epsilon);
	}

	//relative comparison (non-zero standard)
	inline bool IsApproximatelyEqualTo(const scalar p_Query, const scalar p_Standard, const scalar p_Tolerance)
	{
		return IsApproximatelyZero(p_Query - p_Standard, p_Tolerance * AbsoluteValue(p_Standard));
	}

	inline bool IsEqualTo(const scalar p_Query, const scalar p_Standard)
	{
		return IsApproximatelyEqualTo(p_Query, p_Standard, Epsilon);
	}

	//relative comparison (no standard)
	inline bool ApproximatelyEqual(const scalar p_Lhs, const scalar p_Rhs, const scalar p_Tolerance)
	{
		scalar lAbs(AbsoluteValue(p_Lhs));
		scalar rAbs(AbsoluteValue(p_Rhs));
		scalar max = (lAbs > rAbs) ? (lAbs) : (rAbs);
		return (IsApproximatelyZero(p_Lhs, p_Tolerance)) ? (IsApproximatelyZero(p_Rhs, p_Tolerance)) : 
					((IsApproximatelyZero(p_Rhs, p_Tolerance)) ? (IsApproximatelyZero(p_Lhs, p_Tolerance)) : 
						(IsApproximatelyZero(p_Lhs - p_Rhs, p_Tolerance * max)));
	}
	
	inline bool Equal(const scalar p_Lhs, const scalar p_Rhs)
	{
		return ApproximatelyEqual(p_Lhs, p_Rhs, Epsilon);
	}

	//other comparisons
	inline bool IsFinite(const scalar p_Scalar)
	{
		return !IsEqualTo(p_Scalar, Infinity)
			&& !IsEqualTo(p_Scalar, NegativeInfinity);
	}

	inline bool IsInfinite(const scalar p_Scalar)
	{
		return !IsFinite(p_Scalar);
	}
	
	inline bool IsANumber(const scalar p_Scalar)
	{
		return (NotANumber != p_Scalar);
	}
	
	inline bool IsInInterval(const scalar p_Scalar, const scalar p_Min, const scalar p_Max)
	{
		Assert(p_Max > p_Min, "Invalid interval for testing!");
		return (p_Scalar >= p_Min) && (p_Scalar <= p_Max);
	}
	
	//manipulations
	inline void Invert(scalar& p_Scalar)
	{
		Assert(!IsZero(p_Scalar), "Tried a division by zero!");
		p_Scalar = Unity / p_Scalar;
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

	inline void Clean(scalar& p_Value)
	{
		p_Value = (IsZero(p_Value)) ? (Zero) :
						((IsUnity(p_Value)) ? (Unity) :
							((IsUnity(-p_Value)) ? (-Unity) : (p_Value)));
	}

	//===========================================================================
	// Complex Functions
	//===========================================================================

	inline complex Euler(const scalar p_Angle)
	{
		return complex(std::cos(p_Angle), std::sin(p_Angle));
	}

	inline complex RootOfUnity(const u32 p_K, const u32 p_N)
	{
		Assert(p_K < p_N, "Degenerate root!");
		const scalar f = static_cast<scalar>(p_K) / static_cast<scalar>(p_N);
		return Euler(TwoPi * f);
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