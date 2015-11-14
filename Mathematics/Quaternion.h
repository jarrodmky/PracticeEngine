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
#include "Array.h"
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
		inline const bool operator ==(const Quaternion& p_Lhs) const;
		inline const bool operator !=(const Quaternion& p_Lhs) const;

		//arithmetic
		inline Quaternion& Negate();
		inline const Quaternion operator -() const;
		inline Quaternion& operator +=(const Quaternion& p_Lhs);
		inline const Quaternion operator +(const Quaternion& p_Lhs) const;
		inline Quaternion& operator -=(const Quaternion& p_Lhs);
		inline const Quaternion operator -(const Quaternion& p_Lhs) const;
		inline Quaternion& operator *=(const Quaternion& p_Lhs);
		inline const Quaternion operator *(const Quaternion& p_Lhs) const;
		inline Quaternion& operator /=(const Quaternion& p_Lhs);
		inline const Quaternion operator /(const Quaternion& p_Lhs) const;

		//scalar multiplication
		inline Quaternion& operator *=(const scalar& p_Lhs);
		inline const Quaternion operator *(const scalar p_Lhs) const;
		inline Quaternion& operator /=(const scalar& p_Lhs);
		inline const Quaternion operator /(const scalar p_Lhs) const;

	//Methods
	public:

		//rotational eqaulity
		inline const bool RotationallyEqualTo(const Quaternion& p_Lhs) const;

		//relatives
		inline Quaternion& Reciprocate();
		inline const Quaternion Reciprocal() const;
		inline Quaternion& Conjugate();
		inline const Quaternion Conjugal() const;

		//magnitude
		inline const scalar LengthSquared() const;
		inline const scalar Length() const;
		inline const scalar InverseLength() const;

		//direction
		inline Quaternion& Normalize();
		inline const Quaternion Versor() const;

		//decomposition
		inline const scalar ScalarPart();
		inline const Vector& VectorPart() const;

		//boolean
		inline bool IsAtOrigin() const;
		inline bool IsAtInfinity() const;
		inline bool IsValid() const;
		inline bool IsScalar() const;
		inline bool IsVector() const;
		inline bool IsRight() const;
		inline bool IsUnit() const;
	};

	namespace ConstantQuaternions
	{
		const static Quaternion Identity(ConstantVectors::I, ConstantScalars::Zero); //??
	}

	#include "Quaternion.inl"

} // namespace Mathematics

#endif //#ifndef IncludedMathQuaternionH