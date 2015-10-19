#ifndef IncludedMathMatrixH
#define IncludedMathMatrixH

//===========================================================================
// Filename:	Matrix.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 4 by 4 Matrix
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "MathBase.h"
#include "Array.h"
#include "Vector.h"
#include "Point.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	class Matrix
	{
	//Attributes
	private:

		Array<scalar, 4, 4> m_Array;

	//Operators
	public:
		
		inline Matrix(const scalar p_Value = ConstantScalars::Zero);

		inline Matrix(const Vector p_FirstAxis
					, const Vector p_SecondAxis
					, const Vector p_ThirdAxis
					, const Point p_Origin);

		Matrix(const scalar p_11, const scalar p_12, const scalar p_13, const scalar p_14
			 , const scalar p_21, const scalar p_22, const scalar p_23, const scalar p_24
			 , const scalar p_31, const scalar p_32, const scalar p_33, const scalar p_34
			 , const scalar p_41, const scalar p_42, const scalar p_43, const scalar p_44);

		//equality
		const bool operator ==(const Matrix& p_Lhs) const;
		inline const bool operator !=(const Matrix& p_Lhs) const;

		//arithmetic
		Matrix& Negate();
		inline const Matrix operator -() const;
		Matrix& operator +=(const Matrix& p_Lhs);
		inline const Matrix operator +(const Matrix& p_Lhs) const;
		Matrix& operator -=(const Matrix& p_Lhs);
		inline const Matrix operator -(const Matrix& p_Lhs) const;

		//scalar multiplication
		Matrix& operator *=(const scalar& p_Lhs);
		inline const Matrix operator *(const scalar p_Lhs) const;
		Matrix& operator /=(const scalar& p_Lhs);
		inline const Matrix operator /(const scalar p_Lhs) const;

		//product
		Matrix& operator *=(const Matrix& p_Lhs);
		inline const Matrix operator *(const Matrix& p_Lhs) const;


	//Methods
	public:
		
		//metrics
		inline const scalar Determinant() const;
		inline const scalar Trace() const;

		//inverse
		Matrix& Invert();
		const Matrix Inverse() const;
	};

	namespace ConstantMatrices
	{
		const static Matrix Null = Matrix();
		const static Matrix Identity = Matrix(ConstantVectors::UnitX
											, ConstantVectors::UnitY
											, ConstantVectors::UnitZ
											, ConstantPoints::Origin);
	};

	#include "Matrix.inl"

} // namespace Mathematics

#endif //#ifndef IncludedMathMatrixH