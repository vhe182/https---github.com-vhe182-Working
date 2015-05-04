/*PROGRAM: logprt.c 
 *AUTHOR : Victor Hugo Estrada 
 *CLASS  : Systems Programming
 *Professor : Dr. Maynard
 *
 *DESCRIPTION: Program takes a tcpdumb file and reads
 *through the data, record by record.  
 */

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define TCPHDRSZ	24
#define PKTSZ		4096

/* magic constants for pcap file types */
#define PCAP_MAGIC			0xa1b2c3d4
#define PCAP_SWAPPED_MAGIC		0xd4c3b2a1
#define PCAP_MODIFIED_MAGIC		0xa1b2cd34
#define PCAP_SWAPPED_MODIFIED_MAGIC	0x34cdb2a1

/* pcap data */ 
struct pcap_file_header {
	u_int32_t magic;
	u_int16_t version_major;
	u_int16_t version_minor;
	u_int32_t thiszone;
	u_int32_t sigfigs;
	u_int32_t snaplen;
	u_int32_t linktype;
};

struct timev{
	unsigned int tv_sec;
	unsigned int tv_usec;
};


/* data prefixing each packet */
struct my_pkthdr{
	struct timev ts;
	int caplen;
	int len;
};

int main( int argc, char *argv[] ){
	
	int n, fdin, pktnum = 0, firsttime = 1;
	unsigned int b_sec, c_sec;
	int b_usec, c_usec;
	struct pcap_file_header pcaphdrbuf, *tp;
	tp = &pcaphdrbuf;

	struct my_pkthdr  pkthdrbuf, *php;
	php = &pkthdrbuf;
	
	char  pktbuf[ PKTSZ ], *pp;
	pp = pktbuf;

	if ( argc != 2 ){
		printf( "Usage: %s <file.in>\n", argv[0] );
		exit( -1 );
	}
	
	if ( ( fdin = open( argv[ 1 ], O_RDONLY ) ) < 0 ){
		perror( argv[ 1 ] );
		exit( -1 );
	}

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
	printf("Linktype = %d\n\n", tp->linktype );

	while ( ( n = read( fdin, &pkthdrbuf, sizeof( pkthdrbuf ) ) ) > 0 ){

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

		if ( read( fdin, &pktbuf, php->len ) != php->len ){
			perror( argv[ 1 ] );
			close( fdin );
			exit( -1 );
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
