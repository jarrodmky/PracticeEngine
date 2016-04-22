#ifndef IncludedSimParticleSystemH
#define IncludedSimParticleSystemH

//===========================================================================
// Filename:	ParticleSystem.h
// Author:		Jarrod MacKay
// Date:		16/03/2016
// Description:	Handles particles and rigid body simulation
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>

namespace Simulation
{
	//===========================================================================
	// Declarations
	//===========================================================================

	template <u32 t_Dimensions>
	class ParticleSystem
	{
		static const u32 s_MaxParticles = 30;

		typedef Mathematics::Stick<t_Dimensions> Sticks;

		typedef Mathematics::VerletParticle<t_Dimensions> Particle;

		typedef Mathematics::RealVector<t_Dimensions> nVector;

		typedef std::vector<Particle> Particles;

	public:  //Operators

		ParticleSystem();

		~ParticleSystem();

	public:  //Methods

		void Initialize(const Mathematics::scalar p_ParticleRadius);

		void Update(const f32 p_DeltaTime);

		const Particle& SpawnStaticParticle(const nVector& p_Location);

		void RandomSpawnSphere(const u32 p_NumberOfParticles, const Mathematics::Sphere<t_Dimensions>& p_Sphere, 
		const nVector& p_Gravity);

		const Mathematics::scalar GetParticleRadius() { return m_Radius; }

		const Particles& GetParticles() { return m_Particles; }

	private: //Attributes

		Particles m_Particles;



		Mathematics::scalar m_Radius;

		bool m_Initialized;
	};

	//===========================================================================
	// Definitions
	//===========================================================================

	template <u32 t_Dimensions>
	ParticleSystem<t_Dimensions>::ParticleSystem()
		: m_Particles()
		, m_Radius()
		, m_Initialized(false) {}

	template <u32 t_Dimensions>
	ParticleSystem<t_Dimensions>::~ParticleSystem() {}

	template <u32 t_Dimensions>
	void ParticleSystem<t_Dimensions>::Initialize(const Mathematics::scalar p_ParticleRadius)
	{
		Assert(!m_Initialized, "Already initialized");
		m_Particles.reserve(s_MaxParticles);
		m_Radius = p_ParticleRadius;
		m_Initialized = true;
	}

	template <u32 t_Dimensions>
	void ParticleSystem<t_Dimensions>::Update(const f32 p_DeltaTime)
	{
		Assert(m_Initialized, "Not initialized!");

		scalar invDeltaTime = Inverse(p_DeltaTime);
		for (auto& particle : m_Particles)
		{
			particle.Integrate(p_DeltaTime, invDeltaTime);
		}
	}
	
	template <u32 t_Dimensions>
	void ParticleSystem<t_Dimensions>::RandomSpawnSphere(const u32 p_NumberOfParticles
					, const Mathematics::Sphere<t_Dimensions>& p_Sphere
					, const nVector& p_Gravity)
	{
		//randomly spawn particles in sphere and give them gravity
		for (u32 i = 0; i < p_NumberOfParticles; ++i)
		{
			m_Particles.push_back(Particle(p_Sphere.Radius 
				* MakeRandomVector3(-p_Sphere.Radius, p_Sphere.Radius).Direction() 
				+ p_Sphere.Centre, p_Gravity));
		}
	}
	
	template <u32 t_Dimensions>
	const Mathematics::VerletParticle<t_Dimensions>& ParticleSystem<t_Dimensions>::SpawnStaticParticle(const nVector& p_Location)
	{
		m_Particles.push_back(Particle(p_Location, Zero3()));
		return m_Particles.back();
	}
}
#endif // #ifndef IncludedSimParticleSystemH