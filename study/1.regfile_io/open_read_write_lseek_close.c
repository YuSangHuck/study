// open
// O_RDONLY
#include <stdio.h>      // perror
#include <stdlib.h>     // exit, printf
#include <unistd.h>     // close
#include <sys/stat.h>   // open
#include <fcntl.h>      // open

void ShowManual(){
    fprintf(stderr, "#######################\n# 1 : read\n# 2 : write\n# 3 : lseek\n# 4 : close\n#######################\n");
}
int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "[usage] open_read_write_lseek_close <file_name>\n");
        exit(1);
    }

    // open
    int fd;
    int oflag = O_RDWR | O_APPEND | O_CREAT;
    int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
    if ((fd = open(argv[1], oflag, mode)) < 0) {
        perror("open");
        exit(1);
    }
    fprintf(stderr,"open : fd(%s) : %d\n", argv[1], fd);

    while(1){
        ShowManual();
        int op;
        scanf("%d", &op);
        // read
        if(op == 1){
            fprintf(stderr, "put sp,ep : ");
            int sp,ep;
            scanf("%d,%d", &sp, &ep);
            if(ep-sp > 512){
                fprintf(stderr, "condition : ep - sp <= 512");
            }
            __off_t seek;
            if((seek = lseek(fd, sp, SEEK_SET)) < 0){
                perror("lseek");
            }
            fprintf(stderr, "seek : %d\n", seek);

            char r_buf[512] = { 0, };
            int nbytes;
            if((nbytes = read(fd, r_buf, ep-sp)) < 0){
                perror("read");
            }
            fprintf(stderr, "%s\n", r_buf);
            fprintf(stderr, "SEEK_CUR : %d\n", SEEK_CUR);
        }
        // write
        else if(op == 2){

        }
        // lseek
        else if(op == 3){

        }
        // close
        else if(op == 4){

        }
        else{

        }
    }
    // printf("open : fd(%s) : %d\n", path, fd);
    // fprintf(STDERR_FILENO,"open : fd(%s) : %d\n", path, fd);

    // // read
    // char r_buf[512];
    // int nbytes;
    // if ((nbytes = read(fd, r_buf, sizeof(r_buf))) < 0) {
    //     perror("read");
    //     exit(1);
    // }
    // printf("read : %d bytes\n", nbytes);
    // printf("%s\n", r_buf);
    
    // // lseek
    // __off_t f_offset;
    // if((f_offset = lseek(fd, 0, SEEK_CUR)) < 0){
    //     perror("lseek, SEEK_INIT");
    //     exit(1);
    // }
    // printf("cur_pos : %ld\n", f_offset);
    // while(1){
    //     int f_pos;
    //     printf("file offset :");
    //     f_pos = getc(stdin);
    //     printf("f_pos %d\n", f_pos);
    //     // scanf("%d", &f_pos);
    //     if(f_pos = 'q')
    //         break;
    //     if((f_offset = lseek(fd, f_pos, SEEK_CUR)) < 0){
    //         perror("lseek, SEEK_MOVE");
    //         exit(1);
    //     }
    //     printf("cur_pos : %ld\n", f_offset);
    // }
    
    
    // // write
    // char w_buf[512];
    // printf("write string :");
    // scanf("%s", w_buf);
    // if ((nbytes = write(fd, w_buf, sizeof(w_buf)) < 0)) {
    //     perror("write");
    //     exit(1);
    // }
    // printf("write : nbytes:%d\n", nbytes);

    // // read

    // // close
    // int ret;
    // if((ret = close(fd)) < 0){
    //     perror("close");
    //     exit(1);
    // }
    // printf("close : fd(%s) : %d\n", path, fd);
    return 0;
}
