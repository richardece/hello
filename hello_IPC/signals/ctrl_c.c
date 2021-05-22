#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void
ctrlC_signal_handler(int sig){
    printf("Ctrl-C pressed\n");
    printf("Bye Bye\n");
    exit(0);
}

static void
abort_signal_handler(int sig){
    printf("process is aborted\n");
    printf("Bye Bye\n");
    exit(0);
}

int
main(int argc, char **argv){

    // Try to press Ctrl+C to trigger
    // Or comment this out to see if the process can terminate by itself
    signal(SIGINT, ctrlC_signal_handler);

    // Type y to the question in scanf
    signal(SIGABRT, abort_signal_handler);

    char ch;
    printf("Abort process (y/n) ?\n");
    scanf("%c", &ch);
    if(ch == 'y')
        abort();
    return 0;
}
