//===========================================================================
// Filename:	Class.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include "Class.h"
#include "Field.h"

//===========================================================================
// Class Definitions
//===========================================================================

Meta::Class::Class(const char* p_Name
			 , const u32 p_Size
			 , Meta::Type::CreatorFxn p_Create
			 , Meta::Type::DestroyerFxn p_Destroy
			 , const Meta::Class* p_Parent
			 , const Meta::Field* p_Fields
			 , const u32 p_NumFields)
			 : Type(p_Name, BasicType::Class, p_Size
			 , p_Create, p_Destroy)
			 , m_Parent(p_Parent)
			 , m_Fields(p_Fields)
			 , m_NumFields(p_NumFields)
{
}

const Meta::Field* Meta::Class::FindField(const char* p_Name) const
{
	for(u32 i = 0; i < m_NumFields; ++i)
	{
		if(StringsEqual(m_Fields[i].GetName(), p_Name))
		{
			return &m_Fields[i];
		}
	}
	return nullptr;
}