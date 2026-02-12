#pragma once

#include "Util.h"
#include "UrlParserHttp.h"	
#include "IOCPSocket.h"
#include "IOCPSocket2.h"
#include "HttpFormat.h"
#include "HTMLParserBase.h"
#include "Worker.h"

#include <set>
#include <queue>

#ifdef _DEBUG	// only be able to do this define in debug mode
#define BYPASS_HOST_UNIQUENESS false
#define BYPASS_ADDR_UNIQUENESS false
#endif


struct Counters {
	volatile LONG extracted;		// E
	volatile LONG unique_hosts;		// H
	volatile LONG dns_success;		// D
	volatile LONG unique_ips;		// I
	volatile LONG robots_passed;	// R
	volatile LONG crawled;			// C
	volatile LONG nlinks;			// L
	volatile LONG ntamu;

	volatile LONG s2;			// status 2xx
	volatile LONG s3;			// status 3xx
	volatile LONG s4;			// status 4xx
	volatile LONG s5;			// status 5xx
	volatile LONG s_other;		// other status code

	volatile LONG pages_elapsed;
	volatile LONG bytes_elapsed;
	volatile LONG total_bytes;
};

class Crawler {
	friend class Worker;

	std::set<std::string> seen_hosts{};
	std::set<int> seen_addrs{};
	std::queue<char*> urls;

	CRITICAL_SECTION seen_hosts_mutex;
	CRITICAL_SECTION seen_addrs_mutex;
	CRITICAL_SECTION urls_mutex;

	Counters stats;

	volatile LONG active_threads;
	HANDLE event_quit;
	clock_t start_t;

	static DWORD WINAPI StatsThread(LPVOID crawler);

	bool DuplicateHost(ParsedURL url);
	bool DuplicateAddr(int ip);

public:
	Crawler()	 : active_threads(0)
	{
		memset(&stats, 0, sizeof(Counters));

		InitializeCriticalSection(&seen_hosts_mutex);
		InitializeCriticalSection(&seen_addrs_mutex);
		InitializeCriticalSection(&urls_mutex);
		event_quit = CreateEvent(NULL, false, false, NULL);
	}

	~Crawler()
	{
		DeleteCriticalSection(&seen_hosts_mutex);
		DeleteCriticalSection(&seen_addrs_mutex);
		DeleteCriticalSection(&urls_mutex);
		CloseHandle(event_quit);
	}

	void Push(const std::vector<char*>& _urls)
	{
		EnterCriticalSection(&urls_mutex);
		for (char* url : _urls)
			urls.push(url);
		LeaveCriticalSection(&urls_mutex);
	}

	void Crawl(int nthreads);

};


