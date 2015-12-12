//===========================================================================
// Filename:	Matrix.inl
// Author:		Jarrod MacKay
//===========================================================================

namespace Mathematics
{

	//===========================================================================
	// Operators Definitions
	//===========================================================================

	template <u32 t_Rows, u32 t_Columns>
	inline const Matrix<t_Rows, t_Columns> operator *(const scalar p_Lhs, const Matrix<t_Rows, t_Columns>& p_Rhs)
	{
		return p_Rhs * p_Lhs;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const Vector<t_Rows> operator *(const Matrix<t_Rows, t_Columns>& p_Lhs, const Vector<t_Columns>& p_Rhs)
	{
		Vector<t_Rows> sum(0.0f);

		for (u32 i = 1; i <= t_Columns; ++i)
		{
			sum += (p_Lhs.Column(i) * p_Rhs(i));
		}

		return sum;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Ins, u32 t_Columns>
	const Matrix<t_Rows, t_Columns> operator *(const Matrix<t_Rows, t_Ins>& p_Lhs, const Matrix<t_Ins, t_Columns>& p_Rhs)
	{
		Matrix<t_Rows, t_Columns> M(Zero);

		for (u32 i = 1; i <= t_Rows; ++i)
		{
			for (u32 j = 1; j <= t_Columns; ++j)
			{
				M(i, j) = p_Lhs.RowTransposed(i) | p_Rhs.Column(j);
			}
		}

		return M;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& operator *=(const Matrix<t_Rows, t_Columns>& p_Lhs, const Matrix<t_Columns, t_Columns>& p_Rhs)
	{
		*this = *this * p_Rhs;
		return *this;
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 operator ^(const Vector3& p_Lhs, const Vector3& p_Rhs)
	{
		Matrix33 temp;

		temp(1, 1) = p_Lhs(1) * p_Rhs(1);
		temp(1, 2) = temp(2, 1) = p_Lhs(1) * p_Rhs(2);
		temp(1, 3) = temp(3, 1) = p_Lhs(1) * p_Rhs(3);
		temp(2, 2) = p_Lhs(2) * p_Rhs(2);
		temp(2, 3) = temp(3, 2) = p_Lhs(2) * p_Rhs(3);
		temp(3, 3) = p_Lhs(3) * p_Rhs(3);

		return temp;
	}

//===========================================================================
// Constant Definitions
//===========================================================================

	inline const Matrix22 Zero22()
	{
		return Matrix22(Zero);
	}

	inline const Matrix22 I2()
	{
		Matrix22 temp(Zero);
		temp(1, 1) = Unity;
		temp(2, 2) = Unity;
		return temp;
	}

	inline const Matrix33 Zero33()
	{
		return Matrix33(Zero);
	}

	inline const Matrix33 I3()
	{
		Matrix33 temp(Zero);
		temp(1, 1) = Unity;
		temp(2, 2) = Unity;
		temp(3, 3) = Unity;
		return temp;
	}

	inline const Matrix44 Zero44()
	{
		return Matrix44(Zero);
	}

	inline const Matrix44 I4()
	{
		Matrix44 temp(Zero);
		temp(1, 1) = Unity;
		temp(2, 2) = Unity;
		temp(3, 3) = Unity;
		temp(4, 4) = Unity;
		return temp;
	}

//===========================================================================
// Class Definitions
//===========================================================================

template <u32 t_Rows, u32 t_Columns>
Matrix<t_Rows, t_Columns>::Matrix(const scalar p_Value)
	: m_Page(Vector<t_Rows>(p_Value))
{}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const bool Matrix<t_Rows, t_Columns>::operator ==(const Matrix<t_Rows, t_Columns>& p_Rhs) const
{
	for (u32 i = 1; i <= t_Columns; ++i)
	{
		if (Column(i) != p_Rhs.Column(i))
		{
			return false;
		}
	}
	return true;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const bool Matrix<t_Rows, t_Columns>::operator !=(const Matrix<t_Rows, t_Columns>& p_Rhs) const
{
	return !(*this == p_Rhs);
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::Negate()
{
	m_Page.ApplyFunction([](const Vector<t_Rows>& p_Value)->const Vector<t_Rows>
	{
		return -p_Value;
	});

	return *this;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::operator -() const
{
	return Matrix<t_Rows, t_Columns>(*this).Negate();
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::operator +=(const Matrix<t_Rows, t_Columns>& p_Rhs)
{
	m_Page.ApplyFunction(p_Rhs.m_Page,
		[](const Vector<t_Rows>& p_L, const Vector<t_Rows>& p_R)->const Vector<t_Rows>
		{
			return p_L + p_R;
		});

	return *this;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::operator +(const Matrix<t_Rows, t_Columns>& p_Rhs) const
{
	return (Matrix<t_Rows, t_Columns>(*this) += p_Rhs);
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::operator -=(const Matrix<t_Rows, t_Columns>& p_Rhs)
{
	m_Page.ApplyFunction(p_Rhs.m_Page,
		[](const Vector<t_Rows>& p_L, const Vector<t_Rows>& p_R)->const Vector<t_Rows>
	{
		return p_L - p_R;
	});

	return *this;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::operator -(const Matrix<t_Rows, t_Columns>& p_Rhs) const
{
	return (Matrix<t_Rows, t_Columns>(*this) -= p_Rhs);
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::operator *=(const scalar& p_Rhs)
{
	m_Page.ApplyFunction([&](const Vector<t_Rows>& p_Value)->const Vector<t_Rows>
	{
		return p_Value * p_Rhs;
	});

	return *this;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::operator *(const scalar p_Rhs) const
{
	return (Matrix<t_Rows, t_Columns>(*this) *= p_Rhs);
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::operator /=(const scalar& p_Rhs)
{
	const scalar denom = Mathematics::Inverse(p_Rhs);

	m_Page.ApplyFunction([&](const Vector<t_Rows>& p_Value)->const Vector<t_Rows>
	{
		return p_Value * denom;
	});

	return *this;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::operator /(const scalar p_Rhs) const
{
	return (Matrix<t_Rows, t_Columns>(*this) /= p_Rhs);
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
scalar& Matrix<t_Rows, t_Columns>::operator ()(const u32 p_Row, const u32 p_Column)
{
	return m_Page(p_Column - 1)(p_Row);
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const scalar Matrix<t_Rows, t_Columns>::operator ()(const u32 p_Row, const u32 p_Column) const
{
	return Column(p_Column)(p_Row);
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
inline const Vector<t_Columns> Matrix<t_Rows, t_Columns>::RowTransposed(const u32 p_Row) const
{
	Assert(p_Row > 0 && p_Row <= t_Rows, "Invalid row!");
	const Matrix<t_Rows, t_Columns>& M(*this);
	Vector<t_Columns> temp;
	
	for (u32 i = 1; i <= t_Columns; ++i)
	{
		temp(i) = M(p_Row, i);
	}
	
	return temp;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
inline const Vector<t_Rows> Matrix<t_Rows, t_Columns>::Column(const u32 p_Column) const
{
	Assert(p_Column > 0 && p_Column <= t_Columns, "Invalid column!");
	return m_Page(p_Column - 1);
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const scalar Matrix<t_Rows, t_Columns>::Determinant() const
{
	Assert(IsSquare(), "No non-square determinant!");

	//Matrix44 specialize
	//const Matrix<t_Rows, t_Columns>& M(*this);
	//const scalar A = M(3, 3) * M(4, 4) - M(3, 4) * M(4, 3);
	//const scalar B = M(3, 4) * M(4, 2) - M(3, 2) * M(4, 4);
	//const scalar C = M(3, 2) * M(4, 3) - M(3, 3) * M(4, 2);
	//const scalar D = M(3, 1) * M(4, 4) - M(3, 4) * M(4, 1);
	//const scalar E = M(3, 3) * M(4, 1) - M(3, 1) * M(4, 3);
	//const scalar F = M(3, 1) * M(4, 2) - M(3, 2) * M(4, 1);

	//return M(1, 1) * (M(2, 2) * A + M(2, 3) * B + M(2, 4) * C)
	//	+ M(1, 2) * (M(2, 1) * (-A) + M(2, 3) * D + M(2, 4) * E)
	//	+ M(1, 3) * (M(2, 1) * (-B) + M(2, 2) * (-D) + M(2, 4) * F)
	//	+ M(1, 4) * (M(2, 1) * (-C) + M(2, 2) * (-E) + M(2, 3) * (-F));
	return 0;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const Vector<t_Rows> Matrix<t_Rows, t_Columns>::Diagonal() const
{
	Assert(IsSquare(), "No non-square diagonal!");

	Vector<t_Rows> temp(Zero);
	for (u32 i = 1; i <= t_Rows; ++i)
	{
		temp(i) = (*this)(i, i);
	}

	return temp;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const scalar Matrix<t_Rows, t_Columns>::Trace() const
{
	scalar sum(Zero);
	Vector<t_Rows> temp(Diagonal());
	for (u32 i = 1; i <= t_Rows; ++i)
	{
		sum += temp(i);
	}

	return sum;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::Inverse() const
{
	//Matrix44 specialized
	//const scalar D = this->Determinant();
	//Assert(!::EquivalentToZero(D), "Matrix is singular, cannot invert!");

	//const Matrix<t_Rows, t_Columns>& M(*this);
	//const scalar T = M.Trace();
	//const Matrix<t_Rows, t_Columns> M2 = M * M;
	//const scalar T2 = M2.Trace();
	//const Matrix<t_Rows, t_Columns> M3 = M * M2;

	//return (ConstantMatrices::Identity * ((T*T*T - 3 * T*T2 + 2 * M3.Trace()) / 6)
	//	- (M * ((T*T - T2) / 2))
	//	+ (M2 * T)
	//	- M3) / D;
	return Matrix<t_Rows, t_Columns>(Zero);
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::Invert()
{
	*this = this->Inverse();
	return *this;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const Matrix<t_Columns, t_Rows> Matrix<t_Rows, t_Columns>::Transposition() const
{
	//Matrix44 specialized
	//const Matrix<t_Rows, t_Columns>& M(*this);
	//return Matrix<t_Rows, t_Columns>(M(1, 1), M(2, 1), M(3, 1), M(4, 1)
	//	, M(1, 2), M(2, 2), M(3, 2), M(4, 2)
	//	, M(1, 3), M(2, 3), M(3, 3), M(4, 3)
	//	, M(1, 4), M(2, 4), M(3, 4), M(4, 4));

	Matrix<t_Columns, t_Rows> temp;
	for (u32 i = 1; i <= t_Rows; ++i)
	{
		for (u32 j = 1; j <= t_Columns; ++j)
		{
			temp(j, i) = (*this)(i, j);
		}
	}
	return temp;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
Matrix<t_Columns, t_Rows>& Matrix<t_Rows, t_Columns>::Transpose()
{
	Assert(IsSquare(), "Cannot transpose non-square matrix in place!");
	*this = this->Transposition();
	return *this;
}
//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
const scalar Matrix<t_Rows, t_Columns>::Norm() const
{
	const Matrix<t_Rows, t_Columns>& M(*this);
	return std::sqrt((M.Transposition() * M).Trace());
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
bool Matrix<t_Rows, t_Columns>::IsSquare() const
{
	return t_Rows == t_Columns;
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
bool Matrix<t_Rows, t_Columns>::IsOthogonal() const
{
	return IsSquare() && (*this).Inverse() == (*this).Transposition();
}

//---------------------------------------------------------------------------

template <u32 t_Rows, u32 t_Columns>
bool Matrix<t_Rows, t_Columns>::IsSpecialOthogonal() const
{
	return IsOthogonal() && (Determinant() == Unity);
}

} // namespace Mathematics
