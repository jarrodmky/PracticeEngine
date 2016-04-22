#ifndef IncludedMathRoundH
#define IncludedMathRoundH

//===========================================================================
// Filename:	Round.h
// Author:		Jarrod MacKay
// Description:	Defines objects with radii
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "LinearAlgebra.h"
#include "Linear.h"
#include "Planar.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	//==========
	// Sphere
	//==========

	template <u32 t_Dimensions>
	class Sphere
	{
		//Operators
	public:

		Sphere(const RealVector<t_Dimensions>& p_Centre, const scalar& p_Radius)
			: Centre(p_Centre)
			, Radius(p_Radius)
		{}

		//Attributes
	public:

		RealVector<t_Dimensions> Centre;
		scalar Radius;
	};


	//==========
	// Capsule
	//==========

	template <u32 t_Dimensions>
	class Capsule
	{
		//Operators
	public:

		inline Capsule(const Sphere<t_Dimensions>& p_Sphere, const RealVector<t_Dimensions>& p_Velocity, const scalar p_DeltaTime);

		//Methods
	public:

		//Attributes
	private:

		Edge<t_Dimensions> m_Segment;
		scalar m_Radius;
	};

	//==========
	// Lozenge
	//==========

	template <u32 t_Dimensions>
	class Lozenge
	{
		//Operators
	public:

		inline Lozenge(const Quad<t_Dimensions>& p_Quad, const scalar p_Radius);

		inline Lozenge(const Capsule<t_Dimensions>& p_Capsule, const RealVector<t_Dimensions>& p_Velocity, const scalar p_DeltaTime);

		//Methods
	public:

		//Attributes
	private:

		Quad<t_Dimensions> m_Quad;
		scalar m_Radius;
	};

	//===========================================================================
	// Declarations
	//===========================================================================
	
	//==========
	// Functions
	//==========

	inline const scalar CircleOrientation(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C, const Vector2& p_Query);

	inline const bool InCircle(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C, const Vector2& p_Query);

	inline const scalar SphereOrientation(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D, const Vector3& p_Query);

	inline const bool InSphere(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D, const Vector3& p_Query);

	//==========
	// Definitions
	//==========

	typedef Sphere<2> Sphere2;
	typedef Sphere<3> Sphere3;
	typedef Sphere<4> Sphere4;

	typedef Capsule<2> Capsule2;
	typedef Capsule<3> Capsule3;
	typedef Capsule<4> Capsule4;

	typedef Lozenge<2> Lozenge2;
	typedef Lozenge<3> Lozenge3;
	typedef Lozenge<4> Lozenge4;

	//===========================================================================
	// Constants
	//===========================================================================
	
	//===========================================================================
	// Constant Definitions
	//===========================================================================

	//===========================================================================
	// Function Definitions
	//===========================================================================

	inline const scalar CircleOrientation(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C, const Vector2& p_Query)
	{
		const Vector2 Adiff(p_A - p_Query);
		const Vector2 Bdiff(p_B - p_Query);
		const Vector2 Cdiff(p_C - p_Query);

		return MakeMatrix(Adiff(0), Adiff(1), Adiff.LengthSquared()
			, Bdiff(0), Bdiff(1), Bdiff.LengthSquared()
			, Cdiff(0), Cdiff(1), Cdiff.LengthSquared()).Determinant();
	}

	//---------------------------------------------------------------------------

	inline const bool InCircle(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C, const Vector2& p_Query)
	{
		if (CounterClockwise(p_A, p_B, p_C))
		{
			if (CircleOrientation(p_A, p_B, p_C, p_Query) > Zero)
			{
				return true;
			}
			return false;
		}
		else
		{
			if (CircleOrientation(p_A, p_B, p_C, p_Query) < Zero)
			{
				return true;
			}
			return false;
		}
	}

	//---------------------------------------------------------------------------

	inline const scalar SphereOrientation(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D, const Vector3& p_Query)
	{
		const Vector3 Adiff(p_A - p_Query);
		const Vector3 Bdiff(p_B - p_Query);
		const Vector3 Cdiff(p_C - p_Query);
		const Vector3 Ddiff(p_D - p_Query);

		return MakeMatrix(Adiff(0), Adiff(1), Adiff(2), Adiff.LengthSquared()
			, Bdiff(0), Bdiff(1), Bdiff(2), Bdiff.LengthSquared()
			, Cdiff(0), Cdiff(1), Cdiff(2), Cdiff.LengthSquared()
			, Ddiff(0), Ddiff(1), Ddiff(2), Ddiff.LengthSquared()).Determinant();
	}

	//---------------------------------------------------------------------------

	inline const bool InSphere(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D, const Vector3& p_Query)
	{
		if (CounterClockwise(p_A, p_B, p_C, p_D))
		{
			if (SphereOrientation(p_A, p_B, p_C, p_D, p_Query) > Zero)
			{
				return true;
			}
			return false;
		}
		else
		{
			if (SphereOrientation(p_A, p_B, p_C, p_D, p_Query) < Zero)
			{
				return true;
			}
			return false;
		}
	}
} // namespace Mathematics

#endif //#ifndef IncludedMathRoundH