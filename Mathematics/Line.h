#ifndef IncludedMathLineH
#define IncludedMathLineH

//===========================================================================
// Filename:	Line.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 3 dimensional Line
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
	class Ray;

	class Line
	{
		//Operators
		Line(const Point& p_Centre, const Vector& p_Direction);

		Line(const Point& p_Centre, const Point& p_Offset);

		Line(const Ray& p_Ray);

		//Attributes
		public:
	
			Point Centre;
			Vector Direction;
	};
} // namespace Mathematics

#endif //#ifndef IncludedMathLineH