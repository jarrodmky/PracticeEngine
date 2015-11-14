#ifndef IncludedMathPlaneH
#define IncludedMathPlaneH

//===========================================================================
// Filename:	Plane.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 3 dimensional Plane
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Vector.h"
#include "Point.h"
#include "Ray.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	class Plane
	{
	//Operators
	public:

		inline Plane(const Vector& p_Orientation);

		inline Plane(const Point& p_Anchor, const Vector& p_Normal);

		inline Plane(const Ray& p_Ray);

	//Attributes
	public:
	
			Vector Normal;
			scalar Constant;
	};

	namespace ConstantPlanes
	{
		//const static Plane XY(ConstantVectors::K);
		//const static Plane XZ(ConstantVectors::J);
		//const static Plane YZ(ConstantVectors::I);
	}
} // namespace Mathematics

#include "Plane.inl"

#endif //#ifndef IncludedMathPlaneH