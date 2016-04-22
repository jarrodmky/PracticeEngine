#ifndef IncludedMathPolynomialH
#define IncludedMathPolynomialH

//===========================================================================
// Filename:	Polynomial.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a Polynomial of max degree
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include "Vector.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	template <u8 t_MaxDegree>
	class Polynomial
	{
	//Definitions
	private:

		typedef RealVector<t_MaxDegree + 1> CoefficientVector;

	//Attributes
	private:

		CoefficientVector m_Coefs;

	//Operators
	public:

		explicit Polynomial()
			: m_Coefs(Zero)
		{}

		explicit Polynomial(const CoefficientVector& p_Coefficients)
			: m_Coefs(p_Coefficients)
		{
			Assert(!IsDegenerate(), "Invalid polynomial intialization!");
		}

		//addition
		Polynomial<t_MaxDegree>& operator += (const Polynomial<t_MaxDegree>& p_Rhs)
		{
			m_Coefs += p_Rhs.m_Coefs;
		}

		const Polynomial<t_MaxDegree> operator + (const Polynomial<t_MaxDegree>& p_Rhs) const
		{
			return Polynomial(*this) += p_Rhs;
		}

		//subtraction
		Polynomial<t_MaxDegree>& operator -= (const Polynomial<t_MaxDegree>& p_Rhs)
		{
			m_Coefs -= p_Rhs.m_Coefs;
		}

		const Polynomial<t_MaxDegree> operator - (const Polynomial<t_MaxDegree>& p_Rhs) const
		{
			return Polynomial(*this) -= p_Rhs;
		}

		//multiplication
		const Polynomial<t_MaxDegree + t_MaxDegree> operator *(const Polynomial<t_MaxDegree>& p_Rhs) const
		{
			Polynomial<t_MaxDegree + t_MaxDegree> product;
			for (u8 i = 0; i <= t_MaxDegree; ++i)
			{
				for (u8 j = 0; j <= t_MaxDegree; ++j)
				{
					product.Coefficient(i + j) += Coefficient(i) * p_Rhs.Coefficient(j);
				}
			}
			return product;
		}
		
		//evaluation
		const scalar operator() (const scalar p_Value) const
		{
			return (m_Coefs | IndeterminantVector(p_Value));
		}

	//Methods
	public:

		void Normalize()
		{
			Assert(!IsDegenerate(), "Can only normalize with non-zero leading term!");
			m_Coefs /= LeadCoefficient();
			Assert(IsEqualTo(LeadCoefficient(), Unity), "Normalization failed");
		}

		const Polynomial<t_MaxDegree - 1> Derivative() const
		{
			Polynomial<t_MaxDegree - 1> dp;

			for (u32 i = 1; i < t_MaxDegree; ++i)
			{
				dp.Coefficient(i - 1) = static_cast<scalar>(i) * Coefficient(i);
			}

			return dp;
		}

		const Polynomial<t_MaxDegree + 1> Antiderivative(const scalar p_Constant) const
		{
			Polynomial<t_MaxDegree + 1> P;

			for (u32 i = 0; i < t_MaxDegree; ++i)
			{
				P.Coefficient(i + 1) = (static_cast<scalar>(Inverse(i+1))) * Coefficient(i);
			}

			return P;
		}

		scalar& Coefficient(u32 p_TermExponent)
		{
			return m_Coefs(p_TermExponent);
		}

		inline const scalar Coefficient(u32 p_TermExponent) const
		{
			return m_Coefs(p_TermExponent);
		}

		inline const scalar LeadCoefficient() const
		{
			return m_Coefs(t_MaxDegree);
		}

		inline const scalar Constant() const
		{
			return m_Coefs(0);
		}

		inline const CoefficientVector Coefficients() const
		{
			return m_Coefs;
		}

		inline const u32 MaximumDegree() const
		{
			return t_MaxDegree;
		}

		const bool IsZeroPolynomial() const
		{
			return t_MaxDegree == 0 && IsZero(Constant());
		}

		const bool IsDegenerate() const
		{
			return IsZero(LeadCoefficient());
		}

		const bool HasTrivialRoot() const
		{
			return IsZero(LeadCoefficient());
		}

	private:

		inline const CoefficientVector IndeterminantVector(const scalar p_Value) const
		{
			CoefficientVector mask(p_Value);
			CoefficientVector ind(Unity);
			for (u32 i = 0; i < t_MaxDegree; ++i)
			{
				mask(i) = Unity;
				ind %= mask;
			}
			return ind;
		}
	};

	//==========
	// Operators
	//==========

	//multiplication
	template <u8 t_LhsMaxDegree, u8 t_RhsMaxDegree>
	const bool operator ==(const Polynomial<t_LhsMaxDegree>& p_Lhs, const Polynomial<t_RhsMaxDegree>& p_Rhs)
	{
		const bool rightIsBigger = t_LhsMaxDegree < t_RhsMaxDegree;
		const u8 extraTerms = (rightIsBigger) ? (t_RhsMaxDegree - t_LhsMaxDegree) : (t_LhsMaxDegree - t_RhsMaxDegree);
		const u8 smallerDegree = (rightIsBigger) ? (t_LhsMaxDegree) : (t_RhsMaxDegree);

		for (u8 i = 0; i <= smallerDegree; ++i)
		{
			if (!Equal(p_Lhs.Coefficient(i), p_Rhs.Coefficient(i)))
			{
				return false;
			}
		}

		for (u8 i = smallerDegree + 1; i <= smallerDegree + extraTerms; ++i)
		{
			if (!IsZero((rightIsBigger) ? (p_Rhs.Coefficient(i)) : (p_Lhs.Coefficient(i))))
			{
				return false;
			}
		}

		return true;
	}

	//multiplication
	template <u8 t_LhsMaxDegree, u8 t_RhsMaxDegree>
	const Polynomial<t_LhsMaxDegree + t_RhsMaxDegree> operator *(const Polynomial<t_LhsMaxDegree>& p_Lhs, const Polynomial<t_RhsMaxDegree>& p_Rhs)
	{
		Polynomial<t_LhsMaxDegree + t_RhsMaxDegree> product;
		for (u8 i = 0; i <= t_LhsMaxDegree; ++i)
		{
			for (u8 j = 0; j <= t_RhsMaxDegree; ++j)
			{
				product.Coefficient(i + j) += p_Lhs.Coefficient(i) * p_Rhs.Coefficient(j);
			}
		}
		return product;
	}

	//==========
	// Functions
	//==========


	//==========
	// Definitions
	//==========

	typedef Polynomial<1> Linear;
	typedef Polynomial<2> Quadratic;
	typedef Polynomial<3> Cubic;
	typedef Polynomial<4> Quartic;

	inline const Linear MakePolynomial(const scalar p_Linear, const scalar p_Constant)
	{
		return Linear(MakeVector(p_Constant, p_Linear));
	}

	inline const Quadratic MakePolynomial(const scalar p_Quadratic, const scalar p_Linear, const scalar p_Constant)
	{
		return Quadratic(MakeVector(p_Constant, p_Linear, p_Quadratic));
	}

	inline const Cubic MakePolynomial(const scalar p_Cubic, const scalar p_Quadratic, const scalar p_Linear, const scalar p_Constant)
	{
		return Cubic(MakeVector(p_Constant, p_Linear, p_Quadratic, p_Cubic));
	}
	
} // namespace Mathematics

