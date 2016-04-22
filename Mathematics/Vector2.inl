//===========================================================================
// Filename:	Vector2.inl
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

	inline const Vector2 Zero2();
	inline const Vector2 Ones2();
	inline const Vector2 U();
	inline const Vector2 V();

	//==========
	// Operators
	//==========

	//cross product 2D
	inline const scalar operator *(const Vector2& p_Lhs, const Vector2& p_Rhs);

	//==========
	// Functions
	//==========

	//construction
	inline const Vector2 MakeVector(const scalar p_X, const scalar p_Y);
	inline const Vector2 MakeRandomVector2(const scalar p_Min, const scalar p_Max);

	//geometry
	inline const Vector2 LeftHandPerpendicular(const Vector2& p_Vector);
	inline const Vector2 RightHandPerpendicular(const Vector2& p_Vector);
	inline const scalar Orientation(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C);
	inline const bool CounterClockwise(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C);
	inline const bool Clockwise(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C);

	inline const bool Parallel(const Vector2& p_A, const Vector2& p_B);
	inline const bool Antiparallel(const Vector2& p_A, const Vector2& p_B);
	
	inline const scalar SignedTriangularArea(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C);
	inline const scalar TriangularArea(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C);

	//===========================================================================
	// Constant Definitions
	//===========================================================================

	inline const Vector2 Zero2()
	{
		return Vector2(Zero);
	}

	//---------------------------------------------------------------------------

	inline const Vector2 Ones2()
	{
		return Vector2(Unity);
	}

	//---------------------------------------------------------------------------

	inline const Vector2 U()
	{
		return MakeVector(Unity, Zero);
	}

	//---------------------------------------------------------------------------

	inline const Vector2 V()
	{
		return MakeVector(Zero, Unity);
	}

	//===========================================================================
	// Operator Definitions
	//===========================================================================

	inline const scalar operator *(const Vector2& p_Lhs, const Vector2& p_Rhs)
	{
		return p_Lhs(0) * p_Rhs(1) - p_Lhs(1) * p_Rhs(0);
	}

	//===========================================================================
	// Function Definitions
	//===========================================================================

	inline const Vector2 MakeVector(const scalar p_X, const scalar p_Y)
	{
		Vector2 temp;
		temp(0) = p_X;
		temp(1) = p_Y;
		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Vector2 MakeRandomVector2(const scalar p_Min, const scalar p_Max)
	{
		return MakeVector(MakeRandomScalar(p_Min, p_Max)
			, MakeRandomScalar(p_Min, p_Max));
	}

	//---------------------------------------------------------------------------

	inline const Vector2 LeftHandPerpendicular(const Vector2& p_Vector)
	{
		return MakeVector(-p_Vector(1), p_Vector(0));
	}

	//---------------------------------------------------------------------------

	inline const Vector2 RightHandPerpendicular(const Vector2& p_Vector)
	{
		return -LeftHandPerpendicular(p_Vector);
	}

	//---------------------------------------------------------------------------

	inline const scalar Orientation(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C)
	{
		return (p_A - p_C) * (p_B - p_C);
	}

	//---------------------------------------------------------------------------

	inline const bool CounterClockwise(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C)
	{
		return Orientation(p_A, p_B, p_C) > Zero;
	}

	//---------------------------------------------------------------------------

	inline const bool Clockwise(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C)
	{
		return Orientation(p_A, p_B, p_C) < Zero;
	}

	//---------------------------------------------------------------------------

	inline const bool Parallel(const Vector2& p_A, const Vector2& p_B)
	{
		return IsZero(p_A * p_B);
	}

	//---------------------------------------------------------------------------

	inline const bool Antiparallel(const Vector2& p_A, const Vector2& p_B)
	{
		return Parallel(p_A, p_B) && ((p_A + p_B).LengthSquared() < (p_A - p_B).LengthSquared());
	}

	//---------------------------------------------------------------------------

	inline const scalar SignedTriangularArea(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C)
	{
		return Orientation(p_A, p_B, p_C) * 0.5f;
	}

	//---------------------------------------------------------------------------

	inline const scalar TriangularArea(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C)
	{
		return AbsoluteValue(TriangularArea(p_A, p_B, p_C));
	}
}