/*
 * HW2 - DNS Client
 * 
 * Justus Languell
 */
#include "pch.h"

#include "utils.h"
#include "dns.h"

//#define IGNORE_INPUTS

/*
 * 
 *		Flow-chart of the program, based off the one provided in the PDF
 * 
 *        *-------*											  *--------*
 *        | Input |											  | Output |
 *        *-------*											  *--------*
 *            |													  ^
 *            v												      |
 *  *-------------------*   IP							 *------------------* 
 *  | Decide query type |-----------*  Query type PTR	 |  Parse Response  |
 *  *-------------------*      		|					 *------------------* 	
 *            |						|							  ^
 *            | Host				|							  |
 *			  |						v							  |
 *            |          *-------------------*			 *------------------* 
 *            *--------->|   Create Query    |---------->| Transmit/Receive | 
 *      Query type A     *-------------------*			 *------------------*
 * 
 */
int main(int argc, char** argv) 
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data))
	{
		FATAL("WSAStartup failed with %d\n", WSAGetLastError());
		return 1;
	}

#if defined(_DEBUG) && defined(IGNORE_INPUTS)
	//char* lookup_str = (char*)"www.dhs.gov";
	char* lookup_str = (char*)"1.1.1.1";
	//char dns_addr_str[] = "128.194.135.79";
	char dns_addr_str[] = "8.8.8.8";
#else
	if (argc != 3)
	{
		FATAL("Usage: %s <hostname or IP addr to lookup> <IP addr of DNS server>", argv[0]);
		return 1;
	}
	char* lookup_str = argv[1], *dns_addr_str = argv[2];
#endif
	// TODO: swap byte order and add .in-addr.arpa for reverse lookup
	//int query_type = isdigit(lookup_str[0]) ? DNS_PTR : DNS_A;
	char rev_lookup_str[MAX_DNS_LEN];
	int query_type = DNS_A;
	struct in_addr addr;
	if (inet_pton(AF_INET, lookup_str, &addr) == 1)
	{
		query_type = DNS_PTR;
		byte* b = (byte*)&addr.s_addr;
		sprintf_s(rev_lookup_str, sizeof(rev_lookup_str), "%u.%u.%u.%u.in-addr.arpa", b[3], b[2], b[1], b[0]);
		lookup_str = rev_lookup_str;
	}
	
	DNSBuffer query = { 0 }, resp = { 0 };

	if (CreateQuery(&query, lookup_str, query_type))
		return 1;

	printf("Lookup   : %s\n"
		"Query    : %s, type %d, TXID 0x%04X\n"
		"Server   : %s\n"
		"********************************\n",
		lookup_str, lookup_str, query_type, query.txid, dns_addr_str);
	
	if (PerformQuery(dns_addr_str, &query, &resp))
		return 1;

	if (ParseResponse(&query, &resp))
		return 1;

	WSACleanup();
	return 0;
}


