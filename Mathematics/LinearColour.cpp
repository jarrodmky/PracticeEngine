//===========================================================================
// Filename:	LinearColour.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "LinearColour.h"
#include "MathBase.h"

//===========================================================================
// Class Definitions
//===========================================================================

namespace
{
	inline const f32 GetByteAsUnit(const u8 p_Index, const u32 p_FourByteInteger)
	{
		Assert(p_Index < 4, "No byte exists!");
		return static_cast<f32>(((p_FourByteInteger >> (24 - (p_Index * 8))) & 0xFF)) / 255.0f;
	}
}

namespace Mathematics
{
	LinearColour::LinearColour(f32 p_Red, f32 p_Green, f32 p_Blue, f32 p_Alpha)
		: R(p_Red)
		, G(p_Green)
		, B(p_Blue)
		, A(p_Alpha)
	{}

	LinearColour::LinearColour(const u32 p_HexRGB)
		: R(GetByteAsUnit(1, p_HexRGB))
		, G(GetByteAsUnit(2, p_HexRGB))
		, B(GetByteAsUnit(3, p_HexRGB))
		, A(1.0f)
	{}

	LinearColour& LinearColour::operator +=(const LinearColour& p_Other)
	{
		R += p_Other.R;
		G += p_Other.G;
		B += p_Other.B;
		A += p_Other.A;
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
		A *= p_Other.A;
		return *this;
	}

	LinearColour LinearColour::operator*(const LinearColour& p_Other) const
	{
		return LinearColour(R * p_Other.R, G * p_Other.G, B * p_Other.B, A * p_Other.A);
	}

	LinearColour LinearColour::operator*(const f32 p_Scalar) const
	{
		return LinearColour(R * p_Scalar, G * p_Scalar, B * p_Scalar, A * p_Scalar);
	}

	LinearColour operator*(const f32 p_Scalar, const LinearColour& p_Other)
	{
		return p_Other * p_Scalar;
	}

	void LinearColour::Clamp()
	{
		R = Mathematics::ClampInclusive(R, 0.0f, 1.0f);
		B = Mathematics::ClampInclusive(B, 0.0f, 1.0f);
		G = Mathematics::ClampInclusive(G, 0.0f, 1.0f);
		A = Mathematics::ClampInclusive(A, 0.0f, 1.0f);
	}
}