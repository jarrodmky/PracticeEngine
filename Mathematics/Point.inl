//===========================================================================
// Filename:	Point.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Class Definitions
//===========================================================================

namespace Mathematics
{
	Point::Point(const scalar p_Scalar)
	: x(p_Scalar), y(p_Scalar), z(p_Scalar)
	{}

	Point::Point(const scalar p_X, const scalar p_Y, const scalar p_Z)
	: x(p_X), y(p_Y), z(p_Z)
	{}
		
	Point::Point(const Vector& p_Position)
	: x(p_Position.x), y(p_Position.y), z(p_Position.z)
	{}

	const bool Point::operator ==(const Point& p_Lhs) const
	{
		return EquivalentToEachOther(x, p_Lhs.x)
			&& EquivalentToEachOther(y, p_Lhs.y)
			&& EquivalentToEachOther(z, p_Lhs.z);
	}

	const bool Point::operator !=(const Point& p_Lhs) const
	{
		return !((*this) == p_Lhs);
	}

	Point& Point::operator +=(const Vector& p_Lhs)
	{
		x += p_Lhs.x;
		y += p_Lhs.y;
		z += p_Lhs.z;
		return *this;
	}

	const Point Point::operator +(const Vector& p_Lhs) const
	{
		return Point(x + p_Lhs.x, y + p_Lhs.y, z + p_Lhs.z);
	}
	
	const Vector Point::operator -(const Point& p_Lhs) const
	{
		return Vector(x - p_Lhs.x, y - p_Lhs.y, z - p_Lhs.z);
	}

	const scalar Point::DistanceSquaredTo(const Point& p_Lhs) const
	{
		return (p_Lhs - (*this)).LengthSquared();
	}

	const scalar Point::DistanceTo(const Point& p_Lhs) const
	{
		return (p_Lhs - (*this)).Length();
	}

	bool Point::IsOrigin() const
	{
		return (*this) == ConstantPoints::Origin;
	}

	bool Point::IsAtInfinity() const
	{
		return !(IsFinite(x) && IsFinite(y) && IsFinite(z));
	}

	bool Point::IsValid() const
	{
		return (IsANumber(x) && IsANumber(y) && IsANumber(z));
	}
}