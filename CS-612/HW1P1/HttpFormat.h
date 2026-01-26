#pragma once

#include "Util.h"
#include "UrlParserHttp.h"

char* EncodeHttpRequest(ParsedURL url)		
{
	char* buf = (char*)malloc(MAX_REQUEST_LEN + 1);
	assert(buf);
	sprintf_s(buf, MAX_REQUEST_LEN,
		"GET %s%s HTTP/1.0\r\n"
		"User-agent: justustamucrawler/1.0\r\n"
		"Host: %s\r\n"
		"Connection: close\r\n"
		"\r\n",
		url.path, url.query, url.host);
	return buf;
}

struct HttpResponse {
	int status;			// HTTP status code or -1 on error from DecodeHttpResponse
	char* header;		// cstr
	char* body;			// buffer
	size_t len;			// body length

	HttpResponse(int status) : status(status), header((char*)""), 
			body((char*)""), len(0) {}

	inline bool Is2XX() { return status >= 200 && status < 300;  }
};

#define	CHECK_CONTENT_LENGTH	false	
#define CONTENT_LENGTH			"Content-Length:"
#define BODY_MARKER				"\r\n\r\n"

HttpResponse DecodeHttpResponse(char* buf, size_t len)
{
	HttpResponse resp(-1);
	std::cout << "        Verifying header... ";
	if (strncmp(buf, "HTTP/", 5) != 0)
	{
		FATAL("failed with non-HTTP header (does not begin with HTTP/)");
		return resp;
	}
	char* end;			// + 8 to bypass HTTP/X.X 
	resp.status = (int)strtol(buf + 8, &end, 10);
	if (!end)
	{
		FATAL("Failed to parse the response code");
		return HttpResponse(-1);
	}
	// This is not required I belive so I am going to define it out
#if CHECK_CONTENT_LENGTH
	// TODO: switch to case insensitive?
	//https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-strstria
	char* clstr = strstr(buf, CONTENT_LENGTH);
	if (!clstr)
	{
		FATAL("Could not find content length 1");
		return HttpResponse(-1);
	}
	// -1 for nullterm +1 for space = 0
	size_t cl = strtol(clstr + sizeof(CONTENT_LENGTH), &end, 10);
	if (!end)
	{
		// I guess this is not strictly mandatory so maybe should avoid?
		// or make it optional for a check or something
		FATAL("Could not parse content length 2");
		return HttpResponse(-1);
	}
#endif
	resp.body = strstr(buf, BODY_MARKER);
	if (!resp.body)
	{
		FATAL("Cound not find the HTML body");
		return HttpResponse(-1);
	}
	resp.header = extractstrn(buf, resp.body - buf);
	resp.body += sizeof(BODY_MARKER) - 1;	// -1 for null term
	printf("status code %d\n", resp.status);
	resp.len = (buf + len) - resp.body;
	return resp;
}

