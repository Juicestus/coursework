#include "pch.h"
#include "SenderSocket.h"


int SenderSocket::SendPacket(byte* buf, int len)
{
	if (sendto(sock, (char*)buf, len, 0, (struct sockaddr*)&remote, sizeof(remote)) == SOCKET_ERROR)
	{
		printf("[%.3f]\t--> failed sendto with %d\n", TS(), WSAGetLastError());
		return FAILED_SEND;
	}
	return STATUS_OK;
}

int SenderSocket::WaitOnAck(byte* buf, int len)
{
	// TODO: encapsulate send and recive logic into seperate logic into replicable functions
	//		or like send<-> wait for ack or something
	// ^ TODO completed
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(sock, &fd);
	timeval tv;
	tv.tv_sec = (int)rto;
	tv.tv_usec = (int)((rto - tv.tv_sec) * 1000000);
	int avail, resp_size;
	if ((avail = select(0, &fd, NULL, NULL, &tv)) > 0)
	{
		struct sockaddr_in reply;
		int reply_addr_len = sizeof(reply);
		if ((resp_size = recvfrom(sock, (char*)buf, len, 0, (struct sockaddr*)&reply, &reply_addr_len)) == SOCKET_ERROR)
		{
			printf("[%.3f]\t<-- failed recvfrom with %d\n", TS(), WSAGetLastError());
			return FAILED_RECV;
		}
	/*	rto = 3 * ((double)(clock() - sent_at) / 1000.0);
		printf("[%.3f]\t<-- SYN-ACK %d window %d; setting initial RTO to %.3f\n", TS(), resp.ack_seq, resp.rcv_wnd, rto);*/
		return STATUS_OK;
	}
	else if (avail == 0) return TIMEOUT;
	else return FAILED_RECV;
}



int SenderSocket::Open(char* host, ushort port, int window_size, LinkProps* props)
{
	if (conn) return ALREADY_CONNECTED;

	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = 0;

	remote.sin_family = AF_INET;
	remote.sin_port = htons(port);
	
	// pulled from HW3
	DWORD ip;
	struct hostent* rhe;

	if ((ip = inet_addr(host)) != INADDR_NONE)
	{
		remote.sin_addr.S_un.S_addr = ip;
	}
	else
	{
		if ((rhe = (hostent*)gethostbyname(host)) == nullptr)
		{
			//FATAL("failed with %d", WSAGetLastError());
			return INVALID_NAME;
		}
		else
		{
			// I had a hate comment here on HW3
			//memcpy(&remote.sin_addr, rhe->h_addr, rhe->h_length);
			ip = *(DWORD*)rhe->h_addr;
			remote.sin_addr.S_un.S_addr = ip;
		}
	}

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		return FAILED_SEND;	
	}

	if (bind(sock, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR)
	{
		return FAILED_SEND;
	}

	TxSynHeader syn;
	syn.sdh.flags = Flags();
	syn.sdh.flags.syn = 1;
	syn.sdh.seq = 0;
	syn.lp = *props;

	struct in_addr addr;
	addr.s_addr = ip;

	rto = 1.0;
	int status;
	for (int i = 1; i <= MAX_ATTEMPTS_SYN; i++)
	{
		printf("[%.3f]\t--> SYN 0 (attempt %d of %d, RTO %.3f) to %s\n",
			TS(), i, MAX_ATTEMPTS_SYN, rto, inet_ntoa(addr));
	

		clock_t sent_at = clock();
		if ((status = SendPacket((byte*)&syn, sizeof(syn))) != STATUS_OK)
			return status;

		RxHeader resp;
		if ((status = WaitOnAck((byte*)&resp, sizeof(resp))) == STATUS_OK)
		{
			rto = 3 * ((double)(clock() - sent_at) / 1000.0);
			printf("[%.3f]\t<-- SYN-ACK %d window %d; setting initial RTO to %.3f\n", TS(), resp.ack_seq, resp.rcv_wnd, rto);
			conn = true;
			return STATUS_OK;
		}
		else if (status == TIMEOUT) continue;
		else return status;
	}

	return TIMEOUT;
}


int SenderSocket::Close()
{
	if (!conn) return NOT_CONNECTED;

	TxDataHeader fin;
	fin.flags = Flags();
	fin.flags.fin = 1;
	fin.seq = 0;

	int status;
	for (int i = 1; i <= MAX_ATTEMPTS; i++)
	{
		printf("[%.3f]\t--> FIN %d (attempt %d of %d, RTO %.3f)\n",
			TS(), fin.seq, i, MAX_ATTEMPTS, rto);

		if ((status = SendPacket((byte*)&fin, sizeof(fin))) != STATUS_OK)
			return status;

		RxHeader resp;
		if ((status = WaitOnAck((byte*)&resp, sizeof(resp))) == STATUS_OK)
		{
			printf("[%.3f]\t<-- FIN-ACK %d window %d\n", TS(), resp.ack_seq, resp.rcv_wnd);
			conn = false;
			closesocket(sock);
			sock = INVALID_SOCKET;
			return STATUS_OK;
		}
		else if (status == TIMEOUT) continue;
		else return status;
	}
	return TIMEOUT;
}
