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
			, Diffuse(Mathematics::ColourPallet::White)
			, Ambient(Mathematics::ColourPallet::White)
		{}

	//Attributes
	public:

		Mathematics::Vector4 Position;
		Mathematics::LinearColour Diffuse;
		Mathematics::LinearColour Ambient;
	};
} // namespace Visualization

#endif //ifndef IncludedVisuLightH