//===========================================================================
// Filename:	Vector.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Class Definitions
//===========================================================================

namespace Mathematics
{
	Vector::Vector(const scalar p_Scalar)
		: x(p_Scalar), y(p_Scalar), z(p_Scalar)
	{}

	//---------------------------------------------------------------------------

	Vector::Vector(const scalar p_X, const scalar p_Y, const scalar p_Z)
		: x(p_X), y(p_Y), z(p_Z)
	{}

	//---------------------------------------------------------------------------

	const bool Vector::operator ==(const Vector& p_Rhs) const
	{
		return EquivalentToEachOther(x, p_Rhs.x)
			&& EquivalentToEachOther(y, p_Rhs.y)
			&& EquivalentToEachOther(z, p_Rhs.z);
	}

	//---------------------------------------------------------------------------

	const bool Vector::operator !=(const Vector& p_Rhs) const
	{
		return !((*this) == p_Rhs);
	}

	//---------------------------------------------------------------------------

	Vector& Vector::Negate()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::operator -() const
	{
		Vector temp(*this);
		temp.Negate();
		return temp;
	}

	//---------------------------------------------------------------------------

	Vector& Vector::operator +=(const Vector& p_Rhs)
	{
		x += p_Rhs.x;
		y += p_Rhs.y;
		z += p_Rhs.z;
		return *this;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::operator +(const Vector& p_Rhs) const
	{
		return Vector(x + p_Rhs.x, y + p_Rhs.y, z + p_Rhs.z);
	}

	//---------------------------------------------------------------------------

	Vector& Vector::operator -=(const Vector& p_Lhs)
	{
		x -= p_Lhs.x;
		y -= p_Lhs.y;
		z -= p_Lhs.z;
		return *this;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::operator -(const Vector& p_Lhs) const
	{
		Vector temp(*this);
		temp -= p_Lhs;
		return temp;
	}

	//---------------------------------------------------------------------------

	Vector& Vector::operator *=(const scalar& p_Lhs)
	{
		x *= p_Lhs;
		y *= p_Lhs;
		z *= p_Lhs;
		return *this;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::operator *(const scalar p_Lhs) const
	{
		Vector temp(*this);
		temp *= p_Lhs;
		return temp;
	}

	//---------------------------------------------------------------------------

	Vector& Vector::operator /=(const scalar& p_Lhs)
	{
		Assert(!EquivalentToZero(p_Lhs), "Trying to divide by zero!");
		x /= p_Lhs;
		y /= p_Lhs;
		z /= p_Lhs;
		return *this;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::operator /(const scalar p_Lhs) const
	{
		Vector temp(*this);
		temp /= p_Lhs;
		return temp;
	}

	//---------------------------------------------------------------------------

	const scalar Vector::operator |(const Vector& p_Lhs) const
	{
		return x * p_Lhs.x + y * p_Lhs.y + z * p_Lhs.z;
	}

	//---------------------------------------------------------------------------

	Vector& Vector::operator *=(const Vector& p_Lhs)
	{
		const scalar crossX = this->y * p_Lhs.z - this->z * p_Lhs.y;
		const scalar crossY = this->z * p_Lhs.x - this->x * p_Lhs.z;
		const scalar crossZ = this->x * p_Lhs.y - this->y * p_Lhs.x;

		this->x = crossX;
		this->y = crossY;
		this->z = crossZ;

		return *this;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::operator *(const Vector& p_Lhs) const
	{
		Vector temp(*this);
		temp *= p_Lhs;
		return temp;
	}

	//---------------------------------------------------------------------------

	const scalar Vector::LengthSquared() const
	{
		return (*this) | (*this);
	}

	//---------------------------------------------------------------------------

	const scalar Vector::Length() const
	{
		return std::sqrtf(LengthSquared());
	}

	//---------------------------------------------------------------------------

	const scalar Vector::InverseLength() const
	{
		Assert(!EquivalentToZero(LengthSquared()), "Trying to divide by zero!");
		return ConstantScalars::Unity / Length();
	}

	//---------------------------------------------------------------------------

	inline const scalar Vector::ManhattanLength() const
	{
		return AbsoluteValue(x) + AbsoluteValue(y) + AbsoluteValue(z);
	}

	//---------------------------------------------------------------------------

	Vector& Vector::Normalize()
	{
		(*this) *= InverseLength();
		return *this;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::Direction() const
	{
		Vector temp(*this);
		temp.Normalize();
		return temp;
	}

	//---------------------------------------------------------------------------

	bool Vector::IsNull() const
	{
		return EquivalentToZero(x)
			&& EquivalentToZero(y)
			&& EquivalentToZero(z);
	}

	//---------------------------------------------------------------------------

	bool Vector::IsAtInfinity() const
	{
		return IsInfinite(x)
			|| IsInfinite(y)
			|| IsInfinite(z);
	}

	//---------------------------------------------------------------------------

	bool Vector::IsValid() const
	{
		return IsANumber(x)
			&& IsANumber(y)
			&& IsANumber(z);
	}

	//---------------------------------------------------------------------------

	bool Vector::IsUnit() const
	{
		return EquivalentToEachOther(ConstantScalars::Unity, this->LengthSquared());
	}
}