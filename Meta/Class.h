#ifndef IncludedMetaClassH
#define IncludedMetaClassH

//===========================================================================
// Filename:	Class.h
// Author:		Jarrod MacKay
// Description:	Meta data for Classs
//===========================================================================

#include <Core.h>
#include "Type.h"

namespace Meta
{
class Field;

class Class : public Type
{
//Operators
public:

	Class(const char* p_Name
		  , const u32 p_Size
		  , Type::CreatorFxn p_Create
		  , Type::DestroyerFxn p_Destroy
		  , const Class* p_Parent
		  , const Field* p_Fields
		  , const u32 p_NumFields);

	NonCopyable(Class);

//Methods
public:

	const Class* GetParent() const {return m_Parent;}

	const Field* FindField(const char* p_Name) const;

//Attributes
private:

	const Class* m_Parent;
	const Field* m_Fields;
	const u32 m_NumFields;
};
}

#endif //#ifndef IncludedMetaClassH