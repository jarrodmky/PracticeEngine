#ifndef IncludedVisuModelH
#define IncludedVisuModelH

//===========================================================================
// Filename:	Model.h
// Author:		Jarrod MacKay
// Description:	
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "System.h"
#include "GraphicBasic.h"
#include "Mesh.h"
#include "Texture.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	//==========
	// Mesh Model
	//==========

	template <typename t_VertexType>
	class MeshModel
	{
		template <typename t_VertexType>
		friend class Renderer;

		//Operators
	public:

		MeshModel(System& p_System);

		virtual ~MeshModel();

		NonCopyable(MeshModel);

	//Methods
	public:

		void Initialize();

		void Update();

		void Terminate();

	//Attributes
	public:

		Mesh<t_VertexType> Mesh;

	private:

		VertexBuffer<t_VertexType> m_VertexBuffer;

		IndexBuffer<u32> m_IndexBuffer;

		Mathematics::TopologyIndexing m_Topology;

		System& m_System;
	};

	//==========
	// Solid Model
	//==========

	template <typename t_VertexType>
	class SolidModel
	{
		template <typename t_VertexType>
		friend class Renderer;

		//Attributes
	private:

		VertexBuffer<t_VertexType> m_VertexBuffer;

		IndexBuffer<u32> m_IndexBuffer;

		Mathematics::TopologyIndexing m_Topology;

		System& m_System;

		//Operators
	public:

		SolidModel(System& p_System);

		~SolidModel();

		NonCopyable(SolidModel);

		//Functions
	public:

		void Initialize(const Mesh<t_VertexType>& p_Mesh);

		void Terminate();
	};

#include "Model.inl"
}

#endif // #ifndef IncludedVisuModelH