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