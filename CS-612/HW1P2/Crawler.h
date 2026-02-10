#pragma once

#include "Util.h"
#include "UrlParserHttp.h"	
#include "IOCPSocket.h"
#include "HttpFormat.h"
#include "HTMLParserBase.h"
#include "FileReader.h"

#include <set>

#ifdef _DEBUG	// only be able to do this define in debug mode
#define BYPASS_UNIQUENESS true 
#endif


class Crawler {

	IOCPSocket socket;
	HTMLParserBase html_parser;

	std::set<std::string> seen_hosts{};
	std::set<int> seen_addrs{};

	int ParseHTML(char* url, HttpResponse resp)
	{
		// make base URL a buffer b/c some url processing function in the call
		// stack had a bad memory access at a region right next to address space
		// so I think its writing to the URL buffer itself... this fixed it
		// using the extractstr function from ParsedURL, elevated up to Util
		std::cout << "      + Parsing page... ";
		clock_t parse_start_t = clock();
		char* urlbuf = extractstr(url);
		int nlinks = -1;
		html_parser.Parse(resp.body, resp.len, urlbuf, strlen(urlbuf), &nlinks);
		printf("done in %d ms with %d links\n", clock() - parse_start_t, nlinks);
		return nlinks;
	}

	bool DuplicateHost(ParsedURL url)
	{
#if BYPASS_UNIQUENESS
		return false;
#else
		std::cout << "        Checking host uniqueness... ";
		std::string host(url.host);
		if (seen_hosts.contains(host))
		{
			std::cout << "failed\n";
			return true;
		}
		seen_hosts.insert(host);
		std::cout << "passed\n";
		return false;
#endif
	}

	bool DuplicateAddr(int ip)
	{
#if BYPASS_UNIQUENESS 
		return false;
#else
		std::cout << "        Checking IP uniqueness... ";
		if (seen_addrs.contains(ip))
		{
			std::cout << "failed\n";
			return true;
		}
		seen_addrs.insert(ip);
		std::cout << "passed\n";
		return false;
#endif
	}

public:

	// 2MB = 2*2^20 = 2*(2<<19) = 2<<20
	Crawler() : socket(10*1000, 2 << 20) { }

	int Crawl(char* url)
	{
		std::cout << "URL: " << url << "\n";

		ParsedURL parsed(url);
		if (!parsed.valid) return 1;

		parsed.Print();
	
		if (DuplicateHost(parsed))
		{
			return 1;
		}
	
		if (socket.DNS(parsed.host, parsed.port))
		{
			return 1;
		}
		
		if (DuplicateAddr(socket.addr()))
		{
			return 1;
		}

		/*
		* ROBOT REQUEST
		*/

		std::cout << "        Connecting on robots... ";

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

		/*
		* PAGE REQUEST
		*/

		std::cout << "      * Connecting on page... ";

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

};
