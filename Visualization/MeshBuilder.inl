//===========================================================================
// Filename:	MeshBuilder.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "GraphicBasic.h"

namespace Visualization
{
	template <typename t_Type>
	class Mesh;
}

	//===========================================================================
	// Vertex Data Abstraction
	//===========================================================================
	
	template <typename t_VertexType>
	inline t_VertexType Data2Vertex(const Mathematics::Vertex3& p_Data)
	{
		Halt("Unimplemented!");
		return t_VertexType();
	}

	template <>
	inline Visualization::BasicVertex Data2Vertex<Visualization::BasicVertex>(const Mathematics::Vertex3& p_Data)
	{
		return Visualization::BasicVertex(p_Data.Position);
	}

	template <>
	inline Visualization::PaintedVertex Data2Vertex<Visualization::PaintedVertex>(const Mathematics::Vertex3& p_Data)
	{
		return Visualization::PaintedVertex(p_Data.Position, p_Data.Coordinate);
	}

	template <>
	inline Visualization::LitVertex Data2Vertex<Visualization::LitVertex>(const Mathematics::Vertex3& p_Data)
	{
		return Visualization::LitVertex(p_Data.Position, Mathematics::ColourPallet::White, p_Data.Normal);
	}

	template <>
	inline Visualization::SurfaceVertex Data2Vertex<Visualization::SurfaceVertex>(const Mathematics::Vertex3& p_Data)
	{
		return Visualization::SurfaceVertex(p_Data.Position, p_Data.Normal, p_Data.Coordinate);
	}

	template <>
	inline Visualization::FramedVertex Data2Vertex<Visualization::FramedVertex>(const Mathematics::Vertex3& p_Data)
	{
		return Visualization::FramedVertex(p_Data.Position, p_Data.Normal, p_Data.Tangent, p_Data.Coordinate);
	}

	template <typename t_VertexType>
	void TransferVertexData(const Mathematics::Topology3& p_Source, std::vector<t_VertexType>& p_Destination)
	{
		using namespace Visualization;
		p_Destination.resize(p_Source.Vertices.size());
		for (u32 i = 0; i < p_Destination.size(); ++i)
		{
			p_Destination[i] = Data2Vertex<t_VertexType>(p_Source.Vertices[i]);
		}
	}

	template<typename t_VertexType>
	void TransferData(const Mathematics::Topology3& p_Source, Visualization::Mesh<t_VertexType>& p_Mesh)
	{
		std::vector<t_VertexType> vertices;
		TransferVertexData(p_Source, vertices);

		const u32 numVs = vertices.size();
		const u32 numIs = p_Source.Indices.size();

		p_Mesh.Allocate(numVs, numIs, p_Source.Indexing);

		for(u32 j = 0; j < numVs; ++j)
		{
			p_Mesh.GetVertex(j) = vertices[j];
		}

		for(u32 j = 0; j < numIs; ++j)
		{
			p_Mesh.GetIndex(j) = p_Source.Indices[j];
		}
	}

//===========================================================================
// Class Definitions
//===========================================================================

namespace Visualization
{
	template <typename t_MeshType>
	static void MeshBuilder::CreateQuad(t_MeshType& p_Mesh
										, const Mathematics::Quad3& p_Quad
							   , const Mathematics::LinearColour& p_FlatColour)
	{
		Topology3 data;
		AddQuad(data, p_Quad, 1, 1);
		TransferData(data, p_Mesh);

	}

	//----------------------------------------------------------------------------------------------------

	template <typename t_MeshType>
	void MeshBuilder::CreateUnitCube(t_MeshType& p_Mesh
							   , const bool p_Inverted
							   , const Mathematics::LinearColour& p_FlatColour)
	{
		Topology3 data;

		if(p_Inverted)
		{
			AddUnitCubeInv(data, p_FlatColour);
		}
		else
		{
			AddUnitCube(data, p_FlatColour);
		}

		TransferData(data, p_Mesh);

	}

	//----------------------------------------------------------------------------------------------------

