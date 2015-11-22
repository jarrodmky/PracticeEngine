//===========================================================================
// Filename:	Matrix.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Class Definitions
//===========================================================================

namespace Mathematics
{

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
	m_Array(3, 3) = 1.0f;
}

//---------------------------------------------------------------------------

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

} // namespace Mathematics
