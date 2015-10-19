//===========================================================================
// Filename:	Vector.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Vector.h"
#include "Matrix.h"

using namespace Mathematics;

//===========================================================================
// Class Definitions
//===========================================================================

const Matrix Vector::operator ^(const Vector& p_Lhs) const
{
	return ConstantMatrices::Identity;
}

//---------------------------------------------------------------------------
		
const scalar Vector::LengthAlong(const Vector& p_Lhs) const
{
	return (*this) | p_Lhs.Direction();
}

//---------------------------------------------------------------------------

const scalar Vector::AngleBetween(const Vector& p_Lhs) const
{
	return std::acosf(Direction() | p_Lhs.Direction());
}

//---------------------------------------------------------------------------

Vector& Vector::ProjectAlong(const Vector& p_Lhs)
{
	scalar invSquareLHS = p_Lhs.LengthSquared();
	Invert(invSquareLHS);

	(*this) = p_Lhs * (((*this) | p_Lhs) * invSquareLHS);
	return *this;
}

//---------------------------------------------------------------------------

const Vector Vector::ProjectedAlong(const Vector& p_Lhs) const
{
	Vector temp(*this);
	temp.ProjectAlong(p_Lhs);
	return temp;
}