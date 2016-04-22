//===========================================================================
// Filename:	Matrix33.inl
// Author:		Jarrod MacKay
//===========================================================================

namespace Mathematics
{
	//===========================================================================
	// Constant Declarations
	//===========================================================================

	inline const Matrix33 Zero33();
	inline const Matrix33 I3();

	//===========================================================================
	// Operator Declarations
	//===========================================================================

	//===========================================================================
	// Function Declarations
	//===========================================================================

	//construction
	inline const Matrix33 MakeMatrix(
		const scalar p_r0c0, const scalar p_r0c1, const scalar p_r0c2
		, const scalar p_r1c0, const scalar p_r1c1, const scalar p_r1c2
		, const scalar p_r2c0, const scalar p_r2c1, const scalar p_r2c2);

	inline const Matrix33 MakeMatrix(const Vector3& p_Column0, const Vector3& p_Column1, const Vector3& p_Column2);

	inline const Matrix33 MakeMatrix(const Matrix22& p_Submatrix);

	inline const Matrix33 MakeRandomMatrix33(const scalar p_Min, const scalar p_Max);

	inline const Matrix33 Skew(const Vector3& p_Vector);

	//===========================================================================
	// Constant Definitions
	//===========================================================================

	inline const Matrix33 Zero33()
	{
		return Matrix33(Zero);
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 I3()
	{
		return MakeMatrix(I(), J(), K());
	}

	//===========================================================================
	// Operator Definitions
	//===========================================================================

	//===========================================================================
	// Function Definitions
	//===========================================================================

	inline const Matrix33 MakeMatrix(
		const scalar p_r0c0, const scalar p_r0c1, const scalar p_r0c2
		, const scalar p_r1c0, const scalar p_r1c1, const scalar p_r1c2
		, const scalar p_r2c0, const scalar p_r2c1, const scalar p_r2c2)
	{
		Matrix33 temp;

		//first column
		temp(0, 0) = p_r0c0;
		temp(1, 0) = p_r1c0;
		temp(2, 0) = p_r2c0;

		//second column
		temp(0, 1) = p_r0c1;
		temp(1, 1) = p_r1c1;
		temp(2, 1) = p_r2c1;

		//third column
		temp(0, 2) = p_r0c2;
		temp(1, 2) = p_r1c2;
		temp(2, 2) = p_r2c2;

		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 MakeMatrix(const Vector3& p_Column0, const Vector3& p_Column1, const Vector3& p_Column2)
	{
		Matrix33 temp;

		//first column
		temp(0, 0) = p_Column0(0);
		temp(1, 0) = p_Column0(1);
		temp(2, 0) = p_Column0(2);

		//second column
		temp(0, 1) = p_Column1(0);
		temp(1, 1) = p_Column1(1);
		temp(2, 1) = p_Column1(2);

		//third column
		temp(0, 2) = p_Column2(0);
		temp(1, 2) = p_Column2(1);
		temp(2, 2) = p_Column2(2);

		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 MakeMatrix(const Matrix22& p_Submatrix)
	{
		return MakeMatrix(p_Submatrix(0, 0), p_Submatrix(0, 1), Zero
			, p_Submatrix(1, 0), p_Submatrix(1, 1), Zero
			, Zero, Zero, Unity);
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 MakeRandomMatrix33(const scalar p_Min, const scalar p_Max)
	{
		return MakeMatrix(MakeRandomVector3(p_Min, p_Max)
			, MakeRandomVector3(p_Min, p_Max)
			, MakeRandomVector3(p_Min, p_Max));
	}

	//---------------------------------------------------------------------------

	inline const Matrix33 Skew(const Vector3& p_Vector)
	{
		return MakeMatrix(Zero, -p_Vector(2), p_Vector(1)
			, p_Vector(2), Zero, -p_Vector(0)
			, -p_Vector(1), p_Vector(0), Zero);
	}
}