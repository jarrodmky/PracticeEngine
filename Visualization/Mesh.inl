//===========================================================================
// Class Definitions
//===========================================================================

namespace Visualization
{

	template<typename t_VertexType>
	Mesh<t_VertexType>::Mesh()
		: m_Vertices()
		, m_Indices()
		, m_Topology(Mathematics::TopologyIndexing::None)
	{}

	//---------------------------------------------------------------------------

	template<typename t_VertexType>
	Mesh<t_VertexType>::~Mesh()
	{}

	//---------------------------------------------------------------------------

	template<typename t_VertexType>
	void Mesh<t_VertexType>::Allocate(const u32 p_NumVertices, const u32 p_NumIndices, const Mathematics::TopologyIndexing p_Topology)
	{
		Assert(p_NumVertices != 0, "Invalid vertex count!");
		Assert(p_NumIndices != 0, "Invalid index count!!");
		m_Vertices.Resize(p_NumVertices);
		m_Indices.Resize(p_NumIndices);
		m_Topology = p_Topology;
	}

	//---------------------------------------------------------------------------

	template<typename t_VertexType>
	void Mesh<t_VertexType>::Destroy()
	{
		m_Vertices.Destroy();
		m_Indices.Destroy();
		m_Topology = Mathematics::TopologyIndexing::None;
	}

}