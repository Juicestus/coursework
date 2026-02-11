#include "pch.h"
#include "Crawler.h"

#define STATS_PERIOD 500

DWORD WINAPI Crawler::StatsThread(LPVOID _crawler)
{
	Crawler* crawler = (Crawler*)_crawler;

	while (WaitForSingleObject(crawler->event_quit, STATS_PERIOD) == WAIT_TIMEOUT)
	{
		size_t qsize;
		EnterCriticalSection(&crawler->urls_mutex);
		qsize = crawler->urls.size();
		LeaveCriticalSection(&crawler->urls_mutex);

		long elapsed = (clock() - crawler->start_t) / 1000;

		long _pages_elapsed = InterlockedExchange(&crawler->stats.pages_elapsed, 0);
		long _bytes_elapsed = InterlockedExchange(&crawler->stats.bytes_elapsed, 0);

		printf("[%3d] %8d Q %6d E %7d H %6d D %6d I %5d R %5d C %5d L %4dK\n",
			elapsed,
			crawler->active_threads,
			qsize,
			crawler->stats.extracted,
			crawler->stats.unique_hosts,
			crawler->stats.dns_success,
			crawler->stats.unique_ips,
			crawler->stats.robots_passed,
			crawler->stats.crawled,
			crawler->stats.nlinks / 1000);

		printf(" *** crawling %.1f pps @ %.1f Mbps\n",
				_pages_elapsed / (STATS_PERIOD/1000.0), (_bytes_elapsed * 8.0) / (STATS_PERIOD * 1000.0));
	}

	return 0;
}


void Crawler::Crawl(int nthreads)
{
	start_t = clock();

	HANDLE stats_thread;
	if ((stats_thread = CreateThread(NULL, 0, StatsThread, this, 0, NULL)) == NULL)
	{
		FATAL("Could not create stats thread (error %d)\n", GetLastError());
		return;
	}

	std::vector<HANDLE> workers(nthreads);
	for (int i = 0; i < nthreads; i++)
	{
		if ((workers[i] = CreateThread(NULL, 0, Worker::Start, this, 0, NULL)) == NULL)
		{
			FATAL("Could not create worker thread #%d (error %d)\n", i, GetLastError());
			return;
		}
	}

	for (int i = 0; i < workers.size(); i += MAXIMUM_WAIT_OBJECTS)
	{
		int n = min(MAXIMUM_WAIT_OBJECTS, workers.size());
		WaitForMultipleObjects(n, workers.data(), TRUE, INFINITE);
	}
	//std::cout << "DONE!\n";

	SetEvent(event_quit);
	WaitForSingleObject(stats_thread, INFINITE);

	for (int i = 0; i < nthreads; i++)	CloseHandle(workers[i]);
	CloseHandle(stats_thread);

	double elapsed = (clock() - start_t) / 1000.0;
	printf("\n");
	printf("Extracted %d URLs @ %.0f/s\n", stats.extracted, stats.extracted / elapsed);
	printf("Looked up %d DNS names @ %.0f/s\n", stats.dns_success, stats.dns_success / elapsed);
	printf("Attempted %d robots @ %.0f/s\n", stats.unique_ips, stats.unique_ips / elapsed);
	printf("Crawled %d pages @ %.0f/s\n", stats.crawled, stats.crawled / elapsed);
	printf("Parsed %d links @ %.0f/s\n", stats.nlinks, stats.nlinks / elapsed);

	printf("HTTP codes: 2xx = %d, 3xx = %d, 4xx = %d, 5xx = %d, other = %d\n",
		stats.s2, stats.s3, stats.s4, stats.s5, stats.s_other);

}



bool Crawler::DuplicateHost(ParsedURL url)
{
#if BYPASS_HOST_UNIQUENESS
	return false;
#else
	bool ret = false;
	EnterCriticalSection(&seen_hosts_mutex);
	std::string host(url.host);
	if (seen_hosts.contains(host))	
		ret = true;
	else 
		seen_hosts.insert(host);
	LeaveCriticalSection(&seen_hosts_mutex);
	return ret;
#endif
}

bool Crawler::DuplicateAddr(int ip)
{
#if BYPASS_ADDR_UNIQUENESS 
	return false;
#else
	bool ret = false;
	EnterCriticalSection(&seen_addrs_mutex);
	if (seen_addrs.contains(ip))
		ret = true;
	else 
		seen_addrs.insert(ip);
	LeaveCriticalSection(&seen_addrs_mutex);
	return ret;
#endif
}


