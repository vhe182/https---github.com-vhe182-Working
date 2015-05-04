#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define RSZ	5

void err_sys( int fd1, int fd2, char *msg ){
	perror( msg );
	close( fd1 );
	close( fd2 );
	exit( -1 );
}

int main( int argc, char *argv[] ){
	int fd1, fd2, num1, num2, n, i, nrecs1 = 0, nrecs2 = 0;
	char buf[ RSZ ];

	if( argc != 3 ){
		printf("Usage: %s <rec1 position> <rec2 position>\n", argv[0]);
		exit( -1 );
	}
	
	num1 = atoi( argv[ 1 ] );
	num2 = atoi( argv[ 2 ] );
	if( ( fd1 = open( "recs1.txt", O_RDWR ) ) < 0 || ( fd2 = open( "recs2.txt", O_RDWR ) ) < 0 )
		err_sys( fd1, fd2, "open error");

	nrecs1 = lseek( fd1, 0, SEEK_END ) / RSZ;
	nrecs2 = lseek( fd2, 0, SEEK_END ) / RSZ;
	
	printf("nrecs1 = %d\nnrecs2 = %d\n", nrecs1, nrecs2 );

	lseek( fd2, -RSZ, SEEK_CUR );

	printf("FLAG: Before fd2 for-loop\n");

	for( i = nrecs2 ; i >  num2 + 1; i-- ){
		//printf("A%i\n",i);
		
		if( read( fd2, &buf, RSZ ) != RSZ )
			err_sys( fd1, fd2, "read error" );
		
		//printf("B%i\n",i);
		
		if( write( fd2, buf, RSZ ) != RSZ )
			err_sys( fd1, fd2, "write error" );
		
		lseek( fd2, -( 3 * RSZ ), SEEK_CUR );
	}

	if( read( fd2, &buf, RSZ) != RSZ )
		err_sys( fd1, fd2, "read error");
	if( write( fd2, &buf, RSZ) != RSZ )
		err_sys( fd1, fd2, "write error");
	
	printf("FLAG: Past fd2 for-loop\n");

	lseek( fd2, num2*RSZ, SEEK_SET );
	lseek( fd1, num1*RSZ, SEEK_SET );
	
	if( read( fd1, &buf, RSZ) != RSZ )
		err_sys( fd1, fd2, "read error");
	if( write( fd2, &buf, RSZ) != RSZ )
		err_sys( fd1, fd2, "write error");

	printf("FLAG: Read rec from fd1 and transfered to fd2\n");
	
	for( i = num1 + 1 ; i < nrecs1 ; i++ ){
		if( read(fd1, &buf, RSZ ) != RSZ )
			err_sys( fd1, fd2, "read error");
		lseek( fd1, -( 2 * RSZ ), SEEK_CUR);
		if( write( fd1, &buf, RSZ) != RSZ )
			err_sys( fd1, fd2, "write error");
		lseek( fd1, RSZ, SEEK_CUR);
	}

	printf("FLAG: After the fd1 for-loop\n");
	
	ftruncate( fd1, (nrecs1 - 1) * RSZ );

	close( fd1 );
	close( fd2 );
	return ( 0 );
} 
