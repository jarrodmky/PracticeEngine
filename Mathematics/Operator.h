#ifndef IncludedMathOperatorH
#define IncludedMathOperatorH

//===========================================================================
// Filename:	Operator.h
// Author:		Jarrod MacKay
// Date:		16/03/2016
// Description: Attached to a small set of particles, operates on another particle
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
	class Operator;

	template <u32 t_Dimensions>
	class Operator<t_Dimensions, 0>
	{
	public:	//Operators

		explicit Operator() {}

		//virtuals
		virtual ~Operator() {}
		virtual void Operate(const VerletParticle<t_Dimensions>& p_Particle) = 0;
	};

	template <u32 t_Dimensions>
	class Operator<t_Dimensions, 1>
	{
	protected: //Attributes

		VerletParticle<t_Dimensions>& Particle;

	public:	//Operators

		explicit Operator(const VerletParticle<t_Dimensions>& p_Particle)
			: m_Particle(p_Particle) {}

		//virtuals
		virtual ~Operator() {}
		virtual void Operate(const VerletParticle<t_Dimensions>& p_Particle) = 0;
	};

#include "SpecificOperator.inl"

} // namespace Visualization

#endif // #ifdef IncludedMathOperatorH