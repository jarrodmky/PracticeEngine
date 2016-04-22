//===========================================================================
// Filename:	Equations.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Equations.h"

using namespace Mathematics;

//===========================================================================
// Interpolation Definitions
//===========================================================================

const Quaternion InterpolateSpherically(const Quaternion& p_A, const Quaternion& p_B, const scalar p_Ratio)
{
	const scalar dot = p_A | p_B;
	const scalar s = std::sin(std::sqrt(Unity - dot * dot));
	const scalar t = std::acos(dot);
	const scalar a = std::sin(t * (Unity - p_Ratio)) / s;
	const scalar b = std::sin(t * p_Ratio) / s;
	return a * p_A + b * p_B;
}

//---------------------------------------------------------------------------

const Quaternion Slerp(const Quaternion& p_A, const Quaternion& p_B, const scalar p_Ratio)
{
	return ::InterpolateSpherically(p_A, p_B, p_Ratio);
}

//===========================================================================
// Solving Definitions
//===========================================================================

const Quadratic EigenPolynomial(const Matrix22&& p_Matrix)
{
	return MakePolynomial(Unity, -p_Matrix.Trace(), p_Matrix.Determinant());
}

const Cubic EigenPolynomial(const Matrix33&& p_Matrix)
{
	const scalar T = p_Matrix.Trace();
	const Matrix33 A2 = p_Matrix * p_Matrix;
	return MakePolynomial(Unity, -T, 0.5f * (T*T - A2.Trace()), -p_Matrix.Determinant());
}

void SolvePolynomialRoot(const Linear& p_Polynomial, scalar& p_Solution)
{
	const Linear& P(p_Polynomial);

	//for ax + b = 0
	//	a = 0 => b = 0, any x if b = 0, no x otherwise
	//	a <> 0 => x = -b/a

	p_Solution = (P.IsDegenerate()) ? (IsZero(P.Coefficient(0)) ? (Zero) : (NotANumber)) : (-p_Polynomial.Coefficient(0) / p_Polynomial.Coefficient(1));
}

void SolvePolynomialRoot(const Quadratic& p_Polynomial, ComplexPair& p_Solution)
{
	Quadratic P(p_Polynomial);
	if (P.IsDegenerate())
	{
		const Linear L(MakeVector(P.Coefficient(0), P.Coefficient(1)));
		scalar root;

		::SolvePolynomialRoot(L, root);
		p_Solution.first = root;
		p_Solution.second = NotANumber;

		return;
	}

	//for ax^2 + bx + c = 0
	//	a = 0 => linear case, only one root possible
	//	a <> 0 => x = c +/- r; c = -b/2a; r = rt(D)/2a; D = bb - 4ac
	//		D < 0 => roots are complex
	//		D >= 0 =? roots are real

	P.Normalize();

	const scalar D = P.Coefficient(1) * P.Coefficient(1) - 4.0f * P.Coefficient(0);
	const scalar centre = -P.Coefficient(1) * 0.5f;
	const scalar radius = std::sqrt(AbsoluteValue(D)) * 0.5f;

	p_Solution.first = (D < Zero) ? (complex(centre, -radius)) : (centre - radius);
	p_Solution.second = (D < Zero) ? (complex(centre, radius)) : (centre + radius);
};

void SolvePolynomialRoot(const Cubic& p_Polynomial, scalar& p_Solution, ComplexPair& p_SolutionPair)
{
	Cubic P(p_Polynomial);
	if (P.IsDegenerate())
	{
		const Quadratic Q(MakeVector(P.Coefficient(0), P.Coefficient(1), P.Coefficient(2)));
		ComplexPair roots;

		::SolvePolynomialRoot(Q, roots);
		p_SolutionPair.first = roots.first;
		p_SolutionPair.second = roots.second;
		p_Solution = NotANumber;

		return;
	}

	//for ax^3 + bx^2 + cx + d = 0
	//	a = 0 => quadratic case, only two roots possible
	//	a <> 0 
	//		=>	x1 = r + s - b/3a
	//			x2 = rU + sU^2 - b/3a
	//			x3 = rU^2 + sU - b/3a
	//		U = e^i(1/3)
	//		r = cubrt(-q + sqrt(D))
	//		s = cubrt(-q - sqrt(D))
	//		D = p^3 + q^2
	//		p = -(1/9)(b/a)^2 + (1/3)(c/a)
	//		q = (1/27)(b/a)^3 -(1/6)(bc/a^2) + (1/2)(d/a)
	//		
	//		D < 0 => One real root
	//		D >= 0 => Three real roots

	P.Normalize();

	const scalar Third(1.0f / 3.0f);
	const scalar& B(P.Coefficient(2));
	const scalar B3rd(Third*B);
	const scalar& C(P.Coefficient(1));

	const scalar p = -(B3rd * B3rd) + Third * C;
	const scalar q = (B3rd * B3rd * B3rd)
		- Third * 0.5f * B * C
		+ 0.5f * P.Coefficient(0);
	const scalar D = p * p * p + q * q;
	const complex r = std::cbrt(-q + std::sqrt(D));
	const complex s = std::cbrt(-q - std::sqrt(D));
	const complex U = RootOfUnity(1, 3);
	const complex U2 = RootOfUnity(2, 3);

	Assert(IsZero((r + s).imag()), "Real root DNE!");
	p_Solution = (r + s).real() - B3rd;
	p_SolutionPair.first = r*U + s*U2 - B3rd;
	p_SolutionPair.second = r*U2 + s*U - B3rd;
}

bool EigendecompositionSymmetric(const Matrix33& p_Matrix
						, Vector3& p_Eigenvalues, Matrix33& p_Eigenvectors)
{
	SymmetricEigendecomposition<3> symeig(p_Matrix);
	symeig.Eigenvalues(p_Eigenvalues);
	symeig.Eigenvectors(p_Eigenvectors);
	return true;
}