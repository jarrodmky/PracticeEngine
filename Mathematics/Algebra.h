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
	// Definitions
	//===========================================================================
	
	using OneVarFxn = std::function<const scalar(const scalar)>; 
	using TwoVarFxn = std::function<const scalar(const scalar, const scalar)>; 
	using ThreeVarFxn = std::function<const scalar(const scalar, const scalar, const scalar)>; 
	
	using OneVarFld = std::function<const Vector3(const scalar)>; 
	using TwoVarFld = std::function<const Vector3(const scalar, const scalar)>; 
	using ThreeVarFld = std::function<const Vector3(const scalar, const scalar, const scalar)>;

	//===========================================================================
	// Operators
	//===========================================================================
	
	inline const Quaternion operator *(const scalar p_Lhs, const Quaternion& p_Rhs)
	{
		return p_Rhs * p_Lhs;
	}

	//==========
	// Interpolation
	//==========

	template <u32 t_Rows>
	inline const Vector<t_Rows> InterpolateLinearly(const Vector<t_Rows>& p_A, const Vector<t_Rows>& p_B, const scalar p_Ratio)
	{
		return p_A + ((p_B - p_A) * p_Ratio);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const Vector<t_Rows> Lerp(const Vector<t_Rows>& p_A, const Vector<t_Rows>& p_B, const scalar p_Ratio)
	{
		return InterpolateLinearly<t_Rows>(p_A, p_B, p_Ratio);
	}

	//==========
	//  Casts
	//==========

	//vector
	inline Vector2 MakeVector(const scalar p_X, const scalar p_Y)
	{
		Vector2 temp;
		temp(1) = p_X;
		temp(2) = p_Y;
		return temp;
	}

	//---------------------------------------------------------------------------

	inline Vector3 MakeVector(const scalar p_X, const scalar p_Y, const scalar p_Z)
	{
		Vector3 temp;
		temp(1) = p_X;
		temp(2) = p_Y;
		temp(3) = p_Z;
		return temp;
	}

	//---------------------------------------------------------------------------

	inline Vector4 MakeVector(const scalar p_X, const scalar p_Y, const scalar p_Z, const scalar p_W)
	{
		Vector4 temp;
		temp(1) = p_X;
		temp(2) = p_Y;
		temp(3) = p_Z;
		temp(4) = p_W;
		return temp;
	}

	//---------------------------------------------------------------------------

	inline Vector4 MakeVector(const Vector3& p_Vector)
	{
		return MakeVector(p_Vector(1), p_Vector(2), p_Vector(3), Zero);
	}

	//---------------------------------------------------------------------------

	inline Vector3 MakeVector(const Vector4& p_Vector)
	{
		return MakeVector(p_Vector(1), p_Vector(2), p_Vector(3));
	}

	//---------------------------------------------------------------------------

	inline Vector4 MakePoint(const scalar p_X, const scalar p_Y, const scalar p_Z)
	{
		return MakeVector(p_X, p_Y, p_Z, Unity);
	}

	//---------------------------------------------------------------------------

	inline Vector4 MakePoint(const Vector3& p_Vector)
	{
		return MakePoint(p_Vector(1), p_Vector(2), p_Vector(3));
	}

	//---------------------------------------------------------------------------

	inline Vector4 MakePoint(const Vector4& p_Vector)
	{
		const scalar projScale((EquivalentToEachOther(p_Vector(4), 0.0f)) ? (1.0f) : (p_Vector(4)));
		Vector4 temp(p_Vector);
		temp /= projScale;
		return temp;
	}

	//---------------------------------------------------------------------------

	//matrices
	inline const Matrix22 MakeMatrix(
		const scalar p_r1c1, const scalar p_r1c2
		, const scalar p_r2c1, const scalar p_r2c2)
	{
		Matrix22 temp;

		//first column
		temp(1, 1) = p_r1c1;
		temp(2, 1) = p_r2c1;

		//second column
		temp(1, 2) = p_r1c2;
		temp(2, 2) = p_r2c2;
	}

	//---------------------------------------------------------------------------

	inline const Matrix22 MakeMatrix(const Vector2& p_Column1
		, const Vector2& p_Column2)
	{
		Matrix22 temp;

		//first column
		temp(1, 1) = p_Column1(1);
		temp(2, 1) = p_Column1(2);

		//second column
		temp(1, 2) = p_Column2(1);
		temp(2, 2) = p_Column2(2);

		return temp;
	}
	//---------------------------------------------------------------------------

	inline const Matrix33 MakeMatrix(
		const scalar p_r1c1, const scalar p_r1c2, const scalar p_r1c3
		, const scalar p_r2c1, const scalar p_r2c2, const scalar p_r2c3
		, const scalar p_r3c1, const scalar p_r3c2, const scalar p_r3c3)
	{
		Matrix33 temp;

		//first column
		temp(1, 1) = p_r1c1;
		temp(2, 1) = p_r2c1;
		temp(3, 1) = p_r3c1;

		//second column
		temp(1, 2) = p_r1c2;
		temp(2, 2) = p_r2c2;
		temp(3, 2) = p_r3c2;

		//third column
		temp(1, 3) = p_r1c3;
		temp(2, 3) = p_r2c3;
		temp(3, 3) = p_r3c3;

		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 MakeMatrix(const Vector3& p_Column1, const Vector3& p_Column2, const Vector3& p_Column3)
	{
		Matrix33 temp;

		//first column
		temp(1, 1) = p_Column1(1);
		temp(2, 1) = p_Column1(2);
		temp(3, 1) = p_Column1(3);

		//second column
		temp(1, 2) = p_Column2(1);
		temp(2, 2) = p_Column2(2);
		temp(3, 2) = p_Column2(3);

		//third column
		temp(1, 3) = p_Column3(1);
		temp(2, 3) = p_Column3(2);
		temp(3, 3) = p_Column3(3);

		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeMatrix(
		const scalar p_r1c1, const scalar p_r1c2, const scalar p_r1c3, const scalar p_r1c4
		, const scalar p_r2c1, const scalar p_r2c2, const scalar p_r2c3, const scalar p_r2c4
		, const scalar p_r3c1, const scalar p_r3c2, const scalar p_r3c3, const scalar p_r3c4
		, const scalar p_r4c1, const scalar p_r4c2, const scalar p_r4c3, const scalar p_r4c4)
	{
		Matrix44 temp;

		//first column
		temp(1, 1) = p_r1c1;
		temp(2, 1) = p_r2c1;
		temp(3, 1) = p_r3c1;
		temp(4, 1) = p_r4c1;

		//second column
		temp(1, 2) = p_r1c2;
		temp(2, 2) = p_r2c2;
		temp(3, 2) = p_r3c2;
		temp(4, 2) = p_r4c2;

		//third column
		temp(1, 3) = p_r1c3;
		temp(2, 3) = p_r2c3;
		temp(3, 3) = p_r3c3;
		temp(4, 3) = p_r4c3;

		//fourth column
		temp(1, 4) = p_r1c4;
		temp(2, 4) = p_r2c4;
		temp(3, 4) = p_r3c4;
		temp(4, 4) = p_r4c4;

		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeMatrix(const Vector4& p_Column1
		, const Vector4& p_Column2
		, const Vector4& p_Column3
		, const Vector4& p_Column4)
	{
		Matrix44 temp;

		//first column
		temp(1, 1) = p_Column1(1);
		temp(2, 1) = p_Column1(2);
		temp(3, 1) = p_Column1(3);
		temp(4, 1) = p_Column1(4);

		//second column
		temp(1, 2) = p_Column2(1);
		temp(2, 2) = p_Column2(2);
		temp(3, 2) = p_Column2(3);
		temp(4, 2) = p_Column2(4);

		//third column
		temp(1, 3) = p_Column3(1);
		temp(2, 3) = p_Column3(2);
		temp(3, 3) = p_Column3(3);
		temp(4, 3) = p_Column3(4);

		//fourth column
		temp(1, 4) = p_Column4(1);
		temp(2, 4) = p_Column4(2);
		temp(3, 4) = p_Column4(3);
		temp(4, 4) = p_Column4(4);

		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeMatrix(const Matrix33& p_Matrix)
	{
		//copy in matrix
		return MakeMatrix
			( MakeVector(p_Matrix.Column(1))
			, MakeVector(p_Matrix.Column(2))
			, MakeVector(p_Matrix.Column(3))
			, W());
	}

	//==========
	// Vectors
	//==========

	template <u32 t_Rows>
	inline const bool ApproximateToEachOther(const Vector<t_Rows>& p_Lhs, const Vector<t_Rows>& p_Rhs, const scalar p_Tolerance)
	{
		return (p_Lhs - p_Rhs).Length() < p_Tolerance;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const scalar AngleBetween(const Vector<t_Rows>& p_Lhs, const Vector<t_Rows>& p_Rhs)
	{
		return std::acos(p_Lhs.Direction() | p_Rhs.Direction());
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 SkewMatrix(const Vector3& p_Vector)
	{
		return MakeMatrix(Zero, -p_Vector(3), p_Vector(2)
				 , p_Vector(3), Zero, -p_Vector(1)
				, -p_Vector(2), p_Vector(1), Zero);
	}

	//---------------------------------------------------------------------------

	inline const Vector3 RotateVector(const Vector3& p_Axis
									, const scalar p_Angle
									, const Vector3& p_Vector)
	{
		Vector3 temp(p_Vector);
		Quaternion(p_Axis, p_Angle).RotateVector(temp);
		return temp;
	}

	//==========
	// Matrix
	//==========

	inline const Quaternion Rotation(const Matrix33& p_Rotation)
	{
		Assert(p_Rotation.IsSpecialOthogonal(), "Cannot map general matrix to quaternion!");

		scalar trace = p_Rotation.Trace();
		scalar real = 0.0f;
		Vector3 imaginary;

		if (trace > 0.0f) 
		{
			scalar div = Unity / sqrt(trace + Unity) * 2.0f;
			real = 0.25f / div;
			imaginary = MakeVector(p_Rotation(3, 2) - p_Rotation(2, 3), p_Rotation(1, 3) - p_Rotation(3, 1), p_Rotation(2, 1) - p_Rotation(1, 2));
			imaginary *= div;
		}
		else
		{
			Vector3 d = p_Rotation.Diagonal();

			if ((d(1) > d(2)) && (d(1) > d(3))) 
			{
				scalar div = Unity / sqrt(Unity + d(1) - d(2) - d(3)) * 2.0f;
				real = (p_Rotation(3, 2) - p_Rotation(2, 3)) * div;
				imaginary = MakeVector(0.25f / div, (p_Rotation(1, 2) + p_Rotation(2, 1)) * div, (p_Rotation(1, 3) + p_Rotation(3, 1)) * div);
			}
			else if (d(2) > d(3))
			{
				scalar div = Unity / sqrt(Unity + d(2) - d(1) - d(3)) * 2.0f;
				real = (p_Rotation(1, 3) - p_Rotation(3, 1)) * div;
				imaginary = MakeVector((p_Rotation(1, 2) + p_Rotation(2, 1)) * div, 0.25f / div, (p_Rotation(2, 3) + p_Rotation(3, 2)) * div);
			}
			else 
			{
				scalar div = Unity / sqrt(Unity + d(3) - d(1) - d(2)) * 2.0f; //
				real = (p_Rotation(2, 1) - p_Rotation(1, 2)) * div;
				imaginary = MakeVector((p_Rotation(1, 3) + p_Rotation(3, 1)) * div, (p_Rotation(2, 3) + p_Rotation(3, 2)) * div, 0.25f / div);
			}
		}

		return Quaternion(real, imaginary).Normalize();
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 Rotation(const Quaternion& p_Rotation)
	{
		const scalar w(p_Rotation.ScalarPart());
		const Vector3 v(p_Rotation.VectorPart().Direction());

		return (Unity - (2.0f * (v | v))) * I3() + 2.0f * (w * SkewMatrix(v) + (v ^ v));
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 RotationInverse(const Quaternion& p_Rotation)
	{
		Matrix33 temp(Rotation(p_Rotation));
		temp.Transpose();
		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 Rotation(const Vector3& p_Axis, const scalar p_Angle)
	{
		const scalar s(std::sin(p_Angle));
		const scalar c(std::cos(p_Angle));
		const Vector3 a(p_Axis.Direction());

		return c * I3() + s * SkewMatrix(a) + (Unity - c) * (a ^ a);
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 RotationAboutX(const scalar p_Angle)
	{
		const scalar s = std::sin(p_Angle);
		const scalar c = std::cos(p_Angle);

		return MakeMatrix(Unity, Zero, Zero
					, Zero, c, -s
					, Zero, s, c);
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 RotationAboutY(const scalar p_Angle)
	{
		const scalar s = std::sin(p_Angle);
		const scalar c = std::cos(p_Angle);

		return MakeMatrix(c, Zero, s
					, Zero, Unity, Zero
					, -s, Zero, c);
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 RotationAboutZ(const scalar p_Angle)
	{
		const scalar s = std::sin(p_Angle);
		const scalar c = std::cos(p_Angle);

		return MakeMatrix(c, -s, Zero
					, s, c, Zero
					, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 Scaling(const Vector3& p_Scaling)
	{
		return MakeMatrix(p_Scaling(1), Zero, Zero
			, Zero, p_Scaling(2), Zero
			, Zero, Zero, p_Scaling(3));
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 ScalingInverse(const Vector3& p_Scaling)
	{
		return MakeMatrix(Inverse(p_Scaling(1)), Zero, Zero
			, Zero, Inverse(p_Scaling(2)), Zero
			, Zero, Zero, Inverse(p_Scaling(3)));
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 Translation(const Vector3& p_Displacement)
	{
		return MakeMatrix(Unity, Zero, Zero, p_Displacement(1)
					, Zero, Unity, Zero, p_Displacement(2)
					, Zero, Zero, Unity, p_Displacement(3)
					, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 TranslationInverse(const Vector3& p_Displacement)
	{
		return MakeMatrix(Unity, Zero, Zero, -p_Displacement(1)
			, Zero, Unity, Zero, -p_Displacement(2)
			, Zero, Zero, Unity, -p_Displacement(3)
			, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 Transformation(
		const Vector3& p_Translation,
		const Vector3& p_RotationCentre,
		const Quaternion& p_Rotation,
		const Vector3& p_ScalingCentre,
		const Quaternion& p_ScalingRotation,
		const Vector3& p_Scaling)
	{
		return Translation(p_Translation)
			* Translation(p_RotationCentre)
			* MakeMatrix(Rotation(p_Rotation))
			* TranslationInverse(p_RotationCentre)
			* Translation(p_ScalingCentre)
			* MakeMatrix(Rotation(p_ScalingRotation))
			* MakeMatrix(Scaling(p_Scaling))
			* MakeMatrix(RotationInverse(p_ScalingRotation))
			* TranslationInverse(p_ScalingCentre);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 Transformation(
		const Vector3& p_Translation,
		const Vector3& p_RotationCentre,
		const Quaternion& p_Rotation,
		const Vector3& p_Scaling)
	{
		return Translation(p_Translation)
			* Translation(p_RotationCentre)
			* MakeMatrix(Rotation(p_Rotation))
			* TranslationInverse(p_RotationCentre)
			* MakeMatrix(Scaling(p_Scaling));
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 Transformation(
		const Vector3& p_Translation,
		const Quaternion& p_Rotation,
		const Vector3& p_Scaling)
	{
		return Translation(p_Translation)
			* MakeMatrix(Rotation(p_Rotation))
			* MakeMatrix(Scaling(p_Scaling));
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 Transformation(
		const Vector3& p_Translation,
		const Quaternion& p_Rotation)
	{
		return Translation(p_Translation)
			* MakeMatrix(Rotation(p_Rotation));
	}
}

#endif //#ifndef IncludedMathAlgebraH