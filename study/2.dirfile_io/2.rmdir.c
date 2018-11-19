#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
    if (argc != 2){
        fprintf(stderr, "[usage] 2.rmdir <directory_name>\n");
        exit(1);
    }
    int ret;
    if((ret = rmdir(argv[1])) < 0){
        perror("rmdir");
        exit(1);
    }
    return 0;
}