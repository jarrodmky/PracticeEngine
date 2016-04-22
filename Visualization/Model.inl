//====================================================================================================
// Filename:	Model.cpp
// Created by:	Jarrod MacKay
//====================================================================================================

//====================================================================================================
// Function Definitions
//====================================================================================================

//==========
// Mesh Model
//==========

template <typename t_VertexType>
MeshModel<t_VertexType>::MeshModel(System& p_System)
	: m_System(p_System)
	, m_Mesh()
	, m_Texture(p_System)
	, m_VertexBuffer(p_System)
	, m_IndexBuffer(p_System)
	, m_Topology(TopologyIndexing::None)
{}

template <typename t_VertexType>
MeshModel<t_VertexType>::~MeshModel()
{}

template <typename t_VertexType>
void MeshModel<t_VertexType>::Initialize()
{
	FILE* file = nullptr;
	errno_t error = fopen_s(&file, p_Filename, "r");
	if (file == nullptr)
	{
		Log("Failed to read from input file! Error : %d", error);
	}

	MeshBuilder::CreateModelMesh(m_Mesh, file);
	m_VertexBuffer->Allocate(m_Mesh->GetVertices(), m_Mesh->GetVertexCount());
	m_IndexBuffer->Allocate(m_Mesh->GetIndices(), m_Mesh->GetIndexCount());

	u32 numTextures = 0;
	fscanf_s(file, "numTextures: %d\n", &numTextures);
	for(u32 t = 0; t < numTextures; ++t)
	{
		char readBuffer[256];
		fscanf_s(file, "%s\n", readBuffer, 256);

		wchar_t wbuffer[256];
		mbstowcs_s(nullptr, wbuffer, readBuffer, 256);

		//m_Texture.Initialize(wbuffer); //TODO : call texture manager
	}
}

template <typename t_VertexType>
void MeshModel<t_VertexType>::Terminate()
{
	for (std::vector<Part>::iterator P = m_Parts.begin(); P != m_Parts.end(); ++P)
	{
		P->MeshHandle->Destroy();
		ProperlyDelete(P->MeshHandle);
		P->VtxBuffer->Free();
		ProperlyDelete(P->VtxBuffer);
		P->IdxBuffer->Free();
		ProperlyDelete(P->IdxBuffer);
		P->TextureHandle->Terminate();
		ProperlyDelete(P->TextureHandle);
	}
	m_Parts.clear();
	m_ObjBuffer.Free();
}

//==========
// Solid Model
//==========

template <typename t_VertexType>
SolidModel<t_VertexType>::SolidModel(System& p_System)
	: m_VertexBuffer(p_System)
	, m_IndexBuffer(p_System)
	, m_Topology(Mathematics::TopologyIndexing::None)
	, m_System(p_System)
{}

template <typename t_VertexType>
SolidModel<t_VertexType>::~SolidModel(){}

template <typename t_VertexType>
void SolidModel<t_VertexType>::Initialize(const Mesh<t_VertexType>& p_Mesh)
{
	m_VertexBuffer.Allocate(p_Mesh.GetVertices(), p_Mesh.GetVertexCount());
	m_IndexBuffer.Allocate(p_Mesh.GetIndices(), p_Mesh.GetIndexCount());
	m_Topology = p_Mesh.GetTopology();
}

template <typename t_VertexType>
void SolidModel<t_VertexType>::Terminate()
{
	m_VertexBuffer.Free();
	m_IndexBuffer.Free();
}