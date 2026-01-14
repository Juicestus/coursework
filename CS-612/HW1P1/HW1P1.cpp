#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

#include "Util.h"
#include "ParsedURL.h"
#include "Socket.h"

std::vector<std::string> test_urls = {
	// These first couple are from page 1 of the hw assignment pdf
	"http://tamu.edu",										// [no path, no port, no query]
	"http://www.tamu.edu:80",								// [no path, port]
	"http://128.194.135.72:80/courses/index.asp#location",	// [IP, port, path, fragment]
	//"http://165.91.22.70/",								// [IP, path]
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

int Main(char* url)
{
	std::cout << "URL: " << url << "\n";
	ParsedURL parsed(url);
	//std::cout << parsed.Str() << "\n";
	if (!parsed.valid) return 1;
	if (parsed.scheme != "http")
	{
		FATAL("Invalid scheme");
		return 1;
	}
	if (!parsed.HasPort()) parsed.port = 80;	// default for HTTP
	
	Socket socket{};
	if (socket.Connect(parsed.host, parsed.port) != 0)
	{
		std::cout << "-> Connection Failed\n";
		return 1;
	} 
	std::cout << "-> Connection Succeeded\n";

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
	for (const std::string& test_url : test_urls)
	{
		Main((char*)test_url.c_str());
	}



}
