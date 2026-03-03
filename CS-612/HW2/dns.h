/*
 * HW2 - DNS Client
 *
 * Justus Languell
 */
#pragma once

#include "utils.h"

// Copied from the HW PDF:

/* Query types */
#define DNS_A			1			/* name -> IP */
#define DNS_NS			2			/* name server */
#define DNS_CNAME		5			/* canonical name */
#define DNS_PTR			12			/* IP -> name */
#define DNS_HINFO		13			/* host info/SOA */
#define DNS_MX			15			/* mail exchange */
#define DNS_AXFR		252			/* request for zone transfer */
#define DNS_ANY			255			/* all records */ 

/* Query classes */
#define DNS_INET		1 

/* Flags */
#define DNS_QUERY		(0 << 15)	/* 0 = query; 1 = response */
#define DNS_RESPONSE	(1 << 15)
#define DNS_STDQUERY	(0 << 11)	/* opcode - 4 bits */
#define DNS_AA			(1 << 10)	/* authoritative answer */
#define DNS_TC			(1 << 9)	/* truncated */
#define DNS_RD			(1 << 8)	/* recursion desired */
#define DNS_RA			(1 << 7)	/* recursion available */ 

#define DNS_OK			0			/* success */
#define DNS_FORMAT		1			/* format error (unable to interpret) */
#define DNS_SERVERFAIL	2			/* can’t find authority nameserver */
#define DNS_ERROR		3			/* no DNS entry */
#define DNS_NOTIMPL		4			/* not implemented */
#define DNS_REFUSED		5			/* server refused the query */ 

#define MAX_DNS_LEN		512
#define MAX_DNS_WORD	64

#define MAX_ATTEMPTS	3

// A lot of the below code is based off the slides:

#pragma pack(push, 1)


struct DNSQueryHeader
{
	uint16_t qtype;
	uint16_t qclass;
};

struct DNSFixedHeader
{
	uint16_t txid;
	uint16_t flags;
	uint16_t n_questions;
	uint16_t n_answers;
	uint16_t n_authority;
	uint16_t n_additional;
};

struct DNSAnswerHeader
{
	uint16_t rtype;
	uint16_t rclass;
	uint32_t ttl;
	uint16_t len;
};


#pragma pack(pop)

void htons_n(void* vobj, int size)
{
	short* obj = (short*)vobj;
	for (int i = 0; i < size / sizeof(short); i++)
	{
		obj[i] = htons(obj[i]);
	}
}

struct DNSBuffer 
{
	uint16_t size;
	uint16_t txid;	
	byte packet[MAX_DNS_LEN];
};

/*
* Transform a hostname or IP address into a DNS question.
*/
int CreateQuestion(byte* ques, char* lookup)
{
	int i = 0; 
	char* end, *head = lookup;
	while ((end = strchr(head, '.')) || (end = strchr(head, 0)))
	{
		if ((ques[i] = end - head) > MAX_DNS_WORD) return 1;
		memcpy(ques + i + 1, head, end - head);
		i += end - head + 1;
		head = end + 1;
		if (!*end) break;
	}
	ques[i] = 0;
	return 0;
}

/*
* Print a DNS question with word lengths for debugging.
*/
void PrintQuestion(byte* ques)
{
	for (int l; l = *(ques++); putchar(' '))
	{
		printf("(%d)", l);
		while (l--)
			putchar(*(ques++));
	}
	printf("0\n");
}

/*
* Construct a DNS query for a given hostname or IP to lookup
* with a given query type. 
*/
int CreateQuery(DNSBuffer* query, char* lookup, int qtype)
{
	if ((query->size = strlen(lookup) + 2 + sizeof(DNSFixedHeader) + sizeof(DNSQueryHeader)) > MAX_DNS_LEN)
	{
		FATAL("The query packet exceeded the max length of %d\n", MAX_DNS_LEN);
		return 1;
	}
	query->txid = __rdtsc() & 0xFFFF;	// should be random enough

	DNSFixedHeader* fh = (DNSFixedHeader*)query->packet;
	fh->txid         = htons(query->txid);
	fh->flags        = htons(DNS_QUERY | DNS_RD | DNS_STDQUERY);
	fh->n_questions  = htons(1);
	fh->n_answers	 = 0;
	fh->n_authority  = 0;
	fh->n_additional = 0;

	DNSQueryHeader* qh = (DNSQueryHeader*)(query->packet + query->size - sizeof(DNSQueryHeader));
	qh->qtype  = htons(qtype);
	qh->qclass = htons(DNS_INET);

	if (CreateQuestion(query->packet + sizeof(DNSFixedHeader), lookup))
	{
		FATAL("Some word in lookup string exceeded the max length of %d\n", MAX_DNS_WORD);
		return 1;
	}
	//PrintBytes(packet + sizeof(DNSFixedHeader), strlen(lookup) + 2);
	//PrintQuestion(query->packet + sizeof(DNSFixedHeader));
	
	PrintBytes(query->packet, query->size);
	return 0;
}

