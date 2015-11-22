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
	struct TransformData
	{
		DirectX::XMMATRIX MatWorld;
		DirectX::XMMATRIX MatView;
		DirectX::XMMATRIX MatProjection;
	};

	struct MaterialData
	{
		LinearColour MaterialAmbient;
		LinearColour MaterialDiffuse;
		LinearColour MaterialSpecular;
	};

	struct LightingData
	{
		Mathematics::Vector ViewPosition;
		Mathematics::Vector LightDirection;
		LinearColour LightAmbient;
		LinearColour LightDiffuse;
		LinearColour LightSpecular;
	};

	class Solid
	{
	//Attributes
	public:

		Mesh<ShadedVertex> Mesh;

	private:

		System& m_GraphicsSystem;

		Material m_Material;

		TypedConstantBuffer<TransformData> m_TransformBuffer;

		TypedConstantBuffer<LightingData> m_LightingBuffer;

		TypedConstantBuffer<MaterialData> m_MaterialBuffer;
		
		VertexBuffer<ShadedVertex> m_VertexBuffer;

		IndexBuffer<u32> m_IndexBuffer;

		VertexShader<ShadedVertex> m_VertexShader;

		PixelShader m_PixelShader;

		u32 m_IndexCount;

	//Operators
	public:

		NonCopyable(Solid);

		Solid(System& p_GraphicsSystem);

		~Solid();

	//Functions
	public:

		void Initialize(const Material& p_Material);

		void Terminate();

		void Render(const TransformData& p_Transformations, const LightingData* p_Lighting) const;

	};
}

#endif // #ifndef IncludedVisuSolidH