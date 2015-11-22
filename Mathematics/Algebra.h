#ifndef IncludedMathAlgebraH
#define IncludedMathAlgebraH

//===========================================================================
// Filename:	Algebra.h
// Author:		Jarrod MacKay
// Description:	
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Interval.h"

namespace Mathematics
{

	//===========================================================================
	// Operators
	//===========================================================================

	inline const Vector operator *(const scalar p_Lhs, const Vector& p_Rhs)
	{
		return p_Rhs * p_Lhs;
	}

	//---------------------------------------------------------------------------

	inline const Matrix operator *(const scalar p_Lhs, const Matrix& p_Rhs)
	{
		return p_Rhs * p_Lhs;
	}

	//---------------------------------------------------------------------------

	inline const Quaternion operator *(const scalar p_Lhs, const Quaternion& p_Rhs)
	{
		return p_Rhs * p_Lhs;
	}

	//---------------------------------------------------------------------------

	//vector outer product
	inline const Matrix operator ^(const Vector& p_Lhs, const Vector& p_Rhs)
	{
		const scalar xx(p_Lhs.x * p_Rhs.x);
		const scalar xy(p_Lhs.x * p_Rhs.y);
		const scalar xz(p_Lhs.x * p_Rhs.z);
		const scalar yy(p_Lhs.y * p_Rhs.y);
		const scalar yz(p_Lhs.y * p_Rhs.z);
		const scalar zz(p_Lhs.z * p_Rhs.z);

		return Matrix(xx, xy, xz, xy, yy, yz, xz, yz, zz);
	}

	//===========================================================================
	// Functions
	//===========================================================================

	//Interpolation

	inline const Vector InterpolateLinearly(const Vector& p_A, const Vector& p_B, const scalar p_Ratio)
	{
		return p_A + ((p_B - p_A) * p_Ratio);
	}

	//---------------------------------------------------------------------------

	inline const Vector Lerp(const Vector& p_A, const Vector& p_B, const scalar p_Ratio)
	{
		return InterpolateLinearly(p_A, p_B, p_Ratio);
	}

	//---------------------------------------------------------------------------

	inline const Vector RotatedVector(const Quaternion& p_Rotation, const Vector& p_Vector)
	{
		Vector temp(p_Vector);
		p_Rotation.RotateVector(temp);
		return temp;
	}

	//---------------------------------------------------------------------------

	const Matrix RotationMatrixRH(const Quaternion& p_Rotation);

	//---------------------------------------------------------------------------

	const Matrix RotationMatrixRH(const Vector& p_Axis, const scalar p_Angle);

	//---------------------------------------------------------------------------

	const Matrix RotationMatrixLH(const Quaternion& p_Rotation);

	//---------------------------------------------------------------------------

	const Matrix RotationMatrixLH(const Vector& p_Axis, const scalar p_Angle);
}

#endif //#ifndef IncludedMathAlgebraH