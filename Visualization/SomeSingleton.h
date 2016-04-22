#ifndef IncludedVisuSomeSingletonH
#define IncludedVisuSomeSingletonH

//===========================================================================
// Filename:	SomeSingleton.h
// Author:		Jarrod MacKay
// Description:	Renders meshes, sets textures etc.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class System;
	class Material;
	struct PostProcessInfo;

	namespace SomeSingleton
	{
		enum class ShadingMode
		{
			None,
			Lit,
			Shading,
			LitShading,
			FullShading,
			DepthMapping,
			Postprocessing
		};

		void Initialize(System& p_System, bool p_ShadowMapping);

		void Terminate();

		//toggles
		void SetShading(ShadingMode p_Mode);
		void TogglePostProcess();
		void ToggleCelShade();

		//rendering
		void StartShadowMapping();
		void EndShadowMapping();
		void StartScene(ShadingMode p_Mode);
		void EndScene();
		void PostProcess();
		void ShowLightDepth();
		PostProcessInfo& PostProcessSettings();
		const Material& DefaultMaterial();

		//rendering
		void RenderSphere(const Mathematics::Frame& p_Frame, const f32 p_Radius, const Material& p_Material = SomeSingleton::DefaultMaterial());
		void RenderSphere(const Mathematics::Sphere3& p_Sphere, const Mathematics::Quaternion& p_Orientation, const Material& p_Material = SomeSingleton::DefaultMaterial());
		void RenderTorus(const Mathematics::Frame& p_Frame, const f32 p_Scale, const Material& p_Material = DefaultMaterial());
	};
}

#endif // #ifndef IncludedVisuSomeSingletonH