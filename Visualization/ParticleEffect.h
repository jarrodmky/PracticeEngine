#ifndef IncludedVisuParticleEffectH
#define IncludedVisuParticleEffectH

//===========================================================================
// Filename:	ParticleEffect.h
// Author:		Jarrod MacKay
// Description:	Can be added to a scene with a certain particle type
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "../Simulation/Simulation.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	template<typename t_ParticleType>
	class ParticleEffect
	{
	//Operators
	public:

		ParticleEffect();

		~ParticleEffect();

		NonCopyable(ParticleEffect<t_ParticleType>);

	//Methods
	public:

		void Allocate(const u32 p_NumParticles);

		void Destroy();

		void Render() const;

	//Attributes
	private:

		//ParticleFactory

		//Integrator

		//Shaders
		VertexShader

	public:
	};
}

#endif // #ifndef IncludedVisuParticleEffectH