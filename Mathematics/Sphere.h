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
		//Attributes
		public:
	
			Point Centre;
			scalar Radius;
	};
} // namespace Mathematics

#endif //#ifndef IncludedMathSphereH