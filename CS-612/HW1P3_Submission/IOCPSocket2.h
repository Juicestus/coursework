#pragma once
#if 1

#include <cstdlib>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Util.h"

#define INITIAL_BUF_SIZE	(32*4096)
#define THRESHOLD			(4096)

#define MEMSET_BUFFERS true

class IOCPSocket2 {
	SOCKET	sock;
	char* buf;
	size_t	pos;
	size_t	cap;
	size_t	max_cap;
	int		timeout;
	struct sockaddr_in server;

	OVERLAPPED ov{};
	WSABUF cpbuf{};

	static HANDLE cp;

public:
	IOCPSocket2(int timeout, size_t max_cap)
		: timeout(timeout), max_cap(max_cap), sock(INVALID_SOCKET), cap(INITIAL_BUF_SIZE), pos(0)
	{
		// create this buffer once, then possibly reuse for multiple connections in Part 3 
		// use queue, min/max heap to give back blocks and get new blocks?
		buf = (char*)malloc(cap);
		assert(buf);
#if MEMSET_BUFFERS
		memset(buf, 0, cap);
#endif
	}
	~IOCPSocket2()
	{
		free(buf);
		closesocket(sock);
	}

	int DNS(char* host, uint16_t port);
	int Connect();
	
	int Send(char* buf);

	int Recv();
	int StartRecv();
	int ProcessRecv();

	inline void Reset()
	{
		pos = 0;
		closesocket(sock);
		if (cap > INITIAL_BUF_SIZE)
		{
			cap = INITIAL_BUF_SIZE;
			free(buf);
			buf = (char*)malloc(cap);
			assert(buf);
#if MEMSET_BUFFERS
			memset(buf, 0, cap);
#endif
		}
	}

	static int InitWinSock();

	inline static int CloseWinSock()
	{
		return WSACleanup();
	}

	// using the same getter names from the STL like vector
	inline char* data() { return buf; }
	inline size_t	size() { return pos; }

	inline int addr() { return server.sin_addr.S_un.S_addr; }
};

#endif
