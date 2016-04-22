#ifndef IncludedMathConstraintH
#define IncludedMathConstraintH

//===========================================================================
// Filename:	Constraint.h
// Author:		Jarrod MacKay
// Date:		16/03/2016
// Description:	Enforces a particular property on a small set of verlet particles. 
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "VerletParticle.h"

//===========================================================================
// Definitions
//===========================================================================

namespace Mathematics
{
	template <u32 t_Dimensions, u32 t_Particles>
	class Constraint;

	template <u32 t_Dimensions>
	class Constraint<t_Dimensions, 1>
	{
	public: //Attributes

		VerletParticle<t_Dimensions>& Particle;

	public: //Operators

		explicit Constraint(const VerletParticle<t_Dimensions>& p_Particle)
			: Particle(p_Particle) {}

		//virtuals
		virtual ~Constraint() {}
		virtual void Relax(scalar p_DeltaTime) = 0;
	};

	template <u32 t_Dimensions>
	class Constraint<t_Dimensions, 2>
	{
		//Attributes
	public:

		VerletParticle<t_Dimensions>& ParticleA;
		VerletParticle<t_Dimensions>& ParticleB;

		//Operators
	public:

		Constraint(const VerletParticle<t_Dimensions>& p_ParticleA
			, const VerletParticle<t_Dimensions>& p_ParticleB)
			: ParticleA(p_ParticleA)
			, ParticleB(p_ParticleB)
		{}

		//virtuals
		virtual ~Constraint() {}
		virtual void Relax(scalar p_DeltaTime) = 0;
	};

#include "SpecificConstraint.inl"

} // namespace Visualization

#endif // #ifdef IncludedMathConstraintH