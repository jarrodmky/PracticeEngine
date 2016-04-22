#ifndef IncludedSeriPrecompiledH
#define IncludedSeriPrecompiledH

//===========================================================================
// Filename:	Precompiled.h
// Author:		Jarrod MacKay
// Description:	Contains public headers for the visualization project
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include <Abstracts.h>
#include <Mathematics.h>
#include <Algorithms.h>

template <u32 t_MaxDegree>
static std::string PrintPolynomial(const Mathematics::Polynomial<t_MaxDegree>& p_Polynomial)
{
	const Mathematics::Polynomial<t_MaxDegree>& P(p_Polynomial);
	std::ostringstream retString;
	if (t_MaxDegree == 0)
	{
		return retString << P.Coefficient(0);
	}

	for (u32 i = t_MaxDegree; i >= 2; --i)
	{
		if (!IsZero(P.Coefficient(i)))
		{
			retString << "(" << P.Coefficient(i) << ")x^" << i << " + ";
		}
	}

	if (t_MaxDegree > 0 && !IsZero(P.Coefficient(1)))
	{
		retString << "(" << P.Coefficient(1) << ")x + ";
	}

	if (m_Coeffs[0] != 0.0)
	{
		return retString << P.Coefficient(0);
	}
	else
	{
		std::string editStr = retString.str();
		if (editStr.empty())
		{
			editStr = "0";
		}
		else
		{
			std::string::iterator I = editStr.end();
			editStr.erase(I - 3, I);
		}
		retString.str(editStr);
	}

	return retString.str();
}


#endif //#ifndef IncludedSeriPrecompiledH
