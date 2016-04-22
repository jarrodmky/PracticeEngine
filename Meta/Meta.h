#ifndef IncludedMetaH
#define IncludedMetaH

//===========================================================================
// Filename:	Meta.h
// Author:		Jarrod MacKay
// Description:	Main entry point into meta system library
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Type.h"
#include "MetaUtilities.h"
#include "Field.h"
#include "Class.h"
#include "Registry.h"

//===========================================================================
// Macro Definitions
//===========================================================================

#define MetaClassDeclare\
	static const ::Meta::Class* StaticGetMetaClass();\
	virtual const ::Meta::Class* GetMetaClass() const { return StaticGetMetaClass(); }

#define MetaClassBegin(classType)\
	MetaClassBeginInternal(classType);\
	const ::Meta::Class* parentMetaClass = nullptr;

#define MetaDerivedClassBegin(classType, parentType)\
	MetaClassBeginInternal(classType); \
	const ::Meta::Class* parentMetaClass = parentType::StaticGetMetaClass();

#define MetaClassBeginInternal(classType)\
	namespace {	namespace Details {\
	void* Create() { return new classType(); }\
	void Destroy(void* p_Data) { delete static_cast<classType*>(p_Data); }\
	}}\
	template <> const Meta::Type* Meta::DeduceDataType<classType>()\
	{\
		return classType::StaticGetMetaClass(); \
	}\
	const Meta::Class* classType::StaticGetMetaClass() {\
	typedef classType LocalType; \
	const char* className = #classType;

#define MetaFieldBegin static const Meta::Field fields[] = {

#define MetaField(field, name)\
	Meta::Field(name, Meta::DeduceMemberDataType(&LocalType::field)\
	, Meta::GetFieldOffset(&LocalType::field))

#define MetaFieldEnd\
	}; \
	static const u32 numFields = LengthOf(fields);

#define MetaNoFields\
	static const Meta::Field* fields = nullptr; \
	static const u32 numFields = 0;

#define MetaClassEnd\
	static const Meta::Class s_MetaClass(className, sizeof(LocalType)\
	, Details::Create, Details::Destroy, parentMetaClass, fields, numFields);\
	return &s_MetaClass;}

#endif //#ifndef IncludedMetaH