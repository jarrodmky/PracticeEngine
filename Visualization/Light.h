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
			, Ambient(Mathematics::ConstantColours::White)
			, Diffuse(Mathematics::ConstantColours::White)
			, Specular(Mathematics::ConstantColours::White)
		{}

	//Attributes
	public:

		Mathematics::Vector Position;

		Mathematics::LinearColour Ambient;

		Mathematics::LinearColour Diffuse;

		Mathematics::LinearColour Specular;
	};
} // namespace Visualization

#endif //ifndef IncludedVisuLightH