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

	private:

		static Mathematics::scalar m_Mass;
		static Mathematics::scalar m_InvMass;
		
	//Operators
	public:

		Particle();
		virtual ~Particle();
		
	//Methods
	public:

		virtual void Integrate(const Mathematics::scalar p_DeltaTime, const Mathematics::Vector3& p_Force) = 0;
		virtual const Mathematics::Vector3 GetVelocity(const Mathematics::scalar p_InvDeltaTime) const = 0;

		inline const Mathematics::Vector3 GetAcceleration(const Mathematics::Vector3 p_Force);
		
		static void SetMass(const Mathematics::scalar p_Mass);
		static const Mathematics::scalar GetMass();
	};

	class StaticParticle : public Simulation::Particle
	{
	//Operators
	public:

		StaticParticle();
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

		EulerParticle();
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

		VerletParticle();
		virtual ~VerletParticle();

	//Methods
	public:

		virtual void Integrate(const Mathematics::scalar p_DeltaTime, const Mathematics::Vector3& p_Force);

		virtual const Mathematics::Vector3 GetVelocity(const Mathematics::scalar p_InvDeltaTime) const;
	};

} // namespace Simulation

#endif //#ifndef IncludedSimulParticlesH