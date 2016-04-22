//===========================================================================
// Filename:	ColliderComponent.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

using namespace Mathematics;
using namespace Gameplay;

//===========================================================================
// Meta Definition
//===========================================================================

MetaDerivedClassBegin(ColliderComponent, Component)
	MetaFieldBegin
	MetaField(m_BoundingVolume, "AABB3"),
	MetaField(m_Colour, "Colour")
	MetaFieldEnd
MetaClassEnd


//===========================================================================
// Class Definitions
//===========================================================================

ColliderComponent::ColliderComponent()
: m_BoundingVolume(Zero3(), Zero3())
, m_Colour(ColourPallet::White)
{}

ColliderComponent::~ColliderComponent()
{}

void ColliderComponent::Initialize()
{}

void ColliderComponent::Render()
{
	Visualization::Draw::AddBox(m_BoundingVolume, m_Colour);
}

const AABB3 ColliderComponent::GetAABB() const
{
	return m_BoundingVolume;
}