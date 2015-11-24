#include "Precompiled.h"
#include "Matrix.h"

using namespace Mathematics;

//===========================================================================
// Constant Definitions
//===========================================================================

namespace ConstantMatrices
{
	const Matrix Zero(ConstantScalars::Zero);
	const Matrix Identity(ConstantVectors::I, ConstantVectors::J, ConstantVectors::K);
};

//===========================================================================
// Function Definitions
//===========================================================================

Matrix::Matrix(const scalar p_Value)
	: m_Array(p_Value)
{}

//---------------------------------------------------------------------------

Matrix::Matrix(
	const scalar p_r1c1, const scalar p_r1c2, const scalar p_r1c3
	, const scalar p_r2c1, const scalar p_r2c2, const scalar p_r2c3
	, const scalar p_r3c1, const scalar p_r3c2, const scalar p_r3c3)
	: m_Array(ConstantScalars::Zero)
{
	//first column
	m_Array(0, 0) = p_r1c1;
	m_Array(1, 0) = p_r2c1;
	m_Array(2, 0) = p_r3c1;

	//second column
	m_Array(0, 1) = p_r1c2;
	m_Array(1, 1) = p_r2c2;
	m_Array(2, 1) = p_r3c2;

	//third column
	m_Array(0, 2) = p_r1c3;
	m_Array(1, 2) = p_r2c3;
	m_Array(2, 2) = p_r3c3;

	//homogeniety
	m_Array(3, 3) = ConstantScalars::Unity;
}

//---------------------------------------------------------------------------

Matrix::Matrix(const Vector p_Column1, const Vector p_Column2, const Vector p_Column3)
	: m_Array(ConstantScalars::Zero)
{
	//first column
	m_Array(0, 0) = p_Column1.x;
	m_Array(1, 0) = p_Column1.y;
	m_Array(2, 0) = p_Column1.z;

	//second column
	m_Array(0, 1) = p_Column2.x;
	m_Array(1, 1) = p_Column2.y;
	m_Array(2, 1) = p_Column2.z;

	//third column
	m_Array(0, 2) = p_Column3.x;
	m_Array(1, 2) = p_Column3.y;
	m_Array(2, 2) = p_Column3.z;

	//homogeniety
	m_Array(3, 3) = ConstantScalars::Unity;
}

//---------------------------------------------------------------------------
Matrix::Matrix(
		 const scalar p_r1c1, const scalar p_r1c2, const scalar p_r1c3, const scalar p_r1c4
	   , const scalar p_r2c1, const scalar p_r2c2, const scalar p_r2c3, const scalar p_r2c4
	   , const scalar p_r3c1, const scalar p_r3c2, const scalar p_r3c3, const scalar p_r3c4
	   , const scalar p_r4c1, const scalar p_r4c2, const scalar p_r4c3, const scalar p_r4c4)
	   : m_Array(ConstantScalars::Zero)
{
	//first column
	m_Array(0, 0) = p_r1c1;
	m_Array(1, 0) = p_r2c1;
	m_Array(2, 0) = p_r3c1;
	m_Array(3, 0) = p_r4c1;
	
	//second column
	m_Array(0, 1) = p_r1c2;
	m_Array(1, 1) = p_r2c2;
	m_Array(2, 1) = p_r3c2;
	m_Array(3, 1) = p_r4c2;

	//third column
	m_Array(0, 2) = p_r1c3;
	m_Array(1, 2) = p_r2c3;
	m_Array(2, 2) = p_r3c3;
	m_Array(3, 2) = p_r4c3;

	//fourth column
	m_Array(0, 3) = p_r1c4;
	m_Array(1, 3) = p_r2c4;
	m_Array(2, 3) = p_r3c4;
	m_Array(3, 3) = p_r4c4;
}

//---------------------------------------------------------------------------

const Vector Matrix::operator *(const Vector& p_Rhs) const
{
	return Vector(Column(1) * p_Rhs.x + Column(2) * p_Rhs.y + Column(3) * p_Rhs.z);
}

//---------------------------------------------------------------------------

const Matrix Matrix::operator *(const Matrix& p_Rhs) const
{
	Matrix temp(0.0f);

	for (u8 i = 1; i <= 4; ++i)
	{
		for (u8 j = 1; j <= 4; ++j)
		{
			scalar sum(0.0f);

			for (u8 k = 1; k <= 4; ++k)
			{
				sum += ((*this)(i, k) * p_Rhs(k, j));
			}

			temp(i, j) = sum;
		}
	}

	return temp;
}

//---------------------------------------------------------------------------

inline const Vector Matrix::Row(const u32 p_Row) const
{
	const Matrix& M(*this);
	return Vector(M(p_Row, 1), M(p_Row, 2), M(p_Row, 3));
}

//---------------------------------------------------------------------------

inline const Vector Matrix::Column(const u32 p_Column) const
{
	const Matrix& M(*this);
	return Vector(M(1, p_Column), M(2, p_Column), M(3, p_Column));
}

//---------------------------------------------------------------------------

const scalar Matrix::Determinant() const
{
	const Matrix& M(*this);
	const scalar A = M(3, 3) * M(4, 4) - M(3, 4) * M(4, 3);
	const scalar B = M(3, 4) * M(4, 2) - M(3, 2) * M(4, 4);
	const scalar C = M(3, 2) * M(4, 3) - M(3, 3) * M(4, 2);
	const scalar D = M(3, 1) * M(4, 4) - M(3, 4) * M(4, 1);
	const scalar E = M(3, 3) * M(4, 1) - M(3, 1) * M(4, 3);
	const scalar F = M(3, 1) * M(4, 2) - M(3, 2) * M(4, 1);

	return M(1, 1) * (M(2, 2) * A + M(2, 3) * B + M(2, 4) * C)
		+ M(1, 2) * (M(2, 1) * (-A) + M(2, 3) * D + M(2, 4) * E)
		+ M(1, 3) * (M(2, 1) * (-B) + M(2, 2) * (-D) + M(2, 4) * F)
		+ M(1, 4) * (M(2, 1) * (-C) + M(2, 2) * (-E) + M(2, 3) * (-F));
}

//---------------------------------------------------------------------------

const scalar Matrix::Trace() const
{
	return (*this)(1, 1) + (*this)(2, 2) + (*this)(3, 3) + (*this)(4, 4);
}

//---------------------------------------------------------------------------

const Matrix Matrix::Inverse() const
{
	const scalar D = this->Determinant();
	const Matrix& M(*this);
	const scalar T = M.Trace();
	const Matrix M2 = M * M;
	const scalar T2 = M2.Trace();
	const Matrix M3 = M * M2;

	Assert(!::EquivalentToZero(D), "Matrix is singular, cannot invert!");

	return (ConstantMatrices::Identity * ((T*T*T - 3 * T*T2 + 2 * M3.Trace()) / 6)
			  - (M * ((T*T - T2) / 2))
			  + (M2 * T) 
			  - M3) / D;
}

//---------------------------------------------------------------------------

const Matrix Matrix::Transpose() const
{
	const Matrix& M(*this);
	return Matrix(M(1, 1), M(2, 1), M(3, 1), M(4, 1)
				, M(1, 2), M(2, 2), M(3, 2), M(4, 2)
				, M(1, 3), M(2, 3), M(3, 3), M(4, 3)
				, M(1, 4), M(2, 4), M(3, 4), M(4, 4));
}