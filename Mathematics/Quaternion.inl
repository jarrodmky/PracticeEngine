//===========================================================================
// Filename:	Quaternion.inl
// Author:		Jarrod MacKay
//===========================================================================

namespace Mathematics
{

//===========================================================================
// Constant Definitions
//===========================================================================

	inline const Quaternion Origin()
	{
		return Quaternion(Zero, Zero3());
	}

	inline const Quaternion Identity()
	{
		return Quaternion(Unity, Zero3());
	}

//===========================================================================
// Class Definitions
//===========================================================================

	Quaternion::Quaternion(const scalar p_Value)
		: m_Real(p_Value)
		, m_Imaginary(p_Value)
	{}

	//---------------------------------------------------------------------------

	Quaternion::Quaternion(const Vector3& p_Axis, const scalar p_Angle)
		: m_Real(std::cos(p_Angle * 0.5f))
		, m_Imaginary(p_Axis.Direction() * std::sin(p_Angle * 0.5f))
	{}

	//---------------------------------------------------------------------------

	Quaternion::Quaternion(const scalar p_Real, const Vector3& p_Imaginary)
		: m_Real(p_Real)
		, m_Imaginary(p_Imaginary)
	{}

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
		const Vector3& lv = m_Imaginary;
		const Vector3& rv = p_Rhs.m_Imaginary;
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
		return (*this) *= p_Rhs.Inverse();
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

	inline const scalar Quaternion::Angle() const
	{
		return 2.0f * std::acos(m_Real);
	}

	//---------------------------------------------------------------------------

	inline const Vector3 Quaternion::Axis() const
	{
		const scalar angle(Angle());
		const scalar div(Unity / std::sqrt(Unity - (m_Real * m_Real)));

		if (EquivalentToZero(div))
		{
			return m_Imaginary;
		}
		else
		{
			return m_Imaginary * div;
		}
	}

	//---------------------------------------------------------------------------

	//const bool Quaternion::RotationallyEqualTo(const Quaternion& p_Rhs) const;

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::Invert()
	{
		return (this->Conjugate()) /= LengthSquared();
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::Inverse() const
	{
		return Quaternion(*this).Invert();
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
		const Vector3& im(m_Imaginary);
		return m_Real*m_Real + im(1)*im(1) + im(2)*im(2) + im(3)*im(3);
	}

	//---------------------------------------------------------------------------

	const scalar Quaternion::Length() const
	{
		return std::sqrt(LengthSquared());
	}

	//---------------------------------------------------------------------------

	const scalar Quaternion::InverseLength() const
	{
		const scalar len(Length());
		return (EquivalentToEachOther(len, Zero)) ? (Infinity) : (Unity / Length());
	}

	//---------------------------------------------------------------------------

	Quaternion& Quaternion::Normalize()
	{
		this->operator*=(InverseLength());
		return *this;
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::Versor() const
	{
		return Quaternion(*this).Normalize();
	}

	//---------------------------------------------------------------------------

	const scalar Quaternion::ScalarPart() const
	{
		return m_Real;
	}

	//---------------------------------------------------------------------------

	const Vector3 Quaternion::VectorPart() const
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
		return EquivalentToEachOther(Unity, this->LengthSquared());
	}

	//---------------------------------------------------------------------------

	void Quaternion::RotateVector(Vector3& p_Vector) const
	{
		scalar length = p_Vector.Length();
		Vector3 direction = p_Vector.Direction();
		p_Vector = (((*this) * Quaternion(0.0f, p_Vector) * this->Conjugate()).VectorPart().Direction()) * length;
	}
}