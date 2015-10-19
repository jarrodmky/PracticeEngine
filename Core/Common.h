#ifndef IncludedCoreCommonH
#define IncludedCoreCommonH

//===========================================================================
// Filename:	Common.h
// Author:		Jarrod MacKay
// Description:	Common headers and definitions for internal and external usage.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

//Standard headers
#include <stdio.h>
#include <Windows.h>

//STL Headers
#include <limits>
#include <map>
#include <random>
#include <vector>

//===========================================================================
// Macros
//===========================================================================

#define LengthOf(AnArray)\
	sizeof(AnArray) / sizeof(AnArray[0])

#define NonCopyable(Class)\
	Class(const Class&) = delete;\
	Class& operator =(const Class&) = delete;

#define NonInstantiable(Class)\
	Class() = delete;\
	NonCopyable(Class)

//===========================================================================
// Functions
//===========================================================================

template <typename t_Type>
inline void ProperlyDelete(t_Type*& p_Pointer)
{
	delete p_Pointer;
	p_Pointer = nullptr;
}

template <typename t_Type>
inline void ProperlyDeleteArray(t_Type*& p_Pointer)
{
	delete[] p_Pointer;
	p_Pointer = nullptr;
}

template <typename t_Type>
inline void ProperlyRelease(t_Type*& p_Pointer)
{
	if(p_Pointer != nullptr)
	{
		p_Pointer->Release();
		p_Pointer = nullptr;
	}
}

#endif //#ifndef IncludedCoreCommonH