#ifndef IncludedVisuMeshH
#define IncludedVisuMeshH

//===========================================================================
// Filename:	Mesh.h
// Author:		Jarrod MacKay
// Description:	Contains vertex and index data on the CPU side
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Abstracts.h>
#include <Mathematics.h>
#include "GraphicBasic.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{

	template<typename t_VertexType>
	class Mesh
	{
	//Definitions
	public:

		using VertexType = t_VertexType;

	//Operators
	public:

		Mesh();

		~Mesh();

		NonCopyable(Mesh<t_VertexType>);

	//Methods
	public:

		void Allocate(const u32 p_NumVertices, const u32 p_numIndices, const Mathematics::TopologyIndexing p_Topology);

		void Destroy();
		
		inline const t_VertexType& GetVertex(const u32 p_Index) const { return m_Vertices[p_Index]; }
		
		inline const u32& GetIndex(const u32 p_Index) const { return m_Indices[p_Index]; }

		inline t_VertexType& GetVertex(const u32 p_Index) { return m_Vertices[p_Index]; }

		inline u32& GetIndex(const u32 p_Index) { return m_Indices[p_Index]; }
		
		const t_VertexType* const GetVertices() const	{ return m_Vertices.Raw(); }

		const u32* const GetIndices() const	{ return m_Indices.Raw(); }

		u32 GetVertexCount() const				{ return m_Vertices.Size(); }

		u32 GetIndexCount() const				{ return m_Indices.Size(); }

		Mathematics::TopologyIndexing GetTopology() const	{ return m_Topology; }

	//Attributes
	private:

		Abstracts::DynamicArray<t_VertexType> m_Vertices;
		Abstracts::DynamicArray<u32> m_Indices;
		Mathematics::TopologyIndexing m_Topology;
	};

	typedef Mesh<LitVertex> LitMesh;
	typedef Mesh<PaintedVertex> PaintedMesh;
	typedef Mesh<FramedVertex> FramedMesh;
}

//===========================================================================
// Inline Definitions
//===========================================================================

#include "Mesh.inl"

#endif // #ifndef IncludedVisuMeshH