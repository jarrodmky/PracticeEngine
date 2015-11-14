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

#include "System.h"
#include "Vertices.h"
#include "Buffers.h"
#include "ConstantBuffer.h"
#include "Shaders.h"
#include "Mesh.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	struct TransformData
	{
		DirectX::XMMATRIX MatWorld;
		DirectX::XMMATRIX MatView;
		DirectX::XMMATRIX MatProjection;
	};

	class Solid
	{
	//Attributes
	public:

		Mesh<BasicVertex> Mesh;

	private:

		System& m_GraphicsSystem;

		TypedConstantBuffer<TransformData> m_TransformBuffer;
		
		VertexBuffer<BasicVertex> m_VertexBuffer;

		IndexBuffer<u32> m_IndexBuffer;

		VertexShader m_VertexShader;

		PixelShader m_PixelShader;

		u32 m_IndexCount;

	//Operators
	public:

		NonCopyable(Solid);

		Solid(System& p_GraphicsSystem);

		~Solid();

	//Functions
	public:

		void Initialize();

		void Terminate();

		void Render(const TransformData& p_Transformations) const;

	};
}

#endif // #ifndef IncludedVisuSolidH