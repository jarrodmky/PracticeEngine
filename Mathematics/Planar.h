#ifndef IncludedMathPlanarH
#define IncludedMathPlanarH

//===========================================================================
// Filename:	Plane.h
// Author:		Jarrod MacKay
// Description:	Defines an infinite plane in 3D
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "LinearAlgebra.h"
#include "Triangle.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	//==========
	// Parallelogram
	//==========

	template <u32 t_Dimensions>
	class Quad
	{
	//Operators
	public:

		inline Quad(const RealVector<t_Dimensions>& p_U
			, const RealVector<t_Dimensions>& p_V
			, const RealVector<t_Dimensions>& p_Centre = RealVector<t_Dimensions>(Zero))
			: U(p_U)
			, V(p_V)
			, Centre(p_Centre)
		{
			Assert(!Parallel(p_U, p_V), "Degenrate quad!");
		}

		//Methods
	public:

		const RealVector<t_Dimensions> GetNormal() const
		{
			return (U * V).Direction();
		}

		const RealVector<t_Dimensions> GetFirst() const
		{
			return Centre + (-U - V) * 0.5f;
		}

		const RealVector<t_Dimensions> GetSecond() const
		{
			return Centre + (U - V) * 0.5f;
		}

		const RealVector<t_Dimensions> GetThird() const
		{
			return Centre + (U + V) * 0.5f;
		}

		const RealVector<t_Dimensions> GetFourth() const
		{
			return Centre + (-U + V) * 0.5f;
		}

		//Attributes
	public:

		RealVector<t_Dimensions> U;
		RealVector<t_Dimensions> V;
		RealVector<t_Dimensions> Centre;

	};

	//==========
	// Plane
	//==========

	template <u32 t_Dimensions>
	class Plane
	{
	//Operators
	public:

		inline Plane(const RealVector<t_Dimensions>& p_Normal, const scalar p_Constant = Zero)
			: m_Normal(p_Normal.Direction())
			, m_Constant(p_Constant)
		{
			Assert(m_Normal.IsUnit(), "Non-unit normal!");
		}

		inline Plane(const RealVector<t_Dimensions>& p_Normal, const RealVector<t_Dimensions>& p_Point)
			: Plane(p_Normal)
		{
			Assert(m_Normal.IsUnit(), "Non-unit normal!");
			m_Constant = -(m_Normal | p_Point);
		}

	//Methods
	public:

		inline const RealVector<t_Dimensions> Normal() const
		{
			Assert(m_Normal.IsUnit(), "Non-unit normal!");
			return m_Normal;
		}

		inline const RealVector<t_Dimensions> Centre() const
		{
			return Normal() * -m_Constant;
		}

		inline const scalar SignedOffset() const
		{
			return m_Constant;
		}

		inline const scalar SignedDistanceTo(const RealVector<t_Dimensions>& p_Point) const
		{
			return (Normal() | p_Point) + SignedOffset();
		}

		inline const scalar DistanceTo(const RealVector<t_Dimensions>& p_Point) const
		{
			return AbsoluteValue(SignedDistanceTo(p_Point));
		}

		inline const RealVector<t_Dimensions> ClosestPointTo(const RealVector<t_Dimensions>& p_Point) const
		{
			return p_Point.RejectionFrom(Normal());
		}

	//Attributes
	private:

		RealVector<t_Dimensions> m_Normal;
		scalar m_Constant;
	};

	//==========
	// Slab
	//==========

	template <u32 t_Dimensions>
	class Slab
	{
		//Operators
	public:

		inline Slab(const RealVector<t_Dimensions>& p_Normal, const scalar p_Min = -0.5f, const scalar p_Max = 0.5f)
			: m_Normal(p_Normal.Direction())
			, m_Interval(p_Min, p_Max)
		{
			Assert(m_Normal.IsUnit(), "Non-unit normal!");
		}

		//Methods
	public:

		inline const RealVector<t_Dimensions> Normal() const
		{
			return m_Normal;
		}

		inline const bool Contains(const RealVector<t_Dimensions>& p_Point) const
		{
			const scalar proj = p_Point.LengthAlong(m_Normal);
			return m_Interval.HasElement(proj);
		}

		//Attributes
	private:

		RealVector<t_Dimensions> m_Normal;
		RealInterval m_Interval;
	};

	//===========================================================================
	// Declarations
	//===========================================================================
	
	//==========
	// Functions
	//==========
	
	template <u32 t_Dimensions>
	inline const bool InPositiveHalfSpace(const Plane<t_Dimensions>& p_Plane, const RealVector<t_Dimensions>& p_Point)
	{
		return p_Plane.SignedDistanceTo(p_Point) > Zero;
	}

	template <u32 t_Dimensions>
	inline const bool InNegativeHalfSpace(const Plane<t_Dimensions>& p_Plane, const RealVector<t_Dimensions>& p_Point)
	{
		return p_Plane.SignedDistanceTo(p_Point) < Zero;
	}
	
	template <u32 t_Dimensions>
	inline const RealVector<t_Dimensions + 1> MakeVector(const Plane<t_Dimensions>& p_Plane)
	{
		RealVector<t_Dimensions + 1> temp(MakeAffineVector(p_Plane.Normal()));
		temp(t_Dimensions) = p_Plane.SignedOffset();
		return temp;
	}

	template <u32 t_Dimensions>
	inline const Plane<t_Dimensions> MakePlane(const RealVector<t_Dimensions + 1>& p_Vector)
	{
		RealVector<t_Dimensions + 1> temp(p_Vector);
		const scalar offset = temp(t_Dimensions);
		temp(t_Dimensions) = Zero;
		return Plane<t_Dimensions>(MakeProjectedVector(temp), offset);
	}
	
	template <u32 t_Dimensions>
	inline void TransformPlane(const Matrix<t_Dimensions + 1, t_Dimensions + 1>& p_Transform, Plane<t_Dimensions>& p_Plane)	
	{
		p_Plane = MakePlane(p_Transform.InverseTransposition() * MakeVector(p_Plane));
	}

	//==========
	// Definitions
	//==========

	typedef Quad<2> Quad2;
	typedef Quad<3> Quad3;
	typedef Quad<4> Quad4;

	typedef Plane<2> Plane2;
	typedef Plane<3> Plane3;
	typedef Plane<4> Plane4;

	inline const Plane3 MakePlane(const scalar p_N0, const scalar p_N1, const scalar p_N2, const scalar p_Constant)
	{
		return MakePlane<3>(MakeVector(p_N0, p_N1, p_N2, p_Constant));
	}

	//===========================================================================
	// Constants
	//===========================================================================
	
	inline const Plane3 XY();
	
	inline const Plane3 XZ();
	
	inline const Plane3 YZ();
	
	//===========================================================================
	// Constant Definitions
	//===========================================================================

	inline const Plane3 XY()
	{
		return Plane3(K());
	}

	inline const Plane3 XZ()
	{
		return Plane3(J());
	}

	inline const Plane3 YZ()
	{
		return Plane3(I());
	}

	//===========================================================================
	// Function Definitions
	//===========================================================================

	inline const bool Coplanar(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D);

	inline const bool Coplanar(const Line3& p_Line1, const Line3& p_Line2);

	//---------------------------------------------------------------------------

	inline const bool Coplanar(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D)
	{
		return IsZero(Orientation(p_A, p_B, p_C, p_D));
	}

	//---------------------------------------------------------------------------

	inline const bool Coplanar(const Line3& p_Line1, const Line3& p_Line2)
	{
		return !Spanning(p_Line1.Direction(), p_Line2.Direction(), p_Line2.Pivot() - p_Line1.Pivot());
	}
} // namespace Mathematics

#endif //#ifndef IncludedMathPlanarH