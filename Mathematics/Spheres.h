#ifndef IncludedMathSpheresH
#define IncludedMathSpheresH

//===========================================================================
// Filename:	Spheres.h
// Author:		Jarrod MacKay
// Description:	Methods for buidling the topology of a sphere
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Primitives.h"

namespace Mathematics
{
	void AddStandardRingedSphere(Topology3& p_Topology, const u32 p_Resolution);
	void AddStandardRingedTorus(Topology3& p_Topology, const u32 p_Resolution);
}


#endif //#ifndef IncludedMathSpheresH