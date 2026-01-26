#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "Util.h"

#include "HTMLParserBase.h"	// limit for defines


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

	inline void Print()
	{/*
		return
			"Scheme:\t" + scheme + "\nHost:\t" + host + "\nPort:\t"
			+ std::to_string(port) + "\nPath:\t" + path
			+ "\nQuery:\t" + query + "\nValid:\t" + BOOLYN(valid) + "\n";*/
		//printf("Host:\t%s\nPort:\t%d\nPath\t%s\nQuery:\t%s\nValid:\t%s\n",
			//host, port, path, query, BOOLYN(valid));
	}
};


ParsedURL::ParsedURL(char* _raw) 
	// Correctly initialize defaults
	: port(80), valid(false), path((char*)"/"), host((char*)""), query((char*)"") 
{
	if (strlen(_raw) > MAX_URL_LEN)
	{
		FATAL("failed because URL is too long");
		return;
	}
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

	std::cout << "        Parsing URL... ";
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
		//query = extractstr(cptr + 1);	 // no ? sign
		query = extractstr(cptr);	 // including the ? sign so it formats correctly
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
	if (strlen(host) > MAX_HOST_LEN)
	{
		FATAL("failed because host is too long");
		return;
	}
	// done
	printf("host %s, port %d, request %s%s\n", host, port, path, query);
	valid = true;
}
