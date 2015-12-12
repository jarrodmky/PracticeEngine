#ifndef IncludedGeometryH
#define IncludedGeometryH

//===========================================================================
// Filename:	Geometry.h
// Author:		Jarrod MacKay
// Description:	Includes the library objects used for 3D space.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "MathBase.h"
#include "Algebra.h"
#include "Simplices.h"
#include "Frame.h"
#include "MatrixStack.h"

namespace Mathematics
{

//===========================================================================
// Functions
//===========================================================================

//Distance Functions

	//Minimum distance between a point and a line
	const scalar Distance(const Line& p_Line, const Vector4& p_Point);
	const scalar DistanceSquared(const Line& p_Line, const Vector4& p_Point);
	
	//Minimum distance between two lines
	const scalar Distance(const Line& p_Line1, const Line& p_Line2);
	const scalar DistanceSquared(const Line& p_Line1, const Line& p_Line2);
	
	//Minimum distance between a plane and a point
	const scalar Distance(const Plane& p_Plane, const Vector4& p_Point);
	const scalar DistanceSquared(const Plane& p_Plane, const Vector4& p_Point);

//Intersection Functions

	//True if a point is on a plane, false otherwise
	const bool PointIsOnPlane(const Vector4& p_Point, const Plane& p_Plane);

	//True if a line intersects a plane, false otherwise. Sets the point of intersection
	const bool LineIntersectsPlane(const Line& p_Line, const Plane& p_Plane, Vector4& p_Point);

	//True if a plane intersects a plane, false otherwise. Sets the line of intersection
	const bool PlaneIntersectsPlane(const Plane& p_Plane1, const Plane& p_Plane2, Line& p_Line);
	

//Coordinate Transforms

	inline const Vector3 SphericalToCartesian(const Vector3& p_RadPolarAxial)
	{
		const scalar st = sin(p_RadPolarAxial(3));
		const scalar sp = sin(p_RadPolarAxial(2));
		const scalar ct = cos(p_RadPolarAxial(3));
		const scalar cp = cos(p_RadPolarAxial(2));
		const scalar rad = p_RadPolarAxial(1);

		return MakeVector(rad * ct * sp, rad * st * sp, rad * cp);
	}

//Matrix transforms

	inline const Matrix44 Transform_RH(const Vector4& p_Right
									 , const Vector4& p_Forward
									 , const Vector4& p_Up
									 , const Vector4& p_Origin)
	{
		return MakeMatrix(p_Right(1), p_Up(1), p_Forward(1), p_Origin(1)
					, p_Right(2), p_Up(2), p_Forward(2), p_Origin(2)
					, p_Right(3), p_Up(3), p_Forward(3), p_Origin(3)
					, Zero, Zero, Zero, Unity);
	}

	inline const Matrix44 Transform_LH(const Vector3& p_Left
								   , const Vector3& p_Up
								   , const Vector3& p_Forward
								   , const Vector3& p_Origin)
	{
		return MakeMatrix(p_Left(1), p_Up(1), p_Forward(1), p_Origin(1)
					, p_Left(2), p_Up(2), p_Forward(2), p_Origin(2)
					, p_Left(3), p_Up(3), p_Forward(3), p_Origin(3)
					, Zero, Zero, Zero, Unity);
	}

	inline const Matrix44 ViewLookAt_RH(const Vector3& p_Position
		, const Vector3& p_Target
		, const Vector3& p_Up = J())
	{
		const Vector3 zAxis((p_Position - p_Target).Direction());
		const Vector3 xAxis((p_Up * zAxis).Direction());
		const Vector3 yAxis( zAxis * xAxis);
		const Vector3 eye(p_Position);

		return MakeMatrix(xAxis(1), xAxis(2), xAxis(3), xAxis|eye
					, yAxis(1), yAxis(2), yAxis(3), yAxis|eye
					, zAxis(1), zAxis(2), zAxis(3), zAxis|eye
					, Zero, Zero, Zero, Unity);
	}

	inline const Matrix44 ViewLookAt_LH(const Vector3& p_Position
		, const Vector3& p_Target
		, const Vector3& p_Up = J())
	{
		const Vector3 zAxis((p_Target - p_Position).Direction());
		const Vector3 xAxis((p_Up * zAxis).Direction());
		const Vector3 yAxis(zAxis * xAxis);
		const Vector3 eye(p_Position);

		return MakeMatrix(xAxis(1), xAxis(2), xAxis(3), -(xAxis | eye)
			, yAxis(1), yAxis(2), yAxis(3), -(yAxis | eye)
			, zAxis(1), zAxis(2), zAxis(3), -(zAxis | eye)
			, Zero, Zero, Zero, Unity);
	}

	inline const Matrix44 PerspectiveProjection_RH(const scalar p_FieldOfView
		, const scalar p_AspectRatio
		, const scalar p_zFar
		, const scalar p_zNear)
	{
		const scalar yFOV = Inverse(std::tan(p_FieldOfView / 2.0f));
		const scalar xFOV = yFOV / p_AspectRatio;
		const scalar depthScale = p_zFar / (p_zNear - p_zFar);

		return MakeMatrix(xFOV, Zero, Zero, Zero
			, Zero, yFOV, Zero, Zero
			, Zero, Zero, depthScale, p_zNear*depthScale
			, Zero, Zero, -Unity, Zero);
	}

	inline const Matrix44 PerspectiveProjection_LH(const scalar p_FieldOfView
											   , const scalar p_AspectRatio
											   , const scalar p_zFar
											   , const scalar p_zNear)
	{
		const scalar yFOV = Inverse(std::tan(p_FieldOfView / 2.0f));
		const scalar xFOV = yFOV / p_AspectRatio;
		const scalar depthScale = p_zFar / (p_zFar - p_zNear);

		return MakeMatrix(xFOV, Zero, Zero, Zero
			, Zero, yFOV, Zero, Zero
			, Zero, Zero, depthScale, -p_zNear*depthScale
			, Zero, Zero, Unity, Zero);
	}

	inline const Matrix44 ScreenToNDC(const u32 p_Height, const u32 p_Width)
	{
		const scalar w = static_cast<scalar>(p_Width);
		const scalar h = static_cast<scalar>(p_Height);

		return MakeMatrix(2.0f / w, Zero, Zero, Zero
			, Zero, -2.0f / h, Zero, Zero
			, Zero, Zero, Unity, Zero
			, -Unity, Unity, Zero, Unity);
	}
}

#endif //#ifndef IncludedGeometryH