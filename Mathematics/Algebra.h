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
#include "LinearColour.h"

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

	//==========
	// Interpolation
	//==========

	inline const Vector InterpolateLinearly(const Vector& p_A, const Vector& p_B, const scalar p_Ratio)
	{
		return p_A + ((p_B - p_A) * p_Ratio);
	}

	//---------------------------------------------------------------------------

	inline const Vector Lerp(const Vector& p_A, const Vector& p_B, const scalar p_Ratio)
	{
		return InterpolateLinearly(p_A, p_B, p_Ratio);
	}

	//==========
	// Vectors
	//==========
	
	inline const bool ApproximateToEachOther(const Vector& p_Lhs, const Vector& p_Rhs, const scalar p_Tolerance)
	{
		return (p_Lhs - p_Rhs).Length() < p_Tolerance;
	}

	//---------------------------------------------------------------------------
	
	inline const scalar AngleBetween(const Vector& p_Lhs, const Vector& p_Rhs)
	{
		return std::acos(p_Lhs.Direction() | p_Rhs.Direction());
	}

	//==========
	// Matrices
	//==========

	inline const Matrix SkewMatrix(const Vector& p_Vector)
	{
		using namespace ConstantScalars;

		return Matrix(Zero, -p_Vector.z, p_Vector.y
					, p_Vector.z, Zero, -p_Vector.x
					, -p_Vector.y, p_Vector.x, Zero);
	}

	//---------------------------------------------------------------------------

	inline const Vector RotatedVector(const Quaternion& p_Rotation, const Vector& p_Vector)
	{
		Vector temp(p_Vector);
		p_Rotation.RotateVector(temp);
		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Quaternion Rotation(const Matrix& p_Rotation)
	{
		using namespace ConstantScalars;
		using namespace ConstantMatrices;

		Assert(p_Rotation.IsSpecialOthogonal(), "Cannot map general matrix to quaternion!");

		scalar trace = p_Rotation.Trace();
		scalar real = 0.0f;
		Vector imaginary;

		if (trace > 0.0f) 
		{
			scalar div = Unity / sqrt(trace + Unity) * 2.0f;
			real = 0.25f / div;
			imaginary = Vector(p_Rotation(3, 2) - p_Rotation(2, 3), p_Rotation(1, 3) - p_Rotation(3, 1), p_Rotation(2, 1) - p_Rotation(1, 2));
			imaginary *= div;
		}
		else
		{
			Vector d = p_Rotation.Diagonal();

			if ((d.x > d.y) && (d.x > d.z)) 
			{
				scalar div = Unity / sqrt(Unity + d.x - d.y - d.z) * 2.0f;
				real = (p_Rotation(3, 2) - p_Rotation(2, 3)) * div;
				imaginary = Vector(0.25f / div, (p_Rotation(1, 2) + p_Rotation(2, 1)) * div, (p_Rotation(1, 3) + p_Rotation(3, 1)) * div);
			}
			else if (d.y > d.z)
			{
				scalar div = Unity / sqrt(Unity + d.y - d.x - d.z) * 2.0f;
				real = (p_Rotation(1, 3) - p_Rotation(3, 1)) * div;
				imaginary = Vector((p_Rotation(1, 2) + p_Rotation(2, 1)) * div, 0.25f / div, (p_Rotation(2, 3) + p_Rotation(3, 2)) * div);
			}
			else 
			{
				scalar div = Unity / sqrt(Unity + d.z - d.x - d.y) * 2.0f; //
				real = (p_Rotation(2, 1) - p_Rotation(1, 2)) * div;
				imaginary = Vector((p_Rotation(1, 3) + p_Rotation(3, 1)) * div, (p_Rotation(2, 3) + p_Rotation(3, 2)) * div, 0.25f / div);
			}
		}

		return Quaternion(real, imaginary).Normalize();
	}

	//---------------------------------------------------------------------------

	inline const Matrix Rotation(const Quaternion& p_Rotation)
	{
		using namespace ConstantScalars;
		using namespace ConstantMatrices;
		const scalar w(p_Rotation.ScalarPart());
		const Vector v(p_Rotation.VectorPart().Direction());

		return (Unity - (2.0f * (v | v))) * Identity + 2.0f * (w * SkewMatrix(v) + (v ^ v));
	}

	//---------------------------------------------------------------------------

	inline const Matrix Rotation(const Vector& p_Axis, const scalar p_Angle)
	{
		using namespace ConstantScalars;
		using namespace ConstantMatrices;
		const scalar s(std::sin(p_Angle));
		const scalar c(std::cos(p_Angle));
		const Vector a(p_Axis.Direction());

		return c * Identity + s * SkewMatrix(a) + (Unity - c) * (a ^ a);
	}

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

	inline const Matrix Scale(const Vector& p_Scale)
	{
		using namespace ConstantScalars;

		return Matrix(p_Scale.x, Zero, Zero
			, Zero, p_Scale.y, Zero
			, Zero, Zero, p_Scale.z);
	}

	//---------------------------------------------------------------------------

	inline const Matrix Translation(const Vector& p_Displacement)
	{
		using namespace ConstantScalars;

		return Matrix(Unity, Zero, Zero, p_Displacement.x
					, Zero, Unity, Zero, p_Displacement.y
					, Zero, Zero, Unity, p_Displacement.z
					, Zero, Zero, Zero, Unity);
	}
}

#endif //#ifndef IncludedMathAlgebraH