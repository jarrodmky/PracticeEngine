#ifndef IncludedCoreScopeTimerH
#define IncludedCoreScopeTimerH

//====================================================================================================
// Filename:	ScopeTimer.h
// Created by:	Jarrod MacKay
// Description:	Class for high resolution ScopeTimer
//====================================================================================================

#define USE_PROFILER
#include "Types.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

namespace Core
{

class ScopeTimer
{
public:
	ScopeTimer(const char* p_TimerName);
	~ScopeTimer();

	static void StaticInitialize();
	static void StaticShutdown();

private:

	f64 m_StartTime;
	const char* m_NameBuffer;
};

#if defined(USE_PROFILER)
#define Time(name)\
	Core::ScopeTimer scopedTimer(name);
#else
#define Time(name)
#endif


}

#endif // #ifndef IncludedCoreScopeTimerH