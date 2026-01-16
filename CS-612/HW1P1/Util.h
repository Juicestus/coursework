#pragma once

#include <iostream>

#define FATAL(FMT, ...)	fprintf(stderr, FMT "\n", __VA_ARGS__)

#define BOOLTF(BOOL)	( (BOOL) ? "TRUE" : "FALSE" )		// bool -> true/false string
#define BOOLYN(BOOL)	( (BOOL) ? "YES" : "NO" )			// bool -> yes/no string 
