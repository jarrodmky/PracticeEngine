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
			, Ambient(ConstantColours::White)
			, Diffuse(ConstantColours::White)
			, Specular(ConstantColours::White)
			, Emission(ConstantColours::White)
		{}

		Material(const LinearColour& p_Colour)
			: Reflectance(1.0f)
			, Ambient(p_Colour)
			, Diffuse(p_Colour)
			, Specular(p_Colour)
			, Emission(ConstantColours::Black)
		{}

		Material(const LinearColour& p_Ambient, const LinearColour& p_Diffuse, const LinearColour& p_Specular)
			: Reflectance(1.0f)
			, Ambient(p_Ambient)
			, Diffuse(p_Diffuse)
			, Specular(p_Specular)
			, Emission(ConstantColours::Black)
		{}

	//Attributes
	public:

		f32 Reflectance;

		LinearColour Ambient;

		LinearColour Diffuse;

		LinearColour Specular;

		LinearColour Emission;
	};
} // namespace Visualization

#endif //ifndef IncludedVisuMaterialH