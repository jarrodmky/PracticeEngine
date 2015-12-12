//===========================================================================
// Filename:	Vector.inl
// Author:		Jarrod MacKay
//===========================================================================

namespace Mathematics
{

	//===========================================================================
	// Operators Definitions
	//===========================================================================

	//vector scaling
	template <u32 t_Rows>
	inline const Vector<t_Rows> operator *(const scalar p_Lhs, const Vector<t_Rows>& p_Rhs)
	{
		return p_Rhs * p_Lhs;
	}

	//---------------------------------------------------------------------------

	//cross product
	inline Vector3& operator *=(Vector3& p_Lhs, const Vector3& p_Rhs)
	{
		const scalar crossX = p_Lhs(2) * p_Rhs(3) - p_Lhs(3) * p_Rhs(2);
		const scalar crossY = p_Lhs(3) * p_Rhs(1) - p_Lhs(1) * p_Rhs(3);
		const scalar crossZ = p_Lhs(1) * p_Rhs(2) - p_Lhs(2) * p_Rhs(1);

		p_Lhs(1) = crossX;
		p_Lhs(2) = crossY;
		p_Lhs(3) = crossZ;

		return p_Lhs;
	}

	//---------------------------------------------------------------------------

	inline const Vector3 operator *(const Vector3& p_Lhs, const Vector3& p_Rhs)
	{
		return Vector3(p_Lhs) *= p_Rhs;
	}

	//---------------------------------------------------------------------------

	inline Vector4& operator *=(Vector4& p_Lhs, const Vector4& p_Rhs)
	{
		const scalar crossX = p_Lhs(2) * p_Rhs(3) - p_Lhs(3) * p_Rhs(2);
		const scalar crossY = p_Lhs(3) * p_Rhs(1) - p_Lhs(1) * p_Rhs(3);
		const scalar crossZ = p_Lhs(1) * p_Rhs(2) - p_Lhs(2) * p_Rhs(1);

		p_Lhs(1) = crossX;
		p_Lhs(2) = crossY;
		p_Lhs(3) = crossZ;
		p_Lhs(4) = Zero;

		return p_Lhs;
	}

	//---------------------------------------------------------------------------

	inline const Vector4 operator *(const Vector4& p_Lhs, const Vector4& p_Rhs)
	{
		return Vector4(p_Lhs) *= p_Rhs;
	}

	//===========================================================================
	// Constant Definitions
	//===========================================================================

	inline const Vector2 Zero2()
	{
		return Vector2(Zero);
	}

	inline const Vector2 Ones2()
	{
		return Vector2(Unity);
	}

	inline const Vector2 U()
	{
		Vector2 temp(Zero2());
		temp(1) = Unity;
		return temp;
	}

	inline const Vector2 V()
	{
		Vector2 temp(Zero2());
		temp(2) = Unity;
		return temp;
	}

	inline const Vector3 Zero3()
	{
		return Vector3(Zero);
	}

	inline const Vector3 Ones3()
	{
		return Vector3(Unity);
	}

	inline const Vector3 I()
	{
		Vector3 temp(Zero3());
		temp(1) = Unity;
		return temp;
	}

	inline const Vector3 J()
	{
		Vector3 temp(Zero3());
		temp(2) = Unity;
		return temp;
	}

	inline const Vector3 K()
	{
		Vector3 temp(Zero3());
		temp(3) = Unity;
		return temp;
	}

	inline const Vector4 Zero4()
	{
		return Vector4(Zero);
	}

	inline const Vector4 Ones4()
	{
		return Vector4(Unity);
	}

	inline const Vector4 W()
	{
		Vector4 temp(Zero4());
		temp(4) = Unity;
		return temp;
	}

	inline const Vector4 X()
	{
		Vector4 temp(Zero4());
		temp(1) = Unity;
		return temp;
	}

	inline const Vector4 Y()
	{
		Vector4 temp(Zero4());
		temp(2) = Unity;
		return temp;
	}

	inline const Vector4 Z()
	{
		Vector4 temp(Zero4());
		temp(3) = Unity;
		return temp;
	}

	//===========================================================================
	// Class Definitions
	//===========================================================================

