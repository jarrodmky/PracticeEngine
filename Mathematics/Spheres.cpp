//===========================================================================
// Filename:	Spheres.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "LinearAlgebra.h"
#include "Primitives.h"
#include "Spheres.h"

//===========================================================================
// Class Definitions
//===========================================================================

void Mathematics::AddStandardRingedSphere(Topology3& p_Topology, const u32 p_Resolution)
{
	const u32 initNumVertices = p_Topology.Vertices.size();
	const u32 initNumIndices = p_Topology.Indices.size();

	f32 rad = 0.5f;

	//polar angle => phi in [0, PI], paramed by v, counted by height, bitanget direction
	//axial angle => theta in [0, 2PI], paramed by u, counted by width, tangent direction

	u32 height = p_Resolution;
	u32 width = p_Resolution << 1;

	f32 dv(Unity / (height + 1));
	f32 du(Unity / (width - 1));

	//create vertices
	Vector3 northPole = 0.5f * J();
	p_Topology.Vertices.push_back(Vertex3(northPole, northPole, -K(), MakeVector(0.5f, Zero)));

	for (u32 j = 0; j < height; ++j)
	{
		f32 v(static_cast<f32>(j + 1) * dv);
		f32 phi(v * Pi);

		for (u32 i = 0; i < width; ++i)
		{
			f32 u(static_cast<f32>(i)* du);
			f32 theta(u * TwoPi);

			Vector3 current(SphericalToCartesian(MakeVector(rad, phi, theta)));
			Vector3 tangent((current * WorldUp()).Direction());
			p_Topology.Vertices.push_back(Vertex3(current, current.Direction(), tangent, MakeVector(u, v)));
		}
	}

	Vector3 southPole = 0.5f * -J();
	p_Topology.Vertices.push_back(Vertex3(southPole, southPole, K(), MakeVector(0.5f, Unity)));

	const u32 lastIndex = 2 * (1 + p_Resolution * p_Resolution) - 1;
	Assert(p_Topology.Vertices.size() - initNumVertices == lastIndex + 1, "Sphere creation went awry!");

	//index vertices		
	for (u32 i = 2; i <= width; ++i)
	{
		p_Topology.Indices.push_back(0);
		p_Topology.Indices.push_back(i);
		p_Topology.Indices.push_back(i - 1);
	}

	p_Topology.Indices.push_back(0);
	p_Topology.Indices.push_back(1);
	p_Topology.Indices.push_back(width);

	for (u32 i = 1; i < width; ++i)
	{
		for (u32 j = 0; j < height - 1; ++j)
		{
			const u32 ul = j * width + i;
			const u32 ur = j * width + i + 1;
			const u32 ll = (j + 1) * width + i;
			const u32 lr = (j + 1) * width + i + 1;

			p_Topology.Indices.push_back(ul);
			p_Topology.Indices.push_back(ur);
			p_Topology.Indices.push_back(lr);

			p_Topology.Indices.push_back(ul);
			p_Topology.Indices.push_back(lr);
			p_Topology.Indices.push_back(ll);
		}
	}

	for (u32 j = 0; j < height - 1; ++j)
	{
		const u32 ul = (j + 1) * width;
		const u32 ur = j * width + 1;
		const u32 ll = (j + 2) * width;
		const u32 lr = (j + 1) * width + 1;

		p_Topology.Indices.push_back(ul);
		p_Topology.Indices.push_back(ur);
		p_Topology.Indices.push_back(lr);

		p_Topology.Indices.push_back(ul);
		p_Topology.Indices.push_back(lr);
		p_Topology.Indices.push_back(ll);
	}

	for (u32 i = 1; i < width; ++i)
	{
		p_Topology.Indices.push_back(lastIndex);
		p_Topology.Indices.push_back((height - 1) * width + i);
		p_Topology.Indices.push_back((height - 1) * width + i + 1);
	}

	p_Topology.Indices.push_back(lastIndex);
	p_Topology.Indices.push_back(height * width);
	p_Topology.Indices.push_back((height - 1) * width + 1);

	Assert(p_Topology.Indices.size() - initNumIndices == 12 * p_Resolution * p_Resolution, "Sphere creation went awry!");

	p_Topology.Indexing = TopologyIndexing::TriangleList;
}



void Mathematics::AddStandardRingedTorus(Topology3& p_Topology, const u32 p_Resolution)
{
	const u32 initNumVertices = p_Topology.Vertices.size();
	const u32 initNumIndices = p_Topology.Indices.size();
	
	Vector3 centre = Zero3();
	Vector3 outCentre = 0.5f * WorldRight();
	Vector3 outOffset = 0.125f * WorldRight();

	//major angle => major in [0, 2PI], paramed by u, tangent direction
	//minor angle => minor in [0, 2PI], paramed by v, bitanget direction

	u32 slices = p_Resolution * 3;

	const f32 da(Inverse(static_cast<f32>(slices - 1)));
	Quaternion majRot(WorldUp(), da * TwoPi);

	for (u32 idx = 0; idx < slices; ++idx)
	{
		f32 u = static_cast<f32>(idx) * da;
		Vector3 tangent = (outCentre * WorldUp()).Direction();
		Quaternion minRot(tangent, da * TwoPi);
		for (u32 jdx = 0; jdx < slices; ++jdx)
		{
			f32 v = static_cast<f32>(jdx) * da;
			Vector3 surfacePoint = centre + outCentre + outOffset;
			p_Topology.Vertices.push_back(Vertex3(surfacePoint, outOffset.Direction(), tangent, MakeVector(u, v)));

			minRot.Rotate(outOffset);
		}
		majRot.Rotate(outCentre);
		majRot.Rotate(outOffset);
	}

	Assert(p_Topology.Vertices.size() - initNumVertices == slices * slices, "Sphere creation went awry!");

	for (u32 i = 0; i < slices; ++i)
	{
		for (u32 j = 0; j < slices; ++j)
		{
			const u32 ul(j * slices + i);
			const u32 ur(j * slices + ((i + 1) % slices));
			const u32 ll(((j + 1) % slices) * slices + i);
			const u32 lr(((j + 1) % slices) * slices + ((i + 1) % slices));

			p_Topology.Indices.push_back(ul);
			p_Topology.Indices.push_back(lr);
			p_Topology.Indices.push_back(ur);

			p_Topology.Indices.push_back(ul);
			p_Topology.Indices.push_back(ll);
			p_Topology.Indices.push_back(lr);
		}
	}
	
	Assert(p_Topology.Indices.size() - initNumIndices == 6 * slices * slices, "Sphere creation went awry!");

	p_Topology.Indexing = TopologyIndexing::TriangleList;

}