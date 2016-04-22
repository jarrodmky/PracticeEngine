#ifndef IncludedMathFrustumH
#define IncludedMathFrustumH

//===========================================================================
// Filename:	Frustum.h
// Author:		Jarrod MacKay
// Description:	Describes the frustum hexahedron
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Planar.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	class Frustum
	{
	//Definitions

		enum NamedEdge : u16
		{
			LeftTop = 0x1 << 0,
			LeftBottom = 0x1 << 1,
			RightTop = 0x1 << 2,
			RightBottom = 0x1 << 3,
			BottomNear = 0x1 << 4,
			BottomFar = 0x1 << 5,
			TopNear = 0x1 << 6,
			TopFar = 0x1 << 7,
			LeftNear = 0x1 << 8,
			LeftFar = 0x1 << 9,
			RightNear = 0x1 << 10,
			RightFar = 0x1 << 11
		};

		enum NamedVertex : u8
		{
			LeftBottomNear = 0x1 << 0,
			LeftBottomFar = 0x1 << 1,
			LeftTopNear = 0x1 << 2,
			LeftTopFar = 0x1 << 3,
			RightBottomNear = 0x1 << 4,
			RightBottomFar = 0x1 << 5,
			RightTopNear = 0x1 << 6,
			RightTopFar = 0x1 << 7
		};

	//Operators
	public:

		Frustum()
			: Frustum(PiOverTwo, 0.5625f, 1000.0f)
		{}

		Frustum(const scalar p_FieldOfView
			, const scalar p_AspectRatio
			, const scalar p_FarZ
			, const scalar p_NearZ)
			: Frustum(Inverse(std::tan(p_FieldOfView * 0.5f))
			, p_AspectRatio
			, Plane3(MakePlane(Zero, Zero, Unity, p_FarZ))
			, Plane3(MakePlane(Zero, Zero, -Unity, -p_NearZ)))
		{}

		Frustum(const scalar p_FieldOfView
			, const scalar p_AspectRatio
			, const scalar p_FarZ)
			: Frustum(Inverse(std::tan(p_FieldOfView * 0.5f))
			, p_AspectRatio
			, Plane3(MakePlane(Zero, Zero, Unity, p_FarZ)))
		{}

	private:

		Frustum(const scalar p_FocalLength
			, const scalar p_AspectRatio
			, const Plane3& p_FarZ)
			: Frustum(p_FocalLength
			, p_AspectRatio
			, p_FarZ
			, Plane3(MakePlane(Zero, Zero, -Unity, -p_FocalLength)))
		{}

		Frustum(const scalar p_FocalLength
			, const scalar p_AspectRatio
			, const Plane3& p_FarZ
			, const Plane3& p_NearZ)
			: Frustum(p_FocalLength
					, std::sqrt(p_FocalLength * p_FocalLength + p_AspectRatio * p_AspectRatio)
					, std::sqrt(p_FocalLength * p_FocalLength + Unity)
					, p_AspectRatio
					, p_FarZ
					, p_NearZ)
		{}

		Frustum(const scalar p_FocalLength
			, const scalar p_DenomYZ
			, const scalar p_DenomXZ
			, const scalar p_AspectRatio
			, const Plane3& p_FarZ
			, const Plane3& p_NearZ)
			: m_Near(p_NearZ)
			, m_Far(p_FarZ)
			, m_Bottom(MakePlane(Zero, p_FocalLength / p_DenomYZ, -p_AspectRatio / p_DenomYZ, Zero))
			, m_Top(MakePlane(Zero, -p_FocalLength / p_DenomYZ, -p_AspectRatio / p_DenomYZ, Zero))
			, m_Left(MakePlane(p_FocalLength / p_DenomXZ, Zero, -Unity / p_DenomXZ, Zero))
			, m_Right(MakePlane(-p_FocalLength / p_DenomXZ, Zero, -Unity / p_DenomXZ, Zero))
		{}



	//Methods
	public:

		void GetEdge(const NamedEdge p_Edge, Line3& p_Line) const;
		bool GetVertex(const NamedVertex p_Vertex, Vector3& p_Point) const
		{
			switch (p_Vertex)
			{
			case LeftBottomNear :
				return Coincident(m_Left, m_Bottom, m_Near, p_Point);
			case LeftBottomFar:
				return Coincident(m_Left, m_Bottom, m_Far, p_Point);
			case LeftTopNear:
				return Coincident(m_Left, m_Top, m_Near, p_Point);
			case LeftTopFar:
				return Coincident(m_Left, m_Top, m_Far, p_Point);
			case RightBottomNear:
				return Coincident(m_Right, m_Bottom, m_Near, p_Point);
			case RightBottomFar:
				return Coincident(m_Right, m_Bottom, m_Far, p_Point);
			case RightTopNear:
				return Coincident(m_Right, m_Top, m_Near, p_Point);
			case RightTopFar:
				return Coincident(m_Right, m_Top, m_Far, p_Point);
			default:
				Halt("Vertex is unknown");
				return false;
			}
		}

		void GetViewParameters(scalar& p_LeftX, scalar& p_RightX, scalar& p_BottomY, scalar& p_TopY) const
		{
			Vector3 leftTop;
			Vector3 rightTop;
			Vector3 leftBottom;
			Vector3 rightBottom;

			GetVertex(LeftTopNear, leftTop);
			GetVertex(RightTopNear, rightTop);
			GetVertex(LeftBottomNear, leftBottom);
			GetVertex(RightBottomNear, rightBottom);

			Assert(leftTop(0) == leftBottom(0), "Left x is inconsistent.");
			Assert(rightTop(0) == rightBottom(0), "Left x is inconsistent.");
			Assert(leftBottom(0) == rightBottom(0), "Left x is inconsistent.");
			Assert(leftTop(0) == rightTop(0), "Left x is inconsistent.");

			p_LeftX = leftTop(0) + leftBottom(0) * 0.5f;
			p_RightX = rightTop(0) + rightBottom(0) * 0.5f;
			p_BottomY = leftBottom(1) + rightBottom(1) * 0.5f;
			p_TopY = leftTop(1) + rightTop(1) * 0.5f;
		}

	//Attributes
	private:

		Plane3 m_Near;
		Plane3 m_Far;
		Plane3 m_Bottom;
		Plane3 m_Top;
		Plane3 m_Left;
		Plane3 m_Right;

	};
}

#endif // #ifndef IncludedMathFrustumH