//===========================================================================
// Filename:	Logger.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Logger.h"
#include <time.h>

//===========================================================================
// Implementation Declarations
//===========================================================================

namespace
{
	using namespace Core;
}

//===========================================================================
// Interface
//===========================================================================

Logger* Logger::m_spOnlyInstance;

Logger::Logger()
	: m_pLogFile(nullptr)
	, m_LogThread()
	, m_bIsRunning(false)
	, m_sLogFilename()
	, m_ScopeProfile()
	, m_ProfileLock()
	, m_LogQueue()
	, m_QueueLock()
	, m_QueueSemaphore(nullptr)
{
	m_QueueSemaphore = CreateSemaphore(NULL, 0, 10000, NULL);
}

Logger::~Logger()
{
	Assert(!m_bIsRunning, "Still running!");
	Assert(m_QueueSemaphore == nullptr, "Queue semaphore still allocated!");
}

void Logger::run(void)
{
	m_bIsRunning = true;

	//wait for a log entry
	//write if we get one
	while (m_bIsRunning)
	{
		DWORD rc = WaitForSingleObject(m_QueueSemaphore, 100);

		if (rc == WAIT_ABANDONED)
		{
			log("Logging thread was abandoned unexpectedly!");

		}
		else if (rc == WAIT_FAILED)
		{
			log("Something went wrong with logging thread!");
		}
		else if (rc == WAIT_OBJECT_0)
		{
			if (m_LogQueue.empty() == false)
			{
				ProcessEntry();
			}
		}
	}
}

bool Logger::open(void)
{
	char szModName[MAX_PATH + 1];
#if defined(WIN32)
	if (!GetModuleFileNameA(NULL, szModName, MAX_PATH))
#endif
	{
		strcpy_s(szModName, MAX_PATH, "INVALID_PROGRAM");
	}


	//make sure that the szModeBName is only the base file name and not the path or extension

	//eg: thisapplication.syslog
	m_sLogFilename.append(szModName);

	//drive:\\path\\file.ext
	std::string::size_type position = m_sLogFilename.find_last_of('\\');
	if (position != std::string::npos)
	{
		std::string::size_type extpos = m_sLogFilename.find_first_of('.');
		if (extpos != std::string::npos)
		{
			m_sLogFilename = m_sLogFilename.substr(position + 1, extpos - (position + 1));
		}
	}

	m_sLogFilename.append(".syslog");

	fopen_s(&m_pLogFile, m_sLogFilename.c_str(), "wb");
	if (m_pLogFile)
	{
		m_LogThread = std::thread(logThreadFunc, this);
		if (m_LogThread.joinable())
		{
			return true;
		}
	}
	return false;
}

bool Logger::close(void)
{
	for (Profile::const_iterator I = m_ScopeProfile.begin();
		I != m_ScopeProfile.end(); ++I)
	{
		const f64 averageTime = I->second.CumulativeTime / static_cast<f64>(I->second.Amount);
		log("%s took about %10.16f", I->second.Name, averageTime);
	}
	log("");

	while (!m_LogQueue.empty())
	{
		::Sleep(1);
	}

	if (m_pLogFile)
	{
		fclose(m_pLogFile);
	}
	
	m_bIsRunning = false;
	m_LogThread.join();
	return true;
}

void Logger::profile(const char* p_pScopeName, f64 p_ScopeTime)
{
	u64 hashKey = HashStringTo64bitInteger(p_pScopeName);
	p_ScopeTime;
	hashKey;
	m_ProfileLock.lock();
	Scope& scope = m_ScopeProfile[hashKey];
	++scope.Amount;
	scope.CumulativeTime += p_ScopeTime;
	sprintf_s(scope.Name, scopeNameSize, "%s", p_pScopeName);
	m_ProfileLock.unlock();
}

Logger& Logger::get(void)
{
	if (!m_spOnlyInstance)
	{
		m_spOnlyInstance = new Logger();
	}
	return *m_spOnlyInstance;
}

void Logger::ProcessEntry()
{
	m_QueueLock.lock();
	std::string logEntry = m_LogQueue.front();
	m_LogQueue.pop();
	m_QueueLock.unlock();

	if (m_pLogFile)
	{
		::OutputDebugStringA(logEntry.c_str());
		fwrite(logEntry.c_str(), logEntry.length(), 1, m_pLogFile);
	}
}

#undef STRING_BUFFER_SIZE