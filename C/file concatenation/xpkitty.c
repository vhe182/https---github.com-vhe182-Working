/*PROGRAM: xpkitty.c 
 *AUTHOR : Victor Hugo Estrada
 *CLASS  : Systems Programming
 *Professor : Dr. Maynard
 *
 *SYNTAX: xpkitty <file1.in> <file2.in> [file.out]
 *
 *DESCRIPTION:  xpkitty.c interleaves the lines of 2 files ( lines
 * defined as all characters up to and including a newline ).  
 *If a file terminates in no newline, the next line to be 
 *written will be written immediately following the last
 *character of the previous line.  The user can also designate one
 *of the optional input files to be input from stdin.  Both files
 *will then be written, interleaving lines from both files, to
 *stdout or an output file, if specified.
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFSZ	1024

/* Following function located at end of this .c file  */
void closeall( int fdin1, int fdin2, int fdout );


int main ( int argc, char **argv )
{
	
	int n, m, ndx1a, ndx1b, ndx2a, ndx2b, fdin1 = 0, fdin2 = 0, fdout = 0;
	char buf1[ BUFSZ ], buf2[ BUFSZ ];
	char ch = '\n';

	if ( argc < 3 ){
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

	while ( ( n = read( fdin1, buf1, BUFSZ ) ) > 0 && ( m = read( fdin2, buf2, BUFSZ ) ) > 0 ){
		ndx1a = 0, ndx1b = 0, ndx2a = 0, ndx2b = 0;
		/* If the buf1's or buf2's forward ndx (ndx1a and ndx2a respectively) are less than
		 * the location of the data read in for each buffer (n and m respectively), then 
		 * the loop is entered.  Inside the loop, must still test to see which buffer has
		 * data in it, hence the if statements. 
		 */
		while ( ndx1a < n || ndx2a < m ){
			if ( ndx1a < n ){
				/* Previous index ( last char to be read in ) is stored by ndx1b and
				 * ndx2b.  Before write anything, the forward index gets passed to the
				 * back index.
				 */
				ndx1b = ndx1a;
				for( ; ndx1a < n ; ndx1a++ ){
					if( buf1[ ndx1a ] == ch ){
						ndx1a++;
						break;
					}
				}
				if ( write( fdout, &buf1[ ndx1b ], ( &buf1[ ndx1a ] - &buf1[ ndx1b ] ) ) != ( &buf1[ ndx1a ] - &buf1[ ndx1b ] ) ){
					perror( argv[3] );
					closeall( fdin1, fdin2, fdout );
					exit( -1 );
				}
			}
			
			if ( ndx2a < m ){
				ndx2b = ndx2a;
				for ( ; ndx2a < m ; ndx2a++ ){
					if ( buf2[ ndx2a ] == ch ){;
						ndx2a++;
						break;
					}
				}
				if ( write( fdout, &buf2[ ndx2b ], ( &buf2[ ndx2a ] - &buf2[ ndx2b ] ) ) != ( &buf2[ ndx2a ] - &buf2[ ndx2b ] ) ){
					perror( argv[3] );
					closeall( fdin1, fdin2, fdout );
					exit( -1 );
				}
			}
		}
	}
	if ( n < 0 || m < 0 ){
		perror ( "read error" );
		closeall( fdin1, fdin2, fdout );
		exit( -1 );
	}

	if ( n > 0 ){
		if ( write( fdout, buf1, n ) != n ){
			perror( argv[ 3 ] );
			closeall( fdin1, fdin2, fdout );
			exit( -1 );
		}
		while ( (n = read( fdin1, buf1, BUFSZ ) ) > 0 ){
			if ( write( fdout, buf1, n ) != n ){
				perror ( argv[ 3 ] );
				closeall( fdin1, fdin2, fdout );
				exit( -1 );
			}
		}
		if ( n < 0 ){
			perror ( "read error" );
			closeall( fdin1, fdin2, fdout );
			exit( -1 );
		}
	}
	
	if ( m > 0 ){
		if ( write( fdout, buf2, m ) != m ){
			perror ( argv[ 3 ] );
			closeall( fdin1, fdin2, fdout );
			exit( -1 );
		}
		while ( ( m = read( fdin2, buf2, BUFSZ ) ) > 0 ){
			if ( write( fdout, buf2, m ) != m ){
				perror( argv[ 3 ] );
				closeall( fdin1, fdin2, fdout );
				exit( -1 );
			}
		}
		if ( m < 0 ){
			perror ( "read error" );
			closeall( fdin1, fdin2, fdout );
			exit( -1 );
		}
	}


	closeall( fdin1, fdin2, fdout );
	exit( 0 );
}
/*******************************************

FUNCTION FOR CLOSING ALL FILES

********************************************/
void closeall( int fdin1, int fdin2, int fdout){
	close(fdin1);
	close(fdin2);
	close(fdout);
}
