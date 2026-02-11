
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "Util.h"
#include "UrlParserHttp.h"	
#include "IOCPSocket.h"
#include "HttpFormat.h"
#include "HTMLParserBase.h"
#include "Crawler.h"
#include "Worker.h"

int main(int argc, char** argv)
{

	int ret = 1;
	if (argc < 3)
	{
		FATAL("Usage: .\\HW1P3.exe <n threads> <url file>");
		return 1;
	}
	int nthreads = atoi(argv[1]);	// check err condition here?
	if (nthreads < 0)
	{
		FATAL("Usage: .\\HW1P2.exe <n threads> <url file>");
		return 1;
	}

	IOCPSocket::InitWinSock();
	//IOCPSocket2::InitWinSock();

	Crawler crawler;

	std::vector<char*> urls = ReadFileLines(argv[2]);

	crawler.Push(urls);
	crawler.Crawl(nthreads);

	//IOCPSocket2::CloseWinSock();
	IOCPSocket::CloseWinSock();


}

