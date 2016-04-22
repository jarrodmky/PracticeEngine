#ifndef IncludedMathPolygonH
#define IncludedMathPolygonH

//===========================================================================
// Filename:	Polyhedra.h
// Author:		Jarrod MacKay
// Description:	Defines a 3D Polygon.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "LinearAlgebra.h"
#include "Planar.h"
#include "Simplices.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	class Polygon
	{
	//Operators
	public:

		Polygon(const u32 p_Vertices, const u32 p_Faces)
			: Vertices(p_Vertices, Zero2())
			, Faces(p_Faces, Zero2())
		{}
		
	//Methods
	public:

		const bool Contains(const Vector2& p_Point) const
		{
			for(u32 i = 0; i < Faces.GetNumberOfElements(); ++i)
			{
				if(InPositiveHalfSpace(Faces(i), p_Point))
				{
					return false;
				}
			}
			return true;
		}

		const bool IsConvex() const
		{
			for(u32 i = 0; i < Vertices.Size(); ++i)
			{
				if(!Contains(Vertices(i)))
				{
					return false; 
				}
			}
			return true;
		}

	//Attributes
	public:

		PointCloud<2> Vertices;

		Abstracts::List<Plane2> Faces;
	};

	template <u32 t_Intervals, u32 t_Dimensions>
	class DOP
	{
	//Operators
	public:

		DOP()
		{}

	//Methods
	public:

	//Attributes
	public:

		Abstracts::Array<RealVector<t_Dimensions>, t_Intervals> s_Directions;

		VectorInterval<t_Dimensions> m_AxisBounds[t_Intervals];
	};

	typedef DOP<2, 2> Rectangle;

	typedef DOP<3, 3> SixDOP3;
	typedef DOP<4, 3> EightDOP3;
	typedef DOP<5, 3> TenDOP3;
	typedef DOP<6, 3> TwelveDOP3;

	
	class Polyhedra
	{
	//Operators
	public:

		Polyhedra(const u32 p_Vertices, const u32 p_Faces)
			: Vertices(p_Vertices, Zero3())
			, Faces(p_Faces, Zero3())
		{
			Assert(Vertices.GetNumberOfElements() > 4, "Polyhedron is too simple!");
		}
		
	//Methods
	public:

		const bool Contains(const Vector3& p_Point) const
		{
			for(u32 i = 0; i < Faces.GetNumberOfElements(); ++i)
			{
				if(InPositiveHalfSpace(Faces(i), p_Point))
				{
					return false;
				}
			}
			return true;
		}

		const bool IsConvex() const
		{
			for(u32 i = 0; i < Vertices.Size(); ++i)
			{
				if(!Contains(Vertices(i)))
				{
					return false; 
				}
			}
			return true;
		}

	//Attributes
	public:

		PointCloud<3> Vertices;

		Abstracts::List<Plane3> Faces;
	};


	void ConvexHull(const Abstracts::List<Vector3>& p_Points, Polyhedra& p_Hull)
	{
		//find the aabb of the point cloud
		const Vector3 maxX = ExtremePoint(p_Points, I());
		const Vector3 maxY = ExtremePoint(p_Points, J());
		const Vector3 maxZ = ExtremePoint(p_Points, K());
		const Vector3 minX = ExtremePoint(p_Points, -I());
		const Vector3 minY = ExtremePoint(p_Points, -J());
		const Vector3 minZ = ExtremePoint(p_Points, -K());
	}



} // namespace Mathematics

#endif //#ifndef IncludedMathPolygonH