#ifndef IncludedVisuSolidH
#define IncludedVisuSolidH

//===========================================================================
// Filename:	Solid.h
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
	class Solid
	{
	//Attributes
	public:

		Mathematics::Frame Transform;

	private:

		System& m_System;

		ConstantBuffer<ObjectBuffer> m_TransformBuffer;

		VertexBuffer<ShadedVertex> m_VertexBuffer;

		IndexBuffer<u32> m_IndexBuffer;

		u32 m_IndexCount;

	//Operators
	public:

		Solid(System& p_System);

		~Solid();

		NonCopyable(Solid);

	//Functions
	public:

		void Initialize(const Mesh<ShadedVertex>& p_Mesh);

		void Terminate();

		void Render();

	};
}

#endif // #ifndef IncludedVisuSolidH