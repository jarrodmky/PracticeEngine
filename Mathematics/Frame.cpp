//===========================================================================
// Filename:	Frame.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Frame.h"

using namespace Mathematics;

//===========================================================================
// Definitions
//===========================================================================

void Frame::Renormalize()
{
	m_Forward = m_Forward.Direction();
	Vector3 right = GetRight();
	m_Up = (right * m_Forward).Direction();

	//m_Orientation.Normalize();
}

//void Frame::Reorient(const Vector3& p_Up, const Vector3& p_Forward)
//{
//	Quaternion first(WorldForward(), p_Forward);
//	Quaternion second(first.Rotate(WorldUp()), p_Up);
//	m_Orientation = second * first;
//	Renormalize();
//}