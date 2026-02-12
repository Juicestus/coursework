#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include "Windows.h"

#define FATAL(FMT, ...)	fprintf(stderr, FMT "\n", __VA_ARGS__)

#define BOOLTF(BOOL)	( (BOOL) ? "TRUE" : "FALSE" )		// bool -> true/false string
#define BOOLYN(BOOL)	( (BOOL) ? "YES" : "NO" )			// bool -> yes/no string 

__forceinline char* extractstrn(char* src, int n)
{
	char* dst = (char*)malloc(n + 1);
	//if (!dst) return nullptr;
	assert(dst);
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

std::vector<char*> ReadFileLines(const char* path);

