//===========================================================================
// Filename:	GameObjectFactory.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "GameObjectFactory.h"

using namespace Gameplay;
using namespace Serialization;

//===========================================================================
// Class Definitions
//===========================================================================

GameObjectFactory::GameObjectFactory(GameObjectPool& p_Pool)
: m_Pool(p_Pool)
{

}

GameObjectFactory::~GameObjectFactory()
{

}

GameObjectHandle GameObjectFactory::Create(const char* p_FileName)
{
	using namespace Mathematics;

	GameObjectHandle ticket = m_Pool.Allocate();
	GameObject* gameObject = ticket.Get();


	//TODO asserts should be ifs... data is optional!
	TiXmlDocument templateDoc(p_FileName);
	Verify(templateDoc.LoadFile(), "Failed to load %s", p_FileName);
	Assert(templateDoc.Type() == TiXmlNode::TINYXML_DOCUMENT, "Invalid template file %s", p_FileName);

	const TiXmlNode* objectNode = templateDoc.FirstChild();
	if(StringsEqual(objectNode->Value(), "GameObject"), "Malformed template file!")
	{

		const TiXmlNode* componentsNode = objectNode->FirstChild();
		if(StringsEqual(componentsNode->Value(), "Components"), "Malformed template file!")
		{

			const TiXmlNode* nextComponentNode = componentsNode->FirstChild();
			while(nextComponentNode != nullptr)
			{
				const char* componentName = nextComponentNode->Value();

				const Meta::Class* metaClass = nullptr; //Meta::GetClass(componentName);
				if(metaClass == nullptr)
				{
					Log("Class %s is not registered!", componentName);
				}
				else
				{
					void* newComponent = metaClass->Create();
					const TiXmlNode* data = nextComponentNode->FirstChild();
					Verify(Serialization::XmlFile::Read(newComponent, metaClass, data), "Failed to read %s", componentName);
					gameObject->AddComponent((Component*)newComponent);
				}

				nextComponentNode = nextComponentNode->NextSibling();
			}
		}
	}

	gameObject->Initialize();

	return ticket;
}

void GameObjectFactory::Destroy(GameObjectHandle p_Ticket)
{
	if(p_Ticket.IsValid())
	{
		m_Pool.Free(p_Ticket);
	}
}