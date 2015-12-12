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

#include "DataStructures.h"

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

		void Allocate(const u32 p_NumVertices, const u32 p_numIndices);

		void Destroy();
		
		t_VertexType& GetVertex(const u32 p_Index) const;
		
		u32& GetIndex(const u32 p_Index) const;
		
		const t_VertexType* const GetVertices() const	{ return &m_VertexBuffer[0]; }

		const u32* const GetIndices() const			{ return &m_IndexBuffer[0]; }

		u32 GetVertexCount() const				{ return m_VertexCount; }

		u32 GetIndexCount() const				{ return m_IndexCount; }

	//Attributes
	private:

		std::unique_ptr<t_VertexType[]> m_VertexBuffer;
		std::unique_ptr<u32[]> m_IndexBuffer;

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