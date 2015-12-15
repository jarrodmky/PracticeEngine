#ifndef IncludedVisuBumpedSolidH
#define IncludedVisuBumpedSolidH

//===========================================================================
// Filename:	BumpedSolid.h
// Author:		Jarrod MacKay
// Description:	Describes a mesh that is assumed to remain "stiff" but can
//				still undergo linear transformations
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>
#include "System.h"
#include "Vertices.h"
#include "DataStructures.h"
#include "Buffers.h"
#include "Shaders.h"
#include "Mesh.h"
#include "Material.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class BumpedSolid
	{
	//Attributes
	public:

		Mathematics::Frame Transform;

	private:

		System& m_System;

		ConstantBuffer<ObjectBuffer> m_TransformBuffer;

		VertexBuffer<BumpedVertex> m_VertexBuffer;

		IndexBuffer<u32> m_IndexBuffer;

		u32 m_IndexCount;

	//Operators
	public:

		BumpedSolid(System& p_System);

		~BumpedSolid();

		NonCopyable(BumpedSolid);

	//Functions
	public:

		void Initialize(const Mesh<BumpedVertex>& p_Mesh);

		void Terminate();

		void Render(const Mathematics::Matrix44& p_Transform = Mathematics::I4());

	};
}

#endif // #ifndef IncludedVisuBumpedSolidH