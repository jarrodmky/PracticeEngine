#ifndef IncludedVisuDrawH
#define IncludedVisuDrawH

//===========================================================================
// Filename:	Draw.h
// Author:		Jarrod MacKay
// Description:	Simple drawing system.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>

namespace Visualization
{
	class Camera;
	class LinearColour;
	class System;
	struct AABB;
	struct OBB;
	struct Rectangle;

//===========================================================================
// Declarations
//===========================================================================
	
	namespace Draw
	{
		void Initialize(System& p_System, u32 p_MaxVertices = 10000);
		void Terminate();

		//world space rendering
		void AddVector(const Mathematics::Vector3& p_Vector
					 , const Mathematics::LinearColour& p_Colour);

		void AddVector(const Mathematics::Vector3& p_Vector
			, const Mathematics::Vector3& p_Position
					 , const Mathematics::LinearColour& p_Colour);

		void AddSimplex(const Mathematics::Edge& p_Edge
			, const Mathematics::LinearColour& p_Colour);

		void AddFrame(const Mathematics::Frame& p_Frame, f32 p_Length); 
		
		void AddCoordinateAxes();

		//TODO
		//screen space rendering

		void Render(const Camera& p_Camera);

	} // namespace Draw
}// namespace Visualization

#endif // #ifdef IncludedVisuDrawH