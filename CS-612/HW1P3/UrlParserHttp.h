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

