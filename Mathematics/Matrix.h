#ifndef IncludedMathMatrixH
#define IncludedMathMatrixH

//===========================================================================
// Filename:	Matrix.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a M by N Matrix
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "MathBase.h"
#include "Vector.h"
#include "Random.h"

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
		
		Abstracts::Array<RealVector<t_Rows>, t_Columns> m_Page;

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
		
	//Methods
	public:

		//access
		const RealVector<t_Columns> TransposedRow(const u32 p_Row) const;
		const RealVector<t_Rows> Column(const u32 p_Column) const;

		//manipulation
		void SetColumn(const u32 p_Column, const RealVector<t_Rows>& p_NewValue);
		void SetRow(const u32 p_Row, const RealVector<t_Columns>& p_NewValue);

		//metrics
		const scalar Determinant() const;
		const RealVector<t_Rows> Diagonal() const;
		const scalar Trace() const;

		//cofactors
		const scalar Cofactor(const u32 p_Row, const u32 p_Column) const;
		const Matrix<t_Rows, t_Columns> Adjucation() const;

		//inverse
		const Matrix<t_Rows, t_Columns> Inverse() const;
		inline Matrix<t_Rows, t_Columns>& Invert();

		//Transpose
		const Matrix<t_Columns, t_Rows> Transposition() const;
		inline Matrix<t_Columns, t_Rows>& Transpose();

		//inverse transpose
		const Matrix<t_Columns, t_Rows> InverseTransposition() const;
		inline Matrix<t_Columns, t_Rows>& InverseTranspose();

		//Frobenius norm
		const scalar NormSquared() const;
		const scalar Norm() const;

		//Queries
		bool IsSquare() const;
		inline bool IsSingular() const;
		bool IsOrthogonal() const;
		inline bool IsSpecialOrthogonal() const;

		//elementary row ops
		Matrix<t_Rows, t_Columns>& SwitchRows(const u32 p_Row1, const u32 p_Row2);
		Matrix<t_Rows, t_Columns>& ScaleRow(const u32 p_Row, const scalar p_Scalar);
		Matrix<t_Rows, t_Columns>& AddScaledRowToRow(const u32 p_Row, const u32 p_ScaledRow, const scalar p_Scalar);

	private:

		//submatrix
		const Matrix<t_Rows - 1, t_Columns - 1> Submatrix(const u32 p_RemovedRow, const u32 p_RemovedColumn) const;
		const scalar Minor(const u32 p_RemovedRow, const u32 p_RemovedColumn) const;
	};

	//==========
	// Operators
	//==========
	
	template <u32 t_Rows, u32 t_Columns>
	inline const Matrix<t_Rows, t_Columns> operator *(const scalar p_Lhs, const Matrix<t_Rows, t_Columns>& p_Rhs);

	template <u32 t_Rows, u32 t_Columns>
	const RealVector<t_Rows> operator *(const Matrix<t_Rows, t_Columns>& p_Lhs, const RealVector<t_Columns>& p_Rhs);
	
	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& operator *=(const Matrix<t_Rows, t_Columns>& p_Lhs, const Matrix<t_Columns, t_Columns>& p_Rhs);

	//other templatized operators

	//outer product
	template <u32 t_Rank>
	inline const Matrix<t_Rank, t_Rank> operator ^(const RealVector<t_Rank>& p_Lhs, const RealVector<t_Rank>& p_Rhs);

	template <u32 t_Rank>
	inline const Matrix<t_Rank, t_Rank> In();

	template <u32 t_Rows, u32 t_Inner, u32 t_Columns>
	const Matrix<t_Rows, t_Columns> operator *(const Matrix<t_Rows, t_Inner>& p_Lhs, const Matrix<t_Inner, t_Columns>& p_Rhs);

	//==========
	// Functions
	//==========

	template <u32 t_Rows, u32 t_Columns>
	inline const bool Close(const Matrix<t_Rows, t_Columns>& p_Lhs
		, const Matrix<t_Rows, t_Columns>& p_Rhs
		, const scalar p_Tolerance);

	template <u32 t_Rows, u32 t_Columns>
	inline const bool ApproximatelyEqual(const Matrix<t_Rows, t_Columns>& p_Lhs
		, const Matrix<t_Rows, t_Columns>& p_Rhs
		, const scalar p_Tolerance);

	//==========
	// Definitions
	//==========

	typedef Matrix<2, 2> Matrix22;
	typedef Matrix<3, 3> Matrix33;
	typedef Matrix<4, 4> Matrix44;

} // namespace Mathematics

#include "Matrix.inl"
#include "Matrix22.inl"
#include "Matrix33.inl"
#include "Matrix44.inl"

#endif //#ifndef IncludedMathMatrixH