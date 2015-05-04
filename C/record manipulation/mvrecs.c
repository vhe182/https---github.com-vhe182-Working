#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void err_sys( char *msg ){
	perror( msg );
	exit( -1 );
}

int main( int argc, char *argv[] ){

	int fd1, fd2, n, i, trec1, trec2;
	int rsz = 5, num1, num2;
	char buf[ rsz ];
	
	if( argc != 3 ){
		printf("Usage: %s <position of rec1 in file1> <position of rec2 in file2>\n", argv[0] );
		exit( -1 );
	}
	if( ( fd1 = open( "recs1.txt", O_RDWR ) ) < 0 || ( fd2 = open( "recs2.txt", O_RDWR ) ) < 0 ){
		err_sys("open error");
	}

	num1 = atoi(argv[1]);
	num2 = atoi(argv[2]);	

	trec1 = lseek( fd1, 0, SEEK_END ) / rsz;
	trec2 = lseek( fd2, 0, SEEK_END ) / rsz;

	printf("num1 = %i\nnum2 = %i\n", num1, num2);
	printf("trec1 = %i\ntrec2 = %i\n", trec1, trec2 );

	for( i = trec2 ; i > num2 ; i-- ){
		lseek( fd2, -rsz, SEEK_CUR );
		read( fd2, &buf, rsz );
		lseek( fd2, (trec1 - num1 - 1)*rsz, SEEK_CUR );
		write( fd2, &buf, rsz);
		lseek( fd2,(-(trec1 - num1 + 1)*rsz), SEEK_CUR );
	}
	//lseek(fd2, num2*rsz, SEEK_SET );
	lseek(fd1, num1*rsz, SEEK_SET );
	for( i = num1 ; i < trec1 ; i++ ){
		read(fd1, &buf, rsz);
		write(fd2, &buf, rsz);
	}
	ftruncate(fd1, num1*rsz);
	close( fd1 );
	close( fd2 );
	return 0;
}
