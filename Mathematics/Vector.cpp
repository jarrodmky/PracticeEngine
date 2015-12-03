//===========================================================================
// Filename:	Vector.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Vector.h"

using namespace Mathematics;

//===========================================================================
// Class Definitions
//===========================================================================
		
const scalar Vector::LengthAlong(const Vector& p_Rhs) const
{
	return (*this) | p_Rhs.Direction();
}

//---------------------------------------------------------------------------

Vector& Vector::ProjectAlong(const Vector& p_Rhs)
{
	scalar invSquareLHS = p_Rhs.LengthSquared();
	Invert(invSquareLHS);

	(*this) = p_Rhs * (((*this) | p_Rhs) * invSquareLHS);
	return *this;
}

//---------------------------------------------------------------------------

const Vector Vector::ProjectedAlong(const Vector& p_Rhs) const
{
	Vector temp(*this);
	temp.ProjectAlong(p_Rhs);
	return temp;
}