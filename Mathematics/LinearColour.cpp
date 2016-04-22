//===========================================================================
// Filename:	LinearColour.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "LinearColour.h"

//===========================================================================
// Class Definitions
//===========================================================================

namespace
{
	inline const Mathematics::LinearColour ConvertColour(const u32 p_RGB)
	{
		using namespace Mathematics;
		FourBytes bytes;
		bytes.U32 = p_RGB;
		f32 red = Zero, green = Zero, blue = Zero;

		if (BigEndian())
		{
			red = static_cast<f32>(bytes.U8[1]) / 255.0f;
			green = static_cast<f32>(bytes.U8[2]) / 255.0f;
			blue = static_cast<f32>(bytes.U8[3]) / 255.0f;
		}
		else
		{
			red = static_cast<f32>(bytes.U8[2]) / 255.0f;
			green = static_cast<f32>(bytes.U8[1]) / 255.0f;
			blue = static_cast<f32>(bytes.U8[0]) / 255.0f;
		}

		return LinearColour(red, green, blue, 1.0f);
	}
}

namespace Mathematics
{
	LinearColour::LinearColour(scalar p_Red, scalar p_Green, scalar p_Blue, scalar p_Alpha)
		: R(p_Red)
		, G(p_Green)
		, B(p_Blue)
		, A(p_Alpha)
	{}

	LinearColour::LinearColour(const u32 p_HexRGB)
		: LinearColour(ConvertColour(p_HexRGB))
	{}

	LinearColour& LinearColour::operator +=(const LinearColour& p_Other)
	{
		R += p_Other.R;
		G += p_Other.G;
		B += p_Other.B;
		Clamp();
		return *this;
	}

	LinearColour LinearColour::operator +(const LinearColour& p_Other) const
	{
		LinearColour sum(*this);
		sum += p_Other;
		return sum;
	}

	LinearColour& LinearColour::operator *=(const LinearColour& p_Other)
	{
		R *= p_Other.R;
		G *= p_Other.G;
		B *= p_Other.B;
		return *this;
	}

	LinearColour LinearColour::operator*(const LinearColour& p_Other) const
	{
		return LinearColour(R * p_Other.R, G * p_Other.G, B * p_Other.B, A);
	}

	LinearColour& LinearColour::operator *=(const scalar p_Scalar)
	{
		R *= p_Scalar;
		G *= p_Scalar;
		B *= p_Scalar;
		return *this;
	}

	LinearColour LinearColour::operator*(const scalar p_Scalar) const
	{
		return LinearColour(R * p_Scalar, G * p_Scalar, B * p_Scalar, A);
	}

	LinearColour operator*(const scalar p_Scalar, const LinearColour& p_Other)
	{
		return p_Other * p_Scalar;
	}

	void LinearColour::Clamp()
	{
		R = Mathematics::ClampInclusive(R, Zero, Unity);
		B = Mathematics::ClampInclusive(B, Zero, Unity);
		G = Mathematics::ClampInclusive(G, Zero, Unity);
		A = Mathematics::ClampInclusive(A, Zero, Unity);
	}
}