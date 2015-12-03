//===========================================================================
// Anon Definitions
//===========================================================================

namespace
{
	using FlatVertexSet = std::vector<Visualization::FlatVertex>;
	using ShadedVertexSet = std::vector<Visualization::ShadedVertex>;
	using IndexSet = std::vector<u32>;

	const u32 g_SphereResolution = 1; // controls poly level of sphere

	//void InitTetrahedron(ShadedVertexSet& p_Vertices, IndexSet& p_Indices)
	//{
	//	p_Vertices.clear();
	//	p_Indices.clear();
	//	
	//	//vertices
	//	p_Vertices.push_back(Mathematics::Vector(1.0f, 1.0f, 1.0f).Direction());
	//	p_Vertices.push_back(Mathematics::Vector(-1.0f, -1.0f, 1.0f).Direction());
	//	p_Vertices.push_back(Mathematics::Vector(1.0f, -1.0f, -1.0f).Direction());
	//	p_Vertices.push_back(Mathematics::Vector(-1.0f, 1.0f, -1.0f).Direction());

	//	//indices
	//	p_Indices.push_back(0);
	//	p_Indices.push_back(1);
	//	p_Indices.push_back(2);
	//	
	//	p_Indices.push_back(0);
	//	p_Indices.push_back(2);
	//	p_Indices.push_back(3);
	//	
	//	p_Indices.push_back(1);
	//	p_Indices.push_back(3);
	//	p_Indices.push_back(2);
	//	
	//	p_Indices.push_back(0);
	//	p_Indices.push_back(3);
	//	p_Indices.push_back(1);
	//}

	//void FractureTrianglesToTetrahedrons(VectorSet& p_Vertices, IndexSet& p_Indices)
	//{
	//	VectorSet FracturedVertices(0);
	//	IndexSet FracturedIndices(0);

	//	const u32 nV = p_Vertices.size();
	//	const u32 nI = p_Indices.size();

	//	for(u32 i = 0; i < nV; ++i)
	//	{
	//		FracturedVertices.push_back(p_Vertices[i].Direction());
	//	}

	//	for(u32 idx = 0; idx < nI; idx += 3)
	//	{
	//		//get centre point
	//		u32 centreIndex = FracturedVertices.size();
	//		Mathematics::Vector centre((p_Vertices[p_Indices[idx]] 
	//								   + p_Vertices[p_Indices[idx + 1]]
	//								   + p_Vertices[p_Indices[idx + 2]])
	//								   * 0.3333333333f);
	//		FracturedVertices.push_back(centre.Direction());

	//		//add three triangles around the centre
	//		for(u32 i = 0; i < 3; ++i)
	//		{
	//			FracturedIndices.push_back(p_Indices[idx + i]);
	//			FracturedIndices.push_back(p_Indices[idx + ((i + 1) % 3)]);
	//			FracturedIndices.push_back(centreIndex);
	//		}

	//	}

	//	p_Vertices = FracturedVertices;
	//	p_Indices = FracturedIndices;
	//}

	//void InitFractalSphere(VectorSet& p_Vertices, IndexSet& p_Indices, Visualization::IndexTopology& p_Topology)
	//{
	//	InitTetrahedron(p_Vertices, p_Indices);

	//	p_Topology = Visualization::TriangleList;

	//	for (u32 i = 0; i < g_SphereResolution; ++i)
	//	{
	//		FractureTrianglesToTetrahedrons(p_Vertices, p_Indices);
	//	}
	//}

	void InitRingedSphere(ShadedVertexSet& p_Vertices
						, IndexSet& p_Indices
						, Visualization::IndexTopology& p_Topology)
	{
		using namespace Mathematics;
		using namespace Visualization;
		using namespace ConstantScalars;

		u32 uRes = 2 * g_SphereResolution + 3;
		u32 vRes = g_SphereResolution + 2;
		f32 theta, phi;

		f32 deltaAngle = Pi / static_cast<f32>(g_SphereResolution + 1);

		Mathematics::Vector cartesianPosition;

		p_Topology = TriangleStrip;

		for (u32 v = 0; v < vRes; ++v)
		{
			for (u32 u = 0; u < uRes; ++u)
			{
				theta = static_cast<f32>(u) * deltaAngle;

				for (u32 k = 0; k < 2; ++k)
				{
					phi = static_cast<f32>(v + k) * deltaAngle;

					cartesianPosition = SphericalToCartesian(Vector(1.0f, phi, theta));

					p_Vertices.push_back(ShadedVertex(cartesianPosition, cartesianPosition, 
						coordinate(theta * OneOverTwoPi, phi * OneOverPi)));
					p_Indices.push_back(p_Vertices.size() - 1);
				}
			}
		}
	}

