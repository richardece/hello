#include <stdio.h>
#include <memory.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int
create_and_write_shared_memory (char *mmap_key, char *value, unsigned int size){
    
    int shm_fd;
    
    /*
    Create a shared memory object in kernel space. If shared memory already
    exists it will set the size (or truncate in their documentation)  to zero bytes again
     */
    /*
    Flags -
    O_CREAT     : create the shared mem if not existing
    O_RDONLY    : read only
    O_WRONLY    : write only
    O_RDWR      : read and write
    O_APPEND    : if the shared mem already exists and there is data inside, new data shall be appended
    O_TRUNC     : if the shared mem already exists and there is data inside, size will be reduced to zero and data will be deleted
    O_EXCL      : shm_open fails if a process tries to open an existing shared mem, OR-ed with O_CREAT
    */
    shm_fd = shm_open(mmap_key,                 // name of shared memory starting with /
                    O_CREAT | O_RDWR | O_TRUNC, // flags
                    0660);                      // mode
                    // returns a file descriptor if successful, or -1 if failed
    
    if (shm_fd < 0) {
        printf("failure on shm_open on shm_fd, errcode = %d\n", errno);
        return -1;
    }

    /*
    This function will resize of the shared memory region.
    WHAT happens if the reader application runs first, when the shared mem size is not yet set?
    */
    if (ftruncate(shm_fd, size) == -1) {
        printf("Error on ftruncate to allocate size of shared memory region\n");
        return -1;
    }

    /*
    Map the shared memory in kernel space into process's Virtual address space
    This works similar to MMU. shm_reg in the application points to the memory inside the kernel.
    */
    void *shm_reg = mmap(NULL, // let the kernel chose the address of application where the shared mem shall begin mapping
            size,              // sizeof the shared memory to map to virtual address space of the process
            PROT_READ | PROT_WRITE, // shared memory is Read and Writable
            MAP_SHARED,        // shared memory is accessible by different processes
            shm_fd,            // file descriptor of the shared memory 
            0);                // offset from the base address of the physical/shared memory to be mapped

    /* shm_reg is the address in process's Virtual address space (application), just like any other address.
     * The Linux paging mechanism maps this address to starting address of the shared memory region 
     * in kernel space. Any operation performed by process on shm_reg address is actually the operation
     * performed in shared memory which resides in kernel*/

    // Set the shared memory content to zero
    memset(shm_reg, 0, size);

    // Write a value into the shared memory
    memcpy(shm_reg, value, size);

    // Unmap the shared memory
    // The shared memory still contains the data.
    // Reader can still read the data later, even if the writer exits.
    munmap(shm_reg, size);

    /*Reader process will not be able to read shm if writer unlink
     * the name below*/
    //shm_unlink(mmap_key);

    close(shm_fd);
    return size;
}

int
read_from_shared_memory (char *mmap_key, 
                         char *buffer, 
                         unsigned int buff_size, 
                         unsigned int bytes_to_read) {


    int shm_fd = 0, rc = 0;

    shm_fd = shm_open(mmap_key, O_CREAT | O_RDONLY , 0660);
    
    if (shm_fd < 0) {
        printf("failure on shm_open on shm_fd, error code = %d", errno);
        return -1;
    } else {
        printf("shm_open successful\n");
    }

    void *shm_reg = mmap (NULL, bytes_to_read, PROT_READ, MAP_SHARED, shm_fd, 0);

    if(shm_reg == MAP_FAILED){
        printf("Error on mapping\n");
        return -1;
    } else {
        printf("mmap successful\n");
    }
    
    memcpy(buffer, shm_reg, bytes_to_read);

    rc = munmap(shm_reg, bytes_to_read);

    if(rc < 0){
        printf("munmap failed\n");
        return -1;
    } else {
        printf("munmap successful\n");
    }

    close(shm_fd);
    return bytes_to_read; /*Return the number of bytes read */
}
