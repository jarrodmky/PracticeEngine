//===========================================================================
// Filename:	Vector.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Class Definitions
//===========================================================================

namespace Mathematics
{
	Quaternion::Quaternion(const scalar p_Value)
		: m_Real(p_Value), m_Imaginary(p_Value)
	{}

	//---------------------------------------------------------------------------

	Quaternion::Quaternion(const Vector& p_Axis, const scalar p_Angle)
		: m_Real(std::cos(p_Angle * 0.5f))
		, m_Imaginary(p_Axis.x, p_Axis.y, p_Axis.z)
	{
		m_Imaginary.Normalize();
		m_Imaginary *= std::sin(p_Angle * 0.5f);
	}

	//---------------------------------------------------------------------------

	const bool Quaternion::operator ==(const Quaternion& p_Rhs) const
	{
		return EquivalentToEachOther(m_Real, p_Rhs.m_Real) && (m_Imaginary == p_Rhs.m_Imaginary);
	}

	//---------------------------------------------------------------------------

	const bool Quaternion::operator !=(const Quaternion& p_Rhs) const
	{
		return !((*this) == p_Rhs);
	}

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::Negate()
	{
		m_Real = -m_Real;
		m_Imaginary.Negate();

		return *this;
	}

	//---------------------------------------------------------------------------
	
	const Quaternion Quaternion::operator -() const
	{
		return Quaternion(*this).Negate();
	}

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::operator +=(const Quaternion& p_Rhs)
	{
		m_Real += p_Rhs.m_Real;
		m_Imaginary += p_Rhs.m_Imaginary;

		return *this;
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::operator +(const Quaternion& p_Rhs) const
	{
		return Quaternion(*this) += p_Rhs;
	}

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::operator -=(const Quaternion& p_Rhs)
	{
		m_Real -= p_Rhs.m_Real;
		m_Imaginary -= p_Rhs.m_Imaginary;

		return *this;
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::operator -(const Quaternion& p_Rhs) const
	{
		return Quaternion(*this) -= p_Rhs;
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::operator *(const Quaternion& p_Rhs) const
	{
		const scalar& ls = m_Real;
		const scalar& rs = p_Rhs.m_Real;
		const Vector& lv = m_Imaginary;
		const Vector& rv = p_Rhs.m_Imaginary;
		return Quaternion(ls*rs - (lv|rv), rv*ls + lv*rs + lv*rv);
	}

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::operator *=(const Quaternion& p_Rhs)
	{
		(*this) = this->operator*(p_Rhs);

		return *this;
	}

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::operator /=(const Quaternion& p_Rhs)
	{
		return (*this) *= p_Rhs.Reciprocal();
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::operator /(const Quaternion& p_Rhs) const
	{
		return Quaternion(*this) /= p_Rhs;
	}

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::operator *=(const scalar& p_Rhs)
	{
		m_Real *= p_Rhs;
		m_Imaginary *= p_Rhs;

		return *this;
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::operator *(const scalar p_Rhs) const
	{
		return Quaternion(*this) *= p_Rhs;
	}

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::operator /=(const scalar& p_Rhs)
	{
		m_Real /= p_Rhs;
		m_Imaginary /= p_Rhs;

		return *this;
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::operator /(const scalar p_Rhs) const
	{
		return Quaternion(*this) *= p_Rhs;
	}

	//---------------------------------------------------------------------------

	//const bool Quaternion::RotationallyEqualTo(const Quaternion& p_Rhs) const;

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::Reciprocate()
	{
		return (this->Conjugate()) /= LengthSquared();
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::Reciprocal() const
	{
		return Quaternion(*this).Reciprocate();
	}

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::Conjugate()
	{
		m_Imaginary.Negate();

		return *this;
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::Conjugate() const
	{
		return Quaternion(*this).Conjugate();
	}

	//---------------------------------------------------------------------------

	const scalar Quaternion::LengthSquared() const
	{
		const Vector& im = m_Imaginary;
		return m_Real*m_Real + im.x*im.x + im.y*im.y + im.z*im.z;
	}

	//---------------------------------------------------------------------------

	const scalar Quaternion::Length() const
	{
		return std::sqrt(LengthSquared());
	}

	//---------------------------------------------------------------------------

	const scalar Quaternion::InverseLength() const
	{
		return ConstantScalars::Unity / Length();
	}

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::Normalize()
	{
		this->operator*=(InverseLength());
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::Versor() const
	{
		return Quaternion(*this).Normalize();
	}

	//---------------------------------------------------------------------------

	const scalar Quaternion::ScalarPart()
	{
		return m_Real;
	}

	//---------------------------------------------------------------------------

	const Vector Quaternion::VectorPart() const
	{
		return m_Imaginary;
	}

	//---------------------------------------------------------------------------

	bool Quaternion::IsAtOrigin() const
	{
		return EquivalentToZero(m_Real) && m_Imaginary.IsNull();
	}

	//---------------------------------------------------------------------------

	bool Quaternion::IsAtInfinity() const
	{
		return IsInfinite(m_Real) && m_Imaginary.IsAtInfinity();
	}

	//---------------------------------------------------------------------------

	bool Quaternion::IsValid() const
	{
		return IsANumber(m_Real) && m_Imaginary.IsValid();
	}

	//---------------------------------------------------------------------------

	bool Quaternion::IsScalar() const
	{
		return m_Imaginary.IsNull();
	}

	//---------------------------------------------------------------------------

	bool Quaternion::IsVector() const
	{
		return EquivalentToZero(m_Real);
	}

	//---------------------------------------------------------------------------

	bool Quaternion::IsUnit() const
	{
		return EquivalentToEachOther(ConstantScalars::Unity, this->LengthSquared());
	}

	//---------------------------------------------------------------------------

	void Quaternion::RotateVector(Vector& p_Vector) const
	{
		p_Vector = ((*this) * Quaternion(0.0f, p_Vector) * this->Conjugate()).VectorPart();
	}

	//---------------------------------------------------------------------------

	Quaternion::Quaternion(const scalar p_Real, const Vector& p_Imaginary)
		: m_Real(p_Real)
		, m_Imaginary(p_Imaginary)
	{}
}