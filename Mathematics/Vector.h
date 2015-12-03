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
		inline Vector(const scalar p_X, const scalar p_Y, const scalar p_Z = ConstantScalars::Zero);

		//equality
		inline const bool operator ==(const Vector& p_Rhs) const;
		inline const bool operator !=(const Vector& p_Rhs) const;

		//arithmetic
		inline Vector& Negate();
		inline const Vector operator -() const;
		inline Vector& operator +=(const Vector& p_Rhs);
		inline const Vector operator +(const Vector& p_Rhs) const;
		inline Vector& operator -=(const Vector& p_Rhs);
		inline const Vector operator -(const Vector& p_Rhs) const;

		//scalar multiplication
		inline Vector& operator *=(const scalar& p_Rhs);
		inline const Vector operator *(const scalar p_Rhs) const;
		inline Vector& operator /=(const scalar& p_Rhs);
		inline const Vector operator /(const scalar p_Rhs) const;

		//inner (dot) product
		inline const scalar operator |(const Vector& p_Rhs) const;

		//cross product
		inline Vector& operator *=(const Vector& p_Rhs);
		inline const Vector operator *(const Vector& p_Rhs) const;


	//Methods
	public:
		
		//magnitude
		inline const scalar LengthSquared() const;
		inline const scalar Length() const;
		inline const scalar InverseLength() const;

		inline const scalar ManhattanLength() const;

		//direction
		inline Vector& Normalize();
		inline const Vector Direction() const;

		//scalar projection
		const scalar LengthAlong(const Vector& p_Rhs) const;

		//vector projection
		Vector& ProjectAlong(const Vector& p_Rhs);
		const Vector ProjectedAlong(const Vector& p_Rhs) const;

		//boolean
		inline bool IsNull() const;
		inline bool IsAtInfinity() const;
		inline bool IsValid() const;
		inline bool IsUnit() const;
	};

	namespace ConstantVectors
	{
		const Vector Zero(ConstantScalars::Zero);
		const Vector I(ConstantScalars::Unity, ConstantScalars::Zero, ConstantScalars::Zero);
		const Vector J(ConstantScalars::Zero, ConstantScalars::Unity, ConstantScalars::Zero);
		const Vector K(ConstantScalars::Zero, ConstantScalars::Zero, ConstantScalars::Unity);
	};

} // namespace Mathematics

#include "Vector.inl"

#endif //#ifndef IncludedMathVectorH