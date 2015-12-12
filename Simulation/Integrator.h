#ifndef IncludedSimulIntregratorH
#define IncludedSimulIntregratorH

//===========================================================================
// Filename:	Integrator.h
// Author:		Jarrod MacKay
// Description:	Used with particles, 
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Particles.h"

//===========================================================================
// Classes
//===========================================================================

namespace Simulation
{
	template <typename t_Particle>
	struct Body<typename t_Particle>
	{
		bool ShouldUpdate;
		Mathematics::Vector3 Force;
		t_Particle Object;
	};

	template <typename t_Particle>
	class ParticleSystem
	{
	//Definitions
	private:

		typedef ParticleBody Body<t_Particle>; 
		typedef ParticleBodyList Abstracts::List<ParticleBody>;

	//Attributes
	public:

		ParticleBodyList m_Particles;

		Abstracts::List<Operator<t_Particle>*> m_Operators;

	//Operators
	public:

		Integrator();
		~Integrator();

	//Methods
	public:

		void Initialize(const u32 p_NumParticles, const t_Particle* p_Array)
		{
			m_Operators.Clear();
			m_Particles.Clear();

			m_Particles.Resize(p_NumParticles);
		}

		void Update(const Mathematics::scalar p_DeltaTime)
		{
			ParticleBodyList particles;
			GetActiveList(particles);

			//apply operators
			for (u32 i = 0; i < m_Operators.GetNumberOfElements(); ++i)
			{
				m_Operators(i).Operate(particles);
			}

			//for each particle
			for (u32 i = 0; i < m_Particles.; ++i)
			{
				ParticleBody& P(particles(i));
				P.Object.Integrate(p_DeltaTime, P.Force);
			}
		}

		void BindOperator(const Operator* p_Operator)
		{
			m_Operators.Add(p_Operator);
		}

	private:

		void GetActiveList(ParticleBodyList& m_Active)
		{
			m_Active.Clear();

			for (u32 i = 0; i < m_Particles.GetNumberOfElements(); ++i)
			{
				if (m_Particles(i).ShouldIntegrate)
				{
					m_Active.Add(m_Particles(i).WhatToIntegrate);
				}
			}
		}
	};
}

#endif //#ifndef IncludedSimulIntregratorH