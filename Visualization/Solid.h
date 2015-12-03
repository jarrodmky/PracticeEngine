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
#include "LinearColour.h"
#include "Vertices.h"
#include "Buffers.h"
#include "ConstantBuffer.h"
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

		Material m_Material;

		TypedConstantBuffer<TransformBuffer> m_TransformBuffer;

		TypedConstantBuffer<LightingBuffer> m_LightingBuffer;

		TypedConstantBuffer<MaterialBuffer> m_MaterialBuffer;
		
		VertexBuffer<ShadedVertex> m_VertexBuffer;

		IndexBuffer<u32> m_IndexBuffer;

		VertexShader<ShadedVertex> m_VertexShader;

		PixelShader m_PixelShader;

		u32 m_IndexCount;

	//Operators
	public:

		NonCopyable(Solid);

		Solid(System& p_System);

		~Solid();

	//Functions
	public:

		void Initialize(const Material& p_Material, const Mesh<ShadedVertex>& p_Mesh);

		void Terminate();

		void Render(const TransformBuffer& p_Transformations, const LightingBuffer* p_Lighting) const;

	};
}

#endif // #ifndef IncludedVisuSolidH