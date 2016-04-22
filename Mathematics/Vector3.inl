//===========================================================================
// Filename:	Vector3.inl
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
	
	inline const Vector3 Zero3();
	inline const Vector3 Ones3();
	inline const Vector3 I();
	inline const Vector3 J();
	inline const Vector3 K();

	//==========
	// Operators
	//==========

	//cross product 3D
	inline Vector3& operator *=(Vector3& p_Lhs, const Vector3& p_Rhs);
	inline const Vector3 operator *(const Vector3& p_Lhs, const Vector3& p_Rhs);

	//==========
	// Functions
	//==========

	//construction
	inline const Vector3 MakeVector(const scalar p_X, const scalar p_Y, const scalar p_Z);
	inline const Vector3 MakeRandomVector3(const scalar p_Min, const scalar p_Max);

	//special products
	inline const scalar ScalarTripleProduct(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C);
	inline const Vector3 VectorTripleProduct(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C);
	
	//geometry
	inline const scalar Orientation(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D);
	inline const bool CounterClockwise(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_ViewFrom);
	inline const bool Clockwise(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_ViewFrom);

	inline const bool Parallel(const Vector3& p_A, const Vector3& p_B);
	inline const bool Antiparallel(const Vector3& p_A, const Vector3& p_B);
	inline const bool Spanning(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C);

	inline const bool LeftHanded(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C);
	inline const bool RightHanded(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C);

	inline const scalar TriangularArea(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C);
	inline const scalar SignedTetrahedralVolume(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D);
	inline const scalar TetrahedralVolume(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D);

	//===========================================================================
	// Constant Definitions
	//===========================================================================

	inline const Vector3 Zero3()
	{
		return Vector3(Zero);
	}

	//---------------------------------------------------------------------------

	inline const Vector3 Ones3()
	{
		return Vector3(Unity);
	}

	//---------------------------------------------------------------------------

	inline const Vector3 I()
	{
		return MakeVector(Unity, Zero, Zero);
	}

	//---------------------------------------------------------------------------

	inline const Vector3 J()
	{
		return MakeVector(Zero, Unity, Zero);
	}

	//---------------------------------------------------------------------------

	inline const Vector3 K()
	{
		return MakeVector(Zero, Zero, Unity);
	}

	//===========================================================================
	// Operator Definitions
	//===========================================================================

	inline Vector3& operator *=(Vector3& p_Lhs, const Vector3& p_Rhs)
	{
		const scalar crossX = p_Lhs(1) * p_Rhs(2) - p_Lhs(2) * p_Rhs(1);
		const scalar crossY = p_Lhs(2) * p_Rhs(0) - p_Lhs(0) * p_Rhs(2);
		const scalar crossZ = p_Lhs(0) * p_Rhs(1) - p_Lhs(1) * p_Rhs(0);

		p_Lhs(0) = crossX;
		p_Lhs(1) = crossY;
		p_Lhs(2) = crossZ;

		return p_Lhs;
	}

	//---------------------------------------------------------------------------

	inline const Vector3 operator *(const Vector3& p_Lhs, const Vector3& p_Rhs)
	{
		const scalar crossX = p_Lhs(1) * p_Rhs(2) - p_Lhs(2) * p_Rhs(1);
		const scalar crossY = p_Lhs(2) * p_Rhs(0) - p_Lhs(0) * p_Rhs(2);
		const scalar crossZ = p_Lhs(0) * p_Rhs(1) - p_Lhs(1) * p_Rhs(0);

		return MakeVector(crossX, crossY, crossZ);
	}

	//===========================================================================
	// Function Definitions
	//===========================================================================

	inline const Vector3 MakeVector(const scalar p_X, const scalar p_Y, const scalar p_Z)
	{
		Vector3 temp;
		temp(0) = p_X;
		temp(1) = p_Y;
		temp(2) = p_Z;
		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Vector3 MakeRandomVector3(const scalar p_Min, const scalar p_Max)
	{
		return MakeVector(MakeRandomScalar(p_Min, p_Max)
			, MakeRandomScalar(p_Min, p_Max)
			, MakeRandomScalar(p_Min, p_Max));
	}

	//---------------------------------------------------------------------------

	inline const scalar ScalarTripleProduct(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C)
	{
		return (p_A | (p_B * p_C));
	}

	//---------------------------------------------------------------------------
	
	inline const Vector3 VectorTripleProduct(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C)
	{
		return (p_A * (p_B * p_C));
	}

	//---------------------------------------------------------------------------
	
	inline const scalar Orientation(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D)
	{
		return ScalarTripleProduct(p_A - p_D, p_B - p_D, p_C - p_D);
	}

	//---------------------------------------------------------------------------

	inline const bool CounterClockwise(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_ViewFrom)
	{
		return Orientation(p_A, p_B, p_C, p_ViewFrom) < Zero;
	}

	//---------------------------------------------------------------------------

	inline const bool Clockwise(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_ViewFrom)
	{
		return Orientation(p_A, p_B, p_C, p_ViewFrom) > Zero;
	}

	//---------------------------------------------------------------------------

	inline const bool Parallel(const Vector3& p_A, const Vector3& p_B)
	{
		return (p_A * p_B).IsAtOrigin();
	}

	//---------------------------------------------------------------------------

	inline const bool Antiparallel(const Vector3& p_A, const Vector3& p_B)
	{
		return Parallel(p_A, p_B) && ((p_A + p_B).LengthSquared() < (p_A - p_B).LengthSquared());
	}

	//---------------------------------------------------------------------------

	inline const bool Spanning(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C)
	{
		return !IsZero(ScalarTripleProduct(p_A, p_B, p_C));
	}

	//---------------------------------------------------------------------------

	inline const bool LeftHanded(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C)
	{
		return ScalarTripleProduct(p_A, p_B, p_C) < Zero;
	}

	//---------------------------------------------------------------------------

	inline const bool RightHanded(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C)
	{
		return ScalarTripleProduct(p_A, p_B, p_C) > Zero;
	}

	//---------------------------------------------------------------------------

	inline const scalar TriangularArea(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C)
	{
		return ((p_A - p_C) * (p_B - p_C)).Length() * 0.5f;
	}

	//---------------------------------------------------------------------------

	inline const scalar SignedTetrahedralVolume(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D)
	{
		return Orientation(p_A, p_B, p_C, p_D) * 0.16666666666666667f;
	}

	//---------------------------------------------------------------------------

	inline const scalar TetrahedralVolume(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D)
	{
		return AbsoluteValue(TetrahedralVolume(p_A, p_B, p_C, p_D));
	}
}