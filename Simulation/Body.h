#ifndef IncludedSimulBodyH
#define IncludedSimulBodyH

//===========================================================================
// Filename:	Body.h
// Author:		Jarrod MacKay
// Description:	Basic physics objects, only need at least mass and position. 
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>
#include "Particles.h"

//===========================================================================
// Classes
//===========================================================================

namespace Simulation
{
	template <typename t_Particle>
	class Body
	{
	//Attributes
	private:

		bool m_IsMoving;
		Mathematics::Vector3 m_Force;
		t_Particle m_Object;
		
	//Operators
	public:

		Body()
			: m_IsMoving(false)
			, m_Force(Mathematics::Zero3())
			, m_Object()
		{}
		~Body()
		{}
		
	//Methods
	public:

		inline void Initialize(const Mathematics::Vector3& p_Location)
		{
			m_Object.Position = p_Location;
		}

		inline void Initialize(const t_Particle& p_IntialValue)
		{
			m_Object = p_IntialValue;
		}

		inline void Update(const Mathematics::scalar p_DeltaTime, const Mathematics::scalar p_InvDeltaTime)
		{
			using namespace Mathematics;

			m_Object.Integrate(p_DeltaTime, m_Force);
			m_Force = Zero3();
			m_IsMoving = ApproximateToEachOther(m_Object.GetVelocity(p_InvDeltaTime), Zero3(), 0.000001f);
		}

		inline void AddForce(const Mathematics::Vector3& p_Force)
		{
			m_Force += p_Force;
		}

		inline const Mathematics::Vector3 GetPosition() const
		{
			return m_Object.Position;
		}

		inline const bool IsMoving() const
		{
			return m_IsMoving;
		}
	};
} // namespace Simulation

#endif //#ifndef IncludedSimulBodyH