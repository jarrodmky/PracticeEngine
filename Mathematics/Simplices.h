#ifndef IncludedMathSimplicesH
#define IncludedMathSimplicesH

//===========================================================================
// Filename:	Simplices.h
// Author:		Jarrod MacKay
// Description:	Defines simple three dimensional shapes.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Vector.h"
#include "Point.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	//TODO:
	//Cone
	//Box
	//Torus
	//Ellipsoid
	//Cylinder

	//==========
	// Edge
	//==========
	class Edge
	{
	//Operators
	public:

		Edge(const Point& p_First, const Point& p_Second);

	//Attributes
	public:

		Point First;
		Point Second;
	};

	//==========
	// Ray
	//==========
	class Ray
	{
		//Operators
	public:

		Ray(const Point& p_Position, const Vector& p_Direction);

		//Attributes
	public:

		Point Position;
		Vector Direction;
	};

	//==========
	// Trigon
	//==========
	class Trigon
	{
	//Operators
	public:

		Trigon(const Point& p_First, const Point& p_Second, const Point& p_Third);

	//Attributes
	public:

		Point First;
		Point Second;
		Point Third;
	};

	//==========
	// Plane
	//==========
	class Plane
	{
	//Operators
	public:

		inline Plane(const Vector& p_Orientation);

		inline Plane(const Ray& p_Ray);

		inline Plane(const Trigon& p_Ray);

	//Attributes
	public:

		Vector Normal;
		scalar Constant;
	};

	//==========
	// Sphere
	//==========
	class Sphere
	{
	//Operators
	public:

		Sphere::Sphere(const scalar& p_X
			, const scalar& p_Y
			, const scalar& p_Z
			, const scalar& p_Radius)
			: Centre(Point(p_X, p_Y, p_Z))
			, Radius(p_Radius)
		{}

		Sphere::Sphere(const Point& p_Centre, const scalar& p_Radius)
			: Centre(p_Centre)
			, Radius(p_Radius)
		{}

	//Attributes
	public:

		Point Centre;
		scalar Radius;
	};

	//==========
	// Line
	//==========
	class Line
	{
	//Operators
	public:
	
		Line(const Point& p_Centre, const Vector& p_Direction);

		Line(const Point& p_Centre, const Point& p_Offset);

		Line(const Ray& p_Ray);

	//Attributes
	public:
	
		Point Centre;
		Vector Direction;
	};

	namespace ConstantGeometries
	{
		//const static Plane XY(ConstantVectors::K);
		//const static Plane XZ(ConstantVectors::J);
		//const static Plane YZ(ConstantVectors::I);
	}
} // namespace Mathematics

#endif //#ifndef IncludedMathSimplicesH