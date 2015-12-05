//===========================================================================
// Anon Definitions
//===========================================================================

namespace
{
	using FlatVertexSet = std::vector<Visualization::FlatVertex>;
	using ShadedVertexSet = std::vector<Visualization::ShadedVertex>;
	using IndexSet = std::vector<u32>;

	struct VertexData
	{
		VertexData(const Mathematics::Vector& p_Position,
			const Mathematics::coordinate& p_TexelCoord)
			: Position(p_Position)
			, TexelCoord(p_TexelCoord)
		{}

		Mathematics::Vector Position;
		Mathematics::coordinate TexelCoord;
	};

	const u32 g_SphereResolution = 20; // controls poly level of sphere

	void AddTriangle(const VertexData& p_A
				   , const VertexData& p_B
				   , const VertexData& p_C
				   , ShadedVertexSet& p_Vertices
				   , IndexSet& p_Indices)
	{
		using namespace Visualization;
		using namespace Mathematics;

		const u32 startIndex = p_Vertices.size();
		const Vector normal = ((p_B.Position - p_A.Position) * (p_C.Position - p_A.Position)).Direction();

		p_Vertices.push_back(ShadedVertex(p_A.Position, normal, p_A.TexelCoord));
		p_Vertices.push_back(ShadedVertex(p_B.Position, normal, p_B.TexelCoord));
		p_Vertices.push_back(ShadedVertex(p_C.Position, normal, p_C.TexelCoord));

		p_Indices.push_back(startIndex);
		p_Indices.push_back(startIndex + 1);
		p_Indices.push_back(startIndex + 2);
	}

	void AddUnitSquare(const Mathematics::Frame& p_Orientation
		, ShadedVertexSet& p_Vertices
		, IndexSet& p_Indices)
	{
		using namespace Visualization;
		using namespace Mathematics;
		using namespace ConstantScalars;

		const Vector up = p_Orientation.GetUp();
		const Vector right = p_Orientation.GetRight();
		const Vector centre = p_Orientation.GetPosition().PositionVector();

		//describe vertices
		VertexData UpLeft(centre + up - right, coordinate(0.0f, 0.0f));
		VertexData UpRight(centre + up + right, coordinate(1.0f, 0.0f));
		VertexData DownLeft(centre - up - right, coordinate(0.0f, 1.0f));
		VertexData DownRight(centre - up + right, coordinate(1.0f, 1.0f));

		//add triangles
		AddTriangle(UpLeft, UpRight, DownRight, p_Vertices, p_Indices);
		AddTriangle(UpLeft, DownRight, DownLeft, p_Vertices, p_Indices);
	}

	void AddUnitTetrahedron(ShadedVertexSet& p_Vertices, IndexSet& p_Indices)
	{
		using namespace Mathematics;
		
		//describe vertices
		VertexData Peak(Vector(1.0f, 1.0f, 1.0f).Direction(), coordinate(0.5f, 0.0f));
		VertexData One(Vector(-1.0f, -1.0f, 1.0f).Direction(), coordinate(0.5f, 1.0f));
		VertexData Two(Vector(1.0f, -1.0f, -1.0f).Direction(), coordinate(0.5f, 1.0f));
		VertexData Three(Vector(-1.0f, 1.0f, -1.0f).Direction(), coordinate(0.5f, 1.0f));

		//add triangles
		AddTriangle(Peak, One, Two, p_Vertices, p_Indices);
		AddTriangle(Peak, Two, Three, p_Vertices, p_Indices);
		AddTriangle(One, Three, Two, p_Vertices, p_Indices);
		AddTriangle(Peak, Three, One, p_Vertices, p_Indices);
	}

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

	void AddUnitSphere(ShadedVertexSet& p_Vertices, IndexSet& p_Indices)
	{
		using namespace Mathematics;
		using namespace Visualization;
		using namespace ConstantScalars;

		//axial angle => phi in [0, 2PI], paramed by u, counted by slices
		//polar angle => theta in [0, PI], paramed by v, counted by rings

		s32 rings = g_SphereResolution + 1;
		u32 slices = 2* (g_SphereResolution + 1);

		f32 dv = Unity / rings;
		f32 du = Unity / (slices - 1);

		//create vertices
		for(s32 r = 0; r <= rings; ++r)
		{
			f32 v(static_cast<f32>(r) * dv);
			f32 theta(v * Pi);

			for(u32 l = 0; l < slices; ++l)
			{
				f32 u(static_cast<f32>(l)* du);
				f32 phi(u * TwoPi);
				
				Vector current(SphericalToCartesian(Vector(Unity, theta, phi)));
				p_Vertices.push_back(ShadedVertex(current, current, coordinate(1.0f - u, v)));
			}
		}

		Assert(p_Vertices.size() == (rings + 1) * slices, "Sphere creation went awry!");

		//index vertices		
		for(u32 k = 0; k < slices; ++k)
		{
			//const u32 north(0 * slices);
			//const u32 south(1 * slices);
			const u32 west(k);
			const u32 east((k + 1) % slices);

			p_Indices.push_back(west);
			p_Indices.push_back(slices + west);
			p_Indices.push_back(slices + east);

			for (s32 j = 1; j <= rings - 2; ++j)
			{
				const u32 north(j * slices);
				const u32 south((j + 1) * slices);

				p_Indices.push_back(north + east);
				p_Indices.push_back(north + west);
				p_Indices.push_back(south + west);

				p_Indices.push_back(north + east);
				p_Indices.push_back(south + west);
				p_Indices.push_back(south + east);
			}

			//const u32 north((rings - 1) * slices);
			//const u32 south(rings * slices);

			p_Indices.push_back((rings - 1) * slices + west);
			p_Indices.push_back(rings * slices + east);
			p_Indices.push_back((rings - 1) * slices + east);
		}

		Assert(p_Indices.size() == 6 * (rings - 1) * slices, "Sphere creation went awry!");
	}

