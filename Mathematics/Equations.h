#ifndef IncludedMathEquationsH
#define IncludedMathEquationsH

//===========================================================================
// Filename:	Equations.h
// Author:		Jarrod MacKay
// Description:	Contains useful equation manipulators
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Polynomial.h"

namespace Mathematics
{
	//===========================================================================
	// Interpolation Definitions
	//===========================================================================

	template <u32 t_Rows>
	inline const RealVector<t_Rows> InterpolateLinearly(const RealVector<t_Rows>& p_A, const RealVector<t_Rows>& p_B, const scalar p_Ratio);

	template <u32 t_Rows>
	inline const RealVector<t_Rows> Lerp(const RealVector<t_Rows>& p_A, const RealVector<t_Rows>& p_B, const scalar p_Ratio);

	const Quaternion InterpolateSpherically(const Quaternion& p_A, const Quaternion& p_B, const scalar p_Ratio);

	const Quaternion Slerp(const Quaternion& p_A, const Quaternion& p_B, const scalar p_Ratio);

	//===========================================================================
	// Solving Definitions
	//===========================================================================

	const Quadratic EigenPolynomial(const Matrix22&& p_Matrix);

	const Cubic EigenPolynomial(const Matrix33&& p_Matrix);

	template <u32 t_Dimensions>
	bool SolveLinearSystem(const Matrix<t_Dimensions, t_Dimensions>& p_Coefficients, const RealVector<t_Dimensions>& p_Constant, RealVector<t_Dimensions>& p_Solution);

	template <u32 t_Dimensions, u32 t_Sets>
	bool SolveLinearSystems(const Matrix<t_Dimensions, t_Dimensions>& p_Coefficients, const Matrix<t_Dimensions, t_Sets>& p_Constants, Matrix<t_Dimensions, t_Sets>& p_Solutions);

	void SolvePolynomialRoot(const Linear& p_Polynomial, scalar& p_Solution);

	void SolvePolynomialRoot(const Quadratic& p_Polynomial, ComplexPair& p_Solution);

	void SolvePolynomialRoot(const Cubic& p_Polynomial, scalar& p_Solution, ComplexPair& p_SolutionPair);

	bool EigendecompositionSymmetric(const Matrix33& p_Matrix
		, Vector3& p_Eigenvalues, Matrix33& p_Eigenvectors);

	//===========================================================================
	// Definitions
	//===========================================================================
	
	using OneVarFxn = std::function<const scalar(const scalar)>; 
	using TwoVarFxn = std::function<const scalar(const scalar, const scalar)>; 
	using ThreeVarFxn = std::function<const scalar(const scalar, const scalar, const scalar)>; 
	
	using OneVarFld = std::function<const Vector3(const scalar)>; 
	using TwoVarFld = std::function<const Vector3(const scalar, const scalar)>; 
	using ThreeVarFld = std::function<const Vector3(const scalar, const scalar, const scalar)>;

#include "Equations.inl"
}

#endif //#ifndef IncludedMathEquationsH