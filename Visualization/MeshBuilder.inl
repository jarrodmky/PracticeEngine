//===========================================================================
// Filename:	MeshBuilder.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"

//===========================================================================
// Anon Definitions
//===========================================================================

namespace
{
	using FlatVertexSet = std::vector<Visualization::FlatVertex>;
	using ShadedVertexSet = std::vector<Visualization::ShadedVertex>;
	using BumpedVertexSet = std::vector<Visualization::BumpedVertex>;
	using IndexSet = std::vector<u32>;

	struct VertexData
	{
		VertexData(const Mathematics::Vector3& p_Position,
			const Mathematics::Vector2& p_TexelCoord)
			: Position(p_Position)
			, TexelCoord(p_TexelCoord)
		{}

		Mathematics::Vector3 Position;
		Mathematics::Vector2 TexelCoord;
	};

	const u32 g_SphereResolution = 30; // controls poly level of sphere

	void AddTriangle(const VertexData& p_A
				   , const VertexData& p_B
				   , const VertexData& p_C
				   , ShadedVertexSet& p_Vertices
				   , IndexSet& p_Indices)
	{
		using namespace Visualization;
		using namespace Mathematics;

		const u32 startIndex = p_Vertices.size();
		const Vector3 normal = ((p_B.Position - p_A.Position) * (p_C.Position - p_A.Position)).Direction();

		p_Vertices.push_back(ShadedVertex(p_A.Position, normal, p_A.TexelCoord));
		p_Vertices.push_back(ShadedVertex(p_B.Position, normal, p_B.TexelCoord));
		p_Vertices.push_back(ShadedVertex(p_C.Position, normal, p_C.TexelCoord));

		p_Indices.push_back(startIndex);
		p_Indices.push_back(startIndex + 1);
		p_Indices.push_back(startIndex + 2);
	}

//----------------------------------------------------------------------------------------------------

	void AddUnitSquare(const Mathematics::Frame& p_Orientation
		, ShadedVertexSet& p_Vertices
		, IndexSet& p_Indices)
	{
		using namespace Visualization;
		using namespace Mathematics;

		const Vector3 up(p_Orientation.GetUp());
		const Vector3 right(p_Orientation.GetRight());
		const Vector3 centre(p_Orientation.GetPosition());

		//describe vertices
		VertexData UpLeft(centre + up - right, MakeVector(0.0f, 0.0f));
		VertexData UpRight(centre + up + right, MakeVector(1.0f, 0.0f));
		VertexData DownLeft(centre - up - right, MakeVector(0.0f, 1.0f));
		VertexData DownRight(centre - up + right, MakeVector(1.0f, 1.0f));

		//add triangles
		AddTriangle(UpLeft, UpRight, DownRight, p_Vertices, p_Indices);
		AddTriangle(UpLeft, DownRight, DownLeft, p_Vertices, p_Indices);
	}

//----------------------------------------------------------------------------------------------------

	void AddUnitTetrahedron(ShadedVertexSet& p_Vertices, IndexSet& p_Indices)
	{
		using namespace Mathematics;
		
		//describe vertices
		VertexData Peak(MakeVector(1.0f, 1.0f, 1.0f).Direction(), MakeVector(0.5f, 0.0f));
		VertexData One(MakeVector(-1.0f, -1.0f, 1.0f).Direction(), MakeVector(0.5f, 1.0f));
		VertexData Two(MakeVector(1.0f, -1.0f, -1.0f).Direction(), MakeVector(0.5f, 1.0f));
		VertexData Three(MakeVector(-1.0f, 1.0f, -1.0f).Direction(), MakeVector(0.5f, 1.0f));

		//add triangles
		AddTriangle(Peak, One, Two, p_Vertices, p_Indices);
		AddTriangle(Peak, Two, Three, p_Vertices, p_Indices);
		AddTriangle(One, Three, Two, p_Vertices, p_Indices);
		AddTriangle(Peak, Three, One, p_Vertices, p_Indices);
	}

//----------------------------------------------------------------------------------------------------

