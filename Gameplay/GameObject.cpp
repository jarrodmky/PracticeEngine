//===========================================================================
// Filename:	GameObject.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "GameObject.h"
#include "Component.h"

using namespace Gameplay;

namespace
{
}

//===========================================================================
// Class Definitions
//===========================================================================

GameObject::GameObject()
: m_Handle()
, m_Name("Unknown")
, m_World(nullptr)
, m_Components()
{
}

GameObject::~GameObject()
{
	for(auto component : m_Components)
	{
		ProperlyDelete(component);
	}
	m_Components.clear();
}

void GameObject::Initialize()
{
	for(auto component : m_Components)
	{
		component->Initialize();
	}
}

void GameObject::Terminate()
{
	for(auto component : m_Components)
	{
		component->Terminate();
	}
}

void GameObject::Update(f32 p_DeltaTime)
{
	for(auto component : m_Components)
	{
		component->Update(p_DeltaTime);
	}
}

void GameObject::Render()
{
	for(auto component : m_Components)
	{
		component->Render();
	}
}

void GameObject::AddComponent(Component* p_Component)
{
	Assert(p_Component->m_GameObject == nullptr, "Cannot add someone elses component!");
	p_Component->m_GameObject = this;
	m_Components.push_back(p_Component);
}

World& GameObject::GetWorld()
{
	return *m_World;
}

const World& GameObject::GetWorld() const
{
	return *m_World;
}