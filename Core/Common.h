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
#include <algorithm>
#include <complex>
#include <fstream>
#include <functional>
#include <iomanip>
#include <limits>
#include <map>
#include <memory>
#include <random>
#include <regex>
#include <sstream>
#include <vector>

//dubug
#include "Debug.h"

//===========================================================================
// Macros
//===========================================================================

#define LengthOf(StaticArray)\
	sizeof(StaticArray) / sizeof(StaticArray[0])

#define Likely(Condition)\
	__assume(Condition)

#define ScopedBlock(...) do { __VA_ARGS__ } while (0)

#define NonCopyable(Class)\
	Class(const Class&) = delete;\
	Class& operator =(const Class&) = delete

#define NonDynamic(Class)\
      void* operator new(size_t) = delete;\
	  void* operator new[](size_t) = delete;\
	  void operator delete(void *) = delete;\
	  void operator delete[](void*) = delete

/*

#define NonConstructable(Class)\
	template <typename... t_Args>\
	Class(const t_Args&... p_Args) = delete;\
	NonCopyable(Class)*/

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

template <typename t_Type>
using UnaryFxn = std::function<const t_Type(const t_Type&)>;

template <typename t_Type>
using BinaryFxn = std::function<const t_Type(const t_Type&, const t_Type&)>;

template <typename t_Type>
using BoolFxn = std::function<const bool(const t_Type&, const t_Type&)>;



template <typename t_Type>
inline const t_Type SmallerOf(const t_Type& p_A, const t_Type& p_B)
{
	return (p_A < p_B) ? (p_A) : (p_B);
}

template <typename t_Type>
inline const t_Type LargerOf(const t_Type& p_A, const t_Type& p_B)
{
	return (p_A > p_B) ? (p_A) : (p_B);
}

inline const bool StringsEqual(const char* p_A, const char* p_B)
{
	return strcmp(p_A, p_B) == 0;
}

//uses djb2 by Dan Bernstein 
inline const u64 HashStringTo64bitInteger(const char* p_String)
{
	u64 hash = 5381;
	s32 c;

	while (c = *p_String++)
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash;
}

#endif //#ifndef IncludedCoreCommonH