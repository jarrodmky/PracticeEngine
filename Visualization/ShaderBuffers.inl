//===========================================================================
// Filename:	BufferSpecializations.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Class Definitions
//===========================================================================

namespace ShaderInformation
{
	struct PerCameraConstants
	{
		Mathematics::Matrix44 WorldToProjection = Mathematics::I4();
		Mathematics::Vector4 WorldPosition = MakeAffinePoint(Mathematics::Ones3());
	};

	struct PerObjectConstants
	{
		Mathematics::Matrix44 LocalToProjection = Mathematics::I4();
		Mathematics::Matrix44 LocalToWorld = Mathematics::I4();
		Mathematics::Matrix44 WorldToLocalTranpose = Mathematics::I4();
		Mathematics::Matrix44 ShadowLocalToTangent = Mathematics::I4();
		Mathematics::LinearColour Colour = Mathematics::ColourPallet::White;
	};

	struct LightingConstants
	{
		Mathematics::Vector4 LightWorldDirection = Mathematics::W() - Mathematics::Ones4();
		Mathematics::LinearColour LightColour = Mathematics::ColourPallet::White;
		Mathematics::LinearColour WorldAmbient = Mathematics::ColourPallet::Black;
	};

	struct PerMaterialConstants
	{
		Mathematics::LinearColour Emissive = Mathematics::ColourPallet::Black;
		Mathematics::LinearColour Ambient = Mathematics::ColourPallet::White;
		Mathematics::LinearColour Diffuse = Mathematics::ColourPallet::White;
		Mathematics::LinearColour Specular = Mathematics::ColourPallet::White;
		float Reflectance = Mathematics::Unity;
	};

	struct PostProcessConstants
	{
		s32 Index = 0;
		s32 Width = 0;
		s32 Height = 0;
		u32 Intensity = 0;
		bool DetectEdges = false;
		bool __padder = false;

	};

	struct WaterConstants
	{
		Mathematics::Matrix44 LocalToProjection;
		Mathematics::Matrix44 LocalToWorld;
		Mathematics::Matrix44 WorldToLocalTranpose;
		Mathematics::Matrix44 ReflectionLocalToTangent;
		Mathematics::Matrix44 RefractionLocalToTangent;
		Mathematics::LinearColour Colour;
		Mathematics::Vector4 Wave1 = Mathematics::Ones4(); //direction x, y, amplitude, frequency
		Mathematics::Vector4 Wave2 = Mathematics::Ones4() * 0.25f; //direction x, y, amplitude, frequency
		Mathematics::Vector4 Wave3 = Mathematics::Ones4() * 0.25f; //direction x, y, amplitude, frequency
		f32 Time;
	};

	struct ParticleEffectInfo
	{
		Mathematics::Vector3 TextureUp;
		Mathematics::LinearColour DiffuseColour;
		f32 TextureHeight;
		f32 TextureWidth;
	};
}

typedef ConstantBuffer<ShaderInformation::PerObjectConstants> PerObjectBuffer;
typedef ConstantBuffer<ShaderInformation::LightingConstants> SceneLightingBuffer;
typedef ConstantBuffer<ShaderInformation::PerCameraConstants> PerCameraBuffer;
typedef ConstantBuffer<ShaderInformation::PerMaterialConstants> PerMaterialBuffer;
typedef ConstantBuffer<ShaderInformation::PostProcessConstants> PostProcessConstantBuffer;
typedef ConstantBuffer<ShaderInformation::WaterConstants> WaterConstantBuffer;
typedef ConstantBuffer<ShaderInformation::ParticleEffectInfo> ParticleEffectConstantBuffer;