#ifndef IncludedMathVectorH
#define IncludedMathVectorH

//===========================================================================
// Filename:	Vector.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents an N-dimensional vector
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "../Abstracts/Array.h"
#include "MathBase.h"
#include "Random.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	template <typename t_Scalar, u32 t_Rows>
	class Vector
	{
		//Attributes
	public:

		typedef t_Scalar ComponentType;

		Abstracts::Array<t_Scalar, t_Rows> m_Column;

		//Operators
	public:

		inline explicit Vector(const t_Scalar p_Scalar = 0);

		//equality
		inline const bool operator ==(const Vector<t_Scalar, t_Rows>& p_Rhs) const;
		inline const bool operator !=(const Vector<t_Scalar, t_Rows>& p_Rhs) const;

		//arithmetic
		inline Vector<t_Scalar, t_Rows>& Negate();
		inline const  Vector<t_Scalar, t_Rows> operator -() const;
		inline  Vector<t_Scalar, t_Rows>& operator +=(const  Vector<t_Scalar, t_Rows>& p_Rhs);
		inline const  Vector<t_Scalar, t_Rows> operator +(const  Vector<t_Scalar, t_Rows>& p_Rhs) const;
		inline  Vector<t_Scalar, t_Rows>& operator -=(const  Vector<t_Scalar, t_Rows>& p_Rhs);
		inline const  Vector<t_Scalar, t_Rows> operator -(const  Vector<t_Scalar, t_Rows>& p_Rhs) const;

		//componentwise product
		inline  Vector<t_Scalar, t_Rows>& operator %=(const  Vector<t_Scalar, t_Rows>& p_Rhs);
		inline const  Vector<t_Scalar, t_Rows> operator %(const  Vector<t_Scalar, t_Rows>& p_Rhs) const;

		//scalar multiplication
		inline  Vector<t_Scalar, t_Rows>& operator *=(const t_Scalar& p_Rhs);
		inline const  Vector<t_Scalar, t_Rows> operator *(const t_Scalar p_Rhs) const;
		inline  Vector<t_Scalar, t_Rows>& operator /=(const t_Scalar& p_Rhs);
		inline const  Vector<t_Scalar, t_Rows> operator /(const t_Scalar p_Rhs) const;

		//access
		inline t_Scalar& operator ()(const u32 p_Row);
		inline const t_Scalar operator ()(const u32 p_Row) const;

		//Methods
	public:

		//magnitude
		inline const t_Scalar LengthSquared() const;
		inline const t_Scalar Length() const;
		inline const t_Scalar InverseLength() const;

		inline const t_Scalar ManhattanLength() const;
		inline const t_Scalar AffineComponent() const;

		//direction
		inline Vector<t_Scalar, t_Rows>& Normalize();
		inline const Vector<t_Scalar, t_Rows> Direction() const;

		//scalar projection
		const t_Scalar LengthAlong(const Vector<t_Scalar, t_Rows>& p_Direction) const;

		// vector projections
		Vector<t_Scalar, t_Rows>& ProjectAlong(const Vector<t_Scalar, t_Rows>& p_Direction);
		const  Vector<t_Scalar, t_Rows> ProjectionAlong(const Vector<t_Scalar, t_Rows>& p_Direction) const;

		// vector rejections
		Vector<t_Scalar, t_Rows>& RejectFrom(const Vector<t_Scalar, t_Rows>& p_Rhs);
		const Vector<t_Scalar, t_Rows> RejectionFrom(const Vector<t_Scalar, t_Rows>& p_Direction) const;

		//boolean
		inline const bool IsAffineVector() const;
		inline const bool IsAtOrigin() const;
		inline const bool IsAtInfinity() const;
		inline const bool IsValid() const;
		inline const bool IsUnit() const;
	};

	template <u32 t_Rows>
	using IntVector = Vector<s32, t_Rows>;

	template <u32 t_Rows>
	using UintVector = Vector<u32, t_Rows>;

	template <u32 t_Rows>
	using RealVector = Vector<scalar, t_Rows>;

	template <u32 t_Rows>
	using ComplexVector = Vector<complex, t_Rows>;

	//==========
	// Operators
	//==========

	//dot product
	template <typename t_Scalar, u32 t_Rows>
	inline const t_Scalar operator |(const Vector<t_Scalar, t_Rows>& p_Lhs, const Vector<t_Scalar, t_Rows>& p_Rhs);

	//scalar product
	template <typename t_Scalar, u32 t_Rows>
	inline const Vector<t_Scalar, t_Rows> operator *(const t_Scalar p_Lhs, const Vector<t_Scalar, t_Rows>& p_Rhs);

	//==========
	// Functions
	//==========

	template <typename t_Scalar, u32 t_Rows>
	inline const Vector<t_Scalar, t_Rows> Zeroes();

	template <typename t_Scalar, u32 t_Rows>
	inline const Vector<t_Scalar, t_Rows> Ones();

	//casting
	template <u32 t_Rows>
	inline const RealVector<t_Rows + 1> MakeAffineVector(const RealVector<t_Rows>& p_Vector);

	template <u32 t_Rows>
	inline const RealVector<t_Rows + 1> MakeAffinePoint(const RealVector<t_Rows>& p_Vector);

	template <u32 t_Rows>
	inline const RealVector<t_Rows - 1> MakeProjectedVector(const RealVector<t_Rows>& p_Vector);

	template <u32 t_Rows>
	inline const RealVector<t_Rows - 1> MakeProjectedPoint(const RealVector<t_Rows>& p_Vector);

	//geometry
	template <u32 t_Rows>
	inline const scalar AngleBetween(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs);

	template <u32 t_Rows>
	inline const bool Perpendicular(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs);

	template <u32 t_Rows>
	inline const bool Acute(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs);

	template <u32 t_Rows>
	inline const bool Obtuse(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs);

	//approximation
	template <u32 t_Rows>
	inline const bool Close(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs, const scalar p_Tolerance);

	template <u32 t_Rows>
	inline const bool ApproximatelyEqual(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs, const scalar p_Tolerance);

	//==========
	// Definitions
	//==========
	
	//stop compilation of 0 or zero length vectors
	template <typename t_Scalar>
	class Vector<t_Scalar, 0>;
	template <typename t_Scalar>
	class Vector<t_Scalar, 1>;

	typedef RealVector<2> Vector2;
	typedef RealVector<3> Vector3;
	typedef RealVector<4> Vector4;

	typedef IntVector<2> IntVector2;
	typedef IntVector<3> IntVector3;
	typedef IntVector<4> IntVector4;

	typedef UintVector<2> UintVector2;
	typedef UintVector<3> UintVector3;
	typedef UintVector<4> UintVector4;

} // namespace Mathematics

#include "Vector.inl"
#include "Vector2.inl"
#include "Vector3.inl"
#include "Vector4.inl"

#endif //#ifndef IncludedMathVectorH