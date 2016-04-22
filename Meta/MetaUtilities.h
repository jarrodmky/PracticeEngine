#ifndef IncludedMetaUtilitiesH
#define IncludedMetaUtilitiesH

//===========================================================================
// Filename:	MetaUtilities.h
// Author:		Jarrod MacKay
// Description:	Main entry point into MetaUtilities system library
//===========================================================================

namespace Meta
{
	//Requires explicit specialization per type!
	template <typename t_DataType>
	inline const Type* DeduceDataType();

	template <typename t_ClassType, typename t_DataType>
	inline const Type* DeduceMemberDataType(t_DataType t_ClassType::*)
	{
		return DeduceDataType<t_DataType>();
	}

	template <typename t_ClassType, typename t_DataType>
	inline u32 GetFieldOffset(t_DataType t_ClassType::* p_Field)
	{
		return reinterpret_cast<u32>(static_cast<void*>(&(static_cast<t_ClassType*>(nullptr)->*p_Field)));
	}
}




#endif //#ifndef IncludedMetaUtilitiesH