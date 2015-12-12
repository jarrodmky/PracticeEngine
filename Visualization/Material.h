#ifndef IncludedVisuMaterialH
#define IncludedVisuMaterialH

//===========================================================================
// Filename:	Material.h
// Author:		Jarrod MacKay
// Description:	Hold phong shaded data with texture.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>
#include "Buffers.h"
#include "Pigment.h"
#include "Texture.h"
#include "Sampler.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{

	class Material
	{
	//Operations
	public:

		Material(System& p_System)
			: Reflectance(1.0f)
			, Emissive(Mathematics::ColourPallet::White)
			, Pigment(Mathematics::ColourPallet::White)
			, m_MaterialBuffer(p_System)
			, m_Texture()
			, m_Sampler()
		{}

	//Methods
	public:

		void Initialize(System& p_System, const MaterialBuffer& p_MaterialInfo, const wchar_t* p_Filename = nullptr)
		{
			m_MaterialBuffer.Allocate(&p_MaterialInfo);

			if (p_Filename == nullptr)
			{
				m_Texture.Initialize(p_System, L"../Data/Images/Default.jpg");
			}
			else
			{
				m_Texture.Initialize(p_System, p_Filename);
			}
			m_Sampler.Initialize(p_System, Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
		}

		void Terminate()
		{
			m_Sampler.Terminate();
			m_Texture.Terminate();

			m_MaterialBuffer.Free();
		}

		void Bind(System& p_System, u32 p_Index)
		{
			m_MaterialBuffer.BindToPixelShader(p_Index);
			m_Texture.BindPixelShader(p_System, p_Index);
			m_Sampler.BindPixelShader(p_System, p_Index);
		}

	//Attributes
	public:

		f32 Reflectance;

		Mathematics::LinearColour Emissive;

		Pigment Pigment;

	private:

		Visualization::ConstantBuffer<Visualization::MaterialBuffer> m_MaterialBuffer;

		Visualization::Texture m_Texture;

		Visualization::Sampler m_Sampler;
	};
} // namespace Visualization

#endif //ifndef IncludedVisuMaterialH