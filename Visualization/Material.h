#ifndef IncludedVisuVeneerH
#define IncludedVisuVeneerH

//===========================================================================
// Filename:	Veneer.h
// Author:		Jarrod MacKay
// Description:	Hold phong shaded data with texture.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>
#include "Pigment.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{

	class Veneer
	{
	//Operations
	public:

		Veneer()
			: Reflectance(1.0f)
			, Pigment(Mathematics::ConstantColours::White)
			, Emissive(Mathematics::ConstantColours::White)
		{}

	//Attributes
	public:

		f32 Reflectance;

		Mathematics::LinearColour Emissive;

		Pigment Pigment;
	};
} // namespace Visualization

#endif //ifndef IncludedVisuVeneerH