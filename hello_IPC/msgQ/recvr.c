#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>

#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE     (MAX_MSG_SIZE + 10)
#define QUEUE_PERMISSIONS   0660

#define MSGQ_NAME "/MyMsgQ"

/*
To build, 
gcc -g recvr.c -o recvr -lrt
Will not work with mac because it does not support POSIX.

It does not matter if the sender or receiver creates the msgq first.
If sender runs first, the msg will still be kept by the kernel and will be received by the receiver when it runs later.
*/

int 
main(int argc, char **argv){

    fd_set readfds;
    char buffer[MSG_BUFFER_SIZE];
    int msgq_fd = 0;

    printf("Receiver started. Will receive message from %s\n", MSGQ_NAME);

    /*To set msgQ attributes*/
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    //open returns a file descriptor
    /*
    Flags -
    O_RDONLY    : read only
    O_WRONLY    : write only
    O_RDWR      : read and write
    O_CREAT     : create the msgq if not existing
    O_EXCL      : mq_open fails if a process tries to open an existing msgq, OR-ed with O_CREAT
    
    Permissions
    permissions set by the owning process, usually 0660

    Attributes
    mq_flags    : 0
    mq_maxmsg   : max number of msgs in the queue (useful if the receiver is busy)  /proc/sys/fs/mqueue/msg_max
    mq_msgsize  : max size of each msg                                              /proc/sys/fs/mqueue/msgsize_max
    mq_curmsgs  : # of msgs currently inside the queue
    */
    if ((msgq_fd  = mq_open (MSGQ_NAME,         //name
                            O_RDONLY | O_CREAT, //flag
                            QUEUE_PERMISSIONS,  //permissions
                            &attr)) == -1) {    //attributes
        printf ("Receiver: mq_open failed, errno = %d\n", errno);
        exit (1);
    }

    FD_ZERO(&readfds);
    FD_SET( msgq_fd, &readfds);
    while(1){
        printf("Receiver blocked on select()....");
        fflush(stdout); //called to immediately see the printout
                        //printf is implemented internally in batches for efficiency
        select(msgq_fd + 1, &readfds, NULL, NULL, NULL);
        if(FD_ISSET(msgq_fd, &readfds)){
            memset(buffer, 0, MSG_BUFFER_SIZE);
            
            //Oldest msg of the highest priority is deleted from the queue and then passed to the process
            //Default behavior is to block if there is no msg inside the queue, unless the flag O_NONBLOCK is enabled
            if (mq_receive (msgq_fd,        // file descriptor
                            buffer,         // points to an empty msg buffer
                            MSG_BUFFER_SIZE, // buffer size in bytes
                            NULL) == -1) {  // if this parameter is not NULL, the priority of the received msg is stored here
                                            // returns the size of the received msg if successful, or (-1) for failure
                printf ("mq_receive error, errno = %d\n", errno);
                exit (1);
            }
            printf("Msg received from %s = %s\n", MSGQ_NAME, buffer);
        }
    }
}

