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

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	class Plane
	{
		//Operators
		Plane(const Point& p_Point, const Vector& p_Normal);

		Plane(const Point& p_Centre, const Point& p_Offset);

		Plane(const Ray& p_Ray);

		//Attributes
		public:
	
			Vector Normal;
			scalar Constant;
	};
} // namespace Mathematics

#endif //#ifndef IncludedMathPlaneH