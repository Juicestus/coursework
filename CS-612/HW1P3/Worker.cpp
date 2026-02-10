#include "pch.h"
#include "Worker.h"
#include "Crawler.h"

DWORD WINAPI Worker::Start(LPVOID ptr)
{
	Crawler* crawler = (Crawler*)ptr;
	int id = (int)InterlockedIncrement(&crawler->active_threads);

	Worker worker(id, crawler);
	worker.Run();

	InterlockedDecrement(&crawler->active_threads);

	return 0;
}

void Worker::Run()
{
	while (true)
	{
		char* url;
		EnterCriticalSection(&crawler->urls_mutex);
		if (crawler->urls.empty())
		{
			url = nullptr;
		}
		else
		{
			url = crawler->urls.front();
			crawler->urls.pop();
		}
		LeaveCriticalSection(&crawler->urls_mutex);

		if (!url) break;
		InterlockedIncrement(&crawler->stats.extracted);
		Crawl(url);
	}
}

int Worker::Crawl(char* url)
{
	//std::cout << "URL: " << url << "\n";
	//printf("\n%s\n\n", url);

	ParsedURL parsed(url);
	if (!parsed.valid) return 1;

	//parsed.Print();

	if (crawler->DuplicateHost(parsed))
	{
		return 1;
	}
	InterlockedIncrement(&crawler->stats.unique_hosts);

	if (socket.DNS(parsed.host, parsed.port))
	{
		return 1;
	}
	InterlockedIncrement(&crawler->stats.dns_success);

	if (crawler->DuplicateAddr(socket.addr()))
	{
		return 1;
	}
	InterlockedIncrement(&crawler->stats.unique_ips);

	/*
	* ROBOT REQUEST
	*/

	//std::cout << "        Connecting on robots... ";
	socket.Reset();
	if (socket.Connect())
	{
		return 1;
	}

	char* req = EncodeHttpRobotsRequest(parsed);
	if (socket.Send(req))
	{
		free(req);
		return 1;
	}
	free(req);

	if (socket.Recv())
	{
		return 1;
	}

	HttpResponse resp = DecodeHttpResponse(socket.data(), socket.size());
	if (resp.status != 404)
	{
		return 1;
	}
	InterlockedIncrement(&crawler->stats.robots_passed);

	/*
	* PAGE REQUEST
	*/

	//std::cout << "      * Connecting on page... ";
	socket.Reset();
	if (socket.Connect() != 0)
	{
		return 1;
	}

	req = EncodeHttpRequest(parsed);
	if (socket.Send(req))
	{
		free(req);
		return 1;
	}
	free(req);

	if (socket.Recv())
	{
		return 1;
	}
	//std::cout << "Read " << socket.size() << " bytes from socket:\n\n";


	resp = DecodeHttpResponse(socket.data(), socket.size());
	if (resp.status < 0)
	{
		return 1;
	}

	if (resp.status >= 500)			InterlockedIncrement(&crawler->stats.s5);
	else if (resp.status >= 400)	InterlockedIncrement(&crawler->stats.s4);
	else if (resp.status >= 300)	InterlockedIncrement(&crawler->stats.s3);
	else if (resp.status >= 200)	InterlockedIncrement(&crawler->stats.s2);
	else							InterlockedIncrement(&crawler->stats.s_other);	

	//printf("HttpResponse:\n\tstatus = %d\n\tlength = %d\n\tbody:\n%s\n",
		//resp.status, resp.len, resp.body);

	InterlockedAdd(&crawler->stats.bytes_elapsed, socket.size());
	InterlockedAdd(&crawler->stats.total_bytes, socket.size());
	InterlockedIncrement(&crawler->stats.pages_elapsed);

	if (resp.Is2XX())
	{
		char* urlbuf = extractstr(url);
		int nlinks = 0;
		html_parser.Parse(resp.body, resp.len, urlbuf, strlen(urlbuf), &nlinks);
		free(urlbuf);

		InterlockedIncrement(&crawler->stats.crawled);
		//if (nlinks>0) 
		InterlockedAdd(&crawler->stats.nlinks, nlinks);
	}

	//printf("----------------------------------------\n");
	//printf("%s\n", resp.header);

	return 0;
}

