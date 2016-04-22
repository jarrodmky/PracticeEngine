#ifndef INCLUDED_SIEGE_TIMER_H
#define INCLUDED_SIEGE_TIMER_H

//====================================================================================================
// Filename:	Timer.h
// Created by:	Peter Chan
// Description:	Class for high resolution timer
//====================================================================================================

#include "Types.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

namespace Core
{

class Timer
{
public:
	Timer();

	void Initialize();
	void Update();

	f64 GetElapsedTime() const;
	f64 GetTotalTime() const;
	f64 GetFramesPerSecond() const;
	f64 GetTime() const;

private:

	LARGE_INTEGER mTicksPerSecond;
	LARGE_INTEGER mLastTick;
	LARGE_INTEGER mCurrentTick;
	
	f64 m_SecondsPerTick;

	f64 mElapsedTime;
	f64 mTotalTime;
	
	f64 mNextUpdateTime;
	f64 mFrameSinceLastSecond;
	f64 mFramesPerSecond;
};

}

#endif // #ifndef INCLUDED_SIEGE_TIMER_H