	template <u32 t_Rows>
	Vector<t_Rows>::Vector(const scalar p_Scalar)
		: m_Column(p_Scalar)
	{}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const bool Vector<t_Rows>::operator ==(const Vector<t_Rows>& p_Rhs) const
	{
		return m_Column.Equals(p_Rhs.m_Column, EquivalentToEachOther);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const bool Vector<t_Rows>::operator !=(const Vector& p_Rhs) const
	{
		return !((*this) == p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	Vector<t_Rows>& Vector<t_Rows>::Negate()
	{
		m_Column.ApplyFunction([](const scalar& p_Value)->const scalar
		{
			return -p_Value;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const Vector<t_Rows> Vector<t_Rows>::operator -() const
	{
		return Vector<t_Rows>(*this).Negate();
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	Vector<t_Rows>& Vector<t_Rows>::operator +=(const Vector<t_Rows>& p_Rhs)
	{
		m_Column.ApplyFunction(p_Rhs.m_Column,
			[](const scalar& p_L, const scalar& p_R)->const scalar
		{
			return p_L + p_R;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const Vector<t_Rows> Vector<t_Rows>::operator +(const Vector<t_Rows>& p_Rhs) const
	{
		return (Vector<t_Rows>(*this) += p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	Vector<t_Rows>& Vector<t_Rows>::operator -=(const Vector<t_Rows>& p_Rhs)
	{
		m_Column.ApplyFunction(p_Rhs.m_Column,
			[](const scalar& p_L, const scalar& p_R)->const scalar
		{
			return p_L - p_R;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const Vector<t_Rows> Vector<t_Rows>::operator -(const Vector<t_Rows>& p_Rhs) const
	{
		return (Vector<t_Rows>(*this) -= p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	Vector<t_Rows>& Vector<t_Rows>::operator *=(const scalar& p_Rhs)
	{
		m_Column.ApplyFunction([&](const scalar& p_Value)->const scalar
		{
			return p_Value * p_Rhs;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const Vector<t_Rows> Vector<t_Rows>::operator *(const scalar p_Rhs) const
	{
		return (Vector<t_Rows>(*this) *= p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	Vector<t_Rows>& Vector<t_Rows>::operator /=(const scalar& p_Rhs)
	{
		Assert(!EquivalentToZero(p_Rhs), "Trying to divide by zero!");
		const scalar inv = 1.0f / p_Rhs;
		(*this) *= inv;
		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const Vector<t_Rows> Vector<t_Rows>::operator /(const scalar p_Rhs) const
	{
		return (Vector<t_Rows>(*this) /= p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const scalar Vector<t_Rows>::operator |(const Vector<t_Rows>& p_Rhs) const
	{
		scalar sum(0.0f);
		for (u32 i = 0; i < t_Rows; ++i)
		{
			sum += m_Column(i) * p_Rhs.m_Column(i);
		}
		return sum;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline scalar& Vector<t_Rows>::operator ()(const u32 p_Row)
	{
		return m_Column(p_Row-1);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const scalar Vector<t_Rows>::operator ()(const u32 p_Row) const
	{
		return m_Column(p_Row-1);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const scalar Vector<t_Rows>::LengthSquared() const
	{
		return (*this) | (*this);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const scalar Vector<t_Rows>::Length() const
	{
		return std::sqrt(LengthSquared());
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const scalar Vector<t_Rows>::InverseLength() const
	{
		const scalar len(Length());

		return (!EquivalentToZero(len)) ? (Unity / len) : (Zero);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	inline const scalar Vector<t_Rows>::ManhattanLength() const
	{
		scalar sum(0.0f);
		for (u32 i = 0; i < t_Rows; ++i)
		{
			sum += AbsoluteValue(m_Column(i));
		}
		return sum;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	Vector<t_Rows>& Vector<t_Rows>::Normalize()
	{
		(*this) *= InverseLength();
		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const Vector<t_Rows> Vector<t_Rows>::Direction() const
	{
		return Vector<t_Rows>(*this).Normalize();
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const scalar Vector<t_Rows>::LengthAlong(const Vector<t_Rows>& p_Rhs) const
	{
		return (*this) | p_Rhs.Direction();
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	Vector<t_Rows>& Vector<t_Rows>::ProjectAlong(const Vector<t_Rows>& p_Rhs)
	{
		scalar invSquareLHS = p_Rhs.LengthSquared();
		Invert(invSquareLHS);

		(*this) = p_Rhs * (((*this) | p_Rhs) * invSquareLHS);
		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	const Vector<t_Rows> Vector<t_Rows>::ProjectedAlong(const Vector<t_Rows>& p_Rhs) const
	{
		Vector temp(*this);
		temp.ProjectAlong(p_Rhs);
		return temp;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	bool Vector<t_Rows>::IsNull() const
	{
		for (u32 i = 0; i < t_Rows; ++i)
		{
			if (!EquivalentToZero(m_Column(i)))
			{
				return false;
			}
		}
		return true;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	bool Vector<t_Rows>::IsAtInfinity() const
	{
		for (u32 i = 0; i < t_Rows; ++i)
		{
			if (IsInfinite(m_Column(i)))
			{
				return true;
			}
		}
		return false;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	bool Vector<t_Rows>::IsValid() const
	{
		for (u32 i = 0; i < t_Rows; ++i)
		{
			if (!IsANumber(m_Column(i)))
			{
				return false;
			}
		}
		return true;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows>
	bool Vector<t_Rows>::IsUnit() const
	{
		return EquivalentToEachOther(ConstantScalars::Unity, this->LengthSquared());
	}
}