/*PROGRAM: prtlog.c 
 *AUTHOR : Victor Hugo Estrada *CLASS  : Systems Programming
 *Professor : Dr. Maynard
 *
 *DESCRIPTION: Program takes a tcpdumb file as input and outputs
 *the pcap header info.  It then reads through the rest of the
 *records and prints out the ethernet type.  If ethernet type is
 *IP or ARP, the protocol is printed for the IP packets.  If ARP
 *the operation type is printed out.
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "pcap.h"
#include "dnet.h"
#include "prtlog.h"

#define TCPHDRSZ	24
#define PKTSZ		4096


int main( int argc, char *argv[] ){
	
	int n, fdin, pktnum = 0, firsttime = 1;
	unsigned int b_sec, c_sec;
	int b_usec, c_usec;
	
	struct pcap_file_header pcaphdrbuf, *tp;
	tp = &pcaphdrbuf;

	struct my_pkthdr  pkthdrbuf, *php;
	php = &pkthdrbuf;

	char  pktbuf[ PKTSZ ];

	struct eth_hdr *eth;	
	struct arp_hdr *arp;
	struct ip_hdr *ip;

	eth =(struct eth_hdr *) &pktbuf;
	arp = ( struct arp_hdr *) &( pktbuf[ sizeof( struct eth_hdr ) ] );
	ip = (struct ip_hdr * ) &( pktbuf[ sizeof( struct eth_hdr ) ] );

	/* Check for correct number of args */
	if ( argc != 2 ){
		printf( "Usage: %s <file.in>\n", argv[0] );
		exit( -1 );
	}
	
	/* Open the tcpdump file */
	if ( ( fdin = open( argv[ 1 ], O_RDONLY ) ) < 0 ){
		perror( argv[ 1 ] );
		exit( -1 );
	}

	/* Read pcaptcp header data, 24 bytes */
	if ( ( read( fdin, &pcaphdrbuf, TCPHDRSZ ) ) != TCPHDRSZ ){
		perror( argv[ 1 ] );
		exit( -1 );
	}

	printf("PCAP_MAGIC\n");
	printf("Version major number = %d\n", tp->version_major );
	printf("Version minor number = %d\n", tp->version_minor );
	printf("GMT to local correction = %d\n", tp->thiszone );
	printf("Timestamp accuracy = %d\n", tp->sigfigs );
	printf("Snaplen = %d\n", tp->snaplen );
	printf("Linktype = %d\n\n\n", tp->linktype );

	/* Read through all packet header data of the file, pkthdr size bytes */
	while ( ( n = read( fdin, &pkthdrbuf, sizeof( pkthdrbuf ) ) ) > 0 ){

		/* Set up timing variable */
		if ( firsttime ){
			firsttime = 0;
			b_sec = (*php).ts.tv_sec;
			b_usec = (*php).ts.tv_usec;
		}
		c_sec = ( unsigned ) (*php).ts.tv_sec - b_sec;
		c_usec = ( unsigned ) (*php).ts.tv_usec - b_usec;
		while( c_usec < 0 ){
			c_usec += 1000000;
			c_sec--;
		}
		
		printf("Packet %d\n", pktnum );
		printf("%05u.%06u\n", (unsigned)c_sec, (unsigned)c_usec);
		printf("Captured Packet Length = %d\n", php->caplen );
		printf("Actual Packet Length = %d\n", php->len);
		printf("Ethernet Header\n");

		/* Read the packet header into pktbuf */
		if( read( fdin, pktbuf, php->len )  != php->len ){
			perror( argv[ 1 ] );
			close( fdin );
			exit( -1 );
		}
		
		/* Funnel ethernet type into appropriate actions */
		switch ( ntohs( eth->eth_type ) ){
			case ETH_TYPE_IP:

				printf("   IP\n");
	
				switch( ip->ip_p ){
					case IP_PROTO_ICMP:
						printf("      ICMP\n");
						break;
					case IP_PROTO_IGMP:
						printf("      IGMP\n");
						break;
					case IP_PROTO_TCP:
						printf("      TCP\n");
						break;
					case IP_PROTO_UDP:
						printf("      UDP\n");
						break;
					default:
						printf("      UNRECOGNIZED\n");
						break;	
				}

				break;

			case ETH_TYPE_ARP:

				printf("   ARP\n");
				
				switch( ntohs( arp->ar_op ) ){
					case ARP_OP_REQUEST:
						printf("      arp operation = Arp Request\n");
						break;
					case ARP_OP_REPLY:
						printf("      arp operation = Arp Reply\n");
						break;
					case ARP_OP_REVREQUEST:
						printf("      arp operation = Arp Request\n");
						break;
					case ARP_OP_REVREPLY:
						printf("      arp operation = Arp Reply\n");
						break;
					default:
						printf("ERROR: Unkown ARP operation\n");
						close( fdin );
						exit( -1 );
				}
				
				break;

			default:

				switch( ntohs( eth->eth_type ) ){
					case ETH_TYPE_PUP:
						printf("   PUP\n");
						break;
					case ETH_TYPE_REVARP:
						printf("   REVARP\n");
						break;
					case ETH_TYPE_8021Q:
						printf("   8021Q\n");
						break;
					case ETH_TYPE_IPV6:
						printf("   IPV6\n");
						break;
					case ETH_TYPE_MPLS:
						printf("   MPLS\n");
						break;
					case ETH_TYPE_MPLS_MCAST:
						printf("   MPLS MCAST\n");
						break;
					case ETH_TYPE_PPPOEDISC:
						printf("   PPPOEDISC\n");
						break;
					case ETH_TYPE_PPPOE:
						printf("   PPPOE\n");
						break;
					case ETH_TYPE_LOOPBACK:
						printf("   LOOPBACK\n");
						break;
					default:
						printf("   UNRECOGNIZED\n");
						break;
				}
				break;	
		}

		printf("\n\n");
		pktnum++;	
	}
	if( n < 0 ){
		perror( argv[ 1 ] );
		close( fdin );
		exit( -1 );
	}

	close( fdin );
	return ( 0 );
}
