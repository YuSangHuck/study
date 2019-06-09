#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd;
    ssize_t nread;
    char buf[1024];

    printf("open call\n");
    if((fd = open("data",O_RDONLY)) < 0){
        perror("open");
    }
    printf("fd : %d\n", fd);

    printf("read call\n");
    if(nread = read(fd, buf, 1024) < 0){
        perror("read");
    }

    printf("close call\n");
    if(close(fd) < 0){
        perror("close");
    }

    return 0;
}
