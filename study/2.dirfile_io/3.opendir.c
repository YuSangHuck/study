#include <dirent.h>         // opendir, DIR
#include <stdio.h>          // perror, fprintf, stderr
#include <stdlib.h>         // exit
// #include <sys/types.h>   

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "[usage] 3.opendir <directory_name>\n");
        exit(1);
    }
    
    DIR* dirp;
    if((dirp = opendir(argv[1])) == NULL){
        perror("opendir");
        exit(1);
    }

    return 0;
}