#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char** argv){
    if (argc != 2){
        fprintf(stderr, "[usage] 1.mkdir <directory_name>\n");
        exit(1);
    }

    int dirp;
    mode_t mode = 0775;
    if((dirp = mkdir(argv[1], mode)) < 0){
        perror("mkdir");
        exit(1);
    }
    return 0;
}