#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

static void sighandler( int signo ) {
    if ( signo == SIGINT ) {
        printf( "Signal %d received. Exiting and writing to file.\n", signo );
        int d = open( "file.txt", O_CREAT | O_APPEND | O_WRONLY, 0644);
        char *s = "SIGINT received. Program exited.\n";
        write( d, s, strlen(s) );
        close(d);
        exit(1);
    }
    
    else if ( signo == SIGUSR1 ) {
        printf( "The parent process' pid is %d.\n", getppid() );
    }
}

void main() {
  umask( 0111 );
    
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
    
  while(1) {
    printf( "This process' pid is %d.\n", getpid() );
    sleep(1);
  }
    
}
