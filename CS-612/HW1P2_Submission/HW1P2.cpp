
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
#include "FileReader.h"
#include "Crawler.h"


int main(int argc, char** argv)
{
	
	int ret = 1;
	if (argc < 3)
	{
		FATAL("Usage: .\\HW1P2.exe <n threads> <url file>");
		return 1;
	}
	int nthreads = atoi(argv[1]);	// check err condition here?
	if (nthreads != 1)
	{
		FATAL("Usage: .\\HW1P2.exe <n threads> <url file>");
		FATAL("Invalid number of threads %d", nthreads);
		return 1;
	}

	IOCPSocket::InitWinSock();

	Crawler crawler;
	//crawler.Crawl((char*)"http://www.tamu.edu:80");
	//crawler.Crawl((char*)"http://cyberjournalist.org.in/medialaw.html");

	std::vector<char*> urls = ReadFileLines(argv[2]);
	for (char* url : urls)
	{
		//printf("%s\n", url);
		crawler.Crawl(url);
		//std::cin.get();
	}


	IOCPSocket::CloseWinSock();

}

