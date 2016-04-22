//===========================================================================
// Filename:	XmlFile.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "XmlFile.h"
#include <tinyxml.h>
#include <Meta.h>
#include <Mathematics.h>

namespace
{
	using namespace Serialization;
	using namespace Mathematics;

	template <Meta::Type::BasicType t_MetaBaseType, typename t_PointerType>
	bool Read(t_PointerType* p_Instance, const TiXmlNode* p_Node);

	template <>
	bool Read<Meta::Type::BasicType::Int, int>(int* p_Instance, const TiXmlNode* p_Node)
	{
		*p_Instance = atoi(p_Node->Value());
		return true;
	}

	template <>
	bool Read<Meta::Type::BasicType::Float, float>(float* p_Instance, const TiXmlNode* p_Node)
	{
		*p_Instance = static_cast<float>(atof(p_Node->Value()));
		return true;
	}

	template <>
	bool Read<Meta::Type::BasicType::Bool, bool>(bool* p_Instance, const TiXmlNode* p_Node)
	{
		*p_Instance = StringsEqual(p_Node->Value(), "true");
		return true;
	}

	template <>
	bool Read<Meta::Type::BasicType::String, std::string>(std::string* p_Instance, const TiXmlNode* p_Node)
	{
		*p_Instance = std::string(p_Node->Value());
		return true;
	}

	template <>
	bool Read<Meta::Type::BasicType::Vector, Mathematics::Vector3>(Mathematics::Vector3* p_Instance, const TiXmlNode* p_Node)
	{
		if (p_Node->FirstChild() == nullptr
			|| p_Node->NextSibling() == nullptr
			|| p_Node->NextSibling()->FirstChild() == nullptr
			|| p_Node->NextSibling()->NextSibling() == nullptr
			|| p_Node->NextSibling()->NextSibling()->FirstChild() == nullptr)
		{
			return false;
		}

		Read<Meta::Type::BasicType::Float, float>(&((*p_Instance)(0))
			, p_Node->FirstChild());
		Read<Meta::Type::BasicType::Float, float>(&((*p_Instance)(1))
			, p_Node->NextSibling()->FirstChild());
		Read<Meta::Type::BasicType::Float, float>(&((*p_Instance)(2))
			, p_Node->NextSibling()->NextSibling()->FirstChild());
		return true;
	}

	template <>
	bool Read<Meta::Type::BasicType::Colour, Mathematics::LinearColour>(Mathematics::LinearColour* p_Instance, const TiXmlNode* p_Node)
	{
		if (p_Node->FirstChild() == nullptr
			|| p_Node->NextSibling() == nullptr
			|| p_Node->NextSibling()->FirstChild() == nullptr
			|| p_Node->NextSibling()->NextSibling() == nullptr
			|| p_Node->NextSibling()->NextSibling()->FirstChild() == nullptr
			|| p_Node->NextSibling()->NextSibling()->NextSibling() == nullptr
			|| p_Node->NextSibling()->NextSibling()->NextSibling()->FirstChild() == nullptr)
		{
			return false;
		}

		Read<Meta::Type::BasicType::Float, float>(&(p_Instance->R)
			, p_Node->FirstChild());
		Read<Meta::Type::BasicType::Float, float>(&(p_Instance->G)
			, p_Node->NextSibling()->FirstChild());
		Read<Meta::Type::BasicType::Float, float>(&(p_Instance->B)
			, p_Node->NextSibling()->NextSibling()->FirstChild());
		Read<Meta::Type::BasicType::Float, float>(&(p_Instance->A)
			, p_Node->NextSibling()->NextSibling()->NextSibling()->FirstChild());
		return true;
	}

	bool Read(void* p_Instance, const Meta::Type* p_MetaType, const TiXmlNode* p_Node)
	{
		if (p_Node == nullptr)
		{
			return false;
		}

		switch (p_MetaType->GetBaseType())
		{
		case Meta::Type::BasicType::Int: 
			return Read<Meta::Type::BasicType::Int, int>
				(static_cast<int*>(p_Instance), p_Node);

		case Meta::Type::BasicType::Float: 
			return Read<Meta::Type::BasicType::Float, float>
				(static_cast<float*>(p_Instance), p_Node);

		case Meta::Type::BasicType::String: 
			return Read<Meta::Type::BasicType::String, std::string>
				(static_cast<std::string*>(p_Instance), p_Node);

		case Meta::Type::BasicType::Bool: 
			return Read<Meta::Type::BasicType::Bool, bool>
				(static_cast<bool*>(p_Instance), p_Node);

		case Meta::Type::BasicType::Vector: 
			return Read<Meta::Type::BasicType::Vector, Mathematics::Vector3>
				(static_cast<Mathematics::Vector3*>(p_Instance), p_Node);

		case Meta::Type::BasicType::Colour: 
			return Read<Meta::Type::BasicType::Colour, Mathematics::LinearColour>
				(static_cast<Mathematics::LinearColour*>(p_Instance), p_Node);

		case Meta::Type::BasicType::Class: 
			return XmlFile::Read(p_Instance, static_cast<const Meta::Class*>(p_MetaType), p_Node);

		default:
			Halt("Unknown basic type!");
			return false;
		}
	}
}

//===========================================================================
// XmlFile Definitions
//===========================================================================


bool XmlFile::Read(void* p_Instance, const Meta::Class* p_MetaClass, const TiXmlNode* p_Node)
{
	while (p_Node != nullptr)
	{
		const TiXmlElement* element = p_Node->ToElement();

		if (element != nullptr)
		{
			const char* fieldName = element->Attribute("name");
			const Meta::Field* metaField = p_MetaClass->FindField(fieldName);

			if (metaField != nullptr)
			{
				void* member = reinterpret_cast<u8*>(p_Instance)+metaField->GetByteOffset();
				bool success = ::Read(member, metaField->GetType(), element->FirstChild());
				if (!success)
				{
					return false;
				}
			}

		}

		p_Node = p_Node->NextSibling();
	}

	return true;
}