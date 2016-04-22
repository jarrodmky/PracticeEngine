#ifndef IncludedMetaTypeH
#define IncludedMetaTypeH

//===========================================================================
// Filename:	Type.h
// Author:		Jarrod MacKay
// Description:	Meta data for types
//===========================================================================

#include <Core.h>

namespace Meta
{

	class Type
	{
		//Operators
	public:

		typedef void* (*CreatorFxn)();
		typedef void(*DestroyerFxn)(void*);

		enum class BasicType
		{
			Int,
			Float,
			String,
			Bool,
			Vector,
			Colour,
			Frame,
			AABB,
			Class
		};

		Type(const char* p_Name, const BasicType p_Base, const u32 p_Size, CreatorFxn p_Creator, DestroyerFxn p_Destroyer);

		//Methods
	public:

		const char* GetName() const { return m_Name; }
		const u32 GetSize() const { return m_Size; }
		const BasicType GetBaseType() const { return m_Base; }

		void* Create() const { return m_Create(); }
		void Destroy(void* p_Data) const { return m_Destroy(p_Data); }

		NonCopyable(Type);

		//Attributes
	private:

		const char* m_Name;
		const u32 m_Size;
		const BasicType m_Base;

		CreatorFxn m_Create;
		DestroyerFxn m_Destroy;
	};

}

#endif //#ifndef IncludedMetaTypeH