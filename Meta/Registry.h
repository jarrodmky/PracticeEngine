#ifndef IncludedMetaRegistryH
#define IncludedMetaRegistryH

//===========================================================================
// Filename:	Registry.h
// Author:		Jarrod MacKay
// Description:	Registers classes for RTTI
//===========================================================================

namespace Meta
{
	class Class;

	void Register(const Class* p_Class);
	const Class* GetClass(const char* p_Class);
}

#endif //#ifndef IncludedMetaRegistryH