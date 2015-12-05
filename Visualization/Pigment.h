#ifndef IncludedVisuPigmentH
#define IncludedVisuPigmentH

//===========================================================================
// Filename:	Pigment.h
// Author:		Jarrod MacKay
// Description:	Holds basic colouring info
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

	class Pigment
	{
	//Operations
	public:

		Pigment()
			: Ambient(Mathematics::ConstantColours::White)
			, Diffuse(Mathematics::ConstantColours::White)
			, Specular(Mathematics::ConstantColours::White)
		{}

		Pigment(const Mathematics::LinearColour& p_Colour)
			: Ambient(p_Colour)
			, Diffuse(p_Colour)
			, Specular(p_Colour)
		{}

		Pigment(const Mathematics::LinearColour& p_Ambient, const Mathematics::LinearColour& p_Diffuse, const Mathematics::LinearColour& p_Specular)
			: Ambient(p_Ambient)
			, Diffuse(p_Diffuse)
			, Specular(p_Specular)
		{}

	//Attributes
	public:

		Mathematics::LinearColour Ambient;

		Mathematics::LinearColour Diffuse;

		Mathematics::LinearColour Specular;
	};
} // namespace Visualization

#endif //ifndef IncludedVisuPigmentH