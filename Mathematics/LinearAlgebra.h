#ifndef IncludedMathLinearAlgebraH
#define IncludedMathLinearAlgebraH

//===========================================================================
// Filename:	LinearAlgebra.h
// Author:		Jarrod MacKay
// Description:	Contains the basic algebra of R^3
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Interval.h"
#include "LinearColour.h"
#include "Polynomial.h"
#include "Equations.h"

namespace Mathematics
{
	//===========================================================================
	// Vector Functions
	//===========================================================================

	inline Vector4 MakeVector(const LinearColour& p_Colour)
	{
		return MakeVector(p_Colour.R, p_Colour.G, p_Colour.B, p_Colour.A);
	}

	inline const Vector3 WorldUp()
	{
		return J();
	}
	inline const Vector3 WorldForward()
	{
		return -K(); //directx
	}
	inline const Vector3 WorldRight()
	{
		return I();
	}

	//---------------------------------------------------------------------------

	inline const Vector3 ProjectedVector(const Vector3& p_Normal,
		const Vector3& p_Vector)
	{
		return p_Vector.ProjectionAlong(p_Normal);
	}

	//---------------------------------------------------------------------------

	inline const Vector3 RotatedVector(const Vector3& p_Axis
		, const scalar p_Angle
		, const Vector3& p_Vector)
	{
		Vector3 temp(p_Vector);
		Quaternion(p_Axis, p_Angle).Rotate(temp);
		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Vector3 ReflectedVector(const Vector3& p_Normal
									, const Vector3& p_Vector)
	{
		Assert(p_Normal.IsUnit(), "Non-unit vector");
		return p_Vector - 2.0f * (p_Vector | p_Normal) * p_Normal;
	}

	//===========================================================================
	// Special Transforms
	//===========================================================================

	inline const Matrix44 MakeChangeOfBasis(const Vector3& p_I, const Vector3& p_J, const Vector3& p_K)
	{
		return MakeMatrix(MakeMatrix(p_I, p_J, p_K));
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeReflectionAboutXY()
	{
		return MakeChangeOfBasis(I(), J(), -K());
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeReflectionAboutOrigin()
	{
		return MakeChangeOfBasis(-I(), -J(), -K());
	}

	//---------------------------------------------------------------------------

	inline const Vector3 SphericalToCartesian(const Vector3& p_RadPolarAxial)
	{

		const scalar st = sin(p_RadPolarAxial(2));
		const scalar sp = sin(p_RadPolarAxial(1));
		const scalar ct = cos(p_RadPolarAxial(2));
		const scalar cp = cos(p_RadPolarAxial(1));
		const scalar rad = p_RadPolarAxial(0);

		return MakeVector((rad * ct * sp), (rad * cp), (rad * st * sp));
	}

	//---------------------------------------------------------------------------

	inline const Vector3 CartesianToSpherical (const Vector3& p_XYZ)
	{
		const scalar r = p_XYZ.Length();
		const scalar polar = std::atan2(p_XYZ(2), p_XYZ(0));
		const scalar axial = std::acos(p_XYZ(1));

		return MakeVector(r, polar, axial);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 ViewLookAt_RH(const Vector3& p_Position
		, const Vector3& p_Target
		, const Vector3& p_Up = J())
	{
		const Vector3 zAxis((p_Position - p_Target).Direction());
		const Vector3 xAxis((p_Up * zAxis).Direction());
		const Vector3 yAxis(zAxis * xAxis);
		const Vector3 eye(p_Position);

		return MakeMatrix(xAxis(0), xAxis(1), xAxis(2), xAxis | eye
			, yAxis(0), yAxis(1), yAxis(2), yAxis | eye
			, zAxis(0), zAxis(1), zAxis(2), zAxis | eye
			, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 ViewLookAt_LH(const Vector3& p_Position
		, const Vector3& p_Target
		, const Vector3& p_Up = J())
	{
		const Vector3 zAxis((p_Target - p_Position).Direction());
		const Vector3 xAxis((p_Up * zAxis).Direction());
		const Vector3 yAxis(zAxis * xAxis);
		const Vector3 eye(p_Position);

		return MakeMatrix(xAxis(0), xAxis(1), xAxis(2), -(xAxis | eye)
			, yAxis(0), yAxis(1), yAxis(2), -(yAxis | eye)
			, zAxis(0), zAxis(1), zAxis(2), -(zAxis | eye)
			, Zero, Zero, Zero, Unity);
	}

	//===========================================================================
	// Basic Transforms
	//===========================================================================

	inline const Matrix44 MakeRotation(const Quaternion& p_Rotation)
	{
		const scalar W(p_Rotation.ScalarPart());
		const Vector3 V(p_Rotation.VectorPart());
		Assert(p_Rotation.IsUnit(), "Not unit quaternion! Degenerate rotation!");
		const Vector3 TwoV(2.0f * V);
		
		return MakeMatrix(Unity - TwoV(1)*V(1) - TwoV(2)*V(2), TwoV(0)*V(1) - TwoV(2)*W, TwoV(0)*V(2) + TwoV(1)*W, Zero
						, TwoV(0)*V(1) + TwoV(2)*W, Unity - TwoV(0)*V(0) - TwoV(2)*V(2), TwoV(1)*V(2) - TwoV(0)*W, Zero
						, TwoV(0)*V(2) - TwoV(1)*W, TwoV(1)*V(2) + TwoV(0)*W, Unity - TwoV(0)*V(0) - TwoV(1)*V(1), Zero
						, Zero, Zero, Zero, Unity) * MakeChangeOfBasis(WorldRight(), WorldUp(), WorldForward());
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeRotation(const Vector3& p_Axis, const scalar p_Angle)
	{
		Assert(p_Axis.IsUnit(), "Axis is not unit length!");
		const scalar C(std::cos(p_Angle));
		const scalar OneMinusC(Unity - C);
		const Vector3 A(p_Axis);
		const Vector3 SA(std::sin(p_Angle) * A);

		return MakeMatrix(OneMinusC * A(0) * A(0) + C, OneMinusC * A(0) * A(1) - SA(2), OneMinusC * A(0) * A(2) + SA(1), Zero
						, OneMinusC * A(0) * A(1) + SA(2), OneMinusC * A(1) * A(1) + C, OneMinusC * A(1) * A(2) - SA(0), Zero
						, OneMinusC * A(0) * A(2) - SA(1), OneMinusC * A(1) * A(2) + SA(0), OneMinusC * A(2) * A(2) + C, Zero
						, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeInverseRotation(const Quaternion& p_Rotation)
	{
		return MakeRotation(p_Rotation).Transposition();
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeInverseRotation(const Vector3& p_Axis, const scalar p_Angle)
	{
		return MakeRotation(p_Axis, p_Angle).Transposition();
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeRotationAboutX(const scalar p_Angle)
	{
		const scalar s = std::sin(p_Angle);
		const scalar c = std::cos(p_Angle);

		return MakeMatrix(Unity, Zero, Zero, Zero
						, Zero, c, -s, Zero
						, Zero, s, c, Zero
						, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeRotationAboutY(const scalar p_Angle)
	{
		const scalar s = std::sin(p_Angle);
		const scalar c = std::cos(p_Angle);

		return MakeMatrix(c, Zero, s, Zero
						, Zero, Unity, Zero, Zero
						, -s, Zero, c, Zero
						, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeRotationAboutZ(const scalar p_Angle)
	{
		const scalar s = std::sin(p_Angle);
		const scalar c = std::cos(p_Angle);

		return MakeMatrix(c, -s, Zero, Zero
						, s, c, Zero, Zero
						, Zero, Zero, Unity, Zero
						, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeScaling(const scalar p_Scaling)
	{
		return MakeMatrix(p_Scaling, Zero, Zero, Zero
						, Zero, p_Scaling, Zero, Zero
						, Zero, Zero, p_Scaling, Zero
						, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeScaling(const Vector3& p_Scaling)
	{
		return MakeMatrix(p_Scaling(0), Zero, Zero, Zero
						, Zero, p_Scaling(1), Zero, Zero
						, Zero, Zero, p_Scaling(2), Zero
						, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeInverseScaling(const scalar p_Scaling)
	{
		scalar Inv(Inverse(p_Scaling));
		return MakeMatrix(Inv, Zero, Zero, Zero
						, Zero, Inv, Zero, Zero
						, Zero, Zero, Inv, Zero
						, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeInverseScaling(const Vector3& p_Scaling)
	{
		return MakeMatrix(Inverse(p_Scaling(0)), Zero, Zero, Zero
			, Zero, Inverse(p_Scaling(1)), Zero, Zero
			, Zero, Zero, Inverse(p_Scaling(2)), Zero
			, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeTranslation(const Vector3& p_Displacement)
	{
		return MakeMatrix(Unity, Zero, Zero, p_Displacement(0)
					, Zero, Unity, Zero, p_Displacement(1)
					, Zero, Zero, Unity, p_Displacement(2)
					, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeInverseTranslation(const Vector3& p_Displacement)
	{
		return MakeTranslation(-p_Displacement);
	}

	//===========================================================================
	// General Transforms
	//===========================================================================

	inline const Matrix44 MakeTransformation(
		const Vector3& p_Translation,
		const Vector3& p_RotationCentre,
		const Quaternion& p_Rotation,
		const Vector3& p_ScalingCentre,
		const Quaternion& p_ScalingRotation,
		const Vector3& p_Scaling)
	{
		return MakeTranslation(p_Translation)
			 * MakeTranslation(p_RotationCentre)
			 * MakeRotation(p_Rotation)
			 * MakeInverseTranslation(p_RotationCentre)
			 * MakeTranslation(p_ScalingCentre)
			 * MakeRotation(p_ScalingRotation)
			 * MakeScaling(p_Scaling)
			 * MakeInverseRotation(p_ScalingRotation)
			 * MakeInverseTranslation(p_ScalingCentre);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeScaling(
		const Vector3& p_Translation,
		const Vector3& p_ScalingCentre,
		const Quaternion& p_ScalingRotation,
		const Vector3& p_Scaling)
	{
		return MakeTranslation(p_Translation)
			* MakeTranslation(p_ScalingCentre)
			* MakeRotation(p_ScalingRotation)
			* MakeScaling(p_Scaling)
			* MakeInverseRotation(p_ScalingRotation)
			* MakeInverseTranslation(p_ScalingCentre);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeRotation(
		const Vector3& p_Translation,
		const Vector3& p_RotationCentre,
		const Quaternion& p_Rotation)
	{
		return MakeTranslation(p_Translation)
			* MakeTranslation(p_RotationCentre)
			* MakeRotation(p_Rotation)
			* MakeInverseTranslation(p_RotationCentre);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeTransformation(
		const Vector3& p_Translation,
		const Quaternion& p_Rotation,
		const Vector3& p_Scaling)
	{
		return MakeTranslation(p_Translation)
			* MakeRotation(p_Rotation)
			* MakeScaling(p_Scaling);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeTransformation(
		const Vector3& p_Translation,
		const scalar& p_Scaling)
	{
		return MakeTranslation(p_Translation)
			* MakeScaling(p_Scaling);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeTransformation(
		const Vector3& p_Translation,
		const Quaternion& p_Rotation,
		const scalar& p_Scaling)
	{
		return MakeTranslation(p_Translation)
			* MakeRotation(p_Rotation)
			* MakeScaling(p_Scaling);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeTransformation(
		const Vector3& p_Translation,
		const Quaternion& p_Rotation)
	{
		return MakeTranslation(p_Translation)
			* MakeRotation(p_Rotation);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeInverseTransformation(
		const Vector3& p_Translation,
		const Quaternion& p_Rotation)
	{
		return MakeInverseRotation(p_Rotation)
			* MakeInverseTranslation(p_Translation);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeInverseTransformation(
		const Vector3& p_Translation,
		const Quaternion& p_Rotation,
		const Vector3& p_Scaling)
	{
		return MakeInverseScaling(p_Scaling)
			* MakeInverseRotation(p_Rotation)
			* MakeInverseTranslation(p_Translation);
	}

	//===========================================================================
	// Projective Transforms
	//===========================================================================

	inline const Matrix44 MakePerspectiveProjection(const scalar p_LeftX
		, const scalar p_RightX
		, const scalar p_BottomY
		, const scalar p_TopY
		, const scalar p_FarZ
		, const scalar p_NearZ)
	{
		const scalar TwoNear(2.0f * p_NearZ);
		return MakeMatrix(TwoNear / (p_RightX - p_LeftX), Zero, (p_RightX + p_LeftX) / (p_RightX - p_LeftX), Zero
			, Zero, TwoNear / (p_TopY - p_BottomY), (p_TopY + p_BottomY) / (p_TopY - p_BottomY), Zero
			, Zero, Zero, -(p_FarZ + p_NearZ) / (p_FarZ - p_NearZ), -(TwoNear * p_FarZ) / (p_FarZ - p_NearZ)
			, Zero, Zero, -Unity, Zero);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakePerspectiveProjection(const scalar p_LeftX
		, const scalar p_RightX
		, const scalar p_BottomY
		, const scalar p_TopY
		, const scalar p_NearZ)
	{
		const scalar TwoNear(2.0f * p_NearZ);
		return MakeMatrix(TwoNear / (p_RightX - p_LeftX), Zero, (p_RightX + p_LeftX) / (p_RightX - p_LeftX), Zero
			, Zero, TwoNear / (p_TopY - p_BottomY), (p_TopY + p_BottomY) / (p_TopY - p_BottomY), Zero
			, Zero, Zero, -Unity, -TwoNear
			, Zero, Zero, -Unity, Zero);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakePerspectiveProjection(const scalar p_FieldOfView
		, const scalar p_AspectRatio
		, const scalar p_FarZ
		, const scalar p_NearZ)
	{
		const scalar focalLength = Inverse(std::tan(p_FieldOfView * 0.5f));
		const scalar xFOV = focalLength / p_AspectRatio;
		const scalar depthScale = p_FarZ / (p_NearZ - p_FarZ);

		return MakeMatrix(xFOV, Zero, Zero, Zero
			, Zero, focalLength, Zero, Zero
			, Zero, Zero, depthScale, p_NearZ*depthScale
			, Zero, Zero, -Unity, Zero);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakePerspectiveProjection(const u32 p_Width
		, const u32 p_Height
		, const scalar p_FarZ
		, const scalar p_NearZ)
	{
		const scalar TwoNear(2.0f * p_NearZ);
		return MakeMatrix(TwoNear / static_cast<scalar>(p_Width), Zero, Zero, Zero
			, Zero, TwoNear / static_cast<scalar>(p_Height), Zero, Zero
			, Zero, Zero, -(p_FarZ + p_NearZ) / (p_FarZ - p_NearZ), -(TwoNear * p_FarZ) / (p_FarZ - p_NearZ)
			, Zero, Zero, -Unity, Zero);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeOrthographicProjection(const u32 p_Width
		, const u32 p_Height
		, const scalar p_FarZ
		, const scalar p_NearZ)
	{
		return MakeMatrix(2.0f / static_cast<scalar>(p_Width), Zero, Zero, Zero
			, Zero, 2.0f / static_cast<scalar>(p_Height), Zero, Zero
			, Zero, Zero, -2.0f / (p_FarZ - p_NearZ), -(p_NearZ + p_FarZ) / (p_FarZ - p_NearZ)
			, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeOrthographicView(const u32 p_Width
		, const u32 p_Height
		, const scalar p_FarZ
		, const scalar p_NearZ)
	{
		//return MakeMatrix(2.0f / static_cast<scalar>(p_Width), Zero, Zero, Zero
		//	, Zero, 2.0f / static_cast<scalar>(p_Height), Zero, Zero
		//	, Zero, Zero, 1.0f / (p_FarZ - p_NearZ), Zero
		//	, Zero, Zero, Zero, Unity);

		const scalar depthScale = 1.0f / (p_NearZ - p_FarZ);
		const scalar invW = 1.0f / static_cast<scalar>(p_Width);
		const scalar invH = 1.0f / static_cast<scalar>(p_Height);

		return MakeMatrix(1.0f * invW, Zero, Zero, Zero
			, Zero, 1.0f * invH, Zero, Zero
			, Zero, Zero, -depthScale, (p_NearZ + p_FarZ )*depthScale
			, Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakePerspectiveView(const scalar p_FieldOfView
		, const scalar p_AspectRatio
		, const scalar p_FarZ
		, const scalar p_NearZ)
	{
		const scalar yFOV = Inverse(std::tan(p_FieldOfView / 2.0f));
		const scalar xFOV = yFOV * p_AspectRatio;
		const scalar depthScale = p_FarZ / (p_NearZ - p_FarZ);

		return MakeMatrix(xFOV, Zero, Zero, Zero
			, Zero, yFOV, Zero, Zero
			, Zero, Zero, depthScale, p_NearZ*depthScale
			, Zero, Zero, -Unity, Zero);
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeNormalizedProjection(const u32 p_Height, const u32 p_Width)
	{
		const scalar w = static_cast<scalar>(p_Width);
		const scalar h = static_cast<scalar>(p_Height);

		return MakeMatrix(2.0f / w, Zero, Zero, Zero
			, Zero, -2.0f / h, Zero, Zero
			, Zero, Zero, Unity, Zero
			, -Unity, Unity, Zero, Unity);
	}
}

#endif //#ifndef IncludedMathLinearAlgebraH