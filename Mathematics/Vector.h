#ifndef IncludedMathVectorH
#define IncludedMathVectorH

//===========================================================================
// Filename:	Vector.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 3 dimensional vector
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
	class Matrix;

	class Vector
	{
	//Attributes
	public:

		scalar x;
		scalar y;
		scalar z;

	//Operators
	public:
		
		inline Vector(const scalar p_Scalar = ConstantScalars::Zero);
		inline Vector(const scalar p_X, const scalar p_Y, const scalar p_Z);

		//equality
		inline const bool operator ==(const Vector& p_Lhs) const;
		inline const bool operator !=(const Vector& p_Lhs) const;

		//arithmetic
		inline Vector& Negate();
		inline const Vector operator -() const;
		inline Vector& operator +=(const Vector& p_Lhs);
		inline const Vector operator +(const Vector& p_Lhs) const;
		inline Vector& operator -=(const Vector& p_Lhs);
		inline const Vector operator -(const Vector& p_Lhs) const;

		//scalar multiplication
		inline Vector& operator *=(const scalar& p_Lhs);
		inline const Vector operator *(const scalar p_Lhs) const;
		inline Vector& operator /=(const scalar& p_Lhs);
		inline const Vector operator /(const scalar p_Lhs) const;

		//inner (dot) product
		inline const scalar operator |(const Vector& p_Lhs) const;

		//outer product
		const Matrix operator ^(const Vector& p_Lhs) const;

		//cross product
		inline Vector& operator *=(const Vector& p_Lhs);
		inline const Vector operator *(const Vector& p_Lhs) const;


	//Methods
	public:
		
		//magnitude
		inline const scalar LengthSquared() const;
		inline const scalar Length() const;
		inline const scalar InverseLength() const;

		//direction
		inline Vector& Normalize();
		inline const Vector Direction() const;

		//scalar projection
		const scalar LengthAlong(const Vector& p_Lhs) const;
		const scalar AngleBetween(const Vector& p_Lhs) const;

		//vector projection
		Vector& ProjectAlong(const Vector& p_Lhs);
		const Vector ProjectedAlong(const Vector& p_Lhs) const;

		//boolean
		inline bool IsNull() const;
		inline bool IsAtInfinity() const;
		inline bool IsValid() const;
		inline bool IsUnit() const;
	};

	namespace ConstantVectors
	{
		const static Vector Null(ConstantScalars::Zero, ConstantScalars::Zero, ConstantScalars::Zero);
		const static Vector UnitX(ConstantScalars::Unity, ConstantScalars::Zero, ConstantScalars::Zero);
		const static Vector UnitY(ConstantScalars::Zero, ConstantScalars::Unity, ConstantScalars::Zero);
		const static Vector UnitZ(ConstantScalars::Zero, ConstantScalars::Zero, ConstantScalars::Unity);
	};

} // namespace Mathematics

#include "Vector.inl"

#endif //#ifndef IncludedMathVectorH