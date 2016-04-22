//===========================================================================
// Filename:	TransformComponent.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"

#include "TransformComponent.h"

using namespace Gameplay;

MetaDerivedClassBegin(TransformComponent, Component)
	MetaFieldBegin
	MetaField(Transform, "Transform")
	MetaFieldEnd
MetaClassEnd

//===========================================================================
// Class Definitions
//===========================================================================

TransformComponent::TransformComponent()
: Transform()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Initialize()
{

}