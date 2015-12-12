#ifndef IncludedCoreDebugH
#define IncludedCoreDebugH

//===========================================================================
// Filename:	Debug.h
// Author:		Jarrod MacKay
// Description:	Provides assertion macros.
//===========================================================================

//===========================================================================
// Macros
//===========================================================================

#if defined(_DEBUG)

	#define DebugTest(...) do { __VA_ARGS__; } while (0)

	//TODO: should do a memcopy to truncate inputs to fit buffer
	#define Log(format, ...)\
	{\
		char writeOutBuffer[1024];\
		int writeLength = sprintf_s(writeOutBuffer, 1023, (format), __VA_ARGS__);\
		writeOutBuffer[writeLength] = '\n';\
		writeOutBuffer[writeLength + 1] = '\0';\
		OutputDebugStringA(writeOutBuffer);\
		}

	#define Assert(condition, format, ...)\
	{\
		if(!(condition))\
		{\
			Log(format, __VA_ARGS__)\
			DebugBreak();\
		}\
	}

	#define AssertOnly(condition) Assert(condition, #condition);

	#define Verify(condition, format, ...)\
	{\
		Assert(condition, format, __VA_ARGS__);\
	}

#else

	#define DebugTest(...)
	#define Log(format, ...)
	#define Assert(condition, format, ...)
	#define Verify(condition, format, ...) condition

#endif // #if defined(_DEBUG)

#endif //#ifndef IncludedCoreDebugH