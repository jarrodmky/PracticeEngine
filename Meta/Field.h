#ifndef IncludedMetaFieldH
#define IncludedMetaFieldH

//===========================================================================
// Filename:	Field.h
// Author:		Jarrod MacKay
// Description:	Meta data for Fields
//===========================================================================

#include <Core.h>

namespace Meta
{
	class Type;

	class Field
	{
		//Operators
	public:

		Field(const char* p_Name, const Type* p_Type, const u32 p_Offset);

	//Methods
	public:

		const char* GetName() const { return m_Name; }
		const Type* GetType() const { return m_Type; }
		const u32 GetByteOffset() const { return m_Offset; }

		//Attributes
	private:

		const char* m_Name;
		const Type* m_Type;
		const u32 m_Offset;
	};
}

#endif //#ifndef IncludedMetaFieldH