//===========================================================================
// Filename:	MetaRegistration.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "MetaRegistration.h"
#include "Registry.h"

//registrees
#include "Camera.h"

//===========================================================================
// MetaRegistration Definitions
//===========================================================================

void Visualization::MetaRegistration()
{
#define Register(x) ::Meta::Register(x::StaticGetMetaClass())
	Register(Camera);
#undef Register
}