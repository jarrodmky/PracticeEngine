//===========================================================================
// Filename:	Simplices.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "LinearAlgebra.h"
#include "Simplices.h"

namespace Mathematics
{
	//===========================================================================
	// Definitions
	//===========================================================================

	AABB3 MakeBoundingBox(const PointCloud3& p_Points)
	{
		Matrix33 pcs;
		p_Points.Covariance(pcs);
		SymmetricEigendecomposition<3> symeig(pcs);
		symeig.Eigenvectors(pcs);

		PointCloud3 trans(p_Points);
		trans.Transform(MakeMatrix(pcs));

		RealInterval Ix(p_Points.ExtremePoint(-I())(0), p_Points.ExtremePoint(I())(0));
		RealInterval Iy(p_Points.ExtremePoint(-J())(1), p_Points.ExtremePoint(J())(1));
		RealInterval Iz(p_Points.ExtremePoint(-K())(2), p_Points.ExtremePoint(K())(2));

		AABB3 ret;
		ret.Centre = MakeVector(Midpoint(Ix), Midpoint(Iy), Midpoint(Iz));
		ret.Extents = MakeVector(Ix.MaxValue(), Iy.MaxValue(), Iz.MaxValue());
		return ret;
	}

	//---------------------------------------------------------------------------

	inline const bool Skewed(const Line3& p_Line1, const Line3& p_Line2)
	{
		return !Coplanar(p_Line1, p_Line2);
	}

	//---------------------------------------------------------------------------

	inline const bool Parallel(const Line3& p_Line1, const Line3& p_Line2)
	{
		return Parallel(p_Line1.Direction(), p_Line2.Direction());
	}

	//---------------------------------------------------------------------------

	inline const bool Parallel(const Line3& p_Line, const Plane3& p_Plane)
	{
		return Perpendicular(Vector3(p_Plane.Normal()), p_Line.Direction());
	}

	//---------------------------------------------------------------------------

	inline const bool Parallel(const Plane3& p_Plane1, const Plane3& p_Plane2)
	{
		return Parallel(p_Plane1.Normal(), p_Plane2.Normal());
	}

	//---------------------------------------------------------------------------

	inline const bool Coincident(const Vector3& p_Point, const Line3& p_Line)
	{
		return Parallel(p_Line.Direction(), p_Point - p_Line.Pivot());
	}

	//---------------------------------------------------------------------------

	inline const bool Coincident(const Line3& p_Line1, const Line3& p_Line2)
	{
		return Coplanar(p_Line1, p_Line2) && !Parallel(p_Line1, p_Line2);
	}

	//---------------------------------------------------------------------------

	inline const bool Coincident(const Line3& p_Line, const Plane3& p_Plane)
	{
		return !Parallel(p_Line, p_Plane);
	}

	//---------------------------------------------------------------------------

	inline const bool Coincident(const Plane3& p_Plane1, const Plane3& p_Plane2)
	{
		return !Parallel(p_Plane1, p_Plane2);
	}

	//---------------------------------------------------------------------------

	inline const bool Coincident(const Plane3& p_Plane1
							   , const Plane3& p_Plane2
							   , const Plane3& p_Plane3)
	{
		return Spanning(p_Plane1.Normal(), p_Plane2.Normal(), p_Plane3.Normal());
	}

	//---------------------------------------------------------------------------

	inline const scalar DistanceSquared(const Vector3& p_Point, const Line3& p_Line)
	{
		const Vector3 centreToPoint(p_Point - p_Line.Pivot());
		return centreToPoint.LengthSquared() - (centreToPoint.ProjectionAlong(p_Line.Direction())).LengthSquared();
	}

	//---------------------------------------------------------------------------

	inline const scalar Distance(const Vector3& p_Point, const Line3& p_Line)
	{
		return std::sqrt(DistanceSquared(p_Point, p_Line));
	}

	//---------------------------------------------------------------------------

	inline const scalar SignedDistance(const Vector3& p_Point, const Plane3& p_Plane)
	{
		return p_Plane.SignedDistanceTo(p_Point);
	}

	//---------------------------------------------------------------------------

	inline const scalar Distance(const Vector3& p_Point, const Plane3& p_Plane)
	{
		return AbsoluteValue(SignedDistance(p_Point, p_Plane));
	}

	//---------------------------------------------------------------------------

