#ifndef IncludedVisuMaterialH
#define IncludedVisuMaterialH

//===========================================================================
// Filename:	Material.h
// Author:		Jarrod MacKay
// Description:	Base Material class
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

	class Material
	{
	//Operations
	public:

		Material()
			: Reflectance(1.0f)
			, Ambient(Mathematics::ConstantColours::White)
			, Diffuse(Mathematics::ConstantColours::White)
			, Specular(Mathematics::ConstantColours::White)
			, Emission(Mathematics::ConstantColours::White)
		{}

		Material(const Mathematics::LinearColour& p_Colour)
			: Reflectance(1.0f)
			, Ambient(p_Colour)
			, Diffuse(p_Colour)
			, Specular(p_Colour)
			, Emission(Mathematics::ConstantColours::Black)
		{}

		Material(const Mathematics::LinearColour& p_Ambient, const Mathematics::LinearColour& p_Diffuse, const Mathematics::LinearColour& p_Specular)
			: Reflectance(1.0f)
			, Ambient(p_Ambient)
			, Diffuse(p_Diffuse)
			, Specular(p_Specular)
			, Emission(Mathematics::ConstantColours::Black)
		{}

	//Attributes
	public:

		f32 Reflectance;

		Mathematics::LinearColour Ambient;

		Mathematics::LinearColour Diffuse;

		Mathematics::LinearColour Specular;

		Mathematics::LinearColour Emission;
	};
} // namespace Visualization

#endif //ifndef IncludedVisuMaterialH