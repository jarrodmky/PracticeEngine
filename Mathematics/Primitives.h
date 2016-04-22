#ifndef IncludedMathPrimitivesH
#define IncludedMathPrimitivesH

//===========================================================================
// Filename:	Primitives.h
// Author:		Jarrod MacKay
// Description:	Defines procedures for constructing geometric objects
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "LinearAlgebra.h"
#include "Geometry.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	//===========================================================================
	// Basic definitions
	//===========================================================================

	template <u32 t_Dimensions>
	struct Vertex
	{
		Vertex(const RealVector<t_Dimensions>& p_Location
			, const RealVector<t_Dimensions>& p_Normal
			, const RealVector<t_Dimensions>& p_Tangent
			, const Vector2& p_Coordinate)
			: Position(p_Location)
			, Normal(p_Normal)
			, Tangent(p_Tangent)
			, Coordinate(p_Coordinate)
		{}

		RealVector<t_Dimensions> Position;
		RealVector<t_Dimensions> Normal;
		RealVector<t_Dimensions> Tangent;
		Vector2 Coordinate;
	};

	enum class TopologyIndexing
	{
		None,
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip
	};

	template <u32 t_Dimensions>
	struct TopologyData
	{
		std::vector< Vertex<t_Dimensions> > Vertices;
		std::vector<u32> Indices;
		TopologyIndexing Indexing;

		void Points(Mathematics::PointCloud<t_Dimensions>& p_Cloud)
		{
			const u32 numPoints = Vertices.size();
			p_Cloud.Populate(numPoints);

			for (u32 k = 0; k < numPoints; ++k)
			{
				p_Cloud(k) = Vertices[k].Position;
			}
		}
	};

	//===========================================================================
	// 3D Methods
	//===========================================================================

	using Vertex3 = Vertex<3>;
	using Topology3 = TopologyData<3>;


	void AddTriangle(Topology3& p_Topology
		, const Triangle3& p_Positions
		, const Vector3& p_Tangent
		, const Triangle2& p_Coordinates);

	void AddQuad(Topology3& p_Topology, const Quad3& p_Quad
		, const u32 p_Width, const u32 p_Height);

	void AddStandardTetrahedron(Topology3& p_Topology);

	void AddStandardCube(Topology3& p_Topology, const u32 p_Resolution, bool p_Inverted = false);

} // namespace Mathematics

#endif //#ifndef IncludedMathPrimitivesH