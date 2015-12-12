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

		Edge(const Vector3& p_First, const Vector3& p_Second);

	//Attributes
	public:

		Vector3 First;
		Vector3 Second;
	};

	//==========
	// Ray
	//==========
	class Ray
	{
		//Operators
	public:

		Ray(const Vector3& p_Position, const Vector3& p_Direction);

		//Attributes
	public:

		Vector3 Position;
		Vector3 Direction;
	};

	//==========
	// Trigon
	//==========
	class Trigon
	{
	//Operators
	public:

		Trigon(const Vector3& p_First, const Vector3& p_Second, const Vector3& p_Third);

	//Attributes
	public:

		Vector3 First;
		Vector3 Second;
		Vector3 Third;
	};

	//==========
	// Plane
	//==========
	class Plane
	{
	//Operators
	public:

		inline Plane(const Vector3& p_Orientation);

		inline Plane(const Ray& p_Ray);

		inline Plane(const Trigon& p_Ray);

	//Attributes
	public:

		Vector3 Normal;
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
			: Centre(MakeVector(p_X, p_Y, p_Z))
			, Radius(p_Radius)
		{}

		Sphere::Sphere(const Vector3& p_Centre, const scalar& p_Radius)
			: Centre(p_Centre)
			, Radius(p_Radius)
		{}

	//Attributes
	public:

		Vector3 Centre;
		scalar Radius;
	};

	//==========
	// Line
	//==========
	class Line
	{
	//Operators
	public:
	
		Line(const Vector3& p_A, const Vector3& p_B);

		Line(const Ray& p_Ray);

	//Attributes
	public:
	
		Vector3 Centre;
		Vector3 Direction;
	};

	namespace ConstantGeometries
	{
		//const static Plane XY(ConstantVectors::K);
		//const static Plane XZ(ConstantVectors::J);
		//const static Plane YZ(ConstantVectors::I);
	}
} // namespace Mathematics

#endif //#ifndef IncludedMathSimplicesH