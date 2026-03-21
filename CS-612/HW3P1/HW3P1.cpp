// HW3P1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "Util.h"
#include "SenderSocket.h"

int main(int argc, char** argv)
{
	// The homework must accept as input seven command-line parameters of the transfer 
	// * destination server(hostname or IP),
	// * a power-of-2 buffer size to be transmitted (in DWORDs),
	// * sender window(in packets), the round-trip propagation delay(in seconds),
	// * the probability of loss in each
	// * direction, and the speed of the bottleneck link(in Mbps).
	if (argc != 8)
	{
		FATAL("Usage: %s <dest> <buffer size power> <window size> <RTT> <fwd loss prob> <rev loss prob> <bottleneck speed>", argv[0]);
	}
	
	char* target_host = argv[1];
	int buffer_size_pwr = atoi(argv[2]);
	int window_size = atoi(argv[3]);


	LinkProps props = { 0 };
	props.RTT = atof(argv[4]);
	props.p_loss[FWD_PATH] = atof(argv[5]);
	props.p_loss[RET_PATH] = atof(argv[6]);
	props.speed = atof(argv[7]) * 1000000;
	props.buffer_size = window_size + MAX_ATTEMPTS;

	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data))
	{
		FATAL("WSAStartup failed with %d\n", WSAGetLastError());
		return 1;
	}

	
	printf("Main: sender W = %d, RTT %g sec, loss %g / %g, link %g Mbps\n",
		window_size, props.RTT, props.p_loss[FWD_PATH], props.p_loss[RET_PATH], props.speed / 1000000);

	printf("Main: initializing DWORD array with 2^%d elements... ", buffer_size_pwr);
	clock_t ts = clock();
	UINT64 buffer_size = 1llu << buffer_size_pwr;
	DWORD* buffer = new DWORD[buffer_size];
	//memset(buffer, 0, buffer_size * sizeof(DWORD));
	for (int i = 0; i < buffer_size; i++)	buffer[i] = i;
	printf("done in % d ms\n", clock() - ts);


	SenderSocket ss;
	int status;

	if ((status = ss.Open(target_host, MAGIC_PORT, window_size, &props)) != STATUS_OK)
	{
		printf("Main: connect failed with status %d\n", status);	// use FATAL?
		WSACleanup();
		delete[] buffer;
		return 1;
	}
	printf("Main: connected to %s in %.3f sec, pkt size %d bytes\n", target_host, (clock() - ts) / 1000.0, MAX_PKT_SIZE);

	ts = clock();
	// Send transfer would go here but not implementing send yet
	double tt = (clock() - ts) / 1000.0 ;

	ts = clock();
	if ((status = ss.Close()) != STATUS_OK)
	{
		printf("Main: disconnect failed with status %d\n", status);
		delete[] buffer;
		WSACleanup();
		return 1;
	}
	printf("Main: transfer finished in %.3f sec\n", tt);


	WSACleanup();
	delete[] buffer;
	return 0;
}

