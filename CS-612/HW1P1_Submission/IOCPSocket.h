#pragma once

#include <cstdlib>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Util.h"

#define INITIAL_BUF_SIZE	4096
#define THRESHOLD			256

class IOCPSocket {
	SOCKET	sock;
	char*	buf;
	size_t	cap;
	size_t	pos;
	timeval timeout;
	HANDLE	cp;			// completion port

public:
	IOCPSocket() : sock(INVALID_SOCKET), cap(INITIAL_BUF_SIZE), pos(0)
	{
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;

		cp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

		// create this buffer once, then possibly reuse for multiple connections in Part 3 
		// use queue, min/max heap to give back blocks and get new blocks?
		buf = (char*)malloc(cap);
		assert(buf);
		memset(buf, 0, cap);
	}
	~IOCPSocket()
	{
		free(buf);
	}

	int Connect(char* host, uint16_t port);
	
	int Send(char* buf);
	int Recv();
	//int TestRecvIOCP();

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
	
	// using the same getter names from the STL like vector
	inline char*	data()	{	return buf;	}
	inline size_t	size()	{	return pos;	}
};

int IOCPSocket::Connect(char* host, uint16_t port)
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

	// Some of this is referenced from 463-sample winsock.cpp
	struct hostent*		remote;
	struct sockaddr_in	server;
	uint32_t ip;

	std::cout << "        Doing DNS... ";
	clock_t dns_start_t = clock();

	if ((ip = inet_addr(host)) != INADDR_NONE)
	{
		server.sin_addr.S_un.S_addr = ip;
		// still need to print this message even if its already ipv4
		printf(" done in %d ms, found %s\n", clock() - dns_start_t, inet_ntoa(server.sin_addr));
	}
	else
	{
		if ((remote = gethostbyname(host)) == nullptr)
		{
			FATAL("failed with %d", WSAGetLastError());
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

			printf(" done in %d ms, found %s\n", clock() - dns_start_t, inet_ntoa(server.sin_addr));
		}
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	
	std::cout << "      * Connecting on page... ";
	clock_t conn_start_t = clock();
	if (connect(sock, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		//FATAL("Failed to connect to %s:%d (%s:%d), connection error %d", host, port, 
				//inet_ntoa(server.sin_addr), port, WSAGetLastError());
		FATAL("failed with %d", WSAGetLastError());
		return 1;
	}
	printf("done in %d ms\n", clock() - conn_start_t);
	//printf("Successfully connect to %s:%d (%s:%d)\n", host, port, inet_ntoa(server.sin_addr), port);

	// having to use this function for both creating the handle and attaching
	// to the port was very confusing
	if (CreateIoCompletionPort((HANDLE)sock, cp, (ULONG_PTR)sock, 1) == nullptr)	// n async threads = ?
	{
		FATAL("Failed to attach IO completion port, with error %d", WSAGetLastError());
		return 1;
	}
	return 0;
}

int IOCPSocket::Send(char* req)
{
	if (send(sock, req, strlen(req), 0) == SOCKET_ERROR)
	{
		FATAL("Failed to send request with error %d", WSAGetLastError());
		return 1;
	}
	return 0;
}

//int IOCPSocket::TestRecvIOCP()	
//{
//	// use this function screw around with IOCPto learn how IOCP
//	//OVERLAPPED overlapped = {0};
//	OVERLAPPED* overlapped = new OVERLAPPED{};
//
//	for (int i = 0; i < 10; i++)
//	{
//		WSABUF _buf;
//		_buf.buf = new char[128];
//		_buf.len = 128;
//
//		ULONG recvd = 0, flags = 0;
//		WSARecv(sock, &_buf, 1, &recvd, &flags, overlapped, NULL);
//		std::cout << "recvd = " << recvd << "\n";
//		
//		// https://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-getqueuedcompletionstatus
//		ULONG trans = 0;
//		ULONG_PTR comp_key = 0;
//		GetQueuedCompletionStatus(cp, &trans, &comp_key, &overlapped, 10);
//		std::cout << comp_key << " " << trans << "\n";
//
//		if (trans == 0) break;
//		
//		for (int j = 0; j < _buf.len; j++)
//			std::cout << (char)_buf.buf[j] << "";
//		std::cout << "\n";
//	}
//	return 0;
//}


int IOCPSocket::Recv()	
{
	OVERLAPPED* overlapped = new OVERLAPPED{};	// TODO: look into this more?
	WSABUF cpbuf;
	ULONG recvd = 0, flags = 0, trans = 0;
	ULONG_PTR comp_key = 0;
	int err;

	std::cout << "        Loading... ";
	clock_t recv_start_t = clock();
	
	while (true)
	{
		cpbuf.buf = buf + pos;	// the position to read from
		cpbuf.len = cap - pos;	// how many bytes we have left in the buffer

		//std::cout << "Recv:\n" << "\tpos = " << pos << "\n" << "\tcap = " << cap << "\n"
			//<< "\tlen = " << cpbuf.len << "\n";

		if ((err = WSARecv(sock, &cpbuf, 1, &recvd, &flags, overlapped, NULL)) != 0)
		{
			if ((err = WSAGetLastError()) != WSA_IO_PENDING /*997 is ok*/)
			{
				//FATAL("Failed to recv into buffer with error %d", err);
				FATAL("failed with %d on recv", err);
				return 1;
			}
		}
		//std::cout << "\trecvd = " << recvd << "\n";
	
		if (!(err = GetQueuedCompletionStatus(cp, &trans, &comp_key, &overlapped, 10 * 1000)))
		{
			//https://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-getqueuedcompletionstatus?devlangs=cpp&f1url=%3FappId%3DDev17IDEF1%26l%3DEN-US%26k%3Dk(IOAPISET%2FGetQueuedCompletionStatus)%3Bk(GetQueuedCompletionStatus)%3Bk(DevLang-C%2B%2B)%3Bk(TargetOS-Windows)%26rd%3Dtrue
			//FATAL("Checking the rx completion queue status failed with error %d", GetLastError());
			if ((err = GetLastError()) == 258)
				FATAL("failed with timeout");
			else
				//FATAL("failed with %d on GetQueuedCompletionStatus", GetLastError());
				FATAL("failed with %d on recv", GetLastError());
			return 1;
		}

		//std::cout << "\tcqkey = " << comp_key << "\n" << "\ttrans = " << trans << "\n";
		pos += trans;
		//pos += recvd;

		if (trans == 0 && recvd == 0) break;

		if (cap - THRESHOLD < pos)
		{
			//printf("Resize: pos %d, cap %d -> %d\n", pos, cap, cap*2);
			cap = cap * 2;
			buf = (char*)realloc(buf, cap);	//TODO: check warning?
			assert(buf);
			memset(buf + pos, 0, cap - pos);
		}
	}

	printf("done in %d ms with %lld bytes\n", clock() - recv_start_t, pos);
	return 0;	// no err, use .data() and .size() to access the buffer
}

int IOCPSocket::InitWinSock()
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