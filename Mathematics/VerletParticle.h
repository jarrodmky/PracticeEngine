#ifndef IncludedMathVerletParticleH
#define IncludedMathVerletParticleH

//===========================================================================
// Filename:	VerletParticle.h
// Author:		Jarrod MacKay
// Description:	Represenset a point particle with a varible and
//				constant forces with verlet integration.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Vector.h"

//===========================================================================
// Definitions
//===========================================================================

namespace Mathematics
{
	template <u32 t_Dimensions>
	class VerletParticle
	{
	//Attributes
	private:

		RealVector<t_Dimensions> m_LastPosition;
		RealVector<t_Dimensions> m_Velocity;
		RealVector<t_Dimensions> m_ConstantForce;

	public:

		RealVector<t_Dimensions> Position;
		RealVector<t_Dimensions> VariableForce;
		
	//Operators
	public:

		inline explicit VerletParticle(const RealVector<t_Dimensions>& p_InitPosition = RealVector<t_Dimensions>()
			, const RealVector<t_Dimensions>& p_ConstForce = RealVector<t_Dimensions>())
			: m_LastPosition(Zero)
			, m_Velocity(Zero)
			, Position(Zero)
			, m_ConstantForce(p_ConstForce)
			, VariableForce(Zero)
		{
			SetVelocity(0.0f, p_InitPosition, RealVector<t_Dimensions>());
		}

		inline void Integrate(const Mathematics::scalar p_DeltaTime, const Mathematics::scalar p_InvDeltaTime)
		{
			//calculate
			RealVector<t_Dimensions> nextPosition
				= 2.0f * Position
				- m_LastPosition 
				+ (m_ConstantForce + VariableForce) * p_DeltaTime * p_DeltaTime;
			m_Velocity = 0.5f * (nextPosition - m_LastPosition) * p_InvDeltaTime;

			VariableForce = RealVector<t_Dimensions>(Zero);

			//update
			m_LastPosition = Position;
			Position = nextPosition;
		}

		inline void SetVelocity(const Mathematics::scalar p_DeltaTime
			, const Mathematics::RealVector<t_Dimensions>& p_InitPosition = RealVector<t_Dimensions>()
			, const RealVector<t_Dimensions>& p_InitVelocity = RealVector<t_Dimensions>())
		{
			Position = p_InitPosition;
			m_Velocity = p_InitVelocity;
			m_LastPosition = Position - p_InitVelocity * p_DeltaTime;
		}

		Mathematics::RealVector<t_Dimensions> GetVelocity() const { return m_Velocity; }
	};
} // namespace Visualization

#endif // #ifdef IncludedMathVerletParticleH