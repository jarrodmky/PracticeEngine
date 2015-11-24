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

	const Matrix Rotation(const Quaternion& p_Rotation);

	//---------------------------------------------------------------------------

	const Matrix Rotation(const Vector& p_Axis, const scalar p_Angle);

	//---------------------------------------------------------------------------

	inline const Matrix RotationAboutX(const scalar p_Angle)
	{
		using namespace ConstantScalars;
		const scalar s = std::sin(p_Angle);
		const scalar c = std::cos(p_Angle);

		return Matrix(Unity, Zero, Zero
					, Zero, c, -s
					, Zero, s, c);
	}

	//---------------------------------------------------------------------------

	inline const Matrix RotationAboutY(const scalar p_Angle)
	{
		using namespace ConstantScalars;
		const scalar s = std::sin(p_Angle);
		const scalar c = std::cos(p_Angle);

		return Matrix(c, Zero, s
					, Zero, Unity, Zero
					, -s, Zero, c);
	}

	//---------------------------------------------------------------------------

	inline const Matrix RotationAboutZ(const scalar p_Angle)
	{
		using namespace ConstantScalars;
		const scalar s = std::sin(p_Angle);
		const scalar c = std::cos(p_Angle);

		return Matrix(c, -s, Zero
			, s, c, Zero
			, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix Translation(const Vector p_Displacement)
	{
		using namespace ConstantScalars;

		return Matrix(Unity, Zero, Zero, p_Displacement.x
			, Zero, Unity, Zero, p_Displacement.y
			, Zero, Zero, Unity, p_Displacement.z
			, Zero, Zero, Zero, Unity);
	}
}

#endif //#ifndef IncludedMathAlgebraH