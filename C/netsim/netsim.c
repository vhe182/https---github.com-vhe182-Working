/*PROGRAM: netsim.c 
 *AUTHOR : Victor Hugo Estrada
 *CLASS  : Systems Programming
 *Professor : Dr. Maynard
 *
 *DESCRIPTION: Program demonstrates the creation of
 *multiple processes, inter-process communication, 
 *and control of all processes. 
 *This is accomplished via the pipe and fork
 *functions.  NUMPROC pipes are created, then
 *NUMPROC - 1 forks are called.  The child process
 *creates the next child and the parent of each fork
 *breaks out of the for-loop.  Appropriate pipes are
 *close so that each process can only read from
 *their respective pipe but can write to all other
 *processes' pipes except their own.  
 *A random number generator algorithm is used to 
 *randomly select one of the NUMPROC processes and
 *the process sends the message "process%d", with
 *index replacing the %d, to the chosen process.
 *After all children have sent NUM_WRITES quantity of
 *messages, the for loop is exited and all children
 *close all write connections.  All children then
 *read MSGSZ chuncks of data and print out the 
 *message until there is no more data in any pipe.
 *Return 0 signaling successful completion of program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define NUM_WRITES	12
#define BUFSZ		1024
#define MSGSZ		9 // Add extra bytes allotted for scalability
#define NUMPROC		8
#define RAND_MAX	2147483647
#define SEED_NUM	1921739

void err_sys( char *msg );


int main( void ){

	int i, n, num, pid, j, rng, fd[NUMPROC][2], index;
	char myproc[ MSGSZ ];
	char msgbuf[ BUFSZ ];

	for( i = 0 ; i < NUMPROC ; i++ ){
		if ( pipe( fd[ i ] ) )
			err_sys("pipe error");
	}

	index = 0;
	for( i = 1 ; i < NUMPROC ; i++ ){
		switch( pid = fork() ){
			case -1: // ERROR trap
				err_sys("fork error");
			case 0: // CHILD
				index = i;
				//printf("child gets %d for index\n", index );
				//fflush(stdout);
				break;
		}
		if( pid ){
			//printf("parent %d broke out of for loop\n", index);
			break;
		}
	}
	
	//COMMON CODE
	/* All processes close write ends to their own pipe */
	close( fd[ index ][ 1 ] );

	/* All processes close all read ends except to their own */	
	for( i = 0 ; i < NUMPROC ; i++ ){
		if( i != index )
			close( fd[ i ][ 0 ] );
	}
	
	/* Setup message that each process will send to other processes */
	sprintf( myproc,"process%d", index );
	//printf("message: %s : prepped\n", myproc );
	/* 
	 * Seed the random num generator and loop 12 times, creating a child
	 * number and sending a message to them everytime 
	 */
	srand( SEED_NUM * index );
	rng = RAND_MAX/NUMPROC;
	rng *= NUMPROC;
	for( i = 0 ; i < NUM_WRITES ; i++ ){
		do {
			num = rand();
			j = num % NUMPROC;
		}while( num >= rng || index == j );

		//fprintf(stdout, "child %d -> child %d\n", index, j);
		if( (n = write( fd[ j ][ 1 ], &myproc, ( MSGSZ * sizeof( char ) ) ) )  != ( MSGSZ * sizeof( char ) ) ) 
			err_sys( "write error");
		//printf("Bytes sent: %d\n", n);
	}
	
	/* Done writing, all procs close all write ends */
	for( i = 0 ; i < NUMPROC ; i++ ){
		if( i != index ) // Write end to all procs' own pipe has already been closed
			close( fd[ i ][ 1 ] );
	}
	
	/* start reading in MSGSZ chunks until no more data to read */
	while( (n = read( fd[ index ][ 0 ], &msgbuf, ( MSGSZ * sizeof( char ) ) ) ) == ( MSGSZ * sizeof( char ) ) ){
		printf("%s has received a message from %s\n", myproc, msgbuf );
		//printf("Bytes read: %d\n", n );
		fflush( stdout );
	}	
	if( n < 0 )
		err_sys( "read error" ); 
	
	close( fd[ index ][ 0 ] );	
	return 0;
}
void err_sys( char *msg ){
	perror( msg );
	exit( -1 );
}
