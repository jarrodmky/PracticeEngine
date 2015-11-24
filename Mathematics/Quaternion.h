#ifndef IncludedMathQuaternionH
#define IncludedMathQuaternionH

//===========================================================================
// Filename:	Quaternion.h
// Author:		Jarrod MacKay
// Description:	Defines quaternions
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
	class Quaternion
	{
	//Attributes
	private:

		scalar m_Real;
		Vector m_Imaginary;

	//Operators
	public:
		
		inline Quaternion(const scalar p_Value = ConstantScalars::Zero);
		inline Quaternion(const Vector& p_Axis, const scalar p_Angle = ConstantScalars::Zero);

		//equality
		inline const bool operator ==(const Quaternion& p_Rhs) const;
		inline const bool operator !=(const Quaternion& p_Rhs) const;

		//arithmetic
		inline Quaternion& Negate();
		inline const Quaternion operator -() const;
		inline Quaternion& operator +=(const Quaternion& p_Rhs);
		inline const Quaternion operator +(const Quaternion& p_Rhs) const;
		inline Quaternion& operator -=(const Quaternion& p_Rhs);
		inline const Quaternion operator -(const Quaternion& p_Rhs) const;
		inline Quaternion& operator *=(const Quaternion& p_Rhs);
		inline const Quaternion operator *(const Quaternion& p_Rhs) const;
		inline Quaternion& operator /=(const Quaternion& p_Rhs);
		inline const Quaternion operator /(const Quaternion& p_Rhs) const;

		//scalar multiplication
		inline const Quaternion operator *(const scalar p_Rhs) const;
		inline Quaternion& operator *=(const scalar& p_Rhs);
		inline Quaternion& operator /=(const scalar& p_Rhs);
		inline const Quaternion operator /(const scalar p_Rhs) const;

	private:

		inline Quaternion(const scalar p_Real, const Vector& p_Imaginary);

	//Methods
	public:

		//rotational eqaulity
		inline const bool RotationallyEqualTo(const Quaternion& p_Rhs) const;

		//relatives
		inline Quaternion& Reciprocate();
		inline const Quaternion Reciprocal() const;
		inline Quaternion& Conjugate();
		inline const Quaternion Conjugate() const;

		//magnitude
		inline const scalar LengthSquared() const;
		inline const scalar Length() const;
		inline const scalar InverseLength() const;

		//direction
		inline Quaternion& Normalize();
		inline const Quaternion Versor() const;

		//decomposition
		inline const scalar ScalarPart();
		inline const Vector VectorPart() const;

		//boolean
		inline bool IsAtOrigin() const;
		inline bool IsAtInfinity() const;
		inline bool IsValid() const;
		inline bool IsScalar() const;
		inline bool IsVector() const;
		inline bool IsUnit() const;

		//vector functions
		inline void RotateVector(Vector& p_Vector) const;
	};

	namespace ConstantQuaternions
	{
		const Quaternion Zero(ConstantVectors::Zero, ConstantScalars::Zero);
		const Quaternion Unity(ConstantVectors::Zero, ConstantScalars::Unity);
	}

} // namespace Mathematics

#include "Quaternion.inl"

#endif //#ifndef IncludedMathQuaternionH