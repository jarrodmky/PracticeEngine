//===========================================================================
// Filename:	CameraComponent.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "System.h"
#include "CameraComponent.h"

using namespace Gameplay;

MetaDerivedClassBegin(CameraComponent, Component)
	MetaFieldBegin
	MetaField(m_Camera, "Camera")
	MetaFieldEnd
MetaClassEnd

//===========================================================================
// Class Definitions
//===========================================================================

CameraComponent::CameraComponent()
	: m_Camera()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Initialize()
{
	//const u32 windowWidth = p_System.GetWidth();
	//const u32 windowHeight = p_System.GetHeight();

}