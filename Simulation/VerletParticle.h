#ifndef IncludedMathVerletParticleH
#define IncludedMathVerletParticleH

//===========================================================================
// Filename:	VerletParticle.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 
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
	class VerletParticle
	{
	//Attributes
	public:

	//Operators
	public:

		void Integrate();
		
	//Methods
	public:

		Mathematics::Vector m_Position;
		
	};

} // namespace Mathematics

#endif //#ifndef IncludedMathVerletParticleH