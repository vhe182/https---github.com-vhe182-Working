/*PROGRAM: pkitty.c 
 *AUTHOR : Victor Hugo Estrada
 *CLASS  : Systems Programming
 *Professor : Dr. Maynard
 *
 *DESCRIPTION: 
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFSZ	1024

void closeall( int fdin1, int fdin2, int fdout );


int main ( int argc, char **argv )
{
	int n, fdin1 = 0, fdin2 = 0, fdout = 0;
	char buf[BUFSZ];
	
	if ( argc < 3 || argc > 4 ){
		write( STDERR_FILENO, "Usage: ",7 );
		write( STDERR_FILENO, argv[0],strlen(argv[0]) );
		write( STDERR_FILENO, " <file1> <file2> [file.out]\n",28 );
		exit(-1);
	}

	if ( ( strcmp(argv[1], "-") == 0 ) && ( strcmp(argv[2], "-") == 0) ){
		write( STDERR_FILENO, "Error: file1 and file2 cannot both be -\n", 40);
		exit(-1);
	}

	if ( strcmp(argv[1], "-") == 0 ){
		fdin1 = STDIN_FILENO;
	}else if( ( fdin1 = open( argv[1], O_RDONLY ) ) < 0 ){
			perror( argv[1] );
			closeall( fdin1,fdin2,fdout );
			exit( -1 );
	}

	if ( strcmp(argv[2],"-") == 0){
		fdin2 = STDIN_FILENO;
	}else if( ( fdin2 = open(argv[2], O_RDONLY ) ) < 0 ){
			perror( argv[2] );
			closeall( fdin1, fdin2, fdout );
			exit( -1 );
	}

	if ( argc == 4 ){
		if ( ( fdout = open( argv[3],O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0666 ) ) < 0){
			perror( argv[3] );
			closeall( fdin1, fdin2, fdout );
			exit( -1 );
		}
	}else{
		fdout = STDOUT_FILENO;
	}
	
	while ( ( n = read( fdin1, buf, BUFSZ ) ) > 0 )
	{
		if ( ( write ( fdout, buf, n ) ) != n )
		{
			perror( argv[1] );
			closeall( fdin1, fdin2, fdout );
			exit( -1 );
		}
	}
	if ( n < 0 )
	{
		perror( argv[1] );
		closeall( fdin1, fdin2, fdout );
		exit( -1 );

	}
	
	while ( ( n = read( fdin2, buf, BUFSZ ) ) > 0 )
	{
		if ( ( write ( fdout, buf, n) ) != n)
		{
			perror( argv[2] );
			closeall( fdin1, fdin2, fdout );
			exit( -1 );
		}
	}
	if ( n < 0 )
	{
		perror(argv[2]);
		closeall( fdin1, fdin2, fdout );
		exit(-1);
	}
	
	closeall( fdin1, fdin2, fdout );
	return 0;
}

/*******************************************

FUNCTION FOR CLOSING ALL FILES

********************************************/

void closeall( int fdin1, int fdin2, int fdout)
{
	close(fdin1);
	close(fdin2);
	close(fdout);
}
