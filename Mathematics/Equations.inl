//===========================================================================
// Filename:	Equations.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Interpolation Definitions
//===========================================================================

template <u32 t_Rows>
inline const RealVector<t_Rows> InterpolateLinearly(const RealVector<t_Rows>& p_A, const RealVector<t_Rows>& p_B, const scalar p_Ratio)
{
	return p_A + ((p_B - p_A) * p_Ratio);
}

//---------------------------------------------------------------------------

template <u32 t_Rows>
inline const RealVector<t_Rows> Lerp(const RealVector<t_Rows>& p_A, const RealVector<t_Rows>& p_B, const scalar p_Ratio)
{
	return ::InterpolateLinearly<t_Rows>(p_A, p_B, p_Ratio);
}

//===========================================================================
// Solving Definitions
//===========================================================================

template <u32 t_Dimensions>
bool SolveLinearSystem(const Matrix<t_Dimensions, t_Dimensions>& p_Coefficients, const RealVector<t_Dimensions>& p_Constant, RealVector<t_Dimensions>& p_Solution)
{
	MatrixDecomposition<t_Dimensions> decomp(p_Coefficients);
	if (decomp.IsSingular())
	{
		return false;
	}

	decomp.Solve(p_Constant, p_Solution);
	return true;
}

template <u32 t_Dimensions, u32 t_Sets>
bool SolveLinearSystems(const Matrix<t_Dimensions, t_Dimensions>& p_Coefficients, const Matrix<t_Dimensions, t_Sets>& p_Constants, Matrix<t_Dimensions, t_Sets>& p_Solutions)
{
	MatrixDecomposition<t_Dimensions> decomp(p_Coefficients);
	if (decomp.IsSingular())
	{
		return false;
	}

	decomp.Solve(p_Constants, p_Solutions);
	return true;
}