	void InitTestRingedSphere(ShadedVertexSet& p_Vertices
						, IndexSet& p_Indices
						, Visualization::IndexTopology& p_Topology)
	{
		using namespace Mathematics;
		using namespace Visualization;
		using namespace ConstantScalars;

		//polar angle => theta in [0, PI], paramed by u, inited by rings
		//axial angle => phi in [0, 2PI], paramed by v, inited by slices

		u32 rings = 2;//g_SphereResolution + 1;
		u32 slices = 4;//2* (g_SphereResolution + 1);

		f32 du = Unity / rings;
		f32 dv = Unity / slices;

		//create vertices
		Vector northPole = SphericalToCartesian(Vector(Unity, Zero, Zero));
		p_Vertices.push_back(ShadedVertex(northPole, northPole, coordinate(Zero, Zero)));

		for(u32 r = 1; r < rings; ++r)
		{
			f32 u(static_cast<f32>(r) * du);
			f32 theta(u * Pi);

			for(u32 l = 0; l < slices; ++l)
			{
				f32 v(static_cast<f32>(l)* dv);
				f32 phi(v * TwoPi);
				
				Vector current(SphericalToCartesian(Vector(Unity, theta, phi)));
				p_Vertices.push_back(ShadedVertex(current, current, coordinate(u, v)));
			}
		}
		
		Vector southPole = SphericalToCartesian(Vector(Unity, Pi, Zero));
		p_Vertices.push_back(ShadedVertex(southPole, southPole, coordinate(Unity, Unity)));


		//index vertices
		p_Topology = TriangleList;
		
		for(u32 i = 1; i <= slices; ++i)
		{
			p_Indices.push_back(i);
			p_Indices.push_back((i % slices) + 1);
			p_Indices.push_back(0);
		}
		
		u32 N = p_Vertices.size() - 1;
		u32 D = N - slices;
		for(u32 i = 1; i <= slices; ++i)
		{
			p_Indices.push_back((D - 1) + (i % slices) + 1);
			p_Indices.push_back(i);
			p_Indices.push_back(N);
		}
	}
}

//===========================================================================
// Class Definitions
//===========================================================================

namespace Visualization
{
	template <typename t_MeshType>
	void MeshBuilder::CreateQuad(t_MeshType& p_Mesh)
	{
		p_Mesh.Allocate(4, 6);

		p_Mesh.GetVertex(0).Position = Mathematics::Vector(-0.5f, -0.5f, 0.0f);
		p_Mesh.GetVertex(1).Position = Mathematics::Vector(-0.5f, 0.5f, 0.0f);
		p_Mesh.GetVertex(2).Position = Mathematics::Vector(0.5f, 0.5f, 0.0f);
		p_Mesh.GetVertex(3).Position = Mathematics::Vector(0.5f, -0.5f, 0.0f);

		p_Mesh.GetVertex(0).Colour = ConstantColours::Red;
		p_Mesh.GetVertex(1).Colour = ConstantColours::Blue;
		p_Mesh.GetVertex(2).Colour = ConstantColours::Yellow;
		p_Mesh.GetVertex(3).Colour = ConstantColours::Green;

		p_Mesh.GetIndex(0) = 0;
		p_Mesh.GetIndex(1) = 1;
		p_Mesh.GetIndex(2) = 2;
		p_Mesh.GetIndex(3) = 0;
		p_Mesh.GetIndex(4) = 2;
		p_Mesh.GetIndex(5) = 3;
	}

//----------------------------------------------------------------------------------------------------

