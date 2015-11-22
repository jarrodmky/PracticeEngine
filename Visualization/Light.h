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
			: Position(Mathematics::ConstantVectors::Zero)
			, Ambient(ConstantColours::White)
			, Diffuse(ConstantColours::White)
			, Specular(ConstantColours::White)
		{}

	//Attributes
	public:

		Mathematics::Vector Position;

		LinearColour Ambient;

		LinearColour Diffuse;

		LinearColour Specular;
	};
} // namespace Visualization

#endif //ifndef IncludedVisuLightH