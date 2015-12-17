#ifndef IncludedSimulBodySystemH
#define IncludedSimulBodySystemH

//===========================================================================
// Filename:	BodySystem.h
// Author:		Jarrod MacKay
// Description:	Used with particles.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Abstracts.h>
#include <Mathematics.h>
#include "Particles.h"
#include "Body.h"

//===========================================================================
// Classes
//===========================================================================

namespace Simulation
{

	template <typename t_Particle>
	class BodySystem
	{
	//Definitions
	private:

	//Attributes
	public:

		Abstracts::List<Body<t_Particle>> m_ActiveBodies;

		Abstracts::List<Body<t_Particle>> m_InactiveBodies;

		//Abstracts::List<Operator<t_Particle>*> m_Operators;

	//Operators
	public:

		BodySystem()
			: m_ActiveBodies(0)
			, m_InactiveBodies(0)
		{}
		~BodySystem() 
		{}

	//Methods
	public:

		void Initialize(const u32 p_NumParticles, const Mathematics::Vector3& p_Location)
		{
			//m_Operators.Clear();
			m_InactiveBodies.Clear();
			m_InactiveBodies.Resize(p_NumParticles);
			m_ActiveBodies.Reserve(p_NumParticles);

			for(u32 i = 0; i < p_NumParticles; ++i)
			{
				m_InactiveBodies(i).Initialize(p_Location);
			}
		}

		void Destroy()
		{
			m_ActiveBodies.Destroy();
			m_InactiveBodies.Destroy();
		}

		void Update(const Mathematics::scalar p_DeltaTime)
		{
			using namespace Mathematics;

			//apply operators
			//for (u32 i = 0; i < m_Operators.GetNumberOfElements(); ++i)
			//{
			//	m_Operators(i).Operate(particles);
			//}

			//for each particle
			scalar invDeltaTime = 1.0f / p_DeltaTime;
			for (u32 i = 0; i < m_ActiveBodies.GetNumberOfElements(); ++i)
			{
				Body<t_Particle>& B(m_ActiveBodies(i));
				
				//
				//gravity
				B.AddForce(MakeVector(0.0f, 9.82f, 0.0f));
				//
				//
				
				B.Update(p_DeltaTime, invDeltaTime);
			}
		}

		//void AddOperator(Operator* )
		//{
		//}

		void GetLocations(Abstracts::List<Mathematics::Vector3>& p_Locations)
		{
			const u32 len = m_ActiveBodies.GetNumberOfElements();

			p_Locations.Clear();
			p_Locations.Resize(len);

			for(u32 i = 0; i < len; ++i)
			{
				p_Locations(i) = m_ActiveBodies(i).GetPosition();
			}
		}

		void Activate(const t_Particle& p_InitialValue)
		{
			if(m_InactiveBodies.GetNumberOfElements() > 0)
			{
				Body<t_Particle> temp;
				m_InactiveBodies.Remove(temp);
				temp.Initialize(p_InitialValue);
				m_ActiveBodies.Add(temp);
			}
		}
	};
}

#endif //#ifndef IncludedSimulBodySystemH