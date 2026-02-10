#pragma once

#include "Util.h"
#include "UrlParserHttp.h"

char* EncodeHttpRequest(ParsedURL& url);

char* EncodeHttpRobotsRequest(ParsedURL& url);

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

HttpResponse DecodeHttpResponse(char* buf, size_t len);
