#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

#define HTTP_ONLY_URL_PARSER

#include "Util.h"
#ifdef HTTP_ONLY_URL_PARSER
	#include "UrlParserHttp.h"
#else
	#include "UrlParser.h"
#endif
#include "Socket.h"

std::vector<std::string> test_urls = {
	// These first couple are from page 1 of the hw assignment pdf
	"http://tamu.edu",										// [no path, no port, no query]
	"http://www.tamu.edu:80",								// [no path, port]
	"http://128.194.135.72:80/courses/index.asp#location",	// [IP, port, path, fragment]
	"http://165.91.22.70/",								// [IP, path]
	"http://s2.irl.cs.tamu.edu/IRL7",						// [64MB HTML file]
	"http://s2.irl.cs.tamu.edu/IRL8",						// [128MB HTML file with zeros]
	"http://facebook.com:443?addrbook.php",				// [no path, query, non-HTTP response]
	"http://relay.tamu.edu:465/index.html",				// [path, port, recv error]
	"http://s2.irl.cs.tamu.edu:53",						// [recv timeout]
	"http://s22.irl.cs.tamu.edu:990/view?test=1",			// [path, port, query, no DNS]
	"http://128.194.135.25?viewcart.php/",					// [no path, query, connect timeout]
	// These next few are from page 3 (failed parsing)
	"http://xyz.com:/",
	"http://xyz.com:0",
	"ftp://yahoo.com",
};

#define HTTP_REQ_SIZE	4096	

char* CreateHttpRequest(ParsedURL url)
{
	// TODO: make this realloc and check for nullptrs
	char* buf = (char*)malloc(HTTP_REQ_SIZE + 1);
	sprintf_s(buf, HTTP_REQ_SIZE,
		"GET %s%s HTTP/1.0\r\n"
		"Host: %s\r\n"
		"Connection: close\r\n"
		"\r\n",
		url.path, url.query, url.host);
	return buf;
}

int Main(char* url)
{
	std::cout << "URL: " << url << "\n";
#ifdef HTTP_ONLY_URL_PARSER
	ParsedURL parsed(url);
	if (!parsed.valid) return 1;
#else	
	// General parser I wrote first
	ParsedURL parsed(url);
	//std::cout << parsed.Str() << "\n";
	if (!parsed.valid) return 1;
	if (parsed.scheme != "http")
	{
		FATAL("Invalid scheme");
		return 1;
	}
	if (!parsed.HasPort()) parsed.port = 80;	// default for HTTP
#endif
	//std::cout << parsed.Str();

	Socket socket{};
	if (socket.Connect(parsed.host, parsed.port) != 0)
	{
		//std::cout << "-> Connection Failed\n";
		return 1;
	} 
	//std::cout << "-> Connection Succeeded\n";

	char* req = CreateHttpRequest(parsed);
	std::cout << req << "\n";

	std::cout << socket.Send(req);
	std::cout << "\n";

	socket.Read();	// read into internal buffer


	return 0;
}


int main(int argc, char** argv)
{
	Socket::InitWinSock();

	if (argc < 2)
	{
		// there is no URL provided... error?
	}

	// Test for some test urls:
	
	//Main((char*)"http://tamu.edu");
	Main((char*)"http://localhost:8000/hello.txt");
	for (const std::string& test_url : test_urls)
	{
		//Main((char*)test_url.c_str());
	}

	Socket::CloseWinSock();


}
