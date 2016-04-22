//===========================================================================
// Filename:	Registry.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Registry.h"
#include "Class.h"
#include <Mathematics.h>

using namespace Meta;

//===========================================================================
// Registry Definitions
//===========================================================================

namespace
{
	typedef std::map<u64, const Class*> MetaClassMap;

	MetaClassMap s_MetaClasses;
}

void Meta::Register(const Class* p_Class)
{
	const u64 key = HashStringTo64bitInteger(p_Class->GetName());
	s_MetaClasses.insert(std::make_pair(key, p_Class));
}

const Class* Meta::GetClass(const char* p_ClassName)
{
	const u64 key = HashStringTo64bitInteger(p_ClassName);
	auto iter = s_MetaClasses.find(key);
	Assert(iter != s_MetaClasses.end(), "Meta class %s not found!", p_ClassName);
	return iter->second;
}