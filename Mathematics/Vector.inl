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

		return *this;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::operator -() const
	{
		return Vector(-x, -y, -z);
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

	Vector& Vector::operator -=(const Vector& p_Rhs)
	{
		x -= p_Rhs.x;
		y -= p_Rhs.y;
		z -= p_Rhs.z;
		return *this;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::operator -(const Vector& p_Rhs) const
	{
		return Vector(x - p_Rhs.x, y - p_Rhs.y, z - p_Rhs.z);
	}

	//---------------------------------------------------------------------------

	Vector& Vector::operator *=(const scalar& p_Rhs)
	{
		x *= p_Rhs;
		y *= p_Rhs;
		z *= p_Rhs;
		return *this;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::operator *(const scalar p_Rhs) const
	{
		return Vector(x * p_Rhs, y * p_Rhs, z * p_Rhs);
	}

	//---------------------------------------------------------------------------

	Vector& Vector::operator /=(const scalar& p_Rhs)
	{
		Assert(!EquivalentToZero(p_Rhs), "Trying to divide by zero!");
		const scalar inv = 1.0f / p_Rhs;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::operator /(const scalar p_Rhs) const
	{
		Vector temp(*this);
		temp /= p_Rhs;
		return temp;
	}

	//---------------------------------------------------------------------------

	const scalar Vector::operator |(const Vector& p_Rhs) const
	{
		return (x * p_Rhs.x) + (y * p_Rhs.y) + (z * p_Rhs.z);
	}

	//---------------------------------------------------------------------------

	Vector& Vector::operator *=(const Vector& p_Rhs)
	{
		const scalar crossX = this->y * p_Rhs.z - this->z * p_Rhs.y;
		const scalar crossY = this->z * p_Rhs.x - this->x * p_Rhs.z;
		const scalar crossZ = this->x * p_Rhs.y - this->y * p_Rhs.x;

		this->x = crossX;
		this->y = crossY;
		this->z = crossZ;

		return *this;
	}

	//---------------------------------------------------------------------------

	const Vector Vector::operator *(const Vector& p_Rhs) const
	{
		return Vector(*this) *= p_Rhs;
	}

	//---------------------------------------------------------------------------

	const scalar Vector::LengthSquared() const
	{
		return (*this) | (*this);
	}

	//---------------------------------------------------------------------------

	const scalar Vector::Length() const
	{
		return std::sqrt(LengthSquared());
	}

	//---------------------------------------------------------------------------

	const scalar Vector::InverseLength() const
	{
		const scalar len(Length());

		return (!EquivalentToZero(len)) ? (ConstantScalars::Unity / len) : (ConstantScalars::Zero);
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
		return Vector(*this).Normalize();
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