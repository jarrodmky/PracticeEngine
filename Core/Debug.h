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

	#define Verify(condition, format, ...)\
	{\
		if(!(condition))\
		{\
			Log(format, __VA_ARGS__)\
			DebugBreak();\
		}\
	}

#else

	#define Log(format, ...)
	#define Assert(condition, format, ...)
	#define Verify(condition, format, ...) condition

#endif // #if defined(_DEBUG)

#endif //#ifndef IncludedCoreDebugH