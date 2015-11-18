#ifndef IncludedVisuMeshH
#define IncludedVisuMeshH

//===========================================================================
// Filename:	Mesh.h
// Author:		Jarrod MacKay
// Description:	
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

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

		using Vertex = t_VertexType;

	//Operators
	public:

		NonCopyable(Mesh<t_VertexType>);

		Mesh();

		~Mesh();

		void Allocate(const u32 p_NumVertices, const u32 p_numIndices);

		void Destroy();
		
		t_VertexType& GetVertex(const u32 p_Index) const;
		
		u32& GetIndex(const u32 p_Index) const;
		
		const t_VertexType* GetVertices() const	{ return m_VertexBuffer; }

		const u32* GetIndices() const			{ return m_IndexBuffer; }

		u32 GetVertexCount() const				{ return m_VertexCount; }

		u32 GetIndexCount() const				{ return m_IndexCount; }

	//Attributes
	private:

		t_VertexType* m_VertexBuffer;
		u32* m_IndexBuffer;

		u32 m_VertexCount;
		u32 m_IndexCount;

	public:

		IndexTopology Topology;
	};
}

//===========================================================================
// Inline Definitions
//===========================================================================

#include "Mesh.inl"

#endif // #ifndef IncludedVisuMeshH