	template <typename t_MeshType>
	void MeshBuilder::CreateCube(t_MeshType& p_Mesh, const Mathematics::Point& p_Centre, const Mathematics::scalar p_Width)
	{
		p_Mesh.Allocate(8, 36);

		const Mathematics::scalar h = p_Width * 0.5f;

		p_Mesh.GetVertex(0).Position = Mathematics::Vector(p_Centre.x + h, p_Centre.y - h, p_Centre.z - h);
		p_Mesh.GetVertex(1).Position = Mathematics::Vector(p_Centre.x + h, p_Centre.y + h, p_Centre.z - h);
		p_Mesh.GetVertex(2).Position = Mathematics::Vector(p_Centre.x + h, p_Centre.y + h, p_Centre.z + h);
		p_Mesh.GetVertex(3).Position = Mathematics::Vector(p_Centre.x + h, p_Centre.y - h, p_Centre.z + h);
		p_Mesh.GetVertex(4).Position = Mathematics::Vector(p_Centre.x - h, p_Centre.y - h, p_Centre.z - h);
		p_Mesh.GetVertex(5).Position = Mathematics::Vector(p_Centre.x - h, p_Centre.y + h, p_Centre.z - h);
		p_Mesh.GetVertex(6).Position = Mathematics::Vector(p_Centre.x - h, p_Centre.y + h, p_Centre.z + h);
		p_Mesh.GetVertex(7).Position = Mathematics::Vector(p_Centre.x - h, p_Centre.y - h, p_Centre.z + h);

		p_Mesh.GetVertex(0).Colour = ConstantColours::Black;
		p_Mesh.GetVertex(1).Colour = ConstantColours::Red;
		p_Mesh.GetVertex(2).Colour = ConstantColours::Magenta;
		p_Mesh.GetVertex(3).Colour = ConstantColours::Blue;
		p_Mesh.GetVertex(4).Colour = ConstantColours::Green;
		p_Mesh.GetVertex(5).Colour = ConstantColours::Yellow;
		p_Mesh.GetVertex(6).Colour = ConstantColours::White;
		p_Mesh.GetVertex(7).Colour = ConstantColours::Cyan;

		p_Mesh.GetIndex(0) = 0;
		p_Mesh.GetIndex(1) = 4;
		p_Mesh.GetIndex(2) = 1;
		p_Mesh.GetIndex(3) = 5;
		p_Mesh.GetIndex(4) = 1;
		p_Mesh.GetIndex(5) = 4;
		p_Mesh.GetIndex(6) = 0;
		p_Mesh.GetIndex(7) = 1;
		p_Mesh.GetIndex(8) = 2;
		p_Mesh.GetIndex(9) = 0;
		p_Mesh.GetIndex(10) = 2;
		p_Mesh.GetIndex(11) = 3;
		p_Mesh.GetIndex(12) = 1;
		p_Mesh.GetIndex(13) = 6;
		p_Mesh.GetIndex(14) = 2;
		p_Mesh.GetIndex(15) = 1;
		p_Mesh.GetIndex(16) = 5;
		p_Mesh.GetIndex(17) = 6;
		p_Mesh.GetIndex(18) = 3;
		p_Mesh.GetIndex(19) = 2;
		p_Mesh.GetIndex(20) = 7;
		p_Mesh.GetIndex(21) = 2;
		p_Mesh.GetIndex(22) = 6;
		p_Mesh.GetIndex(23) = 7;
		p_Mesh.GetIndex(24) = 0;
		p_Mesh.GetIndex(25) = 7;
		p_Mesh.GetIndex(26) = 4;
		p_Mesh.GetIndex(27) = 0;
		p_Mesh.GetIndex(28) = 3;
		p_Mesh.GetIndex(29) = 7;
		p_Mesh.GetIndex(30) = 6;
		p_Mesh.GetIndex(31) = 5;
		p_Mesh.GetIndex(32) = 4;
		p_Mesh.GetIndex(33) = 7;
		p_Mesh.GetIndex(34) = 6;
		p_Mesh.GetIndex(35) = 4;
	}

//----------------------------------------------------------------------------------------------------

	template <typename t_MeshType>
	void MeshBuilder::CreateSphere(t_MeshType& p_Mesh, const Mathematics::Sphere& p_Sphere)
	{
		ShadedVertexSet vertices(0);
		IndexSet indices(0);
		IndexTopology topology = PointList;

		InitTestRingedSphere(vertices, indices, topology);

		p_Mesh.Topology = topology;

		const u32 numVs = vertices.size();
		const u32 numIs = indices.size();

		p_Mesh.Allocate(numVs, numIs);

		for(u32 j = 0; j < numVs; ++j)
		{
			p_Mesh.GetVertex(j) = vertices[j];
		}

		for(u32 j = 0; j < numIs; ++j)
		{
			p_Mesh.GetIndex(j) = indices[j];
		}
	}
}