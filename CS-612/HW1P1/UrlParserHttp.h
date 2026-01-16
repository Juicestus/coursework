#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "Util.h"

__forceinline char* extractstrn(char* src, int n)
{
	char* dst = (char*)malloc(n + 1);
	if (!dst) return nullptr;
	dst[n] = 0;
	// I hate the microsoft _s functions 
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strncpy-s-strncpy-s-l-wcsncpy-s-wcsncpy-s-l-mbsncpy-s-mbsncpy-s-l?view=msvc-170&devlangs=cpp&f1url=%3FappId%3DDev17IDEF1%26l%3DEN-US%26k%3Dk(STRING%2Fstrncpy_s)%3Bk(strncpy_s)%3Bk(DevLang-C%2B%2B)%3Bk(TargetOS-Windows)%26rd%3Dtrue#remarks
	strncpy_s(dst, n+1, src, n);
	return dst;
}
__forceinline char* extractstr(char* src)
{
	return extractstrn(src, strlen(src));
}

/* 
 * This is a simpler version of ParsedURL from UrlParser 
 * that only handles HTTP urls and only provides the info
 * we need for our purposes.
 */
struct ParsedURL {
	// scheme://host[:port][/path][?query][#fragment] 
	char*		host;
	int16_t		port;			
	char*		path;			
	char*		query;
	bool		valid;

	ParsedURL() : port(80), valid(false), path((char*)"/"), 
			host((char*)""),query((char*)"") {}
	ParsedURL(char* raw);

	inline std::string Str()
	{/*
		return
			"Scheme:\t" + scheme + "\nHost:\t" + host + "\nPort:\t"
			+ std::to_string(port) + "\nPath:\t" + path
			+ "\nQuery:\t" + query + "\nValid:\t" + BOOLYN(valid) + "\n";*/
		char buffer[4096];	// this is a debug only function this is fine
		int k = sprintf_s(buffer, "Host:\t%s\nPort:\t%d\nPath\t%s\nQuery:\t%s\nValid:\t%s\n",
			host, port, path, query, BOOLYN(valid));
		buffer[k + 1] = 0;
		return std::string(buffer);
	}
};


ParsedURL::ParsedURL(char* _raw) 
	// Correctly initialize defaults
	: port(80), valid(false), path((char*)"/"), host((char*)""), query((char*)"") 
{
	char* raw = extractstr(_raw);	// kind of a hack, allows us to modify raw in place
									// even if it is a string literal
	// Notes from class on Thu:
	//	1. scheme == http, case INsensitive
	//	2. throw away fragment: *strchr('#') = 0
	//	3. suggested order:
	//		a. find # using strchr and truncate
	//		b. find ?, extract from ? to end, truncate
	//		c. find /, extract from / to end, truncate
	//		d. find :, extract from : to end, truncate
	//	4. host should be what is left

	std::cout << "Parsing URL... ";
	// (1) ... I searched for this function forever
	if (_strnicmp(raw, "http://", 7))
	{
		FATAL("failed with invalid scheme");
		return;
	}
	raw += 7;
	// (2/3a)
	char* cptr;
	if ((cptr = strchr(raw, '#')))
		*cptr = 0;
	// (3b)
	if ((cptr = strchr(raw, '?')))
	{
		query = extractstr(cptr + 1);	 // no ? sign
		*cptr = 0;
	}
	// (3c)
	if ((cptr = strchr(raw, '/')))
	{
		path = extractstr(cptr);
		*cptr = 0;
	}
	// (4c)
	if ((cptr = strchr(raw, ':')))
	{
		char* end;
		port = (int)strtol(cptr+1, &end, 10);
		// we check end to see if strtol failed and to make sure
		// that there are no random chars after the number 
		if (*end || port <= 0 || port > UINT16_MAX)
		{
			FATAL("failed with invalid port");
			return;
		}
		*cptr = 0;
	}
	// (5)
	host = extractstr(raw);
	// done
	std::cout << "\n";
	valid = true;
}
