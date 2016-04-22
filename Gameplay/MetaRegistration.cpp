//===========================================================================
// Filename:	MetaRegistration.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "MetaRegistration.h"
#include "Component.h"
#include "Registry.h"

//components
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "CameraComponent.h"

//===========================================================================
// MetaRegistration Definitions
//===========================================================================

void Gameplay::MetaRegistration()
{
#define Register(x) Meta::Register(x::StaticGetMetaClass())
	Register(Component);
	Register(TransformComponent);
	Register(CameraComponent);
	Register(ColliderComponent);
#undef Register
}