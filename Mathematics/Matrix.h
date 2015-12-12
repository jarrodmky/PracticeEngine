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
	template <u32 t_Rows, u32 t_Columns>
	class Matrix
	{
	//Attributes
	private:
		
		Abstracts::Array<Vector<t_Rows>, t_Columns> m_Page;

	//Operators
	public:
		
		Matrix(const scalar p_Value = Zero);

		//equality
		inline const bool operator ==(const Matrix<t_Rows, t_Columns>& p_Rhs) const;
		inline const bool operator !=(const Matrix<t_Rows, t_Columns>& p_Rhs) const;

		//arithmetic
		inline Matrix<t_Rows, t_Columns>& Negate();
		inline const Matrix<t_Rows, t_Columns> operator -() const;
		inline Matrix<t_Rows, t_Columns>& operator +=(const Matrix<t_Rows, t_Columns>& p_Rhs);
		inline const Matrix<t_Rows, t_Columns> operator +(const Matrix<t_Rows, t_Columns>& p_Rhs) const;
		inline Matrix<t_Rows, t_Columns>& operator -=(const Matrix<t_Rows, t_Columns>& p_Rhs);
		inline const Matrix<t_Rows, t_Columns> operator -(const Matrix<t_Rows, t_Columns>& p_Rhs) const;

		//scalar multiplication
		inline Matrix<t_Rows, t_Columns>& operator *=(const scalar& p_Rhs);
		inline const Matrix<t_Rows, t_Columns> operator *(const scalar p_Rhs) const;
		inline Matrix<t_Rows, t_Columns>& operator /=(const scalar& p_Rhs);
		inline const Matrix<t_Rows, t_Columns> operator /(const scalar p_Rhs) const;

		//access
		inline scalar& operator ()(const u32 p_Row, const u32 p_Column);
		inline const scalar operator ()(const u32 p_Row, const u32 p_Column) const;
		const Vector<t_Columns> RowTransposed(const u32 p_Row) const;
		const Vector<t_Rows> Column(const u32 p_Column) const;

	//Methods
	public:
		
		//metrics
		const scalar Determinant() const;
		const Vector<t_Rows> Diagonal() const;
		const scalar Trace() const;

		//inverse
		const Matrix<t_Rows, t_Columns> Inverse() const;
		inline Matrix<t_Rows, t_Columns>& Invert();

		//Transpose
		const Matrix<t_Columns, t_Rows> Transposition() const;
		inline Matrix<t_Columns, t_Rows>& Transpose();

		//Frobenius norm
		const scalar Norm() const;

		//Queries
		bool IsSquare() const;
		bool IsOthogonal() const;
		inline bool IsSpecialOthogonal() const;
	};

	//==========
	// Definitions
	//==========

	typedef Matrix<2, 2> Matrix22;
	typedef Matrix<3, 3> Matrix33;
	typedef Matrix<4, 4> Matrix44;

	//==========
	// Operators
	//==========
	
	template <u32 t_Rows, u32 t_Columns>
	inline const Matrix<t_Rows, t_Columns> operator *(const scalar p_Lhs, const Matrix<t_Rows, t_Columns>& p_Rhs);

	template <u32 t_Rows, u32 t_Columns>
	const Vector<t_Rows> operator *(const Matrix<t_Rows, t_Columns>& p_Lhs, const Vector<t_Columns>& p_Rhs);

	template <u32 t_Rows, u32 t_Ins, u32 t_Columns>
	const Matrix<t_Rows, t_Columns> operator *(const Matrix<t_Rows, t_Ins>& p_Lhs, const Matrix<t_Ins, t_Columns>& p_Rhs);
	
	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& operator *=(const Matrix<t_Rows, t_Columns>& p_Lhs, const Matrix<t_Columns, t_Columns>& p_Rhs);

	inline const Matrix33 operator ^(const Vector3& p_Lhs, const Vector3& p_Rhs);

	//==========
	// Constants
	//==========

	inline const Matrix22 Zero22();
	inline const Matrix22 I2();

	inline const Matrix33 Zero33();
	inline const Matrix33 I3();

	inline const Matrix44 Zero44();
	inline const Matrix44 I4();

} // namespace Mathematics

#include "Matrix.inl"

#endif //#ifndef IncludedMathMatrixH