#pragma once

#include "Util.h"
#include "UrlParserHttp.h"	
#include "IOCPSocket.h"
#include "IOCPSocket2.h"
#include "HttpFormat.h"
#include "HTMLParserBase.h"

class Crawler;

class Worker {

	IOCPSocket socket;
	//IOCPSocket2 socket;
	HTMLParserBase html_parser;

	int id;
	Crawler* crawler;

	int Crawl(char* url);		// original Crawler::Crawl from part 2

	Worker(int id, Crawler* crawler) : id(id), crawler(crawler), socket(10 * 1000, 2 << 20) {}
	void Run();

public:

	static DWORD WINAPI Start(LPVOID ptr);
};


