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
#include "Vector.h"
#include "Point.h"
#include "Sphere.h"
#include "Ray.h"
#include "Line.h"
#include "Plane.h"

namespace Mathematics
{
//===========================================================================
// Operators
//===========================================================================

	inline const Vector operator *(const scalar p_Lhs, const Vector& p_Rhs)
	{
		return p_Rhs * p_Lhs;
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
}

#endif //#ifndef IncludedGeometryH