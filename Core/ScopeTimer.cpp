//====================================================================================================
// Filename:	ScopeTimer.cpp
// Created by:	Jarrod MacKay
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"
#include "ScopeTimer.h"
#include "Timer.h"
#include "Debug.h"

using namespace Core;

namespace
{
	const char nestingSpaces[] = "                                       ";
	const u32 nestingSpacesLength = LengthOf(nestingSpaces);
	const char* spaces = nestingSpaces + nestingSpacesLength - 1;

	Timer s_Timer;

	const u32 maxBufferSize = 64;
	char buffer[maxBufferSize];
	char* out = buffer;
	u32 bufferSize = maxBufferSize;
}

//====================================================================================================
// Class Definitions
//====================================================================================================

ScopeTimer::ScopeTimer(const char* p_TimerName)
: m_StartTime(s_Timer.GetTime())
, m_NameBuffer(p_TimerName)
{
	//print
	
	if (bufferSize > 64)
	{
		//int count = sprintf(out, "%sEntering %s\n", spaces, m_NameBuffer);
		//out += count;
		//bufferSize -= count;
	}

	spaces -= 1;
}

ScopeTimer::~ScopeTimer()
{
	f64 totalTime = s_Timer.GetTime() - m_StartTime;

	Core::Logger::get().profile(m_NameBuffer, totalTime);

	//print
	spaces += 1;
	
	if (bufferSize > 64)
	{
		//int count = sprintf(out, "%s%s took %10.16f seconds\n", spaces, m_NameBuffer, totalTime);
		//out += count;
		//bufferSize -= count;
	}
}

void ScopeTimer::StaticInitialize()
{
#if defined(USE_PROFILER)
	s_Timer.Initialize();
#endif
}

void ScopeTimer::StaticShutdown()
{
#if defined(USE_PROFILER)
	out = '\0';
	Log(buffer);
#endif
}