/*
* 
*/
int PerformQuery(char* dns_addr_str, DNSBuffer* query, DNSBuffer* resp)
{
	SOCKET sock;


	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		FATAL("Failed to create socket with %d", WSAGetLastError());
		return 1;
	}

	struct sockaddr_in local = { 0 }, remote = { 0 }, reply = { 0 };
	remote.sin_family = local.sin_family = AF_INET;

	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(0);
	remote.sin_addr.s_addr = inet_addr(dns_addr_str);
	remote.sin_port = htons(53);


	/*
	*/
	if (bind(sock, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR)
	{
		FATAL("Failed to bind local socket with %d\n", WSAGetLastError());
	}
	
	for (int i = 0, avail; i < MAX_ATTEMPTS; i++)
	{
		clock_t start_t = clock();
		printf("Attempt %d with %d bytes... ", i, query->size);
		// tx
		if (sendto(sock, (char*)query->packet, query->size, 0, (struct sockaddr*)&remote, sizeof(remote)) == SOCKET_ERROR)
		{
			FATAL("Failed to transmit with %d", WSAGetLastError());
			goto err;
		}
	
		// rx 
		fd_set fd;
		FD_ZERO(&fd);
		FD_SET(sock, &fd);
		timeval tv;
		tv.tv_sec = 10;
		tv.tv_usec = 0;
		if ((avail = select(0, &fd, NULL, NULL, &tv)) > 0)
		{
			int reply_addr_len = sizeof(reply);
			if ((resp->size = recvfrom(sock, (char*)resp->packet, MAX_DNS_LEN, 0, (struct sockaddr*)&reply, &reply_addr_len)) == SOCKET_ERROR)
			{
				FATAL("Failed to receive response with %d", WSAGetLastError());
				goto err;
			}
			if (reply.sin_addr.s_addr != remote.sin_addr.s_addr || reply.sin_port != remote.sin_port)
			{
				// is this an error or a retransmit?
				FATAL("Received a response for a different socket and port, I am complaining!");
				goto err;
			}
			printf("response in %d ms with %d bytes\n", clock() - start_t, resp->size);
			break;
		} 
		else if (avail == 0)
		{
			printf("timeout in %d ms\n", clock() - start_t);
			continue;
		}
		else
		{
			FATAL("failed on select with %d", WSAGetLastError());
			goto err;
		}
	}

	//PrintBytes(resp->packet, resp->size);

	closesocket(sock);
	return 0;
err:
	closesocket(sock);
	return 1;

}

/*
* 
*/
//int ParseQuestions(byte* buf, int n)
//{
//	static char host[MAX_DNS_LEN] = { 0 };
//	byte* bptr = buf;
//	printf("------------ [questions] ----------\n");
//	while (n--)
//	{
//		char* hptr = host;
//		for (int l; l = *(bptr++); *(hptr++) = '.')
//		{
//			while (l--)
//				*(hptr++) = *(bptr++);
//		}
//		hptr[-1] = 0;
//
//		DNSQueryHeader* qh = (DNSQueryHeader*)bptr;
//		bptr += sizeof(DNSQueryHeader);
//		printf("  %s type %d class %d\n", host, htons(qh->qtype), htons(qh->qclass));
//	}
//	return bptr - buf;
//}


int ParseName(byte* buf, int buflen, int pos, char* name)
{
	int rpos = pos, wpos = 0, len, dif = 0, jmps = 0;

	while (true)
	{
		if (pos >= buflen)
		{
			FATAL("  ++ invalid record: truncated name");
			return -1;
		}
		if ((len = buf[rpos]) == 0)
		{
			if (!jmps) dif = rpos - pos;
			break;
		}
		if ((len & 0xC0) == 0xC0)
		{
			if (rpos + 1 >= buflen)
			{
				FATAL("  ++ invalid record: truncated jump offset");
				return -1;
			}
			int off = ((buf[rpos] & 0x3F) << 8) + buf[rpos + 1];
			if (off >= buflen)
			{
				FATAL("  ++ invalid record: jump beyond packet boundary");
				return -1;
			}
			if (off < sizeof(DNSFixedHeader))
			{
				FATAL("  ++ invalid record: jump into fixed DNS header");
				return -1;
			}
			if (!jmps) dif = rpos - pos + 2;
			if (++jmps > 32)
			{
				FATAL("  ++ invalid record: jump loop");
				return -1;
			}
			rpos = off;
			continue;
		}
		if (rpos + 1 + len > buflen)
		{
			FATAL("  ++ invalid record: truncated name");
			return -1;
		}
		if (wpos > 0) name[wpos++] = '.';
		memcpy(name + wpos, buf + rpos + 1, len);
		wpos += len;
		rpos += 1 + len;
	}
	name[wpos] = 0;
	if (!jmps) dif = rpos - pos + 1;
	return dif;
}


