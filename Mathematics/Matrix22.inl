//===========================================================================
// Filename:	Matrix22.inl
// Author:		Jarrod MacKay
//===========================================================================

namespace Mathematics
{
	//===========================================================================
	// Constant Declarations
	//===========================================================================

	inline const Matrix22 Zero22();
	inline const Matrix22 I2();

	//===========================================================================
	// Operator Declarations
	//===========================================================================

	//===========================================================================
	// Function Declarations
	//===========================================================================

	inline const Matrix22 MakeMatrix(const scalar p_r0c0, const scalar p_r0c1
								   , const scalar p_r1c0, const scalar p_r1c1);

	inline const Matrix22 MakeMatrix(const Vector2& p_Column0, const Vector2& p_Column1);

	inline const Matrix22 MakeRandomMatrix22(const scalar p_Min, const scalar p_Max);

	//===========================================================================
	// Constant Definitions
	//===========================================================================

	inline const Matrix22 Zero22()
	{
		return Matrix22(Zero);
	}

	//---------------------------------------------------------------------------

	inline const Matrix22 I2()
	{
		return MakeMatrix(U(), V());
	}

	//===========================================================================
	// Operator Definitions
	//===========================================================================

	//===========================================================================
	// Function Definitions
	//===========================================================================

	inline const Matrix22 MakeMatrix(
		const scalar p_r0c0, const scalar p_r0c1
		, const scalar p_r1c0, const scalar p_r1c1)
	{
		Matrix22 temp;

		//first column
		temp(0, 0) = p_r0c0;
		temp(1, 0) = p_r1c0;

		//second column
		temp(0, 1) = p_r0c1;
		temp(1, 1) = p_r1c1;

		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Matrix22 MakeMatrix(const Vector2& p_Column0
		, const Vector2& p_Column1)
	{
		Matrix22 temp;

		//first column
		temp(0, 0) = p_Column0(0);
		temp(1, 0) = p_Column0(1);

		//second column
		temp(0, 1) = p_Column1(0);
		temp(1, 1) = p_Column1(1);

		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Matrix22 MakeRandomMatrix22(const scalar p_Min, const scalar p_Max)
	{
		return MakeMatrix(MakeRandomVector2(p_Min, p_Max)
			, MakeRandomVector2(p_Min, p_Max));
	}
}