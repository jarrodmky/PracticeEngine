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
		Vector3 m_Imaginary;

	//Operators
	public:

		inline Quaternion(const scalar p_Value = Zero);
		inline Quaternion(const Vector3& p_Axis, const scalar p_Angle = Zero);
		inline Quaternion(const scalar p_Real, const Vector3& p_Imaginary);

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

	//Methods
	public:

		//Access
		inline const scalar Angle() const;
		inline const Vector3 Axis() const;

		//rotational eqaulity
		inline const bool RotationallyEqualTo(const Quaternion& p_Rhs) const;

		//relatives
		inline Quaternion& Invert();
		inline const Quaternion Inverse() const;
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
		inline const scalar ScalarPart() const;
		inline const Vector3 VectorPart() const;

		//boolean
		inline bool IsAtOrigin() const;
		inline bool IsAtInfinity() const;
		inline bool IsValid() const;
		inline bool IsScalar() const;
		inline bool IsVector() const;
		inline bool IsUnit() const;

		//vector functions
		inline void RotateVector(Vector3& p_Vector) const;
	};

	//==========
	// Constants
	//==========

	inline const Quaternion Origin();
	inline const Quaternion Identity();

} // namespace Mathematics

#include "Quaternion.inl"

#endif //#ifndef IncludedMathQuaternionH