#endif //#ifndef IncludedMathPolynomialH










#if 0

class RealPolynomial
{
	//METHODS
public:

	//evaluate polynomial using Horner's rule
	complex operator ()(const complex& p_Value) const;

	//homebrewed polynomial factoring to take out a real root
	RealPolynomial factorOutRealRoot(const scalar p_Root) const;

	//returns a size - 1 polynomial with derivatives
	RealPolynomial derivative(void) const;

	//find all the roots using newtons method, binary search and polynomial division
	//assumes degree is at least one
	complexStack getRoots(void) const;


private:

	//Newton-Raphson for real roots
	scalar newtonMethod(const scalar p_InitialValue, const scalar p_Tolerance,
						const unsigned int p_MaxIterations) const;

	//Newton-Raphson for complex roots
	complex newtonMethod(const complex p_InitialValue, const scalar p_Tolerance,
						 const unsigned int p_MaxIterations) const;

	//given a range, find subranges of possible real roots
	scalarPairStack realIntervalSearch(const scalar p_IntMin, const scalar p_IntMax, const unsigned int p_Resolution) const;

	//given a range of magnitudes, trys to find given number of complex numbers, should be half of degree
	complexStack RealPolynomial::getPositiveComplexRoots(const scalar p_IntMin, const scalar p_IntMax, const unsigned int p_HalfDegree) const;

	//gets one copy of each real root on the given interval
	//unless the polynomial is quadratic
	scalarStack getRealRoots(const scalar p_IntMin, const scalar p_IntMax) const;

	//checks for linear or quadratic root
	complexStack getQuickRoots(void) const
	{
		complexStack roots(0);

		//if the degree is one, the only root is -b/a
		if(degree() == 1)
		{
			roots.push_back(complex(getLinearRoot(), 0.0));
		}
		//if degree is two, the roots are given by quadratic eqn
		else if(degree() == 2)
		{
			complexPair doubRoot = getQuadraticRoots();
			roots.push_back(doubRoot.first);
			roots.push_back(doubRoot.second);
		}
		return roots;
	}

