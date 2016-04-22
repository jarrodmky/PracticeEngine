#ifndef IncludedVisuMaterialsH
#define IncludedVisuMaterialsH

//===========================================================================
// Filename:	Materials.h
// Author:		Jarrod MacKay
// Description:	Hold phong shaded data with texture.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>
#include "Texture.h"

#ifndef DEFAULT_EXPONENT 
#define DEFAULT_EXPONENT 10.0f
#endif

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class FancyMaterial
	{
		template <typename t_VertexType>
		friend class Renderer;

		//Operations
	public:

		FancyMaterial()
			: m_DiffuseTexture()
			, m_EmissiveTexture()
			, m_UmbralTexture()
			, m_NormalTexture()
			, m_BumpTexture()
			, m_SpecularTexture()
			, m_Emissive(Mathematics::ColourPallet::Black)
			, m_Ambient(Mathematics::ColourPallet::White)
			, m_Diffuse(Mathematics::ColourPallet::White)
			, m_Specular(Mathematics::ColourPallet::White)
			, m_Reflectance(DEFAULT_EXPONENT)
		{}

		//Methods
	public:

		void Initialize(System& p_System, const wchar_t* p_BumpFilename = nullptr
			, const wchar_t* p_DiffuseFilename = nullptr
			, const wchar_t* p_SpecularFilename = nullptr
			, const wchar_t* p_NormalFilename = nullptr
			, const wchar_t* p_EmissiveFilename = nullptr
			, const wchar_t* p_UmbralFilename = nullptr)
		{
			//bump texture
			m_BumpTexture.Initialize(p_System, (p_BumpFilename == nullptr) ?
				(L"../Data/Images/default_bump.jpg") : (p_BumpFilename));

			//diffuse texture
			m_DiffuseTexture.Initialize(p_System, (p_DiffuseFilename == nullptr) ?
				(L"../Data/Images/default_diffuse.jpg") : (p_DiffuseFilename));

			//specular texture
			m_SpecularTexture.Initialize(p_System, (p_SpecularFilename == nullptr) ?
				(L"../Data/Images/default_specular.jpg") : (p_SpecularFilename));

			//normal texture
			m_NormalTexture.Initialize(p_System, (p_NormalFilename == nullptr) ?
				(L"../Data/Images/default_normal.jpg") : (p_NormalFilename));

			//emissive texture
			m_EmissiveTexture.Initialize(p_System, (p_EmissiveFilename == nullptr) ?
				(L"../Data/Images/default_emissive.jpg") : (p_EmissiveFilename));

			//umbral texture
			m_UmbralTexture.Initialize(p_System, (p_UmbralFilename == nullptr) ?
				(L"../Data/Images/default_umbral.jpg") : (p_UmbralFilename));
		}

		void SetColours(const f32 p_Reflectance
			, const Mathematics::LinearColour& p_Ambient
			, const Mathematics::LinearColour& p_Diffuse
			, const Mathematics::LinearColour& p_Specular
			, const Mathematics::LinearColour& p_Emissive = Mathematics::ColourPallet::Black)
		{
			m_Reflectance = p_Reflectance;
			m_Emissive = p_Emissive;
			m_Ambient = p_Ambient;
			m_Diffuse = p_Diffuse;
			m_Specular = p_Specular;
			ApplyEnergyConservation();
		}

		void Terminate()
		{
			m_BumpTexture.Terminate();
			m_NormalTexture.Terminate();
			m_SpecularTexture.Terminate();
			m_DiffuseTexture.Terminate();
			m_EmissiveTexture.Terminate();
			m_UmbralTexture.Terminate();
		}

	private:

		inline void ApplyEnergyConservation()
		{
			using namespace Mathematics;
			//m_Diffuse *= OneOverPi;
			m_Specular *= 0.125f * OneOverPi * (m_Reflectance + 8.0f);
			Vector4 TotalColour = MakeVector(m_Diffuse) + MakeVector(m_Specular);
			if (TotalColour(0) > Unity)
			{
				scalar invComponent = Inverse(TotalColour(0));
				m_Diffuse.R *= invComponent;
				m_Specular.R *= invComponent;
			}
			if (TotalColour(1) > Unity)
			{
				scalar invComponent = Inverse(TotalColour(1));
				m_Diffuse.G *= invComponent;
				m_Specular.G *= invComponent;
			}
			if (TotalColour(2) > Unity)
			{
				scalar invComponent = Inverse(TotalColour(2));
				m_Diffuse.B *= invComponent;
				m_Specular.B *= invComponent;
			}
		}

		//Attributes
	private:

		//colour maps
		Visualization::Texture m_DiffuseTexture;
		Visualization::Texture m_EmissiveTexture;
		Visualization::Texture m_UmbralTexture;

		//vector maps
		Visualization::Texture m_NormalTexture;

		//intensity maps
		Visualization::Texture m_BumpTexture;
		Visualization::Texture m_SpecularTexture;

	public:

		Mathematics::LinearColour m_Emissive;
		Mathematics::LinearColour m_Ambient;
		Mathematics::LinearColour m_Diffuse;
		Mathematics::LinearColour m_Specular;
		f32 m_Reflectance;
	};


	class Material
	{
		template <typename t_VertexType>
		friend class Renderer;

	//Operations
	public:

		Material()
			: m_DiffuseTexture()
			, m_NormalTexture()
			, m_BumpTexture()
			, m_SpecularTexture()
			, m_Ambient(Mathematics::ColourPallet::White)
			, m_Diffuse(Mathematics::ColourPallet::White)
			, m_Specular(Mathematics::ColourPallet::White)
			, m_Reflectance(DEFAULT_EXPONENT)
		{}

	//Methods
	public:

		void Initialize(System& p_System, const wchar_t* p_BumpFilename = nullptr
			, const wchar_t* p_DiffuseFilename = nullptr
			, const wchar_t* p_SpecularFilename = nullptr
			, const wchar_t* p_NormalFilename = nullptr
			, const wchar_t* p_EmissiveFilename = nullptr
			, const wchar_t* p_UmbralFilename = nullptr)
		{
			//bump texture
			m_BumpTexture.Initialize(p_System, (p_BumpFilename == nullptr) ?
				(L"../Data/Images/default_bump.jpg") : (p_BumpFilename));

			//diffuse texture
			m_DiffuseTexture.Initialize(p_System, (p_DiffuseFilename == nullptr) ?
				(L"../Data/Images/default_diffuse.jpg") : (p_DiffuseFilename));

			//specular texture
			m_SpecularTexture.Initialize(p_System, (p_SpecularFilename == nullptr) ?
				(L"../Data/Images/default_spec.jpg") : (p_SpecularFilename));

			//normal texture
			m_NormalTexture.Initialize(p_System, (p_NormalFilename == nullptr) ?
				(L"../Data/Images/default_normal.jpg") : (p_NormalFilename));
		}

		void SetColours(const f32 p_Reflectance
			, const Mathematics::LinearColour& p_Ambient
			, const Mathematics::LinearColour& p_Diffuse
			, const Mathematics::LinearColour& p_Specular)
		{
			m_Ambient = p_Ambient;
			m_Diffuse = p_Diffuse;
			m_Specular = p_Specular;
			m_Reflectance = p_Reflectance;
		}

		void Terminate()
		{
			m_BumpTexture.Terminate();
			m_NormalTexture.Terminate();
			m_SpecularTexture.Terminate();
			m_DiffuseTexture.Terminate();
		}
		
		//Attributes
	private:

		//colour maps
		Visualization::Texture m_DiffuseTexture;

		//vector map
		Visualization::Texture m_NormalTexture;

		//intensity maps
		Visualization::Texture m_BumpTexture;
		Visualization::Texture m_SpecularTexture;

	public:

		Mathematics::LinearColour m_Ambient;
		Mathematics::LinearColour m_Diffuse;
		Mathematics::LinearColour m_Specular;
		f32 m_Reflectance;
	};
} // namespace Visualization

#undef DEFAULT_EXPONENT
#endif //ifndef IncludedVisuMaterialsH