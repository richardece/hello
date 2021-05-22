#include <stdio.h>
#include <signal.h>

int
main(int argc, char **argv){

    //Run kill_recv first, to determin its pid
    //ps -aux | grep kill_recv
    kill(100785, SIGUSR1);
    scanf("\n");
    return 0;
}
