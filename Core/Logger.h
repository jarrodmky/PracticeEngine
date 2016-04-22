#ifndef IncludedSimLoggerH
#define IncludedSimLoggerH

//===========================================================================
// Filename:	Logger.h
// Author:		Jarrod MacKay
// Description:	Creates and manages a seperate thread for string output and profiling
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <queue>
#include <thread>
#include <mutex>

#include "Types.h"

//===========================================================================
// Classes
//===========================================================================

namespace Core
{
	//usage
	//dbprintf("a string");
	//log("a string");

	class Logger;

	//singleton works here so AISysLog::Get().log("some string")

	//enum eSysLogCategory : unsigned long long
	//{
	//	Sys = 1 << 1,
	//	Main = 1 << 2,
	//	Renderer = 1 << 3,
	//	Animator = 1 << 4,
	//	Audio = 1 << 5,
	//	Simulator = 1 << 6,
	//	AssetLoader = 1 << 7,
	//	GUI = 1 << 8,
	//	Memory = 1 << 9,
	//	Networking = 1 << 10,
	//	Metrics = 1 << 11, //analytics subsystem
	//	All = 0xffffffffffff
	//};

	void logThreadFunc(Logger* p_SysLog);

	class Logger
	{
		static const u8 scopeNameSize = 128;
		static const u16 logBufferSize = 8196;
		
		struct Scope
		{
			Scope()
				: CumulativeTime(0.0f)
				, Amount(0)
			{}

			f64 CumulativeTime;
			u32 Amount;
			char Name[scopeNameSize];
		};

		typedef std::map<u64, Scope> Profile;

		friend void logThreadFunc(Logger* p_SysLog);

	public: //methods

		bool open();

		bool close();

		template <typename... t_Args>
		void log(const char* p_pFormat, const t_Args&... p_Args);

		void profile(const char* p_pScopeName, f64 p_ScopeTime);

	private:

		Logger();

		~Logger();

		void run(void);

		void ProcessEntry();

	public: //Statics

		static Logger& get();

	protected: //Attributes

		FILE* m_pLogFile;

		std::thread m_LogThread;

		volatile bool m_bIsRunning;

		std::string m_sLogFilename;

		Profile m_ScopeProfile;

		std::mutex m_ProfileLock;

		std::queue<std::string> m_LogQueue;

		std::mutex m_QueueLock;

		void* m_QueueSemaphore;

	private:

		static Logger* m_spOnlyInstance;
	};

	//shortcut macro
#define LoggerPrint Logger::get().log

	inline void logThreadFunc(Logger* p_SysLog)
	{
		p_SysLog->run();
	}

	//LOG FUNCTION

	template <typename... t_Args>
	void Logger::log(const char* p_pFormat, const t_Args&... p_Args)
	{
		//system category?
		time_t mytime = time(NULL);

		char buffer[logBufferSize];
		int charsUnused = logBufferSize;
		charsUnused -= sprintf_s(buffer, charsUnused - 1, "\n");
		ctime_s(buffer + (logBufferSize - charsUnused), charsUnused - 1, &mytime);

		charsUnused = logBufferSize - strlen(buffer);

		charsUnused -= sprintf_s(buffer + (logBufferSize - charsUnused), charsUnused - 1, p_pFormat, p_Args...);

		m_QueueLock.lock();
		m_LogQueue.push(buffer);
		m_QueueLock.unlock();
		ReleaseSemaphore(m_QueueSemaphore, 1, NULL);
	}
}

#endif // #ifndef IncludedSimLoggerH