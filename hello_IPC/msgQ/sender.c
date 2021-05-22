#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>

#define MAX_MSG_SIZE        256
#define MSG_BUFFER_SIZE     (MAX_MSG_SIZE + 10)

#define MSGQ_NAME "/MyMsgQ"

/*
To build, 
gcc -g sender.c -o sender -lrt
Will not work with mac because it does not support POSIX.
*/


int 
main(int argc, char **argv){

    char buffer[MSG_BUFFER_SIZE];
    int recvr_msgq_fd = 0;

    printf("Receiver started. Will send message to %s\n", MSGQ_NAME);

    memset(buffer, 0, MSG_BUFFER_SIZE);
    printf("Enter msg to be sent: ");
    scanf("%s", buffer);

    if ((recvr_msgq_fd  = mq_open (MSGQ_NAME, O_WRONLY | O_CREAT, 0, 0)) == -1) {
        printf ("Client: mq_open failed, errno = %d\n", errno);
        exit (1);
    }

    // If the msgq is full, mq_send will block until a there is a space in the queue,
    //unless the O_NONBLOCK flag is enabled
    if (mq_send (recvr_msgq_fd,     // msgq file descriptor
                buffer,             // points to the msg buffer
                strlen (buffer) + 1, // size of the msg, must e
                0) == -1) {         // non-negative number specifying the msg priority
                                    // returns success (0) or fail (-1)
        perror ("Client: Not able to send message to server\n");
        exit (1);
    }

    mq_close(recvr_msgq_fd);
    return 0;
}