	//ATTRIBUTES
private:

	scalarStack m_Coeffs;
};#include "RealPolynomial.h"



RealPolynomial RealPolynomial::factorOutRealRoot(const scalar p_Root) const
{
	scalarStack quotientCoeffs(m_Coeffs.size() - 1, 0.0);
	scalarStack coeffCoeffs;
	RealPolynomial coeffPoly;

	unsigned int coeffPolyTerms = 1;
	for (scalarStack::reverse_iterator rI = quotientCoeffs.rbegin(); rI != quotientCoeffs.rend(); ++rI)
	{
		//get the coefficient polynomials coefficients
		coeffCoeffs.clear();
		for (unsigned int i = coeffPolyTerms; i >= 1; --i)
		{
			coeffCoeffs.push_back(m_Coeffs[m_Coeffs.size() - i]);
		}
		coeffPolyTerms++;
		coeffPoly.m_Coeffs = coeffCoeffs;

		//evaluate the coefficient polynomial with the root
		*rI = coeffPoly(p_Root);
	}


	return RealPolynomial(quotientCoeffs);
}

complexStack RealPolynomial::getRoots(void) const
{
	//check simple cases
	complexStack roots(0);
	if (m_Coeffs.size() < 2) return roots;
	roots = getQuickRoots();
	if(!roots.empty()) return roots;

	//more than 2 roots so need factoring
	unsigned int degree = m_Coeffs.size() - 1;
	RealPolynomial workingPoly(m_Coeffs);

	//get bounds on the roots
	scalarStack absCoeffs;
	absCoeffs.resize(m_Coeffs.size());
	std::transform(m_Coeffs.begin(), m_Coeffs.end(),
		absCoeffs.begin(), std::abs<scalar>);

	scalar upperBnd = 1.0 + (1.0 / absCoeffs[degree]) *
		*(max_element(absCoeffs.begin(), absCoeffs.end() - 1));
	scalar lowerBnd = absCoeffs[0] / (absCoeffs[0] +
		*(max_element(absCoeffs.begin()+1, absCoeffs.end())));

	//until no real roots are found, factor
	scalarStack realRoots(0);
	complexStack quickRoots(0);
	do
	{
		//check for the simple cases
		complexStack simpleRoots = workingPoly.getQuickRoots();
		if(!simpleRoots.empty())
		{
			for(complexStack::iterator I = simpleRoots.begin();
				I != simpleRoots.end(); ++I)
			{
				roots.push_back((*I));
			}
			return roots;
		}

		//get real roots
		realRoots = workingPoly.getRealRoots(-upperBnd, upperBnd);

		for (scalarStack::const_iterator I = realRoots.begin(); I != realRoots.end(); ++I)
		{
			roots.push_back(complex(*I, 0.0));
			workingPoly = workingPoly.factorOutRealRoot(*I);
		}
	}
	while (!realRoots.empty());
	
	//ideally only complex roots remain and in pairs and degree is even
	complexStack complexRoots(0);
	if (roots.size() != degree)
	{
		complexRoots = workingPoly.getPositiveComplexRoots(lowerBnd, upperBnd, degree/2);
		for (complexStack::const_iterator I = complexRoots.begin(); I != complexRoots.end(); ++I)
		{
			roots.push_back(*I);
			roots.push_back(complex(std::conj(*I)));
		}
	}

	return roots;
}


scalar RealPolynomial::newtonMethod(const scalar p_InitialValue, const scalar p_Tolerance,
	const unsigned int p_MaxIterations) const
{
	RealPolynomial dF = derivative();

	//initialize
	unsigned int numIterations = 0;
	scalar lastVal = p_InitialValue;
	scalar currVal = p_InitialValue;

	do
	{
		//update
		lastVal = currVal;

		//check for iteration cap
		if (numIterations > p_MaxIterations)
		{
			return currVal;
		}
		++numIterations;

		//newton iteration
		currVal = lastVal - ((*this)(lastVal)) / (dF(lastVal));
	} while (std::abs(currVal - lastVal) > p_Tolerance);

	return currVal;
}

