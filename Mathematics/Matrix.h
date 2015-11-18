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
#include "../Abstracts/Array.h"
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
		
		Abstracts::Array<scalar, 4, 4> m_Array;

	//Operators
	public:
		
		inline Matrix(const scalar p_Value = ConstantScalars::Zero);

		Matrix(const Vector p_FirstAxis
			 , const Vector p_SecondAxis
			 , const Vector p_ThirdAxis
			 , const Point p_Origin);

		Matrix(const scalar p_r1c1, const scalar p_r1c2, const scalar p_r1c3, const scalar p_r1c4
			 , const scalar p_r2c1, const scalar p_r2c2, const scalar p_r2c3, const scalar p_r2c4
			 , const scalar p_r3c1, const scalar p_r3c2, const scalar p_r3c3, const scalar p_r3c4
			 , const scalar p_r4c1, const scalar p_r4c2, const scalar p_r4c3, const scalar p_r4c4);

		//equality
		const bool operator ==(const Matrix& p_Rhs) const;
		inline const bool operator !=(const Matrix& p_Rhs) const;

		//arithmetic
		Matrix& Negate();
		inline const Matrix operator -() const;
		Matrix& operator +=(const Matrix& p_Rhs);
		inline const Matrix operator +(const Matrix& p_Rhs) const;
		Matrix& operator -=(const Matrix& p_Rhs);
		inline const Matrix operator -(const Matrix& p_Rhs) const;

		//scalar multiplication
		Matrix& operator *=(const scalar& p_Rhs);
		inline const Matrix operator *(const scalar p_Rhs) const;
		Matrix& operator /=(const scalar& p_Rhs);
		inline const Matrix operator /(const scalar p_Rhs) const;

		//product
		Matrix& operator *=(const Matrix& p_Rhs);
		inline const Matrix operator *(const Matrix& p_Rhs) const;

		//access
		inline scalar& operator ()(const u32 p_Row, const u32 p_Column);
		inline const scalar operator ()(const u32 p_Row, const u32 p_Column) const;

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
		const static Matrix Identity = Matrix(ConstantVectors::I
											, ConstantVectors::J
											, ConstantVectors::K
											, ConstantPoints::Origin);
	};

} // namespace Mathematics

#include "Matrix.inl"

#endif //#ifndef IncludedMathMatrixH