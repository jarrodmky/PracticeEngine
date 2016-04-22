//===========================================================================
// Filename:	World.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "World.h"
#include "TransformComponent.h"

using namespace Gameplay;
using namespace Serialization;

//===========================================================================
// Class Definitions
//===========================================================================

World::World(const u32 p_Capacity)
: m_Pool(p_Capacity)
, m_Factory(m_Pool)
, m_UpdateList()
, m_DestroyList()
, m_Camera(nullptr)
, m_Terrain(nullptr)
, m_Updating(false)
{
}

World::~World()
{
}

void World::Initialize() 
{
}

void World::Terminate() 
{
	for(auto gameObject : m_UpdateList)
	{
		m_DestroyList.push_back(gameObject->GetHandle());
	}
	m_UpdateList.clear();

	PurgeDestroyList();

	m_Camera = nullptr;
	m_Terrain = nullptr;
}

void World::LoadLevel(const char* p_Filename)
{
	TiXmlDocument levelDoc(p_Filename);
	Verify(levelDoc.LoadFile(), "Failed to load %s", p_Filename);
	Assert(levelDoc.Type() == TiXmlNode::TINYXML_DOCUMENT, "Invalid level file %s", p_Filename);

	const TiXmlNode* gameobjectsNode = levelDoc.FirstChild();
	Assert(strcmp(gameobjectsNode->Value(), "GameObjects") == 0, "Mlformed level file!");

	const TiXmlNode* nextGameObjectNode = gameobjectsNode->FirstChild();
	while(nextGameObjectNode != nullptr)
	{
		const TiXmlNode* nameNode = nextGameObjectNode->FirstChild();
		const TiXmlNode* templateNode = nameNode->NextSibling();
		const TiXmlNode* positionNode = templateNode->NextSibling();

		GameObjectHandle handle = Create(templateNode->FirstChild()->Value(), nameNode->FirstChild()->Value());
		if(handle.IsValid())
		{
			GameObject* gameObject = handle.Get();
			TransformComponent* transformComponent = nullptr;
			if(gameObject->GetComponent(transformComponent))
			{
				const TiXmlNode* xNode = positionNode->FirstChild();
				const TiXmlNode* yNode = positionNode->FirstChild()->NextSibling();
				const TiXmlNode* zNode = positionNode->FirstChild()->NextSibling()->NextSibling();
				
				f32 x = (f32)atof(xNode->FirstChild()->Value());
				f32 y = (f32)atof(yNode->FirstChild()->Value());
				f32 z = (f32)atof(zNode->FirstChild()->Value());

				transformComponent->Transform.SetPosition(Mathematics::MakeVector(x, y, z));
			}
		}
		nextGameObjectNode = nextGameObjectNode->NextSibling();
	}
}

GameObjectHandle World::Create(const char* p_Filename, const char* p_Name)
{
	GameObjectHandle handle = m_Factory.Create(p_Filename);
	Assert(handle.IsValid(), "Invalid ticket!");

	GameObject* gameObject = handle.Get();
	gameObject->m_World = this;
	gameObject->m_Handle = handle;
	gameObject->m_Name = p_Name;
	gameObject->Initialize();

	m_UpdateList.push_back(gameObject);

	return handle;
}

GameObjectHandle World::Find(const char* p_Name)
{
	for(auto gameObject : m_UpdateList)
	{
		if(strcmp(gameObject->GetName(), p_Name) == 0)
		{
			return gameObject->GetHandle();
		}
	}
	return GameObjectHandle();
}

void World::Destroy(GameObjectHandle p_Handle)
{
	if(!p_Handle.IsValid())
	{
		return;
	}
	
	if(!m_Updating)
	{
		DestroyImmediately(p_Handle);
	}
	else
	{
		m_DestroyList.push_back(p_Handle);
	}
}

void World::Update(f32 p_DeltaTime)
{
	Assert(!m_Updating, "Already updating the world");

	m_Updating = true;
	//recompute size as objects are updated
	for(u32 i = 0; i < m_UpdateList.size(); ++i) 
	{
		GameObject* gameObject = m_UpdateList[i];
		gameObject->Update(p_DeltaTime);
	}
	m_Updating = false;

	PurgeDestroyList();
}

void World::Render()
{
	const u32 numObjects = m_UpdateList.size();
	for(u32 i = 0; i < numObjects; ++i) 
	{
		GameObject* gameObject = m_UpdateList[i];
		gameObject->Render();
	}
}


void World::DestroyImmediately(GameObjectHandle p_Handle)
{
	Assert(!m_Updating, "Cannot destroy when updating!");

	if(!p_Handle.IsValid())
	{
		return;
	}

	GameObject* gameObject = p_Handle.Get();
	gameObject->Terminate();

	auto iter = std::find(m_UpdateList.begin(), m_UpdateList.end(), gameObject);
	if(iter != m_UpdateList.end())
	{
		m_UpdateList.erase(iter);
	}

	m_Factory.Destroy(p_Handle);
}


void World::PurgeDestroyList()
{
	for(auto object : m_DestroyList)
	{
		DestroyImmediately(object);
	}
	m_DestroyList.clear();
}