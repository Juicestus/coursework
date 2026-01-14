#pragma once

#include <cstdlib>

// https://learn.microsoft.com/en-us/windows/win32/winsock/creating-a-basic-winsock-application
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#include "Util.h"

#define INITIAL_BUF_SIZE 4096

class Socket {
// This class was based off the code sample on page 3 and 4 of the hw pdf
// and this winsock reference from MSDN:
// https://learn.microsoft.com/en-us/windows/win32/winsock/complete-client-code
	SOCKET	sock;
	char*	buf;
	size_t	cap;
	int		pos;

public:
	Socket() : sock(INVALID_SOCKET), cap(INITIAL_BUF_SIZE), pos(0)
	{
		// create this buffer once, then possibly reuse for multiple connections in Part 3 
		// use queue, min/max heap to give back blocks and get new blocks?
		buf = (char*)malloc(cap);
	}

	int Connect(const std::string& host, uint16_t port);
	int Read(void);
	inline int Close(void)
	{
		free(buf);
		return closesocket(sock);
	}

	static int InitWinSock();
	static int CleanupWinSock();
};

int Socket::Connect(const std::string& host, uint16_t port)
{
	// Much of this is based off the MSDN sample code
	// https://learn.microsoft.com/en-us/windows/win32/winsock/complete-client-code
	int ret = 0;
	struct addrinfo* ainfo = nullptr, hints = { 0 };	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	std::string portstr = std::to_string(port);
	if ((ret = getaddrinfo(host.c_str(), portstr.c_str(), &hints, &ainfo)) != 0)
	{
		FATAL("Failed to get addr info for %s:%d with %d (%d)", host.c_str(), port, ret, WSAGetLastError());
		WSACleanup();
		return 1;
	}
	
	int connecterr;
	for (; ainfo; ainfo = ainfo->ai_next)
	{
		sock = socket(ainfo->ai_family, ainfo->ai_socktype, ainfo->ai_protocol);
		if (sock == INVALID_SOCKET)
		{
			FATAL("Failed to create socket with %d", WSAGetLastError());
			return 1;
		}
		if ((ret = connect(sock, ainfo->ai_addr, ainfo->ai_addrlen)) != 0)
		{
			//FATAL("Could not connect socket because %d", WSAGetLastError());
			connecterr = WSAGetLastError();		// if this is the last run and still fails
			closesocket(sock);					// the error needs to be preserved...
			sock = INVALID_SOCKET;
			continue;
		}
		break;	// one of them worked
	}

	freeaddrinfo(ainfo);
	if (sock == INVALID_SOCKET)	// could not find a good one
	{
		FATAL("Could not connect to server, error %d", connecterr);	// ...for this message
		return 1;
	}
	printf("Socket created for %s:%d\n", host.c_str(), port);
	return ret;
}


int Socket::Read(void)
{
	while (true)
	{
		//if ((ret = select(0, &fd, )))
	}

}



int Socket::InitWinSock()
{
	// https://learn.microsoft.com/en-us/windows/win32/winsock/initializing-winsock
	int ret;
	WSADATA data;
	if ((ret = WSAStartup(MAKEWORD(2, 2), &data)) != 0)
	{
		FATAL("WSAStartup failed: %d", ret);
		return ret;
	}
	return 0;
}
int Socket::CleanupWinSock()
{
	return WSACleanup();
}

