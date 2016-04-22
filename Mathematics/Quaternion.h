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

		inline Quaternion(const scalar p_Real, const Vector3& p_Imaginary);
		inline Quaternion();
		inline explicit Quaternion(const scalar p_Value);
		inline explicit Quaternion(const Vector3& p_Axis, const scalar p_Angle = Zero);
		inline Quaternion(const Vector3& p_Start, const Vector3& p_Final);
		inline Quaternion(const scalar p_Real, const scalar p_Imag0, const scalar p_Imag1, const scalar p_Imag2);

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

		//inner (dot) product
		inline const scalar operator |(const Quaternion& p_Rhs) const;

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
		inline const Quaternion Conjugation() const;

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
		inline const scalar Real() const;
		inline const Vector3 Imaginary() const;

		//boolean
		inline bool IsAtOrigin() const;
		inline bool IsAtInfinity() const;
		inline bool IsValid() const;
		inline bool IsScalar() const;
		inline bool IsVector() const;
		inline bool IsUnit() const;

		//vector rotation
		inline void Rotate(Vector3& p_Vector) const;
		inline Vector3 Rotate(const Vector3& p_Vector) const;
	};

	//==========
	// Operators
	//==========

	inline const Quaternion operator *(const scalar p_Lhs, const Quaternion& p_Rhs);

	//==========
	// Functions
	//==========

	inline const bool ApproximatelyEqual(const Quaternion& p_Lhs, const Quaternion& p_Rhs, const scalar p_Tolerance);
	inline const Quaternion MakeRandomVersor();

	//==========
	// Constants
	//==========

	inline const Quaternion ZeroRotor();
	inline const Quaternion IdentityRotor();

} // namespace Mathematics

#include "Quaternion.inl"

#endif //#ifndef IncludedMathQuaternionH