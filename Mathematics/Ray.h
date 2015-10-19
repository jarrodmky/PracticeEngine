#ifndef IncludedMathRayH
#define IncludedMathRayH

//===========================================================================
// Filename:	Ray.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 3 dimensional Ray
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
	class Ray
	{
		//Operators
		Ray(const Point& p_Centre, const Vector& p_Direction);

		//Attributes
		public:
	
			Point Centre;
			Vector Direction;
	};
} // namespace Mathematics

#endif //#ifndef IncludedMathRayH