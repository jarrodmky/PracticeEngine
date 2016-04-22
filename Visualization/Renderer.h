#ifndef IncludedVisuRendererH
#define IncludedVisuRendererH

//===========================================================================
// Filename:	Renderer.h
// Author:		Jarrod MacKay
// Description:	Controls multiple shading styles of a specific vertex type
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "GraphicBasic.h"
#include "Texture.h"
#include "Materials.h"
#include "DepthMap.h"
#include "RenderTarget.h"
#include "Sampler.h"
#include "Model.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class System;

	template <typename t_VertexType>
	class Renderer;

	//==========
	// Flat Renderer
	//==========

	template <>
	class Renderer<FlatVertex>
	{
	//Methods
	public:

		Renderer(System& p_System);
		~Renderer();

		void Initialize();
		void Terminate();

		void StartRendering(const Camera& p_Camera);
		void Render(const VertexBuffer<FlatVertex>& m_Buffer
			, Mathematics::TopologyIndexing p_Toplogy);
		void StopRendering();

	//Attributes
	private:

		//vertex shaders
		DrawnVertexShader m_VertexShader;

		//pixel shaders
		DrawnPixelShader m_PixelShader;

		//sources
		PerCameraBuffer m_CameraBuffer;

		//misc
		bool m_Initialized;
		bool m_Rendering;
		System& m_System;
	};

	typedef Renderer<FlatVertex> FlatVertexRenderer;

	//==========
	// Lit Renderer
	//==========

	template <>
	class Renderer<LitVertex>
	{
	//Methods
	public:

		Renderer(System& p_System);
		~Renderer();

		void Initialize();
		void Terminate();
		void RegisterLight(const Light& p_Light);
		void StartRendering(const Camera& p_Camera);
		void RenderSphere(const Mathematics::Sphere3& p_Sphere);
		void StopRendering();

	//Attributes
	private:

		//shaders
		LitVertexShader m_VertexShader;
		LitPixelShader m_PixelShader;

		//sources
		PerCameraBuffer m_CameraBuffer;
		PerObjectBuffer m_ObjectBuffer;
		SceneLightingBuffer m_LightBuffer;
		
		//geometry
		SolidModel<LitVertex> m_Sphere;

		//misc
		bool m_Initialized;
		bool m_Rendering;
		System& m_System;
	};

	typedef Renderer<LitVertex> LitRenderer;

	//==========
	// Painted Renderer
	//==========

	template <>
	class Renderer<PaintedVertex>
	{
		static const u32 numEffects = 11;

	//Methods
	public:

		Renderer(System& p_System);
		~Renderer();

		void Initialize();
		void Terminate();

		void BindRenderTarget();
		void UnbindRenderTarget();
		void Render();

		const char* GetEffectName() const;
		void NextEffect();
		void LastEffect();

	//Attributes
	private:

		//vertex shaders
		PostProcessVertexShader m_VertexShader;

		//pixel shaders
		PostProcessPixelShader m_PixelShader;

		//sources
		PostProcessConstantBuffer m_PostProcessBuffer;
		PerObjectBuffer m_ObjectBuffer;

		RenderTarget m_RenderTarget;
		Sampler m_TextureSampler;

		//geometry
		SolidModel<PaintedVertex> m_RenderQuad;

		//misc
		bool m_Initialized;
		bool m_Rendering;
		System& m_System;
	};

	typedef Renderer<PaintedVertex> PostProcessor;

	//==========
	// Surface Renderer
	//==========

	template <>
	class Renderer<SurfaceVertex>
	{
	//Methods
	public:

		Renderer(System& p_System);
		~Renderer();

		void Initialize();
		void Terminate();

		void StartRendering(const Camera& p_Camera);
		void StopRendering();

		void StartRefractionMapping(const Camera& p_Camera);
		void StopRefractionMapping();
		void StartReflectionMapping(const Camera& p_Camera);
		void StopReflectionMapping();

		void RegisterLight(const Light& p_Light);

		void Update(f32 p_Time);

		void RenderModel(const Mathematics::Frame& p_Frame
						 , const SolidModel<SurfaceVertex>& p_Model);
		
		//Attributes
	private:

		//shaders
		WaterVertexShader m_VertexShader;
		WaterPixelShader m_PixelShader;

		//sources
		PerCameraBuffer m_CameraBuffer;
		WaterConstantBuffer	m_WaterBuffer;
		SceneLightingBuffer m_LightBuffer;

		RenderTarget m_ReflectionMap;
		RenderTarget m_RefractionMap;
		Sampler m_TextureSampler;

		Mathematics::Matrix44 m_ReflectionWorldToView;
		Mathematics::Matrix44 m_RefractionWorldToView;
		Mathematics::Matrix44 m_ReflectionProjection;
		Mathematics::Matrix44 m_RefractionProjection;

		//misc
		bool m_Initialized;
		bool m_Rendering;
		System& m_System;
	};

	typedef Renderer<SurfaceVertex> WaterRenderer;

	//==========
	// Framed Renderer
	//==========

	template <>
	class Renderer<FramedVertex>
	{
	//Definitions
	public:

		enum class Shading
		{
			Default,
			Cel,
			Fancy
		};

	//Methods
	public:
		
		Renderer(System& p_System);
		~Renderer();

		void Initialize();
		void Terminate();

		void StartRenderingOrtho(const Camera& p_Camera, const u32 p_ScreenWidth, const u32 p_ScreenHeight);
		void StartRenderingPersp(const Camera& p_Camera);
		void StopRendering();
		void SwitchShading(const Shading p_ShadingType);

		void StartDepthMapping();
		void StopDepthMapping();

		void RegisterLight(const Light& p_Light);

		void BindMaterial(const Material& p_Material);
		void BindMaterial(const FancyMaterial& p_Material);

		void RenderModel(const Mathematics::Frame& p_Frame,
			const SolidModel<FramedVertex>& p_Model);
		void RenderModel(const Mathematics::Frame& p_Frame,
			const MeshModel<FramedVertex>& p_Model);
		void RenderSphere(const Mathematics::Frame& p_Frame
			, const f32 p_Radius);
		void RenderTorus(const Mathematics::Frame& p_Frame
			, const f32 p_Radius);
		void RenderSphere(const Mathematics::Sphere3& p_Sphere
			, const Mathematics::Quaternion& p_Orientation = Mathematics::IdentityRotor());

	private:

		void StartShadingInternal();
		void RenderSphereInternal();
		void RenderTorusInternal();

	//Attributes
	private:

		//vertex shaders
		FrameVertexShader m_VertexShader;
		FrameDepthMapping m_DepthMapper;

		//pixel shaders
		FramePixelShader m_StandardPixelShader;
		FrameCelPixelShader m_CelPixelShader;
		FrameFancyPixelShader m_FancyPixelShader;

		//sources
		PerObjectBuffer m_ObjectBuffer;
		SceneLightingBuffer m_LightBuffer;
		PerCameraBuffer m_CameraBuffer;
		PerMaterialBuffer m_MaterialBuffer;

		FancyMaterial m_DefaultMaterial;
		Texture m_GradientMap;
		DepthMap m_DepthMap;
		Sampler m_TextureSampler;
		Sampler m_DepthSampler;

		//geometry
		SolidModel<FramedVertex> m_Sphere;
		SolidModel<FramedVertex> m_Torus;

		//misc
		Shading m_CurrentShading;
		bool m_Initialized;
		bool m_Rendering;
		System& m_System;
	};

	typedef Renderer<FramedVertex> FramedVertexRenderer;
}

#endif // #ifndef IncludedVisuRendererH