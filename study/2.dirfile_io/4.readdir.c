#include <stdio.h>          // stderr
#include <stdlib.h>         // exit
#include <dirent.h>         // DIR, opendir, readdir

void PrintDirent(struct dirent* ap_dirent){
    printf("----------------------------------\n");
    printf("d_ino<__ino_t> : %lu\n", ap_dirent->d_ino);
    printf("d_off<__off_t> : %lu\n", ap_dirent->d_off);
    printf("d_reclen<unsigned short int> : %uh\n", ap_dirent->d_reclen);
    printf("d_type<unsigned char> : %o\n", ap_dirent->d_type);
    printf("d_name<char*> : %s\n", ap_dirent->d_name);
    printf("----------------------------------\n");
    return;
}
int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "[usage] 4.readdir <directory_name>\n");
        exit(1);
    }
    
    DIR* dirp;
    if((dirp = opendir(argv[1])) == NULL){
        perror("opendir");
        exit(1);
    }
    struct dirent* p_dirent;
    while((p_dirent = readdir(dirp)) != NULL) {
        PrintDirent(p_dirent);
    }

    return 0;
}