#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void PrintfStatus(struct stat* pStat){
    printf("st_dev : %lu\n", pStat->st_dev);                                      /* Device.  */
    printf("st_ino : %lu\n", pStat->st_ino);                                      /* File serial number.	*/
    printf("st_nlink : %lu\n", pStat->st_nlink);                                  /* Link count.  */
    printf("st_mode : %o\n", pStat->st_mode);                                     /* File mode.  */           
    printf("st_uid : %d\n", pStat->st_uid);                                       /* User ID of the file's owner.	*/
    printf("st_gid : %d\n", pStat->st_gid);                                       /* Group ID of the file's group.*/
    printf("st_rdev : %lu\n", pStat->st_rdev);                                    /* Device number, if device.  */
    printf("st_size : %ld\n", pStat->st_size);                                    /* Size of file, in bytes.  */
    printf("st_blksize : %ld\n", pStat->st_blksize);                              /* Optimal block size for I/O.  */
    printf("st_blocks : %ld\n", pStat->st_blocks);                                /* Number 512-byte blocks allocated. */
    printf("st_atime : %ld\n", pStat->st_atime);                                  /* Time of last access.  */
    // printf("st_atimensec : %d", pStat->st_atimensec);                        /* Nscecs of last access.  */
    printf("st_mtime : %ld\n", pStat->st_mtime);                                  /* Time of last modification.  */
    // printf("st_mtimensec : %d", pStat->st_mtimensec);                        /* Nsecs of last modification.  */
    printf("st_ctime : %ld\n", pStat->st_ctime);   	                            /* Time of last status change.  */
    // printf("st_ctimensec : %d", pStat->st_ctimensec);                        /* Nsecs of last status change.  */
    printf("__glibc_reserved[0] : %ld\n", pStat->__glibc_reserved[0]);   
    printf("__glibc_reserved[1] : %ld\n", pStat->__glibc_reserved[1]);   
    printf("__glibc_reserved[2] : %ld\n", pStat->__glibc_reserved[2]);   
    return;
}

// struct stat : /usr/include/x86_64-linux-gnu/bits/stat.h
void Stat(char* path, struct stat* pStat){
    printf("path : %s\n", path);
    printf("pStat address : %p\n", pStat);

    int ret;
    if((ret = stat(path, pStat)) < 0){
        fprintf(stderr, "stat func return %d\n", ret);
        perror("stat");
        exit(1);
    }
    PrintfStatus(pStat);
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr,"[usage] metadata <file_name>\n");
        exit(1);
    }
    struct stat status;
    // char* path = "./foo.txt";
    Stat(argv[1], &status);
    
    // Stat(argv[1], status);

    // struct stat *status;
    // char* path = "/home/turtlog/workspace/siso/1.system_level_io/foo.txt";
    // int fd;
    // int oflag = O_RDWR | O_CREAT;
    // if(fd = open(path, oflag) < 0){
    //     perror("open");
    //     exit(1);
    // }
    // printf("open : fd(%d)\n", fd);
    // Stat(path, status);
    return 0;
}
