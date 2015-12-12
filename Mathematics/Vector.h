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

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	template <u32 t_Rows>
	class Vector
	{
	//Attributes
	public:

		Abstracts::Array<scalar, t_Rows> m_Column;

	//Operators
	public:
		
		inline Vector(const scalar p_Scalar = Zero);
		
		//equality
		inline const bool operator ==(const Vector& p_Rhs) const;
		inline const bool operator !=(const Vector& p_Rhs) const;

		//arithmetic
		inline Vector<t_Rows>& Negate();
		inline const  Vector<t_Rows> operator -() const;
		inline  Vector<t_Rows>& operator +=(const  Vector<t_Rows>& p_Rhs);
		inline const  Vector<t_Rows> operator +(const  Vector<t_Rows>& p_Rhs) const;
		inline  Vector<t_Rows>& operator -=(const  Vector<t_Rows>& p_Rhs);
		inline const  Vector<t_Rows> operator -(const  Vector<t_Rows>& p_Rhs) const;

		//scalar multiplication
		inline  Vector<t_Rows>& operator *=(const scalar& p_Rhs);
		inline const  Vector<t_Rows> operator *(const scalar p_Rhs) const;
		inline  Vector<t_Rows>& operator /=(const scalar& p_Rhs);
		inline const  Vector<t_Rows> operator /(const scalar p_Rhs) const;

		//inner (dot) product
		inline const scalar operator |(const  Vector<t_Rows>& p_Rhs) const;

		//access
		inline scalar& operator ()(const u32 p_Row);
		inline const scalar operator ()(const u32 p_Row) const;


	//Methods
	public:
		
		//magnitude
		inline const scalar LengthSquared() const;
		inline const scalar Length() const;
		inline const scalar InverseLength() const;

		inline const scalar ManhattanLength() const;

		//direction
		inline  Vector<t_Rows>& Normalize();
		inline const  Vector<t_Rows> Direction() const;

		//scalar projection
		const scalar LengthAlong(const  Vector<t_Rows>& p_Rhs) const;

		// vector projection
		 Vector<t_Rows>& ProjectAlong(const  Vector<t_Rows>& p_Rhs);
		const  Vector<t_Rows> ProjectedAlong(const  Vector<t_Rows>& p_Rhs) const;

		//boolean
		inline bool IsNull() const;
		inline bool IsAtInfinity() const;
		inline bool IsValid() const;
		inline bool IsUnit() const;
	};

	//==========
	// Definitions
	//==========

	typedef Vector<2> Vector2;
	typedef Vector<3> Vector3;
	typedef Vector<4> Vector4;

	//==========
	// Operators
	//==========

	//vector scaling
	template <u32 t_Rows>
	inline const Vector<t_Rows> operator *(const scalar p_Lhs, const Vector<t_Rows>& p_Rhs);

	//cross product
	inline Vector3& operator *=(Vector3& p_Lhs, const Vector3& p_Rhs);
	inline const Vector3 operator *(const Vector3& p_Lhs, const Vector3& p_Rhs);
	inline Vector4& operator *=(Vector4& p_Lhs, const Vector4& p_Rhs);
	inline const Vector4 operator *(const Vector4& p_Lhs, const Vector4& p_Rhs);

	//==========
	// Constants
	//==========

	inline const Vector2 Zero2();
	inline const Vector2 Ones2();
	inline const Vector2 U();
	inline const Vector2 V();

	inline const Vector3 Zero3();
	inline const Vector3 Ones3();
	inline const Vector3 I();
	inline const Vector3 J();
	inline const Vector3 K();

	inline const Vector4 Zero4();
	inline const Vector4 Ones4();
	inline const Vector4 W();
	inline const Vector4 X();
	inline const Vector4 Y();
	inline const Vector4 Z();
} // namespace Mathematics

#include "Vector.inl"

#endif //#ifndef IncludedMathVectorH