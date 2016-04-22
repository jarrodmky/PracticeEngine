//===========================================================================
// Filename:	Matrix33.inl
// Author:		Jarrod MacKay
//===========================================================================

namespace Mathematics
{
	//===========================================================================
	// Constant Declarations
	//===========================================================================
	
	inline const Matrix44 Zero44();
	inline const Matrix44 I4();

	//===========================================================================
	// Operator Declarations
	//===========================================================================

	//===========================================================================
	// Function Declarations
	//===========================================================================

	inline const Matrix44 MakeMatrix(
		const scalar p_r0c0, const scalar p_r0c1, const scalar p_r0c2, const scalar p_r0c3
		, const scalar p_r1c0, const scalar p_r1c1, const scalar p_r1c2, const scalar p_r1c3
		, const scalar p_r2c0, const scalar p_r2c1, const scalar p_r2c2, const scalar p_r2c3
		, const scalar p_r3c0, const scalar p_r3c1, const scalar p_r3c2, const scalar p_r3c3);

	inline const Matrix44 MakeMatrix(const Vector4& p_Column0
		, const Vector4& p_Column1
		, const Vector4& p_Column2
		, const Vector4& p_Column3);

	inline const Matrix44 MakeMatrix(const Matrix33& p_Matrix);

	inline const Matrix44 MakeRandomMatrix44(const scalar p_Min, const scalar p_Max);

	//===========================================================================
	// Constant Definitions
	//===========================================================================

	inline const Matrix44 Zero44()
	{
		return Matrix44(Zero);
	}

	inline const Matrix44 I4()
	{
		return MakeMatrix(X(), Y(), Z(), W());
	}

	//===========================================================================
	// Operator Definitions
	//===========================================================================

	//===========================================================================
	// Function Definitions
	//===========================================================================

	inline const Matrix44 MakeMatrix(
		const scalar p_r0c0, const scalar p_r0c1, const scalar p_r0c2, const scalar p_r0c3
		, const scalar p_r1c0, const scalar p_r1c1, const scalar p_r1c2, const scalar p_r1c3
		, const scalar p_r2c0, const scalar p_r2c1, const scalar p_r2c2, const scalar p_r2c3
		, const scalar p_r3c0, const scalar p_r3c1, const scalar p_r3c2, const scalar p_r3c3)
	{
		Matrix44 temp;

		//first column
		temp(0, 0) = p_r0c0;
		temp(1, 0) = p_r1c0;
		temp(2, 0) = p_r2c0;
		temp(3, 0) = p_r3c0;

		//second column
		temp(0, 1) = p_r0c1;
		temp(1, 1) = p_r1c1;
		temp(2, 1) = p_r2c1;
		temp(3, 1) = p_r3c1;

		//third column
		temp(0, 2) = p_r0c2;
		temp(1, 2) = p_r1c2;
		temp(2, 2) = p_r2c2;
		temp(3, 2) = p_r3c2;

		//fourth column
		temp(0, 3) = p_r0c3;
		temp(1, 3) = p_r1c3;
		temp(2, 3) = p_r2c3;
		temp(3, 3) = p_r3c3;

		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeMatrix(const Vector4& p_Column0
		, const Vector4& p_Column1
		, const Vector4& p_Column2
		, const Vector4& p_Column3)
	{
		Matrix44 temp;

		//first column
		temp(0, 0) = p_Column0(0);
		temp(1, 0) = p_Column0(1);
		temp(2, 0) = p_Column0(2);
		temp(3, 0) = p_Column0(3);

		//second column
		temp(0, 1) = p_Column1(0);
		temp(1, 1) = p_Column1(1);
		temp(2, 1) = p_Column1(2);
		temp(3, 1) = p_Column1(3);

		//third column
		temp(0, 2) = p_Column2(0);
		temp(1, 2) = p_Column2(1);
		temp(2, 2) = p_Column2(2);
		temp(3, 2) = p_Column2(3);

		//fourth column
		temp(0, 3) = p_Column3(0);
		temp(1, 3) = p_Column3(1);
		temp(2, 3) = p_Column3(2);
		temp(3, 3) = p_Column3(3);

		return temp;
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeMatrix(const Matrix33& p_SubMatrix)
	{
		//copy in matrix
		return MakeMatrix
			(MakeAffineVector(p_SubMatrix.Column(0))
			, MakeAffineVector(p_SubMatrix.Column(1))
			, MakeAffineVector(p_SubMatrix.Column(2))
			, W());
	}

	//---------------------------------------------------------------------------

	inline const Matrix44 MakeRandomMatrix44(const scalar p_Min, const scalar p_Max)
	{
		return MakeMatrix(MakeRandomVector4(p_Min, p_Max)
			, MakeRandomVector4(p_Min, p_Max)
			, MakeRandomVector4(p_Min, p_Max)
			, MakeRandomVector4(p_Min, p_Max));
	}
}