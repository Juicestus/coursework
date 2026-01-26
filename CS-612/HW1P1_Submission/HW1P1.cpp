#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

#include "Util.h"
//#include "UrlParser.h"	general parser wasnt a good idea
#include "UrlParserHttp.h"	// switched to HTTP only parser
#include "IOCPSocket.h"
#include "HttpFormat.h"
#include "HTMLParserBase.h"

std::vector<std::string> test_urls = {
	// These first couple are from page 1 of the hw assignment pdf
	"http://tamu.edu",										// [no path, no port, no query]
	"http://www.tamu.edu:80",								// [no path, port]
	"http://128.194.135.72:80/courses/index.asp#location",	// [IP, port, path, fragment]
	//"http://165.91.22.70/",								// [IP, path]
	"http://s2.irl.cs.tamu.edu/IRL7",						// [64MB HTML file]
	"http://s2.irl.cs.tamu.edu/IRL8",						// [128MB HTML file with zeros]	//noticed this<-
	"http://facebook.com:443?addrbook.php",				// [no path, query, non-HTTP response]
	"http://relay.tamu.edu:465/index.html",				// [path, port, recv error]
	"http://s2.irl.cs.tamu.edu:53",						// [recv timeout]
	"http://s22.irl.cs.tamu.edu:990/view?test=1",			// [path, port, query, no DNS]
	"http://128.194.135.25?viewcart.php/",					// [no path, query, connect timeout]
	// These next few are from page 3 (failed parsing)
	"http://xyz.com:/",
	"http://xyz.com:0",
	"ftp://yahoo.com",
	// These are some testcases I made myself on a localhost so they load faster
	"http://localhost:8000/32k.txt",
	"http://localhost:8000/1m.txt",
	"http://localhost:8000/irl6.html",		// code 404
	"http://localhost:8000/irl7.html",		// code 200 + 1005752 links
	"http://localhost:8000/irl8.html",		// code 200 +  1985349 links
};

int ParseHTML(char* url, HttpResponse resp)
{
	// make base URL a buffer b/c some url processing function in the call
	// stack had a bad memory access at a region right next to address space
	// so I think its writing to the URL buffer itself... this fixed it
	// using the extractstr function from ParsedURL, elevated up to Util
	std::cout << "      + Parsing page... ";
	clock_t parse_start_t = clock();
	char* urlbuf = extractstr(url);	
	HTMLParserBase html_parser;
	int nlinks = -1;
	html_parser.Parse(resp.body, resp.len, urlbuf, strlen(urlbuf), &nlinks);
	printf("done in %d ms with %d links\n", clock() - parse_start_t, nlinks);
	return nlinks;
}


int Main(char* url)
{
	std::cout << "URL: " << url << "\n";

	ParsedURL parsed(url);
	if (!parsed.valid) return 1;

	IOCPSocket socket{};
	if (socket.Connect(parsed.host, parsed.port) != 0)
	{
		return 1;
	} 

	char* req = EncodeHttpRequest(parsed);
	//std::cout << req << "\n";

	if (socket.Send(req))
	{
		return 1;
	}

	if (socket.Recv())
	{
		return 1;
	}
	//std::cout << "Read " << socket.size() << " bytes from socket:\n\n";

	HttpResponse resp = DecodeHttpResponse(socket.data(), socket.size());
	if (resp.status < 0)
	{
		return 1;
	}

	//printf("HttpResponse:\n\tstatus = %d\n\tlength = %d\n\tbody:\n%s\n",
		//resp.status, resp.len, resp.body);
	
	if (resp.Is2XX())
	{
		int nlinks = ParseHTML(url, resp);
	}
	printf("----------------------------------------\n");
	printf("%s\n", resp.header);
	
	return 0;
}

void Test()
{
	// Test for some test urls:
	//Main((char*)"http://tamu.edu");
	//Main((char*)"http://localhost:8000/hello.txt");
	//Main((char*)"http://localhost:8000/32k.txt");
	//Main((char*)"http://localhost:8000/1m.txt");
	//Main((char*)"http://localhost:8000/irl6.html");		// code 404
	//Main((char*)"http://localhost:8000/irl7.html");		// code 200 + 1005752 links
	//Main((char*)"http://localhost:8000/irl8.html");		// code 200 +  1985349 links

	//Main((char*)"http://s2.irl.cs.tamu.edu/IRL7");
	//Main((char*)"http://s2.irl.cs.tamu.edu/IRL8");
	//Main((char*)"http://relay.tamu.edu:465/index.html");
	for (const std::string& test_url : test_urls)
		Main((char*)test_url.c_str());
}

int main(int argc, char** argv)
{
	IOCPSocket::InitWinSock();
	//Test();

	if (argc < 2)
	{
		// there is no URL provided... error?
		FATAL("Usage: .\\HW1P1.exe <url>");
		IOCPSocket::CloseWinSock();
		return 1;
	}
	int ret = Main(argv[1]);
	IOCPSocket::CloseWinSock();
	return ret;
}

/*
Test in the terminal:

.\HW1P1.exe http://tamu.edu
.\HW1P1.exe http://www.tamu.edu:80
.\HW1P1.exe http://128.194.135.72:80/courses/index.asp#location
.\HW1P1.exe http://165.91.22.70/
.\HW1P1.exe http://s2.irl.cs.tamu.edu/IRL7
.\HW1P1.exe http://s2.irl.cs.tamu.edu/IRL8
.\HW1P1.exe http://facebook.com:443?addrbook.php
.\HW1P1.exe http://relay.tamu.edu:465/index.html
.\HW1P1.exe http://s2.irl.cs.tamu.edu:53
.\HW1P1.exe http://s22.irl.cs.tamu.edu:990/view?test=1
.\HW1P1.exe http://128.194.135.25?viewcart.php/
.\HW1P1.exe http://xyz.com:/
.\HW1P1.exe http://xyz.com:0
.\HW1P1.exe ftp://yahoo.com
.\HW1P1.exe http://localhost:8000/32k.txt
.\HW1P1.exe http://localhost:8000/1m.txt
.\HW1P1.exe http://localhost:8000/irl6.html
.\HW1P1.exe http://localhost:8000/irl7.html
.\HW1P1.exe http://localhost:8000/irl8.html

*/