	const scalar DistanceSquared(const Line3& p_Line1, const Line3& p_Line2)
	{
		if (Coplanar(p_Line1, p_Line2))
		{
			//lines aren't skew
			if (Parallel(p_Line1, p_Line2))
			{
				//lines are aren't necessarily coincident
				return DistanceSquared(p_Line1.Pivot(), p_Line2);
			}
			return Zero;
		}
		else
		{
			const Vector3 diff(p_Line2.Pivot() - p_Line1.Pivot());
			const scalar dot(p_Line1.Direction() | p_Line2.Direction());
			const scalar v1sqr(p_Line1.Direction().LengthSquared());
			const scalar v2sqr(p_Line2.Direction().LengthSquared());

			const Vector2 t(MakeMatrix(v1sqr, -dot, dot, -v2sqr).Inverse() * MakeVector(diff | p_Line1.Direction(), diff | p_Line2.Direction()));
			return (p_Line1(t(0)) - p_Line2(t(1))).LengthSquared();
		}
	}

	//---------------------------------------------------------------------------

	const scalar Distance(const Line3& p_Line1, const Line3& p_Line2)
	{
		return std::sqrt(DistanceSquared(p_Line1, p_Line2));
	}

	//---------------------------------------------------------------------------

	const scalar Distance(const Line3& p_Line, const Plane3& p_Plane)
	{
		if (Parallel(p_Line, p_Plane))
		{
			return Distance(p_Line.Pivot(), p_Plane);
		}
		return Zero;
	}

	//---------------------------------------------------------------------------

	const scalar Distance(const Plane3& p_Plane1, const Plane3& p_Plane2)
	{
		if (Parallel(p_Plane1, p_Plane2))
		{
			return Distance(p_Plane1.Centre(), p_Plane2);
		}
		return Zero;
	}

	//---------------------------------------------------------------------------

	inline const bool Intersecting(const Line3& p_Line1, const Line3& p_Line2)
	{
		return Coplanar(p_Line1, p_Line2) && (Coincident(p_Line1, p_Line2) || Collinear(p_Line1, p_Line2));
	}

	//---------------------------------------------------------------------------

	inline const bool Intersecting(const Line3& p_Line, const Plane3& p_Plane)
	{
		return IsZero(Distance(p_Line, p_Plane));
	}

	//---------------------------------------------------------------------------

	inline const bool Intersecting(const Plane3& p_Plane1, const Plane3& p_Plane2)
	{
		return IsZero(Distance(p_Plane1, p_Plane2));
	}

	//---------------------------------------------------------------------------

	const bool Coincident(const Line3& p_Line1, const Line3& p_Line2, Vector3& p_Point)
	{
		Halt("Unimplemented!");
		return false;
	}

	//---------------------------------------------------------------------------

	const bool Coincident(const Line3& p_Line, const Plane3& p_Plane, Vector3& p_Point)
	{
		if (Coincident(p_Line, p_Plane))
		{
			const Vector4 P(MakeVector(p_Plane));
			const scalar t = -(P | MakeAffinePoint(p_Line.Pivot()))
				/ (P | MakeAffineVector(p_Line.Direction()));
			p_Point = p_Line(t);
			return true;
		}
		return false;
	}

	//---------------------------------------------------------------------------

	const bool Coincident(const Plane3& p_Plane1, const Plane3& p_Plane2, const Plane3& p_Plane3, Vector3& p_Point)
	{
		if (Coincident(p_Plane1, p_Plane2, p_Plane3))
		{
			p_Point = MakeMatrix(p_Plane1.Normal(), p_Plane2.Normal(), p_Plane3.Normal())
				* MakeVector(-p_Plane1.SignedOffset(), -p_Plane2.SignedOffset(), -p_Plane3.SignedOffset());
			return true;
		}
		return false;
	}

	//---------------------------------------------------------------------------

	const bool Coincident(const Plane3& p_Plane1, const Plane3& p_Plane2, Line3& p_Line)
	{
		if (Coincident(p_Plane1, p_Plane2))
		{
			//find direction
			const Vector3 direction = p_Plane1.Normal() * p_Plane2.Normal();
			
			//find centre with 3 plane intersect
			const Plane3 P(direction);
			Vector3 centre;
			Coincident(p_Plane1, p_Plane2, P, centre);

			//line is fully specified
			p_Line = Line3(centre, direction);
			return true;
		}
		return false;
	}
}