#pragma once

#include <cstdlib>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Util.h"

#define INITIAL_BUF_SIZE	4096
#define THRESHOLD			256

class Socket {
	SOCKET	sock;
	char*	buf;
	size_t	cap;
	size_t	pos;
	timeval timeout;

public:
	Socket() : sock(INVALID_SOCKET), cap(INITIAL_BUF_SIZE), pos(0)
	{
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;

		// create this buffer once, then possibly reuse for multiple connections in Part 3 
		// use queue, min/max heap to give back blocks and get new blocks?
		buf = (char*)malloc(cap);
	}

	int Connect(char* host, uint16_t port);
	
	int Send(char*);
	int Read(void);

	inline int Close(void)
	{
		free(buf);
		return closesocket(sock);
	}

	static int InitWinSock();

	inline static int CloseWinSock()
	{
		return WSACleanup();
	}
};

int Socket::Connect(char* host, uint16_t port)
{
	int ret = 0;
	struct addrinfo* ainfo = nullptr, hints = { 0 };	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		FATAL("Failed to create socket with %d", WSAGetLastError());
		return 1;
	}

	// based off of 463-sample winsock.cpp
	struct hostent*		remote;
	struct sockaddr_in	server;
	uint32_t ip;

	if ((ip = inet_addr(host)) != INADDR_NONE)
	{
		server.sin_addr.S_un.S_addr = ip;
	}
	else
	{
		if ((remote = gethostbyname(host)) == nullptr)
		{
			FATAL("Invalid hostname: neither FQDN nor IP addr");
			return 1;
		}
		else
		{
			// I HATE that msft (or posix standard) made h_addr 
			// a DEFINE for h_add_list[0]
			// ....that is so confusing and makes things harder to debug
			// I couldnt figure out why it wasnt connecting... 
			// ... I was using h_addr_list b/c I hit tab on the autocomplete
			// They shouldve made a function like macro like
			// #define H_ADDR(SPTR) SPTR->h_addr_list[0]
			memcpy(&server.sin_addr, remote->h_addr, remote->h_length);
		}
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (connect(sock, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		FATAL("Failed to connect to %s:%d (%s:%d), connection error %d", host, port, 
				inet_ntoa(server.sin_addr), port, WSAGetLastError());
		return 1;
	}
	printf("Successfully connect to %s:%d (%s:%d)\n", host, port,
		inet_ntoa(server.sin_addr), port);
	return 0;
}

int Socket::Send(char* req)
{
	if (send(sock, req, strlen(req), 0) == SOCKET_ERROR)
	{
		FATAL("Failed to send request with error %d", WSAGetLastError());
		return 1;
	}
	return 0;
}

int Socket::Read(void)
{
	int ret;
	size_t nbytes;

	// This structure was based off the code sample on page 3 and 4 of the hw pdf
	while (true)
	{
		fd_set readfdset;
		// FD_ZERO(*set) - Initializes set to the empty set. A set should always be cleared before using.
		FD_ZERO(&readfdset);
		// FD_SET(s, *set) - Adds socket s to set.
		FD_SET(sock, &readfdset);
		
		if ((ret = select(0, &readfdset, nullptr, nullptr, &timeout)) > 0)
		{
			if ((nbytes = recv(sock, buf + pos, cap - pos, 0)) < 0)
			{
				FATAL("Read error %d", WSAGetLastError());
				return 1;
			}
			pos += nbytes;
		
			if (cap - pos <= THRESHOLD)		// too close to end of buffer
			{
				cap *= 2;
				buf = (char*)realloc(buf, cap);
			}
		}
		else
		{
			FATAL("Read error %d", WSAGetLastError());
			return 1;
		}
	}
	return 0;
}


int Socket::InitWinSock()
{
	int ret;
	WSADATA data;
	if ((ret = WSAStartup(MAKEWORD(2, 2), &data)) != 0)
	{
		FATAL("WSAStartup failed: %d", ret);
		return ret;
	}
	return 0;
}