	template <typename t_MeshType>
	void MeshBuilder::CreateUnitSphere(t_MeshType& p_Mesh
							   , const u32 p_Resolution
							   , const Mathematics::LinearColour& p_FlatColour)
	{
		Topology3 data;

		AddStandardRingedSphere(data, p_Resolution);

		TransferData(data, p_Mesh);
	}

	//----------------------------------------------------------------------------------------------------

	template <typename t_MeshType>
	static void MeshBuilder::CreateUnitTorus(t_MeshType& p_Mesh, const u32 p_Resolution
		, const Mathematics::LinearColour& p_FlatColour)
	{
		Topology3 data;

		AddStandardRingedTorus(data, p_Resolution);

		TransferData(data, p_Mesh);
	}

	//----------------------------------------------------------------------------------------------------

	template <typename t_MeshType>
	void MeshBuilder::CreateHeightMesh(t_MeshType& p_Mesh, const std::string& p_Filename)
	{
		Topology3 data;

		const f32 maxHeight = 3.0f;

		Serialization::BMP::ColourTable table;
		if(Serialization::Loader::ReadBmpToColourTable(p_Filename, table))
		{

			AddQuad(data, Quad3(WorldForward(), WorldRight()), table.Columns(), table.Rows());
		}

		for (u32 i = 0; i < data.Data.size(); ++i)
		{
			data.Data[i].Position(1) = table[i].LengthSquared() * maxHeight;
		}

		TransferData(data, p_Mesh);
	}

	//----------------------------------------------------------------------------------------------------

	template <typename t_MeshType>
	void MeshBuilder::CreateHeightMesh(t_MeshType& p_Mesh, const u32 p_Rows, const u32 p_Columns)
	{
		using namespace Mathematics;

		Topology3 data;

		AddQuad(data, Quad3(-K(), -I()), p_Rows, p_Columns);

		for (u32 i = 0; i < data.Vertices.size(); ++i)
		{
			const scalar& x(data.Vertices[i].Position(0));
			const scalar& z(data.Vertices[i].Position(2));

			//data.Vertices[i].Position(1) = f(x, z);
			data.Vertices[i].Normal = -J();
			data.Vertices[i].Tangent = -I();
		}

		TransferData(data, p_Mesh);
	}

	//----------------------------------------------------------------------------------------------------

	template <typename t_MeshType>
	static void CreateModelMesh(t_MeshType& p_Mesh, FILE* p_File)
	{
		Topology3 data;
		u32 numMeshes = 0;
		fscanf_s(file, "numMeshes: %d\n", &numMeshes);
		for (u32 m = 0; m < numMeshes; ++m)
		{
			u32 numVertices = 0;
			u32 numIndices = 0;
			const u32 firstVertex = topology.Vertices.size();
			const u32 firstIndex = topology.Indices.size();
			fscanf_s(file, "numVertices: %d\n", &numVertices);
			fscanf_s(file, "numIndices: %d\n", &numIndices);
			Mathematics::Topology3 topology;
			topology.Indexing = TopologyIndexing::TriangleList;
			topology.Vertices.resize(numVertices + firstVertex);
			topology.Indices.resize(numIndices + firstIndex);
			for (u32 v = firstVertex; v < (firstVertex + numVertices); ++v)
			{
				Vertex3& vertex = topology.Vertices[v];
				fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n"
					, &vertex.Position(0), &vertex.Position(1), &vertex.Position(2)
					, &vertex.Normal(0), &vertex.Normal(1), &vertex.Normal(2)
					, &vertex.Tangent(0), &vertex.Tangent(1), &vertex.Tangent(2)
					, &vertex.TextureCoord(0), &vertex.TextureCoord(1));
			}

			for (u32 i = firstIndex; i < (firstIndex + numIndices); i += 3)
			{
				Vertex3& indexA = topology.Indices[i];
				Vertex3& indexB = topology.Indices[i + 1];
				Vertex3& indexC = topology.Indices[i + 2];
				fscanf_s(file, "%d %d %d\n", &indexA, &indexB, &indexC);
			}
		}

		TransferData(data, p_Mesh);
	}
}