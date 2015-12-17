#ifndef IncludedVisuParticleEffectH
#define IncludedVisuParticleEffectH

//===========================================================================
// Filename:	ParticleEffect.h
// Author:		Jarrod MacKay
// Description:	Can be added to a scene with a certain particle type
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>
#include <../Simulation/Simulation.h>
#include "Vertices.h"
#include "Buffers.h"
#include "Shaders.h"
#include "Blend.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class ParticleEffect
	{
	//Operators
	public:

		ParticleEffect(System& p_GraphicsSystem)
			: m_Graphics(p_GraphicsSystem)
			, m_System()
			, m_Buffer(p_GraphicsSystem)
			, m_BlendEnable()
			, m_BlendDisable()
			, m_EnableAdditive()
			, m_DisableAdditive()
			, m_VS(p_GraphicsSystem)
			, m_GS(p_GraphicsSystem)
			, m_PS(p_GraphicsSystem)
			, m_TransformBuffer(p_GraphicsSystem)
			, m_TextureBuffer(p_GraphicsSystem)
			, m_CameraBuffer(p_GraphicsSystem)
			, m_EmitDelay(0.0f)
			, Transform()
		{}

		~ParticleEffect()
		{}

		NonCopyable(ParticleEffect);

	//Methods
	public:

		void Create(const u32 p_NumParticles, const Mathematics::Vector3& p_Location)
		{
			m_System.Initialize(p_NumParticles, p_Location);
			m_Buffer.Allocate(p_NumParticles);
			
			m_BlendEnable.Initialize(m_Graphics, DepthStencil::DepthTest::AdditiveBlend);
			m_BlendDisable.Initialize(m_Graphics, DepthStencil::DepthTest::Default);
			m_EnableAdditive.Initialize(m_Graphics, Blend::BlendMethod::Additive);
			m_DisableAdditive.Initialize(m_Graphics, Blend::BlendMethod::Default);

			m_VS.Compile(L"../Data/Shaders/ParticleBillboard.fx", "VS", "vs_5_0");
			m_GS.Compile(L"../Data/Shaders/ParticleBillboard.fx", "GS", "gs_5_0");
			m_PS.Compile(L"../Data/Shaders/ParticleBillboard.fx", "PS", "ps_5_0");
			
			m_TransformBuffer.Allocate();
			m_CameraBuffer.Allocate();
			m_TextureBuffer.Allocate();
			
			Transform.SetPosition(p_Location);
			
			Simulation::VerletParticle::SetMass(5.0f);
		}

		void Destroy()
		{
			m_TextureBuffer.Free();
			m_CameraBuffer.Free();
			m_TransformBuffer.Free();
			m_PS.Release();
			m_GS.Release();
			m_VS.Release();

			m_BlendDisable.Terminate();
			m_BlendEnable.Terminate();
			m_EnableAdditive.Terminate();
			m_DisableAdditive.Terminate();

			m_Buffer.Free();
			m_System.Destroy();
		}

		void Update(f32 p_DeltaTime)
		{
			using namespace Simulation;
			m_EmitDelay += p_DeltaTime;

			if(m_EmitDelay > m_MaxEmitDelay)
			{
				Emit();
				m_EmitDelay = 0.0f;
			}

			m_System.Update(p_DeltaTime);

			m_Buffer.Clear();

			Abstracts::List<Mathematics::Vector3> loci;
			m_System.GetLocations(loci);

			for (u32 i = 0; i < loci.GetNumberOfElements(); ++i)
			{
				m_Buffer.Add(EmptyVertex(loci(i)));
			}

			loci.Destroy();
		}

		void Render(const Camera& p_Camera)
		{
			m_VS.Bind();
			m_GS.Bind();
			m_PS.Bind();

			ObjectBuffer ob;
			ob.LocalToWorld = Transform.GetLocalToWorld();
			m_TransformBuffer.Set(&ob);
			m_TransformBuffer.BindToVertexShader();
			
			CameraBuffer cb;
			cb.WorldToProjection = p_Camera.GetWorldToProjectionTransform();
			m_CameraBuffer.Set(&cb);
			m_CameraBuffer.BindToVertexShader();

			TextureBuffer tb;
			tb.TextureHeight = 2.0f;
			tb.TextureWidth = 2.0f;
			tb.TextureUp = Mathematics::MakeVector(Transform.GetUp());
			tb.DiffuseColour = Mathematics::ColourPallet::Gray;
			m_TextureBuffer.Set(&tb);
			m_TextureBuffer.BindToGeometryShader();
			m_TextureBuffer.BindToPixelShader();

			m_Buffer.Bind();

			m_BlendEnable.BindToOutput(m_Graphics, 0);
			m_EnableAdditive.BindToOutput(m_Graphics, 0);

			m_Graphics.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			m_Graphics.GetContext()->Draw(m_Buffer.GetNumberOfVertices(), 0);

			m_DisableAdditive.BindToOutput(m_Graphics, 0);
			m_BlendDisable.BindToOutput(m_Graphics, 0);

			m_GS.Unbind();
		}

		void Emit()
		{
			using namespace Simulation;
			using namespace Mathematics;

			VerletParticle newParticle;
			newParticle.Position = Transform.GetPosition();
			newParticle.LastPosition = Transform.GetPosition();

			m_System.Activate(newParticle);
		}

	//Attributes
	private:

		//ParticleFactory

		System& m_Graphics;

		Simulation::BodySystem<Simulation::VerletParticle> m_System;
		
		DynamicVertexBuffer<EmptyVertex> m_Buffer;

		DepthStencil m_BlendEnable;
		DepthStencil m_BlendDisable;
		Blend m_EnableAdditive;
		Blend m_DisableAdditive;

		VertexShader<EmptyVertex> m_VS;
		GeometryShader m_GS;
		PixelShader m_PS;

		ConstantBuffer<ObjectBuffer> m_TransformBuffer;
		ConstantBuffer<TextureBuffer> m_TextureBuffer;
		ConstantBuffer<CameraBuffer> m_CameraBuffer;
		
		f32 m_EmitDelay;
		const f32 m_MaxEmitDelay = 1.0f;

	public:

		Mathematics::Frame Transform;
	};
}

#endif // #ifndef IncludedVisuParticleEffectH