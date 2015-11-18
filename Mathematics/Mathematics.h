#ifndef IncludedMathematicsH
#define IncludedMathematicsH

//===========================================================================
// Filename:	Mathematics.h
// Author:		Jarrod MacKay
// Description:	Main entry point to the mathematics library.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "MathBase.h"
#include "Algebra.h"
#include "Geometry.h"
#include "Random.h"

//===========================================================================
// Functions
//===========================================================================

namespace Mathematics
{

	//vector outer product
	inline const Matrix operator ^(const Vector& p_Lhs, const Vector& p_Rhs)
	{
		//TODO

		return Matrix(Vector(), Vector(), Vector(), ConstantPoints::Origin);
	}

	inline Matrix RotationMatrixLH(const Vector& p_Axis, const scalar p_Angle)
	{

	}

	Matrix RotationMatrixLH(const Quaternion& p_Rotation);

	inline Vector InterpolateLinearly(const Vector& p_A, const Vector& p_B, const scalar p_Ratio)
	{
		return p_A + ((p_B - p_A) * p_Ratio);
	}

	inline Vector Lerp(const Vector& p_A, const Vector& p_B, const scalar p_Ratio)
	{
		return InterpolateLinearly(p_A, p_B, p_Ratio);
	}

} // namespace Mathematics
#endif //#ifndef IncludedMathematicsH