//===========================================================================
// Filename:	Matrix.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Class Definitions
//===========================================================================

namespace Mathematics
{

const bool Matrix::operator ==(const Matrix& p_Rhs) const
{
	return m_Array.Equals(p_Rhs.m_Array, EquivalentToEachOther);
}

//---------------------------------------------------------------------------

const bool Matrix::operator !=(const Matrix& p_Rhs) const
{
	return !(*this == p_Rhs);
}

//---------------------------------------------------------------------------

Matrix& Matrix::Negate()
{
	m_Array.ApplyFunction([](const scalar& p_Value)->const scalar
	{
		return -p_Value;
	});

	return *this;
}

//---------------------------------------------------------------------------

const Matrix Matrix::operator -() const
{
	return Matrix(*this).Negate();
}

//---------------------------------------------------------------------------

Matrix& Matrix::operator +=(const Matrix& p_Rhs)
{
	m_Array.ApplyFunction(p_Rhs.m_Array, 
		[](const scalar& p_L, const scalar& p_R)->const scalar
		{
			return p_L + p_R;
		});

	return *this;
}

//---------------------------------------------------------------------------

const Matrix Matrix::operator +(const Matrix& p_Rhs) const
{
	return (Matrix(*this) += p_Rhs);
}

//---------------------------------------------------------------------------

Matrix& Matrix::operator -=(const Matrix& p_Rhs)
{
	m_Array.ApplyFunction(p_Rhs.m_Array,
		[](const scalar& p_L, const scalar& p_R)->const scalar
	{
		return p_L - p_R;
	});

	return *this;
}

//---------------------------------------------------------------------------

const Matrix Matrix::operator -(const Matrix& p_Rhs) const
{
	return (Matrix(*this) -= p_Rhs);
}

//---------------------------------------------------------------------------

Matrix& Matrix::operator *=(const scalar& p_Rhs)
{
	m_Array.ApplyFunction([&](const scalar& p_Value)->const scalar
	{
		return p_Value * p_Rhs;
	});

	return *this;
}

//---------------------------------------------------------------------------

const Matrix Matrix::operator *(const scalar p_Rhs) const
{
	return (Matrix(*this) *= p_Rhs);
}

//---------------------------------------------------------------------------

Matrix& Matrix::operator /=(const scalar& p_Rhs)
{
	const scalar denom = Mathematics::Inverse(p_Rhs);

	m_Array.ApplyFunction([&](const scalar& p_Value)->const scalar
	{
		return p_Value * denom;
	});

	return *this;
}

//---------------------------------------------------------------------------

const Matrix Matrix::operator /(const scalar p_Rhs) const
{
	return (Matrix(*this) /= p_Rhs);
}

//---------------------------------------------------------------------------

Matrix& Matrix::operator *=(const Matrix& p_Rhs)
{
	*this = *this * p_Rhs;
	return *this;
}

//---------------------------------------------------------------------------

scalar& Matrix::operator ()(const u32 p_Row, const u32 p_Column)
{
	return m_Array(p_Row - 1, p_Column - 1);
}

//---------------------------------------------------------------------------

const scalar Matrix::operator ()(const u32 p_Row, const u32 p_Column) const
{
	return m_Array(p_Row - 1, p_Column - 1);
}

//---------------------------------------------------------------------------

Matrix& Matrix::Invert()
{
	*this = this->Inverse();
	return *this;
}

//---------------------------------------------------------------------------

Matrix& Matrix::Transpose()
{
	*this = this->Transpose();
	return *this;
}

} // namespace Mathematics
