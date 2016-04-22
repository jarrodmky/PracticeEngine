#ifndef IncludedSimRaycasterH
#define IncludedSimRaycasterH

//===========================================================================
// Filename:	Raycaster.h
// Author:		Jarrod MacKay
// Date:		16/03/2016
// Description:	Controls multiple shading styles of a specific vertex type
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>
#include "ParticleSystem.h"

//===========================================================================
// Classes
//===========================================================================

namespace Simulation
{
	template <u32 t_Dimensions>
	class Raycaster
	{
		typedef Mathematics::Ray<t_Dimensions> CastedRay;

	public: //Operators
		Raycaster();
		~Raycaster();

		Mathematics::VerletParticle<t_Dimensions> Cast(const CastedRay& p_Ray
			, const Mathematics::scalar p_Distance
			, const ParticleSystem<t_Dimensions>& p_System);
	};

	template <u32 t_Dimensions>
	Raycaster<t_Dimensions>::Raycaster()
	{
	}

	template <u32 t_Dimensions>
	Raycaster<t_Dimensions>::~Raycaster()
	{
	}

}

#endif // #ifndef IncludedSimRaycasterH