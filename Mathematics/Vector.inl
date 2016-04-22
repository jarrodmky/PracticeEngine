//===========================================================================
// Filename:	Vector.inl
// Author:		Jarrod MacKay
//===========================================================================

namespace Mathematics
{

	//===========================================================================
	// Operator Definitions
	//===========================================================================

	template <typename t_Scalar, u32 t_Rows>
	inline const t_Scalar operator |(const Vector<t_Scalar, t_Rows>& p_Lhs, const Vector<t_Scalar, t_Rows>& p_Rhs)
	{
		scalar sum(0.0f);
		for (u32 i = 0; i < t_Rows; ++i)
		{
			sum += p_Lhs(i) * p_Rhs(i);
		}
		return sum;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	inline const Vector<t_Scalar, t_Rows> operator *(const t_Scalar p_Lhs, const Vector<t_Scalar, t_Rows>& p_Rhs)
	{
		return p_Rhs * p_Lhs;
	}

	//===========================================================================
	// Function Definitions
	//===========================================================================

	template <typename t_Scalar, u32 t_Rows>
	inline const Vector<t_Scalar, t_Rows> Zeroes()
	{
		return Vector<t_Scalar, t_Rows>(0);
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	inline const Vector<t_Scalar, t_Rows> Ones()
	{
		return Vector<t_Scalar, t_Rows>(1);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const RealVector<t_Rows + 1> MakeAffineVector(const RealVector<t_Rows>& p_Vector)
	{
		RealVector<t_Rows + 1> temp(Zero);
		for (u32 i = 0; i < t_Rows; ++i)
		{
			temp(i) = p_Vector(i);
		}
		return temp;
	}
	
	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const RealVector<t_Rows + 1> MakeAffinePoint(const RealVector<t_Rows>& p_Vector)
	{
		RealVector<t_Rows + 1> temp(Unity);
		for (u32 i = 0; i < t_Rows; ++i)
		{
			temp(i) = p_Vector(i);
		}
		return temp;
	}
	
	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const RealVector<t_Rows - 1> MakeProjectedVector(const RealVector<t_Rows>& p_Vector)
	{
		RealVector<t_Rows - 1> temp;
		for (u32 i = 0; i < t_Rows - 1; ++i)
		{
			temp(i) = p_Vector(i);
		}
		return temp;
	}
	
	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const RealVector<t_Rows - 1> MakeProjectedPoint(const RealVector<t_Rows>& p_Vector)
	{
		Assert(!p_Vector.IsAffineVector(), "Cannot project vector!");
		RealVector<t_Rows - 1> temp;
		const scalar invAffinity = Inverse(p_Vector.AffineComponent());
		for (u32 i = 0; i < t_Rows - 1; ++i)
		{
			temp(i) = p_Vector(i) * invAffinity;
		}
		Assert(IsEqualTo(p_Vector.AffineComponent() * invAffinity, Unity), "Projection was invalid!");
		return temp;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const scalar AngleBetween(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs)
	{
		return std::acos(p_Lhs.Direction() | p_Rhs.Direction());
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const bool Perpendicular(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs)
	{
		return IsZero(p_Lhs | p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const bool Acute(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs)
	{
		return (p_Lhs | p_Rhs) > Zero;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const bool Obtuse(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs)
	{
		return (p_Lhs | p_Rhs) < Zero;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const bool Close(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs, const scalar p_Tolerance)
	{
		return IsApproximatelyZero((p_Lhs - p_Rhs).LengthSquared(), p_Tolerance);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const bool ApproximatelyEqual(const RealVector<t_Rows>& p_Lhs, const RealVector<t_Rows>& p_Rhs, const scalar p_Tolerance)
	{
		for (u32 i = 0; i < t_Rows; ++i)
		{
			if (!ApproximatelyEqual(p_Lhs(i), p_Rhs(i), p_Tolerance))
			{
				return false;
			}
		}
		return true;
	}

	//===========================================================================
	// Class Definitions
	//===========================================================================

	template <typename t_Scalar, u32 t_Rows>
	Vector<t_Scalar, t_Rows>::Vector(const t_Scalar p_Scalar)
		: m_Column(p_Scalar)
	{}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const bool Vector<t_Scalar, t_Rows>::operator ==(const Vector<t_Scalar, t_Rows>& p_Rhs) const
	{
		return m_Column.Equals(p_Rhs.m_Column, Equal);
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const bool Vector<t_Scalar, t_Rows>::operator !=(const Vector<t_Scalar, t_Rows>& p_Rhs) const
	{
		return !((*this) == p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	Vector<t_Scalar, t_Rows>& Vector<t_Scalar, t_Rows>::Negate()
	{
		m_Column.Map([](const scalar& p_Value)->const scalar
		{
			return -p_Value;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const Vector<t_Scalar, t_Rows> Vector<t_Scalar, t_Rows>::operator -() const
	{
		return Vector<t_Scalar, t_Rows>(*this).Negate();
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	Vector<t_Scalar, t_Rows>& Vector<t_Scalar, t_Rows>::operator +=(const Vector<t_Scalar, t_Rows>& p_Rhs)
	{
		m_Column.Map(p_Rhs.m_Column,
			[](const t_Scalar& p_L, const t_Scalar& p_R)->const t_Scalar
		{
			return p_L + p_R;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const Vector<t_Scalar, t_Rows> Vector<t_Scalar, t_Rows>::operator +(const Vector<t_Scalar, t_Rows>& p_Rhs) const
	{
		return (Vector<t_Scalar, t_Rows>(*this) += p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	Vector<t_Scalar, t_Rows>& Vector<t_Scalar, t_Rows>::operator -=(const Vector<t_Scalar, t_Rows>& p_Rhs)
	{
		m_Column.Map(p_Rhs.m_Column,
			[](const t_Scalar& p_L, const t_Scalar& p_R)->const t_Scalar
		{
			return p_L - p_R;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const Vector<t_Scalar, t_Rows> Vector<t_Scalar, t_Rows>::operator -(const Vector<t_Scalar, t_Rows>& p_Rhs) const
	{
		return (Vector<t_Scalar, t_Rows>(*this) -= p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	Vector<t_Scalar, t_Rows>& Vector<t_Scalar, t_Rows>::operator %=(const Vector<t_Scalar, t_Rows>& p_Rhs)
	{
		m_Column.Map(p_Rhs.m_Column,
			[](const t_Scalar& p_L, const t_Scalar& p_R)->const t_Scalar
		{
			return p_L * p_R;
		});
		return *this;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const Vector<t_Scalar, t_Rows> Vector<t_Scalar, t_Rows>::operator %(const Vector<t_Scalar, t_Rows>& p_Rhs) const
	{
		return (Vector<t_Scalar, t_Rows>(*this) %= p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	Vector<t_Scalar, t_Rows>& Vector<t_Scalar, t_Rows>::operator *=(const t_Scalar& p_Rhs)
	{
		m_Column.Map([&](const t_Scalar& p_Value)->const t_Scalar
		{
			return p_Value * p_Rhs;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const Vector<t_Scalar, t_Rows> Vector<t_Scalar, t_Rows>::operator *(const t_Scalar p_Rhs) const
	{
		return (Vector<t_Scalar, t_Rows>(*this) *= p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	Vector<t_Scalar, t_Rows>& Vector<t_Scalar, t_Rows>::operator /=(const t_Scalar& p_Rhs)
	{
		const t_Scalar inv = Inverse(p_Rhs);
		(*this) *= inv;
		return *this;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const Vector<t_Scalar, t_Rows> Vector<t_Scalar, t_Rows>::operator /(const t_Scalar p_Rhs) const
	{
		return (Vector<t_Scalar, t_Rows>(*this) /= p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	inline t_Scalar& Vector<t_Scalar, t_Rows>::operator ()(const u32 p_Row)
	{
		return m_Column[p_Row];
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	inline const t_Scalar Vector<t_Scalar, t_Rows>::operator ()(const u32 p_Row) const
	{
		return m_Column[p_Row];
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const t_Scalar Vector<t_Scalar, t_Rows>::LengthSquared() const
	{
		return (*this) | (*this);
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const t_Scalar Vector<t_Scalar, t_Rows>::Length() const
	{
		return std::sqrt(LengthSquared());
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const t_Scalar Vector<t_Scalar, t_Rows>::InverseLength() const
	{
		const t_Scalar len(Length());

		return (IsZero(len)) ? (Infinity) : (Unity / len);
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	inline const t_Scalar Vector<t_Scalar, t_Rows>::ManhattanLength() const
	{
		t_Scalar sum(0);
		for (u32 i = 0; i < t_Rows; ++i)
		{
			sum += AbsoluteValue(m_Column(i));
		}
		return sum;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	inline const t_Scalar Vector<t_Scalar, t_Rows>::AffineComponent() const
	{
		return m_Column[t_Rows - 1];
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	Vector<t_Scalar, t_Rows>& Vector<t_Scalar, t_Rows>::Normalize()
	{
		(*this) *= InverseLength();
		return *this;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const Vector<t_Scalar, t_Rows> Vector<t_Scalar, t_Rows>::Direction() const
	{
		return (IsUnit()) ? (*this) : (Vector<t_Scalar, t_Rows>(*this).Normalize());
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const t_Scalar Vector<t_Scalar, t_Rows>::LengthAlong(const Vector<t_Scalar, t_Rows>& p_Direction) const
	{
		Assert(p_Direction.IsUnit(), "Vector is not unit length!");
		return (*this) | p_Direction;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	Vector<t_Scalar, t_Rows>& Vector<t_Scalar, t_Rows>::ProjectAlong(const Vector<t_Scalar, t_Rows>& p_Direction)
	{
		(*this) = ProjectionAlong(p_Direction);
		return *this;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const Vector<t_Scalar, t_Rows> Vector<t_Scalar, t_Rows>::ProjectionAlong(const Vector<t_Scalar, t_Rows>& p_Direction) const
	{
		return p_Direction * (LengthAlong(p_Direction));
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	Vector<t_Scalar, t_Rows>& Vector<t_Scalar, t_Rows>::RejectFrom(const Vector<t_Scalar, t_Rows>& p_Direction)
	{
		(*this) -= ProjectionAlong(p_Direction);
		return *this;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const Vector<t_Scalar, t_Rows> Vector<t_Scalar, t_Rows>::RejectionFrom(const Vector<t_Scalar, t_Rows>& p_Direction) const
	{
		return Vector<t_Scalar, t_Rows>(*this).RejectFrom(p_Direction);
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const bool Vector<t_Scalar, t_Rows>::IsAffineVector() const
	{
		return IsZero(AffineComponent());
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const bool Vector<t_Scalar, t_Rows>::IsAtOrigin() const
	{
		for (u32 i = 0; i < t_Rows; ++i)
		{
			if (!IsZero(m_Column[i]))
			{
				return false;
			}
		}
		return true;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const bool Vector<t_Scalar, t_Rows>::IsAtInfinity() const
	{
		for (u32 i = 0; i < t_Rows; ++i)
		{
			if (IsInfinite(m_Column[i]))
			{
				return true;
			}
		}
		return false;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const bool Vector<t_Scalar, t_Rows>::IsValid() const
	{
		for (u32 i = 0; i < t_Rows; ++i)
		{
			if (!IsANumber(m_Column[i]))
			{
				return false;
			}
		}
		return true;
	}

	//---------------------------------------------------------------------------

	template <typename t_Scalar, u32 t_Rows>
	const bool Vector<t_Scalar, t_Rows>::IsUnit() const
	{
		return IsUnity(this->LengthSquared());
	}
}