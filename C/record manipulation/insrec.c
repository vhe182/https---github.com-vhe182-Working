#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int insrec( char *fdb, int num, char *rec, int rsz );

int main( int argc, char *argv[] ){
	char rec[ 6 ] = "sock ";
	printf("rec is : %s\n", rec);
	if( argc != 5 ){
		printf( "Usage: %s <filepath> <num> <rec to insert> <rec size>\n", argv[0] );
		exit( -1 );
	}

	
	return 0;
}


int insrec( char *fdb, int num, char *rec, int rsz ){
	
