#ifndef IncludedCoreDebugH
#define IncludedCoreDebugH

//===========================================================================
// Filename:	Macros.h
// Author:		Jarrod MacKay
// Description:	Provides assertion macros.
//===========================================================================

#include "Logger.h"

//===========================================================================
// Macros
//===========================================================================

#if defined(_DEBUG)

//TODO: should do a memcopy to truncate inputs to fit buffer
#define Log(format, ...)\
	Core::Logger::get().log(format, __VA_ARGS__)

#define Halt(format, ...)\
		{\
			Log((format), __VA_ARGS__);\
			Core::Logger::get().close();\
			DebugBreak();\
		}

#define Assert(condition, format, ...)\
		{\
		if(!(condition))\
			{\
			Halt((format), __VA_ARGS__);\
			}\
		}

#define AssertOnly(condition) Assert(condition, #condition)

#define Verify(condition, format, ...) Assert(condition, format, __VA_ARGS__)

#define DebugBlock(...) ScopedBlock(__VA_ARGS__)

#else

#define Log(format, ...)
#define Assert(condition, format, ...) Likely(condition)
#define Verify(condition, format, ...) condition
#define TestBlock(...)

#define DebugBlock(...)

#endif // #if defined(_DEBUG)

#endif //#ifndef IncludedCoreDebugH