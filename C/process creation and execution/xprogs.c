#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <wait.h>

struct header{
	int flen;
	int alen;
};

int xprogs( int fd ){

	char fbuf[ 25 ], abuf[ 25 ];
	struct header hd;
	int n, pid;

	printf( "Inside xprogs function\n");

	while( (n = read( fd, &hd, sizeof( hd ) ) ) > 0 ){
	
		if( read( fd, &fbuf, hd.flen  ) < 0 ){
			perror(" read flen error");
			return( -1 );
		}
		if( read( fd, &abuf, hd.alen ) < 0 ){
			perror(" read alen error");
			return( -1 );
		}
	
		switch( pid = fork() ){
			case -1:
				perror("fork child 1 error");
				return( -1 );
			case 0:
				switch( fork() ){
					case -1:
						perror("fork child 1 error");
						return( -1 );
					case 0:
						close( fd );
						execlp(fbuf, fbuf, abuf, NULL);
						perror("exec error");
						return( -1 );
					default:
						close( fd );
						exit(0);
				}
			default:
				wait( NULL );
		}
	}
	if( n < 0 ){
		perror("read error");
		return( -1 );
	}
	close( fd );

	return ( 0 );
}
int main( void ){

	int fd;
	struct header m, p, c;
	char prog1[ 3 ] = "ls";
	char arg1[ 4 ] = "-hl";
	char prog2[ 3 ] = "ps";
	char arg2[ 4 ] = "aux";
	char buf[ 100 ];

	m.flen = 3;
	m.alen = 4;
	p.flen = 3;
	p.alen = 4;

	if( (fd = open( "blarg", O_RDWR ) ) < 0 ){
		perror(" open fifo error" );
		exit( -1 );
	}
	
	write( fd, &m, sizeof( struct header ) );
	write( fd, &prog1, 3 * sizeof( char ) );
	write( fd, &arg1, 4 * sizeof( char ) );
	write( fd, &p, sizeof( struct header ) );
	write( fd, &prog2, 3*sizeof( char ) );
	write( fd, &arg2, 4*sizeof( char ) );
/*
	read( fd, &c, sizeof( struct header ) );
	printf( " prog1 header: \n\tflen = %i\n\talen = %i\n", c.flen, c.alen );
	read( fd, &buf, c.flen );
	printf(" prog1 = %s\n", buf );
	read( fd, &buf, c.alen );
	printf(" arg1 = %s\n", buf );
	
	read( fd, &c, sizeof( struct header) );
	printf( "prog2 header: \n\tflen = %i\n\talen = %i\n", c.flen, c.alen );
	read( fd, &buf, c.flen );
	printf(" prog2 = %s\n", buf );
	read( fd, &buf, c.alen );
	printf(" arg2 = %s\n", buf );
*/
	int fd2;

	if( ( fd2 = open( "blarg", O_RDONLY ) ) < 0 ){
		perror(" open read only error");
		exit( -1 );
	}

	if( xprogs( fd2 ) ){
		printf("xprogs returned -1, error\n");
	}else{
		printf("xprogs returned 0, good!\n");
	}
	close( fd );
	close( fd2 );
	return( 0 );
}
