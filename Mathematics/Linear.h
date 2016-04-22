#ifndef IncludedMathLinearH
#define IncludedMathLinearH

//===========================================================================
// Filename:	Linear.h
// Author:		Jarrod MacKay
// Description:	Defines one dimensional geometry.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "LinearAlgebra.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	template<u32 t_Dimensions>
	class PointPair
	{
	public:

		inline PointPair(const RealVector<t_Dimensions>& p_Point1, const RealVector<t_Dimensions>& p_Point2)
			: m_Pivot(p_Point1)
			, m_Direction(p_Point2 - p_Point1)
		{
			Assert(!m_Direction.IsAtOrigin(), "Points are coincident!");
		}

		inline const RealVector<t_Dimensions> operator()(const scalar p_Parameter) const
		{
			return m_Pivot + p_Parameter * m_Direction;
		}

		inline const RealVector<t_Dimensions> GetFirst() const
		{
			return m_Pivot;
		}

		inline const RealVector<t_Dimensions> GetSecond() const
		{
			return m_Pivot + m_Direction;
		}

		inline const RealVector<t_Dimensions> GetDirection() const
		{
			return m_Direction;
		}

	private:

		RealVector<t_Dimensions> m_Pivot;
		RealVector<t_Dimensions> m_Direction;
	};

	//==========
	// Edge
	//==========

	template<u32 t_Dimensions>
	class Edge
	{
	//Operators
	public:

		Edge(const RealVector<t_Dimensions>& p_Point1, const RealVector<t_Dimensions>& p_Point2)
			: m_Points(p_Point1, p_Point2)
		{}

		const RealVector<t_Dimensions> operator()(const scalar p_Parameter) const
		{
			return (p_Parameter > Zero) ?
						((p_Parameter < Unity) ?
							(m_Points(p_Parameter)) : (Second())) : (First());
		}

	//Methods
	public:

		inline const RealVector<t_Dimensions> First() const
		{
			return m_Points.GetFirst();
		}

		inline const RealVector<t_Dimensions> Second() const
		{
			return m_Points.GetSecond();
		}

	//Attributes
	public:

		PointPair<t_Dimensions> m_Points;
	};

	//==========
	// Ray
	//==========

	template<u32 t_Dimensions>
	class Ray
	{
	//Operators
	public:

		Ray(const RealVector<t_Dimensions>& p_Point, const RealVector<t_Dimensions>& p_Direction)
			: m_Points(p_Point, p_Direction + p_Point)
		{}

		const RealVector<t_Dimensions> operator()(const scalar p_Parameter) const
		{
			return (p_Parameter > Zero) ? (m_Points(p_Parameter)) : (Pivot());
		}

	//Methods
	public:

		inline const RealVector<t_Dimensions> Direction() const
		{
			return m_Points.GetDirection();
		}

		inline const RealVector<t_Dimensions> Pivot() const
		{
			return m_Points.GetFirst();
		}

	//Attributes
	private:

		PointPair<t_Dimensions> m_Points;
	};

	//==========
	// Line
	//==========

	template<u32 t_Dimensions>
	class Line
	{
	//Operators
	public:

		Line(const RealVector<t_Dimensions>& p_Point, const RealVector<t_Dimensions>& p_Direction)
			: m_Points(p_Point, p_Direction + p_Point)
		{}

		const RealVector<t_Dimensions> operator()(const scalar p_Parameter) const
		{
			return m_Points(p_Parameter);
		}

	//Methods
	public:

		inline const RealVector<t_Dimensions> Direction() const
		{
			return m_Points.GetDirection();
		}

		inline const RealVector<t_Dimensions> Pivot() const
		{
			return m_Points.GetFirst();
		}

	//Attributes
	private:

		PointPair<t_Dimensions> m_Points;
	};

	//===========================================================================
	// Definitions
	//===========================================================================

	typedef Edge<2> Edge2;
	typedef Edge<3> Edge3;
	typedef Edge<4> Edge4;

	typedef Ray<2> Ray2;
	typedef Ray<3> Ray3;
	typedef Ray<4> Ray4;

	typedef Line<2> Line2;
	typedef Line<3> Line3;
	typedef Line<4> Line4;

	//===========================================================================
	// Constants
	//===========================================================================

	//===========================================================================
	// Functions
	//===========================================================================

	inline const bool Collinear(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C);
	inline const bool Collinear(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C);
	inline const bool Collinear(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C, const Vector3& p_D);
	inline const bool Collinear(const Line3& p_Line1, const Line3& p_Line2);

	//---------------------------------------------------------------------------

	inline const bool Collinear(const Vector2& p_A, const Vector2& p_B, const Vector2& p_C)
	{
		return IsZero(Orientation(p_A, p_B, p_C));
	}

	//---------------------------------------------------------------------------

	inline const bool Collinear(const Vector3& p_A, const Vector3& p_B, const Vector3& p_C)
	{
		return Parallel(p_A - p_C, p_B - p_C);
	}

	//---------------------------------------------------------------------------

	inline const bool Collinear(const Vector3& p_PointA, const Vector3& p_PointB, const Vector3& p_PointC, const Vector3& p_PointD)
	{
		return Collinear(p_PointA, p_PointB, p_PointC) && Collinear(p_PointA, p_PointB, p_PointD);
	}

	//---------------------------------------------------------------------------

	inline const bool Collinear(const Line3& p_Line1, const Line3& p_Line2)
	{
		return Collinear(p_Line1.Direction() + p_Line1.Pivot(), p_Line1.Pivot(), p_Line2.Direction() + p_Line2.Pivot(), p_Line2.Pivot());
	}

} // namespace Mathematics

#endif //#ifndef IncludedMathLinearH