#ifndef IncludedVisuConicColourH
#define IncludedVisuConicColourH

//===========================================================================
// Filename:	ConicColour.h
// Author:		Jarrod MacKay
// Description:	Defines colour in HSV colour space on 
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "LinearColour.h"

//===========================================================================
// Definitions
//===========================================================================


namespace Visualization
{
	class ConicColour
	{
	//Attributes
	public:

		f32 H;
		f32 S;
		f32 V;
		f32 A;

	//Operators
	public:

		ConicColour(const LinearColour& p_Colour);
	};
} // namespace Visualization

#endif // #ifdef IncludedVisuConicColourH