//===========================================================================
// Filename:	Quaternion.inl
// Author:		Jarrod MacKay
//===========================================================================

namespace Mathematics
{
	//===========================================================================
	// Operator Definitions
	//===========================================================================

	inline const Quaternion operator *(const scalar p_Lhs, const Quaternion& p_Rhs)
	{
		return p_Rhs * p_Lhs;
	}

	//===========================================================================
	// Function Definitions
	//===========================================================================

	inline const bool ApproximatelyEqual(const Quaternion& p_Lhs, const Quaternion& p_Rhs, const scalar p_Tolerance)
	{
		return IsApproximatelyZero((p_Lhs - p_Rhs).LengthSquared(), p_Tolerance);
	}

	inline const Quaternion MakeRandomVersor()
	{
		const scalar angle = MakeRandomScalar(Zero, TwoPi);
		const Vector3 axis = MakeRandomVector3(Zero, Unity).Direction();
		return Quaternion(axis, angle);
	}

	//===========================================================================
	// Constant Definitions
	//===========================================================================

	inline const Quaternion ZeroRotor()
	{
		return Quaternion(Zero, Zero3());
	}

	inline const Quaternion IdentityRotor()
	{
		return Quaternion(Unity, Zero3());
	}

	//===========================================================================
	// Class Definitions
	//===========================================================================
	
	Quaternion::Quaternion(const scalar p_Real, const Vector3& p_Imaginary)
		: m_Real(p_Real)
		, m_Imaginary(p_Imaginary)
	{}

	//---------------------------------------------------------------------------

	Quaternion::Quaternion()
		: Quaternion(IdentityRotor())
	{}

	//---------------------------------------------------------------------------

	Quaternion::Quaternion(const scalar p_Value)
		: m_Real(p_Value)
		, m_Imaginary(p_Value)
	{}

	//---------------------------------------------------------------------------

	Quaternion::Quaternion(const Vector3& p_Axis, const scalar p_Angle)
		: Quaternion(std::cos(p_Angle * 0.5f), p_Axis.Direction() * std::sin(p_Angle * 0.5f))
	{}

	//---------------------------------------------------------------------------

	Quaternion::Quaternion(const Vector3& p_Start, const Vector3& p_Final)
		: Quaternion(std::cos(AngleBetween(p_Start, p_Final) * 0.5f)
		, (p_Start.Direction() * p_Final.Direction()) * std::sin(AngleBetween(p_Start, p_Final) * 0.5f))
	{}

	//---------------------------------------------------------------------------

	Quaternion::Quaternion(const scalar p_Real, const scalar p_Imag0, const scalar p_Imag1, const scalar p_Imag2)
		: m_Real(p_Real)
		, m_Imaginary(MakeVector(p_Imag0, p_Imag1, p_Imag2))
	{}

	//---------------------------------------------------------------------------

	const bool Quaternion::operator ==(const Quaternion& p_Rhs) const
	{
		return Equal(m_Real, p_Rhs.m_Real) && (m_Imaginary == p_Rhs.m_Imaginary);
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
		return Quaternion(m_Real + p_Rhs.m_Real, m_Imaginary + p_Rhs.m_Imaginary);
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
		return Quaternion(m_Real - p_Rhs.m_Real, m_Imaginary - p_Rhs.m_Imaginary);
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::operator *(const Quaternion& p_Rhs) const
	{
		const scalar& w1 = m_Real;
		const scalar& w2 = p_Rhs.m_Real;
		const scalar& x1 = m_Imaginary(0);
		const scalar& x2 = p_Rhs.m_Imaginary(0);
		const scalar& y1 = m_Imaginary(1);
		const scalar& y2 = p_Rhs.m_Imaginary(1);
		const scalar& z1 = m_Imaginary(2);
		const scalar& z2 = p_Rhs.m_Imaginary(2);
		return Quaternion(w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2
			, w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2
			, w1 * y2 - x1 * z2 + y1 * w2 + z1 * x2
			, w1 * z2 + x1 * y2 - y1 * x2 + z1 * w2);
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
		Assert(!IsZero(p_Rhs), "Division by zero!");
		m_Real /= p_Rhs;
		m_Imaginary /= p_Rhs;
		return *this;
	}

	//---------------------------------------------------------------------------

	const Quaternion Quaternion::operator /(const scalar p_Rhs) const
	{
		return Quaternion(*this) /= p_Rhs;
	}

	//---------------------------------------------------------------------------

	inline const scalar Quaternion::operator |(const Quaternion& p_Rhs) const
	{
		return Real() * p_Rhs.Real() + (Imaginary() | p_Rhs.Imaginary());
	}

	//---------------------------------------------------------------------------

	inline const scalar Quaternion::Angle() const
	{
		return 2.0f * std::acos(m_Real);
	}

	//---------------------------------------------------------------------------

	inline const Vector3 Quaternion::Axis() const
	{
		const scalar denom(std::sqrt(Unity - (m_Real * m_Real)));

		if (IsZero(denom))
		{
			return m_Imaginary.Direction();
		}
		else
		{
			return m_Imaginary / denom;
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

	const Quaternion Quaternion::Conjugation() const
	{
		return Quaternion(m_Real, -m_Imaginary);
	}

	//---------------------------------------------------------------------------

	const scalar Quaternion::LengthSquared() const
	{
		const Vector3& im(m_Imaginary);
		return m_Real*m_Real + im(0)*im(0) + im(1)*im(1) + im(2)*im(2);
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
		return (IsZero(len)) ? (Infinity) : (Unity / Length());
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

	const scalar Quaternion::Real() const
	{
		return m_Real;
	}

	//---------------------------------------------------------------------------

	const Vector3 Quaternion::Imaginary() const
	{
		return m_Imaginary;
	}

	//---------------------------------------------------------------------------

	const scalar Quaternion::ScalarPart() const
	{
		return Real();
	}

	//---------------------------------------------------------------------------

	const Vector3 Quaternion::VectorPart() const
	{
		return Imaginary();
	}

	//---------------------------------------------------------------------------

	bool Quaternion::IsAtOrigin() const
	{
		return IsZero(m_Real) && m_Imaginary.IsAtOrigin();
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
		return m_Imaginary.IsAtOrigin();
	}

	//---------------------------------------------------------------------------

	bool Quaternion::IsVector() const
	{
		return IsZero(m_Real);
	}

	//---------------------------------------------------------------------------

	bool Quaternion::IsUnit() const
	{
		return IsUnity(this->LengthSquared());
	}

	//---------------------------------------------------------------------------

	void Quaternion::Rotate(Vector3& p_Vector) const
	{
		scalar length = p_Vector.Length();
		Vector3 direction = p_Vector.Direction();
		p_Vector = (((*this) * Quaternion(0.0f, direction) * this->Conjugation()).VectorPart().Direction()) * length;
	}

	//---------------------------------------------------------------------------

	Vector3 Quaternion::Rotate(const Vector3& p_Vector) const
	{
		Vector3 temp(p_Vector);
		Rotate(temp);
		return temp;
	}
}