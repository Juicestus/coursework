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

#pragma pack(pop)

struct DNSQuery
{
	uint16_t size;
	uint16_t txid;
	byte packet[MAX_DNS_LEN];
};

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

void PrintQuestion(byte* ques)
{
	for (int l; l = *(ques++); putchar(' '))
	{
		while (l--)
			putchar(*(ques++));
	}
	putchar('\n');
}

int CreateQuery(DNSQuery* query, char* lookup, int qtype)
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
	PrintQuestion(query->packet + sizeof(DNSFixedHeader));
	
	PrintBytes(query->packet, query->size);
	return 0;
}

