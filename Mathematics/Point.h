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

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	class Vector;

	class Point
	{
	//Attributes
	public:

		scalar x;
		scalar y;
		scalar z;

	//Operators
	public:
		
		inline Point();
		inline Point(const scalar p_Scalar);
		inline Point(const scalar p_X, const scalar p_Y, const scalar p_Z);

		//equality
		inline const bool operator ==(const Point& p_Lhs) const;
		inline const bool operator !=(const Point& p_Lhs) const;

		//arithmetic
		inline Point& Negate();
		inline const Point operator -() const;
		inline Point& operator +=(const Vector& p_Lhs);
		inline const Point operator +(const Vector& p_Lhs) const;
		inline const Vector operator -(const Point& p_Lhs) const;

		//scalar multiplication
		inline Point& operator *=(const scalar& p_Lhs);
		inline const Point operator *(const scalar p_Lhs) const;
		inline Point& operator /=(const scalar& p_Lhs);
		inline const Point operator /(const scalar p_Lhs) const;

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

	#include "Point.inl"

} // namespace Mathematics

#endif //#ifndef IncludedMathPointH