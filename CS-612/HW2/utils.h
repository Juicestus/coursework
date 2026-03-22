/*
 * HW2 - DNS Client
 *
 * Justus Languell
 */
#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include "Windows.h"

#define FATAL(FMT, ...)	fprintf(stderr, FMT "\n", __VA_ARGS__)

void PrintBytes(byte* buf, int len)
{
	for (int i = 0; i < len; i++)
		printf("%4d", i);
	printf("\n");
	for (int i = 0; i < len; i++)
		printf("%4c", buf[i]);
	printf("\n");
	for (int i = 0; i < len; i++)
		printf("%4d", buf[i]);
	printf("\n");
	for (int i = 0; i < len; i++)
		printf("%4x", buf[i]);
	printf("\n");
}

