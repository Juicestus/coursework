/*
 * HW2 - DNS Client
 * 
 * Justus Languell
 */
#include "pch.h"

#include "utils.h"
#include "query.h"

#define IGNORE_INPUTS

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
#if defined(_DEBUG) && defined(IGNORE_INPUTS)
	char lookup_str[] = "www.justusl.com";
	//char lookup_str[] = "1.1.1.1";
	char dns_addr_str[] = "128.194.135.79";
#else
	if (argc != 3)
	{
		FATAL("Usage: %s <hostname or IP addr to lookup> <IP addr of DNS server>", argv[0]);
		return 1;
	}
	char* lookup_str = argv[1], *dns_addr_str = argv[2];
#endif
	int query_type = isdigit(lookup_str[0]) ? DNS_PTR : DNS_A;

	DNSQuery query = { 0 };

	if (CreateQuery(&query, lookup_str, query_type))
		return 1;

	printf("Lookup   : %s\n"
		"Query    : %s, type %d, TXID 0x%04X\n"
		"Server   : %s\n",
		lookup_str, lookup_str, query_type, query.txid, dns_addr_str);
	



}


