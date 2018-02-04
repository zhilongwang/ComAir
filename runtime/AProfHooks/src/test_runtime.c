#include <stdio.h>
#include "aproflib.h"

struct stack_elem Ele;

void read_shared_momery() {
    int fd = shm_open(APROF_MEM_LOG, O_RDWR | O_CREAT | O_EXCL, 0777);

    if (fd < 0) {
        fd = shm_open(APROF_MEM_LOG, O_RDWR, 0777);

    } else
        ftruncate(fd, BUFFERSIZE);

    void *ptr = mmap(NULL, BUFFERSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    puts("start reading data....");
    memcpy(&Ele, ptr, sizeof(Ele));

    while (Ele.funcId > 0) {
        printf("%d\n", Ele.funcId);
        ptr += sizeof(Ele);
        memcpy(&Ele, ptr, sizeof(Ele));
    }

    puts("read over");
    shm_unlink(APROF_MEM_LOG);
    close(fd);

}

int main() {

    aprof_init();
    aprof_call_before(1);
    aprof_call_before(2);

    aprof_increment_rms(10);
    aprof_increment_rms(5);

    aprof_return(3);
    aprof_return(2);
    read_shared_momery();
    return 0;
}
