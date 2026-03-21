#pragma once

#include "pch.h"

#define	MAGIC_PORT		22345
#define	MAX_PKT_SIZE	(1500-28)

#define STATUS_OK		0

using ushort = unsigned short;

// possible status codes from ss.Open, ss.Send, ss.Close
#define STATUS_OK			0	// no error
#define ALREADY_CONNECTED	1	// second call to ss.Open() without closing connection
#define NOT_CONNECTED		2	// call to ss.Send()/Close() without ss.Open()
#define INVALID_NAME		3	// ss.Open() with targetHost that has no DNS entry
#define FAILED_SEND			4	// sendto() failed in kernel
#define TIMEOUT				5	// timeout after all retx attempts are exhausted
#define FAILED_RECV			6	// recvfrom() failed in kernel


#define MAGIC_PROTOCOL 0x8311AA 
#define FWD_PATH	0
#define RET_PATH	1

#define MAX_ATTEMPTS_SYN	3
#define MAX_ATTEMPTS		5

#pragma pack(push, 1)

struct Flags
{
	DWORD	res : 5;
	DWORD	syn : 1;
	DWORD	ack : 1;
	DWORD	fin : 1;
	DWORD   magic : 24;
	Flags() : res(0), syn(0), ack(0), fin(0), magic(MAGIC_PROTOCOL) {}
};

struct LinkProps
{
	float	RTT;
	float	speed;
	float	p_loss[2];
	DWORD	buffer_size;
};

struct TxDataHeader
{
	Flags	flags;
	DWORD	seq;
	TxDataHeader() : flags(), seq() {}
};


struct TxSynHeader
{
	TxDataHeader	sdh;
	LinkProps		lp;
	TxSynHeader() : sdh(), lp() {}
};

struct RxHeader
{
	Flags	flags;
	DWORD	rcv_wnd;
	DWORD	ack_seq;
};

#pragma pack(pop)

class SenderSocket
{
	SOCKET sock;

	clock_t ts;
	bool conn;

	struct sockaddr_in local, remote;

	double rto;

	inline double TS()
	{
		return (clock() - ts) / 1000.0;
	}

	int SendPacket(byte* buf, int len);

	int WaitOnAck(byte* buf, int len);

public:
	
	SenderSocket() : sock(INVALID_SOCKET), conn(false), local({0}), remote({0})
	{
		ts = clock();
	}

	int Open(char* host, ushort port, int window_size, LinkProps* props);

	inline int Send()
	{
		return STATUS_OK;
	}

	int Close();


};

