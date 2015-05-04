#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

struct msg{
	int num;
	int pid;
	int ndx;
};

void err_sys( char *msg ){	
	perror( msg );
	exit( -1 );
}


int main( void ){

	int fd[33][2], d, n = 0, i, pid;
	struct msg m;

	m.ndx = 0;

	for( i = 0 ; i < 33 ; i++ )
		if( pipe( fd[i] ) ){
			perror("pipe error");
			exit( -1 );
		}

	for( i = 1 ; i < 33 ; i++ ){
		switch( pid = fork() ){
			case -1:
				for( d = 0 ; d < 33 ; d++ ){
					close( fd[d][0] );
					close( fd[d][1] );
				}
				err_sys( "fork error" );
			case 0:
				m.ndx = i;
		}
		if( !pid )
			break;
	}

	/////////COMMON CODE//////////////

	m.pid = getpid();
	close( fd[m.ndx][1] );
	for( i = 0 ; i < 33 ; i++ ){
		if( i != m.ndx ){
			close( fd[i][0] );
		}
	}

	if( m.ndx == 0){ 		// ORIGINAL PROCESS
		for( i = 1; i < 33 ; i++ ){
			do{
				n = rand() % 33;
			}while( n == 0 );
			
			if( write( fd[i][1], &n, sizeof( int ) ) !=  sizeof( int ) ){
				for( d = 0 ; d < 33 ; d++ ){
					close( fd[d][0] );
					close( fd[d][1] );
				}
				err_sys( "write error, parent sends integer" );
			}
			close( fd[i][1] );
		}
		
		//for( i = 0 ; i < 33 ; i++ ){
		//	close( fd[i][1] );
		//}
		
		while( ( n = read( fd[0][0], &m, sizeof( struct msg ) ) ) == sizeof( struct msg ) ){
			printf("Original Process 0 read random number %d from process %d index %d\n", m.num, m.pid, m.ndx );
		}
		if( n < 0 ){
			for( d = 0 ; d < 33 ; d++ ){
					close( fd[d][0] );
					close( fd[d][1] );
			}
			err_sys( "read error, parent reads message struct" );
		}

		//close( fd[m.ndx][0] );
	}else{ 		// CHILDREN
		if( read( fd[m.ndx][0], &n, sizeof( int ) ) != sizeof( int ) ){
			for( d = 0 ; d < 33 ; d++ ){
					close( fd[d][0] );
					close( fd[d][1] );
			}
			err_sys( "read error, children reads integer" );
		}

		close( fd[m.ndx][0] );
		m.num = n;

		if( ( m.num % 2 ) == 0 ){
			if( write( fd[0][1], &m, sizeof( struct msg ) ) != sizeof( struct msg ) ){
				for( d = 0 ; d < 33 ; d++ ){
					close( fd[d][0] );
					close( fd[d][1] );
				}
				err_sys( "write error, children write message struct" );
			}
		}
		for( i = 0 ; i < 33 ; i++ ){
			close( fd[i][1] );
		}
	}
	for( i = 0 ; i < 33 ; i++ ){
		close( fd[i][0] );
	}
	return ( 0 );
}
