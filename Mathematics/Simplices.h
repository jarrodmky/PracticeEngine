#ifndef IncludedMathSimplicesH
#define IncludedMathSimplicesH

//===========================================================================
// Filename:	Simplices.h
// Author:		Jarrod MacKay
// Description:	Defines simple three dimensional shapes.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "../Abstracts/List.h"
#include "LinearAlgebra.h"
#include "Linear.h"
#include "Triangle.h"
#include "Planar.h"
#include "Round.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{

	//===========================================================================
	// Solid Geometries
	//===========================================================================

	//TODO:
	//Cone
	//Torus
	//Ellipsoid
	//Cylinder



	//==========
	// AABB
	//==========
	template <u32 t_Dimensions>
	class AlignedBox
	{
	//Operators
	public:

		AlignedBox()
			: Centre()
			, Extents()
		{}

		AlignedBox(const RealVector<t_Dimensions>& p_Centre, const RealVector<t_Dimensions>& p_Extents)
			: Centre(p_Centre)
			, Extents(p_Extents)
		{}

	//Attributes
	public:

		RealVector<t_Dimensions> Centre;
		RealVector<t_Dimensions> Extents;
	};

	typedef AlignedBox<2> AABB2;
	typedef AlignedBox<3> AABB3;
	typedef AlignedBox<4> AABB4;


	template <u32 t_Dimensions>
	class PointCloud
	{
	//Definitions
	private:

		typedef Abstracts::List<RealVector<t_Dimensions> > PointList;

	//Operators
	public:

		PointCloud()
			: m_List(0)
		{
		}

		explicit PointCloud(const PointList& p_List)
			: m_List(p_List)
		{
		}

		~PointCloud()
		{
			m_List.Destroy();
		}

		const RealVector<t_Dimensions> operator ()(const u32 p_Index) const
		{
			return m_List(p_Index);
		}

		RealVector<t_Dimensions>& operator ()(const u32 p_Index)
		{
			return m_List(p_Index);
		}

	//Methods
	public:

		void Populate(const u32 p_Amount)
		{
			m_List.Resize(p_Amount, RealVector<t_Dimensions>(Zero));
		}

		const u32 Size() const
		{
			return m_List.GetNumberOfElements();
		}

		const RealVector<t_Dimensions> Centroid() const
		{
			RealVector<t_Dimensions> accum(Zero);
			for (u32 i = 0; i < Size(); ++i)
			{
				accum += m_List(i);
			}
			return accum * Inverse(static_cast<scalar>(Size()));
		}

		const RealVector<t_Dimensions> ExtremePoint(const RealVector<t_Dimensions>& p_Direction) const
		{
			scalar maxDot = NegativeInfinity;
			u32 maxIndex = -1;

			for(u32 i = 0; i < m_List.GetNumberOfElements(); ++i)
			{
				scalar currDot = (p_Direction | m_List(i));
				if(maxDot < currDot)
				{
					maxIndex = i;
					maxDot = currDot;
				}
			}
			return m_List(maxIndex);
		}

		void Covariance(Matrix<t_Dimensions, t_Dimensions>& p_Matrix) const
		{
			const RealVector<t_Dimensions> mean(Centroid());
			const u32 N(m_List.GetNumberOfElements());
			p_Matrix = Zero33();

			for (u32 i = 0; i < N; ++i)
			{
				Vector3 relativeOffset(m_List(i) - mean);
				p_Matrix += (relativeOffset ^ relativeOffset);
			}
			p_Matrix /= Inverse(static_cast<scalar>(N));
		}

		void Transform(const Matrix<t_Dimensions + 1, t_Dimensions + 1>& p_Transform)
		{
			for (u32 i = 0; i < m_List.GetNumberOfElements(); ++i)
			{
				m_List(i) = MakeProjectedPoint(p_Transform * MakeAffinePoint(m_List(i)));
			}
		}

	//Attributes
	private:

		PointList m_List;
	};
	
	typedef PointCloud<2> PointCloud2;
	typedef PointCloud<3> PointCloud3;

	//===========================================================================
	// Functions
	//===========================================================================



	//===========================================================================
	// Functions
	//===========================================================================

	AABB3 MakeBoundingBox(const PointCloud3& p_Points);

	//==========
	// Simple Inclusions
	//==========

	//===========================================================================
	// Boolean tests
	//===========================================================================

	//==========
	// Lines
	//==========

	inline const bool Skewed(const Line3& p_Line1, const Line3& p_Line2);

	//==========
	// Parallelism
	//==========

	inline const bool Parallel(const Line3& p_Line1, const Line3& p_Line2);

	inline const bool Parallel(const Line3& p_Line, const Plane3& p_Plane);

	inline const bool Parallel(const Plane3& p_Plane1, const Plane3& p_Plane2);

	//==========
	// Coincidence
	//==========

	//point is in line
	inline const bool Coincident(const Vector3& p_Point, const Line3& p_Line);

	//point is in plane
	inline const bool Coincident(const Vector3& p_Point, const Plane3& p_Plane);

	//lines share exactly one finite point
	inline const bool Coincident(const Line3& p_Line1, const Line3& p_Line2);

	//line and plane share exactly one finite point
	inline const bool Coincident(const Line3& p_Line, const Plane3& p_Plane);

	//planes share exactly one point
	inline const bool Coincident(const Plane3& p_Plane1, const Plane3& p_Plane2, const Plane3& p_Plane3);

	//planes share exactly one line
	inline const bool Coincident(const Plane3& p_Plane1, const Plane3& p_Plane2);

	//===========================================================================
	// Distances
	//===========================================================================

	//==========
	// Point-Line
	//==========

	inline const scalar DistanceSquared(const Vector3& p_Point, const Line3& p_Line);

	//distance between a point and a line
	inline const scalar Distance(const Vector3& p_Point, const Line3& p_Line);

	//==========
	// Point-Plane
	//==========

	//signed distance between a plane and a point
	inline const scalar SignedDistance(const Vector3& p_Point, const Plane3& p_Plane);

	//distance between a plane and a point
	inline const scalar Distance(const Vector3& p_Point, const Plane3& p_Plane);

	//==========
	// Line-Line
	//==========

	const scalar DistanceSquared(const Line3& p_Line1, const Line3& p_Line2);

	//minimum distance between two lines
	const scalar Distance(const Line3& p_Line1, const Line3& p_Line2);

	//==========
	// Line-Plane
	//==========

	//minimum distance between line and plane
	const scalar Distance(const Line3& p_Line, const Plane3& p_Plane);

	//==========
	// Plane-Plane
	//==========

	//minimum distance between planes
	const scalar Distance(const Plane3& p_Plane1, const Plane3& p_Plane2);

	//===========================================================================
	// Intersection queries
	//===========================================================================

	//lines share at least one point
	inline const bool Intersecting(const Line3& p_Line1, const Line3& p_Line2);

	//line and plane share at least one point
	inline const bool Intersecting(const Line3& p_Line, const Plane3& p_Plane);

	//planes share at least one line
	inline const bool Intersecting(const Plane3& p_Plane1, const Plane3& p_Plane2);

	//===========================================================================
	// Coincidence queries
	//===========================================================================

	//true if lines are coincident, sets unique point
	const bool Coincident(const Line3& p_Line1, const Line3& p_Line2, Vector3& p_Point);

	//true if line and plane are coincident, sets unique point
	const bool Coincident(const Line3& p_Line, const Plane3& p_Plane, Vector3& p_Point);

	//true if planes are coincident, sets unique point
	const bool Coincident(const Plane3& p_Plane1, const Plane3& p_Plane2, const Plane3& p_Plane3, Vector3& p_Point);

	//true if planes are coincident, sets unique line
	const bool Coincident(const Plane3& p_Plane1, const Plane3& p_Plane2, Line3& p_Line);
} // namespace Mathematics

#endif //#ifndef IncludedMathSimplicesH