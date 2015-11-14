//===========================================================================
// Anon Definitions
//===========================================================================

namespace
{
	using VertexSet = std::vector<Mathematics::Vector>;
	using IndexSet = std::vector<u32>;

	const u32 NumSphereIterations = 9;

	void InitTetrahedron(VertexSet& p_Vertices, IndexSet& p_Indices)
	{
		p_Vertices.clear();
		p_Indices.clear();
		
		//vertices

		p_Vertices.push_back(Mathematics::Vector(1.0f, 1.0f, 1.0f).Direction());
		p_Vertices.push_back(Mathematics::Vector(-1.0f, -1.0f, 1.0f).Direction());
		p_Vertices.push_back(Mathematics::Vector(1.0f, -1.0f, -1.0f).Direction());
		p_Vertices.push_back(Mathematics::Vector(-1.0f, 1.0f, -1.0f).Direction());

		//indices
		p_Indices.push_back(0);
		p_Indices.push_back(1);
		p_Indices.push_back(2);
		
		p_Indices.push_back(0);
		p_Indices.push_back(2);
		p_Indices.push_back(3);
		
		p_Indices.push_back(1);
		p_Indices.push_back(3);
		p_Indices.push_back(2);
		
		p_Indices.push_back(0);
		p_Indices.push_back(3);
		p_Indices.push_back(1);
	}

	void FractureTrianglesToTetrahedrons(VertexSet& p_Vertices, IndexSet& p_Indices)
	{
		VertexSet FracturedVertices(0);
		IndexSet FracturedIndices(0);

		const u32 nV = p_Vertices.size();
		const u32 nI = p_Indices.size();

		for(u32 i = 0; i < nV; ++i)
		{
			FracturedVertices.push_back(p_Vertices[i].Direction());
		}

		for(u32 idx = 0; idx < nI; idx += 3)
		{
			//get centre point
			u32 centreIndex = FracturedVertices.size();
			Mathematics::Vector centre((p_Vertices[p_Indices[idx]] 
									   + p_Vertices[p_Indices[idx + 1]]
									   + p_Vertices[p_Indices[idx + 2]])
									   * 0.3333333333f);
			FracturedVertices.push_back(centre.Direction());

			//add three triangles around the centre
			for(u32 i = 0; i < 3; ++i)
			{
				FracturedIndices.push_back(p_Indices[idx + i]);
				FracturedIndices.push_back(p_Indices[idx + ((i + 1) % 3)]);
				FracturedIndices.push_back(centreIndex);
			}

		}

		p_Vertices = FracturedVertices;
		p_Indices = FracturedIndices;
	}

	void InitFractalSphere(VertexSet& p_Vertices, IndexSet& p_Indices)
	{
		InitTetrahedron(p_Vertices, p_Indices);

		for (u32 i = 0; i < NumSphereIterations; ++i)
		{
			FractureTrianglesToTetrahedrons(p_Vertices, p_Indices);
		}
	}

	void InitRingedSphere(VertexSet& p_Vertices, IndexSet& p_Indices)
	{
		InitTetrahedron(p_Vertices, p_Indices);

		for (u32 i = 0; i < NumSphereIterations; ++i)
		{
			FractureTrianglesToTetrahedrons(p_Vertices, p_Indices);
		}
	}
}

//===========================================================================
// Class Definitions
//===========================================================================

namespace Visualization
{
	template <typename t_MeshType>
	void MeshBuilder<t_MeshType>::CreateQuad(t_MeshType& p_Mesh)
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
	void MeshBuilder<t_MeshType>::CreateCube(t_MeshType& p_Mesh, const Mathematics::Point& p_Centre, const Mathematics::scalar p_Width)
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
	void MeshBuilder<t_MeshType>::CreateSphere(t_MeshType& p_Mesh, const Mathematics::Sphere& p_Sphere)
	{
		VertexSet vertices;
		IndexSet indices;

		//TODO:Apply transform to get on centre and radius

		InitFractalSphere(vertices, indices);

		const u32 numVs = vertices.size();
		const u32 numIs = indices.size();

		p_Mesh.Allocate(numVs, numIs);

		for(u32 j = 0; j < numVs; ++j)
		{
			p_Mesh.GetVertex(j).Position = vertices[j];
		}

		for(u32 j = 0; j < numVs; ++j)
		{
			p_Mesh.GetVertex(j).Colour = LinearColour(vertices[j].x, vertices[j].y, vertices[j].z, 1.0f);
		}

		for(u32 j = 0; j < numIs; ++j)
		{
			p_Mesh.GetIndex(j) = indices[j];
		}
	}
}