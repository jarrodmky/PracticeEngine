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

#include "../Simulation/Simulation.h"
#include "Vertices.h"
#include "Buffers.h"
#include "Shaders.h"

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
			: m_System(p_GraphicsSystem)
			, m_Particles()
			, m_Buffer(p_GraphicsSystem)
			, m_VS(p_GraphicsSystem)
			, m_GS(p_GraphicsSystem)
			, m_PS(p_GraphicsSystem)
			, m_TransformBuffer(p_GraphicsSystem)
			, m_TextureBuffer(p_GraphicsSystem)
			, m_CameraBuffer(p_GraphicsSystem)
			, Transform()
		{}

		~ParticleEffect()
		{}

		NonCopyable(ParticleEffect);

	//Methods
	public:

		void Create(const u32 p_NumParticles)
		{
			m_Particles.Initialize(p_NumParticles, nullptr);
			m_Buffer.Allocate(p_NumParticles);
			m_VS.Compile(L"../Data/Shaders/ParticleBillboard.fx", "VS", "vs_4_0");
			m_GS.Compile(L"../Data/Shaders/ParticleBillboard.fx", "GS", "gs_4_0");
			m_PS.Compile(L"../Data/Shaders/ParticleBillboard.fx", "PS", "ps_4_0");
			m_TransformBuffer.Allocate();
			m_CameraBuffer.Allocate();

			TextureBuffer tb;
			tb.TextureHeight = 8.0f;
			tb.TextureWidth = 8.0f;
			m_TextureBuffer.Allocate(&tb);
			Transform.Set();
		}

		void Destroy()
		{
			m_TextureBuffer.Free();
			m_CameraBuffer.Free();
			m_TransformBuffer.Free();
			m_PS.Release();
			m_GS.Release();
			m_VS.Release();

			m_Buffer.Free();
		}

		void Update(f32 p_DeltaTime)
		{
			m_Particles.Update(p_DeltaTime);

			std::vector<Mathematics::Vector3> loci;

			m_Particles.GetLocations(loci);

			m_Buffer.Clear();

			for (u32 i = 0; i < loci.size(); ++i)
			{
				m_Buffer.Add(EmptyVertex(loci[i]));
			}
		}

		void Render(const Camera& p_Camera)
		{
			m_VS.Bind();
			m_GS.Bind();
			m_PS.Bind();

			ObjectBuffer ob;
			ob.LocalToWorld = Transform.GetLocalToWorldTR();
			m_TransformBuffer.Set(&ob);
			m_TransformBuffer.BindToVertexShader();
			
			CameraBuffer cb;
			cb.WorldToViewToProjection = p_Camera.GetWorldToProjectionTransformT();
			m_CameraBuffer.Set(&cb);
			m_CameraBuffer.BindToVertexShader();

			m_TextureBuffer.BindToGeometryShader();

			m_Buffer.Bind();

			m_System.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			m_System.GetContext()->Draw(m_Buffer.GetNumberOfVertices(), 0);

			m_GS.Unbind();
		}

	//Attributes
	private:

		//ParticleFactory

		System& m_System;

		Simulation::ParticleSystem<Simulation::VerletParticle> m_Particles;
		
		DynamicVertexBuffer<EmptyVertex> m_Buffer;

		VertexShader<EmptyVertex> m_VS;

		GeometryShader m_GS;

		PixelShader m_PS;

		ConstantBuffer<ObjectBuffer> m_TransformBuffer;

		ConstantBuffer<TextureBuffer> m_TextureBuffer;

		ConstantBuffer<CameraBuffer> m_CameraBuffer;

	public:

		Mathematics::Frame Transform;
	};
}

#endif // #ifndef IncludedVisuParticleEffectH