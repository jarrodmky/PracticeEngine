#ifndef IncludedMathSphereH
#define IncludedMathSphereH

//===========================================================================
// Filename:	Sphere.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 3 dimensional Sphere
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Point.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	class Sphere
	{
	//Operators
	public:

		inline Sphere(const scalar& p_X
			 , const scalar& p_Y
			 , const scalar& p_Z
			 , const scalar& p_Radius);

		inline Sphere(const Point& p_Centre, const scalar& p_Radius);

	//Attributes
	public:
	
		Point Centre;
		scalar Radius;
	};
} // namespace Mathematics

#include "Sphere.inl"

#endif //#ifndef IncludedMathSphereH