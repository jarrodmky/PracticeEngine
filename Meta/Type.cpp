//===========================================================================
// Filename:	Type.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include <Mathematics.h>
#include "Type.h"
#include "MetaUtilities.h"

using namespace Mathematics;

//===========================================================================
// Type Definitions
//===========================================================================

Meta::Type::Type(const char* p_Name
	, const BasicType p_Base
		   , const u32 p_Size
		   , CreatorFxn p_Creator
		   , DestroyerFxn p_Destroyer)
			 : m_Name(p_Name)
			 , m_Base(p_Base)
			 , m_Size(p_Size)
			 , m_Create(p_Creator)
			 , m_Destroy(p_Destroyer)
{}

#define MetaRegisterType(name, dataType)\
namespace { namespace Details {\
	void* Create##name() {	return new dataType; }\
	void Destroy##name(void* p_Data) { delete static_cast<dataType*>(p_Data); }\
}}\
	template<> const Meta::Type* Meta::DeduceDataType<dataType>()\
{\
	static Meta::Type s_Type(#name, Meta::Type::BasicType::##name, sizeof(dataType)\
	, Details::Create##name, Details::Destroy##name);\
	return &s_Type;\
}

MetaRegisterType(Int, int);
MetaRegisterType(Float, float);
MetaRegisterType(Bool, bool);
MetaRegisterType(String, std::string);
MetaRegisterType(Colour,  Mathematics::LinearColour);
MetaRegisterType(Vector,  Mathematics::Vector3);
MetaRegisterType(Frame, Mathematics::Frame);
MetaRegisterType(AABB, Mathematics::AABB3);