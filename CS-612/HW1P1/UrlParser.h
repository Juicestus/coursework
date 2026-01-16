#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Util.h"

// Get the first non null char pointer from the args. If all null, return null
inline char* FirstCharPtr(char* a, char* b)
{
	if (!a) return b;
	if (!b) return a;
	return a < b ? a : b;
}
inline char* FirstCharPtr(char* a, char* b, char* c)
{
	return FirstCharPtr(FirstCharPtr(a, b), c);
}
inline char* FirstCharPtr(char* a, char* b, char* c, char* d)
{
	return FirstCharPtr(FirstCharPtr(FirstCharPtr(a, b), c), d);
}

/*
 * This was my first attempt at the URL parser. I made a general URL
 * parser which I belive works correctly. However it is more complicated
 * than is required for this lab, so I wrote a new version in UrlParserHttp.h.
 */
struct ParsedURL {
	// scheme://host[:port][/path][?query][#fragment] 
	std::string		scheme;
	std::string		host;
	int16_t			port;			// if port is 0 but valid is true, than there was none provided
	std::string		path;			// split into some array?
	std::string		query;
	std::string		fragment;
	bool			valid;

	ParsedURL() : port(0), valid(false) {}
	ParsedURL(char* raw);

	inline std::string Str()
	{
		return
			"Scheme:\t" + scheme + "\nHost:\t" + host + "\nPort:\t"
			+ std::to_string(port) + "\nPath:\t" + path
			+ "\nQuery:\t" + query + "\nFrag:\t" + fragment
			+ "\nValid:\t" + BOOLYN(valid) 
			//+ "\nPortOK:\t" + BOOLYN(HasPort()) 
			+ "\n";
	}
	inline bool HasPort() { return port > 0 && valid; }
};

// TODO: do error messages have to be exact
ParsedURL::ParsedURL(char* raw) : port(0), valid(false)
{
	// TODO: maybe make all the char* -> const char* ???
	size_t len = strlen(raw);
	char* end = raw + len;

	char* scheme_colon = strstr(raw, "://");
	if (!scheme_colon)
	{
		FATAL("Could not find ://");
		return;
	}

	// at this point [raw, scheme_colon) is the scheme, [scheme_colon, scheme_colon+3) is ://
	scheme = std::string(raw, scheme_colon - raw);
	char* host_start = scheme_colon + 3;

	char* port_colon = strchr(host_start, ':');
	char* path_slash = strchr(host_start, '/');		// there cannot be an earlier/ 
	char* query_mark = strchr(host_start, '?');		// I think there cannot be an earlier ?
	char* frag_hash = strchr(host_start, '#');		// I think there cannot be an earlier #

	char* end_host = FirstCharPtr(port_colon, path_slash, query_mark, frag_hash);		// the first of the above is what terminates the host
	if (!end_host)	end_host = end;
	host = std::string(host_start, end_host - host_start);
	if (host.size() <= 0)
	{
		FATAL("Invalid hostname");
		return;
	}

	// TODO:	I think it will currently pass if there are extra, non-numeric characters
	//			between the port number and first(/, ?, #, \0).
	// FIX:		end_port = first(/, ?, #, \0), enforce [port_colon, end_port) is all numeric

	if (port_colon)			// there is a port
	{
		port = atoi(port_colon + 1);
		if (port > UINT16_MAX || port <= 0)
		{
			FATAL("Invalid port");
			return;
		}
	}

	if (path_slash && path_slash == end_host)
	{
		char* end_path = FirstCharPtr(query_mark, frag_hash);
		if (!end_path) end_path = end;
		path = std::string(path_slash, end_path - path_slash);
	}
	else path = "/";

	if (query_mark)
	{
		char* end_query = frag_hash;		// frag hash is the only one left
		if (!end_query) end_query = end;	// if we didnt use another var it would screw up the next if that checks for frag_hash
		query = std::string(query_mark+1, end_query - query_mark);
	}
	if (frag_hash)
	{
		fragment = std::string(frag_hash+1, end - frag_hash);	// only the end of raw can terminate
	}

	valid = true;
}