int ParseQuestions(byte* buf, int buflen, int pos, int n)
{
	char name[MAX_DNS_LEN];
	int r;
	for (int i = 0; i < n; i++)
	{
		if (pos >= buflen)
		{
			FATAL("  ++ invalid section: not enough records");
			return -1;
		}
		if ((r = ParseName(buf, buflen, pos, name)) < 0)
			return -1;
		pos += r;
		if (pos + sizeof(DNSQueryHeader) > buflen)
			return -1;
		DNSQueryHeader* qh = (DNSQueryHeader*)(buf + pos);
		pos += sizeof(DNSQueryHeader);
		printf("  %s type %d class %d\n", name, ntohs(qh->qtype), ntohs(qh->qclass));
	}
	return pos;
}

char* RecordTypeStr(short type)
{
	switch (type)
	{
	case DNS_A: return (char*)"A";
	case DNS_NS: return (char*)"NS";
	case DNS_CNAME: return (char*)"CNAME";
	case DNS_PTR: return (char*)"PTR";
	case DNS_MX: return (char*)"MX";
	default: return (char*)"?";
	}
}


int ParseRecords(byte* buf, int buflen, int pos, int n)
{
	char name[MAX_DNS_LEN], rr[MAX_DNS_LEN];
	int r;
	for (int i = 0; i < n; i++)
	{
		if (pos >= buflen)
		{
			FATAL("  ++ invalid section: not enough records");
			return -1;
		}
		if ((r = ParseName(buf, buflen, pos, name)) < 0)
			return -1;
		pos += r;
		if (pos + (int)sizeof(DNSAnswerHeader) > buflen)
		{
			FATAL("  ++ invalid record: truncated RR answer header");
			return -1;
		}

		DNSAnswerHeader* ah = (DNSAnswerHeader*)(buf + pos);
		ah->rtype = ntohs(ah->rtype);
		ah->ttl = ntohl(ah->ttl);
		ah->len = ntohs(ah->len);
		pos += sizeof(DNSAnswerHeader);

		if (pos + ah->len > buflen)
		{
			FATAL("  ++ invalid record: RR value length stretches the answer beyond packet");
			return -1;
		}

		if (ah->rtype == DNS_A && ah->len == 4)
		{
			struct in_addr addr;
			memcpy(&addr, buf + pos, 4);
			printf("  %s A %s TTL = %u\n", name, inet_ntoa(addr), ah->ttl);
		}
		else
		{
			ParseName(buf, buflen, pos, rr);
			printf("  %s %s %s TTL = %u\n", name, RecordTypeStr(ah->rtype), rr, ah->ttl);
		}

		pos += ah->len;
	}
	return pos;
}

/*
*/
int ParseResponse(DNSBuffer* query, DNSBuffer* resp)
{
	if (resp->size <= sizeof(DNSFixedHeader))
	{
		FATAL("  ++ packet smaller than fixed DNS header\n");
		return 1;
	}

	DNSFixedHeader* fh = (DNSFixedHeader*)resp->packet;
	fh->txid = ntohs(fh->txid);
	fh->flags = ntohs(fh->flags);
	fh->n_questions = ntohs(fh->n_questions);
	fh->n_answers = ntohs(fh->n_answers);
	fh->n_authority = ntohs(fh->n_authority);
	fh->n_additional = ntohs(fh->n_additional);

	printf("  TXID 0x%04X flags 0x%04X questions %d answers %d authority %d additional %d\n",
		fh->txid, fh->flags, fh->n_questions, fh->n_answers, fh->n_authority, fh->n_additional);
	if (query->txid != fh->txid)
	{
		FATAL("  ++ invalid reply TXID mismatch, sent 0x%04X, received 0x%04X\n", query->txid, fh->txid);
		return 1;
	}
	int rcode, pos = sizeof(DNSFixedHeader);
	if ((rcode = fh->flags & 0x000F) != DNS_OK)
	{
		printf("  failed with Rcode = %d\n", rcode);
	}
	else
	{
		printf("  succeeded with Rcode = %d\n", rcode);
	}

	//byte* buf = (byte*)(resp->packet + sizeof(DNSFixedHeader));	// TODO: switch to index based

	printf("  ------------ [questions] ----------\n");
	if ((pos = ParseQuestions(resp->packet, resp->size, pos, fh->n_questions)) < 0)
		return 1;

	printf("  ------------ [answers] ------------\n");
	if ((pos = ParseRecords(resp->packet, resp->size, pos, fh->n_answers)) < 0)
		return 1;

	printf("  ------------ [authority] ----------\n");
	if ((pos = ParseRecords(resp->packet, resp->size, pos, fh->n_authority)) < 0)
		return 1;

	printf("  ------------ [additional] ---------\n");
	if ((pos = ParseRecords(resp->packet, resp->size, pos, fh->n_additional)) < 0)
		return 1;

	//PrintBytes(buf, 128);

	return 0;
}
