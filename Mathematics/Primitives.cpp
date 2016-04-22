//===========================================================================
// Filename:	Primitives.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Primitives.h"

using namespace Mathematics;

//===========================================================================
// Class Definitions
//===========================================================================

void Mathematics::AddTriangle(Topology3& p_Topology
	, const Triangle3& p_Positions
	, const Vector3& p_Tangent
	, const Triangle2& p_Coordinates)
{
	const u32 initNumVertices = p_Topology.Vertices.size();
	const u32 initNumIndices = p_Topology.Indices.size();

	const u32 startIndex = p_Topology.Vertices.size();
	const Vector3 normal = p_Positions.Normal();

	p_Topology.Vertices.push_back(Vertex3(p_Positions.First, normal, p_Tangent, p_Coordinates.First));
	p_Topology.Vertices.push_back(Vertex3(p_Positions.Second, normal, p_Tangent, p_Coordinates.Second));
	p_Topology.Vertices.push_back(Vertex3(p_Positions.Third, normal, p_Tangent, p_Coordinates.Third));

	Assert(p_Topology.Indexing == TopologyIndexing::TriangleList, "Not prepared for indexing.");

	p_Topology.Indices.push_back(startIndex + 0);
	p_Topology.Indices.push_back(startIndex + 1);
	p_Topology.Indices.push_back(startIndex + 2);

	Assert(p_Topology.Vertices.size() - initNumVertices == 3, "vertexing went awry!");
	Assert(p_Topology.Indices.size() - initNumIndices == 3, "indexing went awry!");
}

//----------------------------------------------------------------------------------------------------

void Mathematics::AddQuad(Topology3& p_Topology, const Quad3& p_Quad
	, const u32 p_Width, const u32 p_Height)
{
	const u32 initNumVertices = p_Topology.Vertices.size();
	const u32 initNumIndices = p_Topology.Indices.size();
	const Vector3 normal = p_Quad.GetNormal();

	//add vertices
	const Vector2 halfWH = 0.5f * MakeVector(static_cast<f32>(p_Width), static_cast<f32>(p_Height));
	const Vector2 invWH = MakeVector(Inverse(static_cast<f32>(p_Width)), Inverse(static_cast<f32>(p_Height)));

	for (u32 jdx = 0; jdx <= p_Height; ++jdx)
	{
		f32 j = static_cast<f32>(jdx);
		for (u32 idx = 0; idx <= p_Width; ++idx)
		{
			f32 i = static_cast<f32>(idx);
			Vector3 local = p_Quad.U * (i - halfWH(0)) + p_Quad.V * (j - halfWH(1));
			p_Topology.Vertices.push_back(Vertex3(p_Quad.Centre + local, normal, p_Quad.U.Direction()
				, MakeVector(i * invWH(0), j * invWH(1))));
		}
	}

	Assert(p_Topology.Vertices.size() - initNumVertices
		== (p_Width + 1) * (p_Height + 1), "vertexing went awry!");

	//index vertices	
	for (u32 c = 0; c < p_Width; ++c)
	{
		for (u32 r = 0; r < p_Height; ++r)
		{
			u32 ul(r * (p_Width + 1) + c);
			u32 ur(r * (p_Width + 1) + c  + 1);
			u32 dl((r + 1) * (p_Width + 1) + c);
			u32 dr((r + 1) * (p_Width + 1) + c + 1);

			p_Topology.Indices.push_back(ul);
			p_Topology.Indices.push_back(ur);
			p_Topology.Indices.push_back(dr);

			p_Topology.Indices.push_back(ul);
			p_Topology.Indices.push_back(dr);
			p_Topology.Indices.push_back(dl);
		}
	}
	Assert(p_Topology.Indices.size() - initNumIndices == 6 * p_Width * p_Height, "indexing went awry!");

	p_Topology.Indexing = TopologyIndexing::TriangleList;
}

//----------------------------------------------------------------------------------------------------

void Mathematics::AddStandardTetrahedron(Topology3& p_Topology)
{
	//describe vertices
	Vector3 peakLoc = MakeVector(1.0f, 1.0f, 1.0f).Direction();
	Vector3 OneLoc = MakeVector(-1.0f, -1.0f, 1.0f).Direction();
	Vector3 TwoLoc = MakeVector(1.0f, -1.0f, -1.0f).Direction();
	Vector3 ThreeLoc = MakeVector(-1.0f, 1.0f, -1.0f).Direction();

	Vector2 peakTex = MakeVector(0.5f, 0.0f);
	Vector2 OneTex = MakeVector(0.5f, 1.0f);
	Vector2 TwoTex = MakeVector(0.5f, 1.0f);
	Vector2 ThreeTex = MakeVector(0.5f, 1.0f);


	//add triangles
	AddTriangle(p_Topology, Triangle3(peakLoc, OneLoc, TwoLoc), (TwoLoc - OneLoc).Direction()
		, Triangle2(peakTex, OneTex, TwoTex));
	AddTriangle(p_Topology, Triangle3(peakLoc, TwoLoc, ThreeLoc), (ThreeLoc - TwoLoc).Direction()
		, Triangle2(peakTex, TwoTex, ThreeTex));
	AddTriangle(p_Topology, Triangle3(OneLoc, ThreeLoc, TwoLoc), ((TwoLoc - OneLoc) + (ThreeLoc - OneLoc)).Direction()
		, Triangle2(OneTex, ThreeTex, TwoTex));
	AddTriangle(p_Topology, Triangle3(peakLoc, ThreeLoc, OneLoc), (OneLoc - ThreeLoc).Direction()
		, Triangle2(peakTex, ThreeTex, OneTex));
}

//----------------------------------------------------------------------------------------------------

void Mathematics::AddStandardCube(Topology3& p_Topology, const u32 p_Resolution, bool p_Inverted)
{
	const Vector3 up(WorldUp() * 0.5f);
	const Vector3 forward(WorldForward() * 0.5f);
	const Vector3 right(WorldRight() * 0.5f);

	if (p_Inverted)
	{
		//top
		AddQuad(p_Topology, Quad3(forward, -right, up), p_Resolution, p_Resolution);

		//bottom
		AddQuad(p_Topology, Quad3(-forward, -right, -up), p_Resolution, p_Resolution);

		//right
		AddQuad(p_Topology, Quad3(-up, forward, right), p_Resolution, p_Resolution);

		//left
		AddQuad(p_Topology, Quad3(up, forward, -right), p_Resolution, p_Resolution);

		//front
		AddQuad(p_Topology, Quad3(-up, -right, forward), p_Resolution, p_Resolution);

		//back
		AddQuad(p_Topology, Quad3(up, -right, -forward), p_Resolution, p_Resolution);
	}
	else
	{
		//top
		AddQuad(p_Topology, Quad3(forward, right, up), p_Resolution, p_Resolution);

		//bottom
		AddQuad(p_Topology, Quad3(-forward, right, -up), p_Resolution, p_Resolution);

		//right
		AddQuad(p_Topology, Quad3(-up, -forward, right), p_Resolution, p_Resolution);

		//left
		AddQuad(p_Topology, Quad3(up, -forward, -right), p_Resolution, p_Resolution);

		//front
		AddQuad(p_Topology, Quad3(-up, right, forward), p_Resolution, p_Resolution);

		//back
		AddQuad(p_Topology, Quad3(up, right, -forward), p_Resolution, p_Resolution);
	}
}