complex RealPolynomial::newtonMethod(const complex p_InitialValue, const scalar p_Tolerance,
	const unsigned int p_MaxIterations) const
{
	RealPolynomial dF = derivative();

	//initialize
	unsigned int numIterations = 0;
	complex lastVal = p_InitialValue;
	complex currVal = p_InitialValue;

	do
	{
		//update
		lastVal = currVal;

		//check for iteration cap
		if (numIterations > p_MaxIterations)
		{
			return currVal;
		}
		++numIterations;

		//newton iteration
		currVal = lastVal - ((*this)(lastVal)) / (dF(lastVal));
	} while (std::abs(currVal - lastVal) > p_Tolerance);

	return currVal;
}

scalarPairStack RealPolynomial::realIntervalSearch(const scalar p_IntMin, const scalar p_IntMax, const unsigned int p_Resolution) const
{
	scalarPairStack retStack;

	//check three times the expected root amount in intervals
	const scalar dVal = (p_IntMax - p_IntMin) / p_Resolution;
	scalar currVal = p_IntMin;
	scalar currFuncStartVal = (*this)(currVal);
	scalar currFuncEndVal = 0.0;
	scalarPair interval(0.0, 0.0);

	//for each endpoint see if the sign has changed
	for (unsigned int i = 0; i < p_Resolution; i++)
	{
		currVal += dVal;
		currFuncEndVal = (*this)(currVal);

		if (currFuncStartVal * currFuncEndVal <= 0.0)
		{
			//keep last interval
			interval.first = currVal - dVal;
			interval.second = currVal;
			retStack.push_back(interval);
		}

		currFuncStartVal = currFuncEndVal;
	}

	return retStack;
}

scalarStack RealPolynomial::getRealRoots(const scalar p_IntMin, const scalar p_IntMax) const
{
	RealPolynomial dP = derivative();
	scalarStack roots(0);
	unsigned int degree = m_Coeffs.size() - 1;
	if (degree == 0) return roots;

	scalar tol = 0.0000000001;
	
	//get possible root intervals
	scalarPairStack possibleRoots = realIntervalSearch(p_IntMin, p_IntMax, 10000);

	if (possibleRoots.empty())
	{
		//possible double root, so find critical point instead
		scalarStack critPoints(0);
		critPoints = dP.getRealRoots(p_IntMin, p_IntMax);
		for(scalarStack::iterator I = critPoints.begin();
			I != critPoints.end(); ++I)
		{
			if (scalarEquals(0.0, (*this)(*I)))
			{
				roots.push_back(*I);
			}
		}
	}

	//refine each root interval with newton method
	scalar root = 0.0;
	for (scalarPairStack::iterator I = possibleRoots.begin();
		I != possibleRoots.end(); ++I)
	{
		root = maxScalar;
		root = newtonMethod((I->first + I->second) / 2, tol, 100);
		if (scalarEquals(0.0, (*this)(root)))
		{
			roots.push_back(root);
		}
	}

	//remove duplicate roots
	scalarStack::iterator uniqueEnd = std::unique(roots.begin(), roots.end(), scalarEquals);
	scalarStack uniqueRoots(std::distance(roots.begin(), uniqueEnd), 0.0);
	std::copy(roots.begin(), uniqueEnd, uniqueRoots.begin());

	return uniqueRoots;
}

complexStack RealPolynomial::getPositiveComplexRoots(const scalar p_IntMin, const scalar p_IntMax, const unsigned int p_HalfDegree) const
{
	
	complexStack roots;
	complex randZ(0.0, 0.0);
	complex polZ(0.0, 0.0);
	complex zero(0.0, 0.0);

	realRand randMod(p_IntMin, p_IntMax);
	realRand randAng(0.0, Pi);
	scalar mod = 0.0;
	scalar angle = 0.0;

	//find possible numbers until the number is reached
	while(roots.size() <= 100)
	{
		//generate a random complex number on the semiannulus r:[|min|, |max|] x phi:[0, pi]
		mod = randMod(gen);
		angle = randAng(gen);
		randZ = complex(mod*std::cos(angle), mod*std::sin(angle));

		//do a complex newton method for a small iteration count
		polZ = newtonMethod(randZ, 0.0001, 100);

		//if f(z) ~ 0 then add it to the possible list
		if(complexEquals((*this)(polZ), 0.0))
		{
			roots.push_back(polZ);
		}
	}

	//polish those that were found
	for(complexStack::iterator I = roots.begin(); I != roots.end(); ++I)
	{
		*I = newtonMethod(*I, 0.0000001, 200);
	}

	//remove duplicates
	complexStack::iterator uniqueEnd = std::unique(roots.begin(), roots.end(), complexEquals);
	complexStack uniqueRoots(std::distance(roots.begin(), uniqueEnd), 0.0);
	std::copy(roots.begin(), uniqueEnd, uniqueRoots.begin());
	uniqueRoots.resize(p_HalfDegree);

	return uniqueRoots;
}

#endif