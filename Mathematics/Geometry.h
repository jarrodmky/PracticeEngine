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
#include "Point.h"
#include "Sphere.h"
#include "Ray.h"
#include "Line.h"
#include "Plane.h"
#include "Frame.h"

namespace Mathematics
{
//===========================================================================
// Operators
//===========================================================================

	inline const Point operator *(const Matrix& p_Matrix, const Point& p_Point)
	{
		return Point(p_Matrix.Column(4)) + (p_Matrix * p_Point.PositionVector());
	}

//===========================================================================
// Functions
//===========================================================================

//Distance Functions

	//Minimum distance between a point and a line
	const scalar Distance(const Line& p_Line, const Point& p_Point);
	const scalar DistanceSquared(const Line& p_Line, const Point& p_Point);
	
	//Minimum distance between two lines
	const scalar Distance(const Line& p_Line1, const Line& p_Line2);
	const scalar DistanceSquared(const Line& p_Line1, const Line& p_Line2);
	
	//Minimum distance between a plane and a point
	const scalar Distance(const Plane& p_Plane, const Point& p_Point);
	const scalar DistanceSquared(const Plane& p_Plane, const Point& p_Point);

//Intersection Functions

	//True if a point is on a plane, false otherwise
	const bool PointIsOnPlane(const Point& p_Point, const Plane& p_Plane);

	//True if a line intersects a plane, false otherwise. Sets the point of intersection
	const bool LineIntersectsPlane(const Line& p_Line, const Plane& p_Plane, Point& p_Point);

	//True if a plane intersects a plane, false otherwise. Sets the line of intersection
	const bool PlaneIntersectsPlane(const Plane& p_Plane1, const Plane& p_Plane2, Line& p_Line);
	

//Coordinate Transforms

	inline const Vector SphericalToCartesian(const Vector& p_RadPhiTheta)
	{
		scalar st = sin(p_RadPhiTheta.z);
		scalar sp = sin(p_RadPhiTheta.y);
		scalar ct = cos(p_RadPhiTheta.z);
		scalar cp = cos(p_RadPhiTheta.y);
		scalar rad = p_RadPhiTheta.x;

		return Vector(rad * ct * sp, rad * st * sp, rad * cp);
	}

//Matrix transforms

	inline const Matrix ViewLookAt_RH(const Point& p_Position
		, const Point& p_Target
		, const Vector& p_Up = ConstantVectors::J)
	{
		using namespace ConstantScalars;
		const Vector zAxis((p_Position - p_Target).Direction());
		const Vector xAxis((p_Up * zAxis).Direction());
		const Vector yAxis( zAxis * xAxis);
		const Vector eye(p_Position.PositionVector());

		return Matrix(xAxis.x, xAxis.y, xAxis.z, xAxis|eye
					, yAxis.x, yAxis.y, yAxis.z, yAxis|eye
					, zAxis.x, zAxis.y, zAxis.z, zAxis|eye
					, Zero, Zero, Zero, Unity);
	}

	inline const Matrix ViewLookAt_LH(const Point& p_Position
		, const Point& p_Target
		, const Vector& p_Up = ConstantVectors::J)
	{
		using namespace ConstantScalars;
		const Vector zAxis((p_Target - p_Position).Direction());
		const Vector xAxis((p_Up * zAxis).Direction());
		const Vector yAxis(zAxis * xAxis);
		const Vector eye(p_Position.PositionVector());

		return Matrix(xAxis.x, xAxis.y, xAxis.z, -(xAxis | eye)
			, yAxis.x, yAxis.y, yAxis.z, -(yAxis | eye)
			, zAxis.x, zAxis.y, zAxis.z, -(zAxis | eye)
			, Zero, Zero, Zero, Unity);
	}

	inline const Matrix PerspectiveProjection_LH(const scalar p_FieldOfView
											   , const scalar p_AspectRatio
											   , const scalar p_zFar
											   , const scalar p_zNear)
	{
		using namespace ConstantScalars;
		const scalar yFOV = Inverse(std::tan(p_FieldOfView / 2.0f));
		const scalar xFOV = yFOV / p_AspectRatio;
		const scalar depthScale = p_zFar / (p_zFar - p_zNear);

		return Matrix(xFOV, Zero, Zero, Zero
			, Zero, yFOV, Zero, Zero
			, Zero, Zero, depthScale, -p_zNear*depthScale
			, Zero, Zero, Unity, Zero);
	}

	inline const Matrix PerspectiveProjection_RH(const scalar p_FieldOfView
		, const scalar p_AspectRatio
		, const scalar p_zFar
		, const scalar p_zNear)
	{
		using namespace ConstantScalars;
		const scalar yFOV = Inverse(std::tan(p_FieldOfView / 2.0f));
		const scalar xFOV = yFOV / p_AspectRatio;
		const scalar depthScale = p_zFar / (p_zNear - p_zFar);

		return Matrix(xFOV, Zero, Zero, Zero
			, Zero, yFOV, Zero, Zero
			, Zero, Zero, depthScale, p_zNear*depthScale
			, Zero, Zero, -Unity, Zero);
	}
}

#endif //#ifndef IncludedGeometryH