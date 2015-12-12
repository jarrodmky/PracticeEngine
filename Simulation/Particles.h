#ifndef IncludedSimulParticlesH
#define IncludedSimulParticlesH

//===========================================================================
// Filename:	Particles.h
// Author:		Jarrod MacKay
// Description:	Basic physics objects, only need at least mass and position. 
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>

//===========================================================================
// Classes
//===========================================================================

namespace Simulation
{
	class Particle
	{
	//Attributes
	public:

		Mathematics::Vector3 Position;

	protected:

		static Mathematics::scalar m_Mass;
		static Mathematics::scalar m_InvMass;

	//Operators
	public:

		Particle(const Mathematics::Vector3& p_Location = Mathematics::Zero3());
		virtual ~Particle();
		
	//Methods
	public:

		virtual void Integrate(const Mathematics::scalar p_DeltaTime, const Mathematics::Vector3& p_Force) = 0;
		
		static void SetMass(const Mathematics::scalar p_Mass);
		static const Mathematics::scalar GetMass();

		virtual const Mathematics::Vector3 GetVelocity(const Mathematics::scalar p_InvDeltaTime) const = 0;
		inline static const Mathematics::Vector3 GetAcceleration(const Mathematics::Vector3 p_Force);
	};

	class StaticParticle : public Simulation::Particle
	{
	//Operators
	public:

		StaticParticle(const Mathematics::Vector3& p_Location = Mathematics::Zero3());
		virtual ~StaticParticle();

	//Methods
	public:

		virtual void Integrate(const Mathematics::scalar p_DeltaTime, const Mathematics::Vector3& p_Force);

		virtual const Mathematics::Vector3 GetVelocity(const Mathematics::scalar p_InvDeltaTime) const;
	};


	class EulerParticle : public Particle
	{
	//Attributes
	public:

		Mathematics::Vector3 Velocity;

	//Operators
	public:

		EulerParticle(const Mathematics::Vector3& p_Location = Mathematics::Zero3());
		virtual ~EulerParticle();

	//Methods
	public:

		virtual void Integrate(const Mathematics::scalar p_DeltaTime, const Mathematics::Vector3& p_Force);

		virtual const Mathematics::Vector3 GetVelocity(const Mathematics::scalar p_InvDeltaTime) const;
	};


	class VerletParticle : public Particle
	{
	//Attributes
	public:
		
		Mathematics::Vector3 LastPosition;

	//Operators
	public:

		VerletParticle(const Mathematics::Vector3& p_Location = Mathematics::Zero3());
		virtual ~VerletParticle();

	//Methods
	public:

		virtual void Integrate(const Mathematics::scalar p_DeltaTime, const Mathematics::Vector3& p_Force);

		virtual const Mathematics::Vector3 GetVelocity(const Mathematics::scalar p_InvDeltaTime) const;
	};

} // namespace Simulation

#endif //#ifndef IncludedSimulParticlesH