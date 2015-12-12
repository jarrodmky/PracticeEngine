#ifndef IncludedVisuLightH
#define IncludedVisuLightH

//===========================================================================
// Filename:	Light.h
// Author:		Jarrod MacKay
// Description:	Base light class
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>
#include "LinearColour.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{

	class Light
	{
	//Operations
	public:

		Light()
			: Position(Mathematics::Zero4())
			, Ambient(Mathematics::ColourPallet::White)
			, Diffuse(Mathematics::ColourPallet::White)
			, Specular(Mathematics::ColourPallet::White)
		{}

	//Attributes
	public:

		Mathematics::Vector4 Position;

		Mathematics::LinearColour Ambient;

		Mathematics::LinearColour Diffuse;

		Mathematics::LinearColour Specular;
	};
} // namespace Visualization

#endif //ifndef IncludedVisuLightH