	void AddUnitSphere(ShadedVertexSet& p_Vertices, IndexSet& p_Indices)
	{
		using namespace Mathematics;
		using namespace Visualization;

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

				Vector3 current(SphericalToCartesian(MakeVector(Unity, theta, phi)));
				p_Vertices.push_back(ShadedVertex(current, current, MakeVector(1.0f - u, v)));
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

//----------------------------------------------------------------------------------------------------

	void AddBumpSphere(BumpedVertexSet& p_Vertices, IndexSet& p_Indices)
	{
		using namespace Mathematics;
		using namespace Visualization;

		//axial angle => phi in [0, 2PI], paramed by u, counted by slices, tangent direction
		//polar angle => theta in [0, PI], paramed by v, counted by rings, binormal direction

		s32 rings = g_SphereResolution + 1;
		u32 slices = (g_SphereResolution + 1) << 1;

		f32 dv(Unity / rings);
		f32 du(Unity / (slices - 1));

		//create vertices
		for(s32 r = 0; r <= rings; ++r)
		{
			f32 v(static_cast<f32>(r) * dv);
			f32 theta(v * Pi);

			for(u32 l = 0; l < slices; ++l)
			{
				f32 u(static_cast<f32>(l)* du);
				f32 phi(u * TwoPi);
				
				Vector3 current(SphericalToCartesian(MakeVector(Unity, theta, phi)));
				p_Vertices.push_back(BumpedVertex(current, current, (current).Direction(), MakeVector(1.0f - u, v)));
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

//----------------------------------------------------------------------------------------------------

	void AddUnitCube(ShadedVertexSet& p_Vertices, IndexSet& p_Indices)
	{
		using namespace Mathematics;

		const Vector3 up(J());
		const Vector3 forward(K());
		const Vector3 right(I());

		Frame worker;
		worker.Set();
		
		//top
		worker.Set(right, up, up);
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//bottom
		worker.Set(-right, -up, -up);
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//right
		worker.Set(forward, right, right);
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//left
		worker.Set(-forward, -right, -right);
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//front
		worker.Set(up, forward, forward);
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//back
		worker.Set(-up, -forward, -forward);
		AddUnitSquare(worker, p_Vertices, p_Indices);
	}

//----------------------------------------------------------------------------------------------------

	void AddUnitInvertedCube(ShadedVertexSet& p_Vertices, IndexSet& p_Indices)
	{
		using namespace Mathematics;

		const Vector3 up(J());
		const Vector3 forward(K());
		const Vector3 right(I());

		Frame worker;
		worker.Set();
		
		//top
		worker.Set(right, -up, up);
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//bottom
		worker.Set(-right, up, -up);
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//right
		worker.Set(forward, -right, right);
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//left
		worker.Set(-forward, right, -right);
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//front
		worker.Set(up, -forward, forward);
		AddUnitSquare(worker, p_Vertices, p_Indices);

		//back
		worker.Set(-up, forward, -forward);
		AddUnitSquare(worker, p_Vertices, p_Indices);
	}

//----------------------------------------------------------------------------------------------------

	void AddFlatMesh(ShadedVertexSet& p_Vertices, IndexSet& p_Indices, const u32 p_Rows, const u32 p_Columns, const f32 p_Distance)
	{
		using namespace Mathematics;
		using namespace Visualization;

		Assert(p_Rows > 1 && p_Columns > 1, "No mesh can be made!");

		f32 rowDelta = Unity / static_cast<f32>(p_Rows - 1);
		f32 colDelta = Unity / static_cast<f32>(p_Columns - 1);

		f32 width(p_Distance / colDelta);
		f32 height(p_Distance / rowDelta);

		//create vertices
		for (u32 r = 0; r < p_Rows; ++r)
		{
			for (u32 c = 0; c < p_Columns; ++c)
			{
				p_Vertices.push_back(ShadedVertex(MakeVector(-width * 0.5f + static_cast<f32>(c)* p_Distance, 0.0f, -height * 0.5f + static_cast<f32>(r)* p_Distance)
					, J()
					, MakeVector(static_cast<f32>(c) * colDelta, static_cast<f32>(r) * rowDelta)));
			}
		}

		Assert(p_Vertices.size() == p_Rows * p_Columns, "Mesh creation went awry!");

		//index vertices	
		for (u32 r = 0; r < p_Rows - 1; ++r)
		{
			for (u32 c = 0; c < p_Columns - 1; ++c)
			{
				u32 ul((r * p_Rows) + c);
				u32 ur((r * p_Rows) + c + 1);
				u32 dl(((r + 1) * p_Rows) + c);
				u32 dr(((r + 1) * p_Rows) + c + 1);

				p_Indices.push_back(ul);
				p_Indices.push_back(ur);
				p_Indices.push_back(dr);

				p_Indices.push_back(ul);
				p_Indices.push_back(dr);
				p_Indices.push_back(dl);
			}
		}
		Assert(p_Indices.size() == 6 * (p_Rows - 1) * (p_Columns - 1), "Mesh creation went awry!");
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
	void MeshBuilder::CreateCube(t_MeshType& p_Mesh, const Mathematics::Vector3& p_Centre, const Mathematics::scalar p_Width)
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
	void MeshBuilder::CreateInvertedCube(t_MeshType& p_Mesh, const Mathematics::Vector3& p_Centre, const Mathematics::scalar p_Width)
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
	
	//----------------------------------------------------------------------------------------------------
		
	template <typename t_MeshType>
	static void MeshBuilder::CreateBumpedSphere(t_MeshType& p_Mesh, const Mathematics::Sphere& p_Sphere)
	{
		BumpedVertexSet vertices(0);
		IndexSet indices(0);

		p_Mesh.Topology = TriangleList;
		AddBumpSphere(vertices, indices);

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

	//----------------------------------------------------------------------------------------------------
	
	template <typename t_MeshType>
	void MeshBuilder::CreateHeightMesh(t_MeshType& p_Mesh, const std::string& p_Filename)
	{
		ShadedVertexSet vertices(0);
		IndexSet indices(0);

		f32 maxHeight = 3.0f;

		p_Mesh.Topology = TriangleList;

		Serialization::BMP::ColourTable table;
		if (Serialization::Loader::ReadBmpToColourTable(p_Filename, table))
		{
			AddFlatMesh(vertices, indices, table.GetNumberOfRows(), table.GetNumberOfColumns(), 0.5f);
		}

		const u32 numVs = vertices.size();
		const u32 numIs = indices.size();

		for (u32 j = 0; j < numVs; ++j)
		{
			vertices[j].Position.y = table(j).LengthSquared() * maxHeight;
		}

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
	void MeshBuilder::CreateHeightMesh(t_MeshType& p_Mesh, const u32 p_Rows, const u32 p_Columns)
	{
		using namespace Mathematics;

		ShadedVertexSet vertices(0);
		IndexSet indices(0);

		p_Mesh.Topology = TriangleList;

		AddFlatMesh(vertices, indices, p_Rows, p_Columns, 0.5f);

		const u32 numVs = vertices.size();
		const u32 numIs = indices.size();

		TwoVarFxn g = [](const scalar x, const scalar z) -> const scalar
		{
			return std::sin(x) * std::cos(z) + 2.0f * (std::sin(x * 0.5f) * std::cos(z * 0.5f));
		};

		TwoVarFxn f = [&](const scalar x, const scalar z) -> const scalar
		{
			return -(x * x/1000.0f + z * z/1000.0f) + g(x, z);
		};

		TwoVarFxn dgdx = [](const scalar x, const scalar z) -> const scalar
		{
			return std::cos(x) * std::cos(z) + 0.5f * std::cos(x * 0.5f) * std::cos(z * 0.5f);
		};

		TwoVarFxn dgdz = [](const scalar x, const scalar z) -> const scalar
		{
			return -std::sin(x) * std::sin(z) - 0.5f * std::sin(x * 0.5f) * std::sin(z * 0.5f);
		};

		TwoVarFld DF = [&](const scalar x, const scalar z) -> const Vector3
		{
			return MakeVector( -(2.0f * x)/1000.0f + dgdx(x, z)
						 , -1
						 , -(2.0f * z)/1000.0f + dgdz(x, z));
		};

		for (u32 j = 0; j < numVs; ++j)
		{
			const scalar& x(vertices[j].Position(1));
			const scalar& z(vertices[j].Position(3));

			vertices[j].Position(2) = f(x,z);
			vertices[j].Normal = MakeVector(DF(x, z));
		}

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
}