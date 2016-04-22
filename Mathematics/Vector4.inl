//===========================================================================
// Filename:	Vector4.inl
// Author:		Jarrod MacKay
//===========================================================================

namespace Mathematics
{
	//===========================================================================
	// Declarations
	//===========================================================================
	
	//==========
	// Constants
	//==========

	inline const Vector4 Zero4();
	inline const Vector4 Ones4();
	inline const Vector4 W();
	inline const Vector4 X();
	inline const Vector4 Y();
	inline const Vector4 Z();

	//==========
	// Operators
	//==========

	//cross product 3D
	inline Vector4& operator *=(Vector4& p_Lhs, const Vector4& p_Rhs);
	inline const Vector4 operator *(const Vector4& p_Lhs, const Vector4& p_Rhs);

	//==========
	// Functions
	//==========

	//construction
	inline const Vector4 MakeVector(const scalar p_X, const scalar p_Y, const scalar p_Z, const scalar p_W);
	inline const Vector4 MakeRandomVector4(const scalar p_Min, const scalar p_Max);

	//===========================================================================
	// Constant Definitions
	//===========================================================================

	inline const Vector4 Zero4()
	{
		return Vector4(Zero);
	}

	//---------------------------------------------------------------------------

	inline const Vector4 Ones4()
	{
		return Vector4(Unity);
	}

	//---------------------------------------------------------------------------

	inline const Vector4 W()
	{
		return MakeVector(Zero, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Vector4 X()
	{
		return MakeVector(Unity, Zero, Zero, Zero);
	}

	//---------------------------------------------------------------------------

	inline const Vector4 Y()
	{
		return MakeVector(Zero, Unity, Zero, Zero);
	}

	//---------------------------------------------------------------------------

	inline const Vector4 Z()
	{
		return MakeVector(Zero, Zero, Unity, Zero);
	}

	//===========================================================================
	// Operator Definitions
	//===========================================================================

	inline Vector4& operator *=(Vector4& p_Lhs, const Vector4& p_Rhs)
	{
		Assert(p_Lhs.IsAffineVector() && p_Rhs.IsAffineVector(), "Not valid for cross product!");

		const scalar crossX = p_Lhs(1) * p_Rhs(2) - p_Lhs(2) * p_Rhs(1);
		const scalar crossY = p_Lhs(2) * p_Rhs(0) - p_Lhs(0) * p_Rhs(2);
		const scalar crossZ = p_Lhs(0) * p_Rhs(1) - p_Lhs(1) * p_Rhs(0);

		p_Lhs(0) = crossX;
		p_Lhs(1) = crossY;
		p_Lhs(2) = crossZ;
		p_Lhs(3) = Zero;

		return p_Lhs;
	}

	//---------------------------------------------------------------------------

	inline const Vector4 operator *(const Vector4& p_Lhs, const Vector4& p_Rhs)
	{
		const scalar crossX = p_Lhs(1) * p_Rhs(2) - p_Lhs(2) * p_Rhs(1);
		const scalar crossY = p_Lhs(2) * p_Rhs(0) - p_Lhs(0) * p_Rhs(2);
		const scalar crossZ = p_Lhs(0) * p_Rhs(1) - p_Lhs(1) * p_Rhs(0);

		return MakeVector(crossX, crossY, crossZ, Zero);
	}


	//===========================================================================
	// Function Definitions
	//===========================================================================
	
	inline const Vector4 MakeVector(const scalar p_X, const scalar p_Y, const scalar p_Z, const scalar p_W)
	{
		Vector4 temp;
		temp(0) = p_X;
		temp(1) = p_Y;
		temp(2) = p_Z;
		temp(3) = p_W;
		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Vector4 MakeRandomVector4(const scalar p_Min, const scalar p_Max)
	{
		return MakeVector(MakeRandomScalar(p_Min, p_Max)
			, MakeRandomScalar(p_Min, p_Max)
			, MakeRandomScalar(p_Min, p_Max)
			, MakeRandomScalar(p_Min, p_Max));
	}
}