#ifndef IncludedMathPointH
#define IncludedMathPointH

//===========================================================================
// Filename:	Point.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 3 dimensional Point
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "MathBase.h"
#include "Vector.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	class Point
	{
	//Attributes
	public:

		scalar x;
		scalar y;
		scalar z;

	//Operators
	public:
		
		inline Point(const scalar p_Scalar = ConstantScalars::Zero);
		inline Point(const scalar p_X, const scalar p_Y, const scalar p_Z);
		inline explicit Point(const Vector& p_Position);
		
		//equality
		inline const bool operator ==(const Point& p_Lhs) const;
		inline const bool operator !=(const Point& p_Lhs) const;

		//arithmetic
		inline Point& operator +=(const Vector& p_Lhs);
		inline const Point operator +(const Vector& p_Lhs) const;
		inline const Vector operator -(const Point& p_Lhs) const;

	//Methods
	public:
		
		//magnitude
		inline const scalar DistanceSquaredTo(const Point& p_Lhs) const;
		inline const scalar DistanceTo(const Point& p_Lhs) const;

		//boolean
		inline bool IsOrigin() const;
		inline bool IsAtInfinity() const;
		inline bool IsValid() const;

	};

	namespace ConstantPoints
	{
		const static Point Origin(ConstantScalars::Zero, ConstantScalars::Zero, ConstantScalars::Zero);
		const static Point Infinity(ConstantScalars::Infinity, ConstantScalars::Infinity, ConstantScalars::Infinity);
	};

	typedef std::pair<Point, Point> PointPair;

} // namespace Mathematics

#include "Point.inl"

#endif //#ifndef IncludedMathPointH