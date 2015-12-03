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

#include "../Abstracts/Array.h"
#include "MathBase.h"
#include "Vector.h"

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
		
		Matrix(const scalar p_Value = ConstantScalars::Zero);

		Matrix(const scalar p_r1c1, const scalar p_r1c2, const scalar p_r1c3
			, const scalar p_r2c1, const scalar p_r2c2, const scalar p_r2c3
			, const scalar p_r3c1, const scalar p_r3c2, const scalar p_r3c3);

		Matrix(const scalar p_r1c1, const scalar p_r1c2, const scalar p_r1c3, const scalar p_r1c4
			 , const scalar p_r2c1, const scalar p_r2c2, const scalar p_r2c3, const scalar p_r2c4
			 , const scalar p_r3c1, const scalar p_r3c2, const scalar p_r3c3, const scalar p_r3c4
			 , const scalar p_r4c1, const scalar p_r4c2, const scalar p_r4c3, const scalar p_r4c4);

		Matrix(const Vector p_Column1, const Vector p_Column2, const Vector p_Column3);

		//equality
		inline const bool operator ==(const Matrix& p_Rhs) const;
		inline const bool operator !=(const Matrix& p_Rhs) const;

		//arithmetic
		inline Matrix& Negate();
		inline const Matrix operator -() const;
		inline Matrix& operator +=(const Matrix& p_Rhs);
		inline const Matrix operator +(const Matrix& p_Rhs) const;
		inline Matrix& operator -=(const Matrix& p_Rhs);
		inline const Matrix operator -(const Matrix& p_Rhs) const;

		//scalar multiplication
		inline Matrix& operator *=(const scalar& p_Rhs);
		inline const Matrix operator *(const scalar p_Rhs) const;
		inline Matrix& operator /=(const scalar& p_Rhs);
		inline const Matrix operator /(const scalar p_Rhs) const;

		//vector multiplication
		const Vector operator *(const Vector& p_Rhs) const;

		//product
		const Matrix operator *(const Matrix& p_Rhs) const;
		inline Matrix& operator *=(const Matrix& p_Rhs);

		//access
		inline scalar& operator ()(const u32 p_Row, const u32 p_Column);
		inline const scalar operator ()(const u32 p_Row, const u32 p_Column) const;
		const Vector Row(const u32 p_Row) const;
		const Vector Column(const u32 p_Column) const;

	//Methods
	public:
		
		//metrics
		const scalar Determinant() const;
		const scalar Trace() const;
		const Vector Diagonal() const;

		//inverse
		const Matrix Inverse() const;
		inline Matrix& Invert();

		//Transpose
		const Matrix Transposition() const;
		inline Matrix& Transpose();

		//Frobenius norm
		const scalar Norm() const;

		//Queries
		bool IsOthogonal() const;
		inline bool IsSpecialOthogonal() const;
	};

	namespace ConstantMatrices
	{
		const Matrix Zero(ConstantScalars::Zero);
		const Matrix Identity(ConstantVectors::I, ConstantVectors::J, ConstantVectors::K);
	};

} // namespace Mathematics

#include "Matrix.inl"

#endif //#ifndef IncludedMathMatrixH