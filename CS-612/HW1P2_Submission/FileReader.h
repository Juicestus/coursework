#pragma once

#include <vector>
#include "Windows.h"
#include "Util.h"

std::vector<char*> ReadFileLines(const char* path)
{
	std::vector<char*> ret;
	
	// in HTMLParserTest example CreateFile -> CreateFileA, in this project -> CreateFileW by default 
	// because UNICODE defined, so im going to just try with CreateFileA directly
	HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		FATAL("CreateFile failed with %d", GetLastError());
		return ret;
	}

	LARGE_INTEGER li;
	if (!GetFileSizeEx(file, &li))
	{
		FATAL("CreateFileSizeEx failed with %d", GetLastError());
		CloseHandle(file);
		return ret;
	}
	DWORD fsize = (DWORD)li.QuadPart, bread = 0;
	
	printf("Opened %s with size %d\n", path, fsize);

	char* fbuf = (char*)malloc(fsize+1);
	fbuf[fsize] = '\0';

	if (!ReadFile(file, fbuf, fsize, &bread, NULL) || bread != fsize)
	{
		FATAL("ReadFile failed with %d", GetLastError());
		CloseHandle(file);
		return ret;
	}

	CloseHandle(file);
	
	for (char* k = fbuf, *n; ; )
	{

		if ((n = strstr(k, "\r\n")) == nullptr) 
		{
			//ret.push_back(extractstr(k));
			if (strlen(k) > 0)
			{
				ret.push_back(k);
			}
			break;
		}
		else {
			//ret.push_back(extractstrn(k, n-k));
			*n = 0;
			ret.push_back(k);
		}
		k = n + 2;
	}

	//free(fbuf);

	return ret;
}
