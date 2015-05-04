#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

void err_sys( char *str ){
	perror( str );
	exit( -1 );
}

int main( void ){

	int fd[2], fdout, pid;
	
	if( pipe( fd ) )
		err_sys( "pipe" );

	switch( pid = fork() ){
		case -1:
			err_sys( "fork" );
		case 0:
			close( fd[0] );
			dup2( fd[1], STDOUT_FILENO );
			close( fd[1] );
			execlp( "diff" , "diff" , "recs1.txt" , "recs2.txt" , NULL);
			err_sys("exec diff error");
		default:
			close( fd[1] );
			dup2(fd[0], STDIN_FILENO );
			close( fd[0]);
			if( (fdout = open( "log.txt", O_WRONLY | O_APPEND | O_CREAT, 0600 ) ) < 0 ){
				close( fd[0] );
				close( fd[1] );
				err_sys("open error");
			}
			dup2( fdout, STDOUT_FILENO );
			close( fdout ); 
			execlp( "grep", "grep", "BR", NULL );
			err_sys("exec write error");
	}
	err_sys("exec problem");
	return (-1);
}
