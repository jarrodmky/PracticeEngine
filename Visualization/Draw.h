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
	class System;

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

		void AddSimplex(const Mathematics::Edge3& p_Edge
			, const Mathematics::LinearColour& p_Colour); 
		
		void AddCube(const Mathematics::Vector3& p_Centre
			, const Mathematics::Quaternion& p_Rotation
			, const Mathematics::scalar p_Width
			, const Mathematics::LinearColour& p_Colour);

		void AddBox(const Mathematics::AABB3& p_Box
			, const Mathematics::LinearColour& p_Colour);

		void AddLine(const Mathematics::Line3& p_Line, const Mathematics::LinearColour& p_Colour);

		void AddFrame(const Mathematics::Frame& p_Frame, f32 p_Length); 
		
		void AddCoordinateAxes();
		
		void AddCoordinatePlaneXZ();

		void AddCircle(const Mathematics::Vector3& p_Centre
						   , const Mathematics::Vector3& p_Normal
						   , const Mathematics::scalar p_Radius
						   , const Mathematics::LinearColour& p_Colour);

		//TODO
		//screen space rendering

		void Render(const Camera& p_Camera);

	} // namespace Draw
}// namespace Visualization

#endif // #ifdef IncludedVisuDrawH