	void AddUnitCube(ShadedVertexSet& p_Vertices, IndexSet& p_Indices)
	{
		using namespace Mathematics;
		using namespace ConstantVectors;

		const Vector up(J);
		const Vector forward(K);
		const Vector right(I);

		Frame worker;
		worker.Set();
		
		//top
		worker.Set(right, up, Point(up));
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//bottom
		worker.Set(-right, -up, Point(-up));
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//right
		worker.Set(forward, right, Point(right));
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//left
		worker.Set(-forward, -right, Point(-right));
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//front
		worker.Set(up, forward, Point(forward));
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//back
		worker.Set(-up, -forward, Point(-forward));
		AddUnitSquare(worker, p_Vertices, p_Indices);
	}

	void AddUnitInvertedCube(ShadedVertexSet& p_Vertices, IndexSet& p_Indices)
	{
		using namespace Mathematics;
		using namespace ConstantVectors;

		const Vector up(J);
		const Vector forward(K);
		const Vector right(I);

		Frame worker;
		worker.Set();

		//top
		worker.Set(right, -up, Point(up));
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//bottom
		worker.Set(-right, up, Point(-up));
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//right
		worker.Set(forward, -right, Point(right));
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//left
		worker.Set(-forward, right, Point(-right));
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//front
		worker.Set(up, -forward, Point(forward));
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//back
		worker.Set(-up, forward, Point(-forward));
		AddUnitSquare(worker, p_Vertices, p_Indices);
	}
}

//===========================================================================
// Class Definitions
//===========================================================================

namespace Visualization
{
	//template <typename t_MeshType>
	//void MeshBuilder::CreateQuad(t_MeshType& p_Mesh)
	//{
	//	p_Mesh.Allocate(4, 6);

	//	p_Mesh.GetVertex(0).Position = Mathematics::Vector(-0.5f, -0.5f, 0.0f);
	//	p_Mesh.GetVertex(1).Position = Mathematics::Vector(-0.5f, 0.5f, 0.0f);
	//	p_Mesh.GetVertex(2).Position = Mathematics::Vector(0.5f, 0.5f, 0.0f);
	//	p_Mesh.GetVertex(3).Position = Mathematics::Vector(0.5f, -0.5f, 0.0f);

	//	p_Mesh.GetVertex(0).Colour = ConstantColours::Red;
	//	p_Mesh.GetVertex(1).Colour = ConstantColours::Blue;
	//	p_Mesh.GetVertex(2).Colour = ConstantColours::Yellow;
	//	p_Mesh.GetVertex(3).Colour = ConstantColours::Green;

	//	p_Mesh.GetIndex(0) = 0;
	//	p_Mesh.GetIndex(1) = 1;
	//	p_Mesh.GetIndex(2) = 2;
	//	p_Mesh.GetIndex(3) = 0;
	//	p_Mesh.GetIndex(4) = 2;
	//	p_Mesh.GetIndex(5) = 3;
	//}

//----------------------------------------------------------------------------------------------------

	template <typename t_MeshType>
	void MeshBuilder::CreateCube(t_MeshType& p_Mesh, const Mathematics::Point& p_Centre, const Mathematics::scalar p_Width)
	{
		ShadedVertexSet vertices(0);
		IndexSet indices(0);

		p_Mesh.Topology = TriangleList;
		AddUnitCube(vertices, indices);

		const u32 numVs = vertices.size();
		const u32 numIs = indices.size();

		p_Mesh.Allocate(numVs, numIs);

		for (u32 j = 0; j < numVs; ++j)
		{
			p_Mesh.GetVertex(j) = vertices[j];
		}

		for (u32 j = 0; j < numIs; ++j)
		{
			p_Mesh.GetIndex(j) = indices[j];
		}
	}

//----------------------------------------------------------------------------------------------------

	template <typename t_MeshType>
	void MeshBuilder::CreateInvertedCube(t_MeshType& p_Mesh, const Mathematics::Point& p_Centre, const Mathematics::scalar p_Width)
	{
		ShadedVertexSet vertices(0);
		IndexSet indices(0);

		p_Mesh.Topology = TriangleList;
		AddUnitInvertedCube(vertices, indices);

		const u32 numVs = vertices.size();
		const u32 numIs = indices.size();

		p_Mesh.Allocate(numVs, numIs);

		for (u32 j = 0; j < numVs; ++j)
		{
			p_Mesh.GetVertex(j) = vertices[j];
		}

		for (u32 j = 0; j < numIs; ++j)
		{
			p_Mesh.GetIndex(j) = indices[j];
		}
	}

//----------------------------------------------------------------------------------------------------

	template <typename t_MeshType>
	void MeshBuilder::CreateSphere(t_MeshType& p_Mesh, const Mathematics::Sphere& p_Sphere)
	{
		ShadedVertexSet vertices(0);
		IndexSet indices(0);

		p_Mesh.Topology = TriangleList;
		AddUnitSphere(vertices, indices);

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