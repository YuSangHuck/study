// #include <string.h>
// #include <stdlib.h>     // qsort
// #include <stdio.h>

// typedef struct item{
//     int age;
//     char name[100];
// } item;

// int val_compare(const void* a, const void* b){
//     item *pa = (item*)a;
//     item *pb = (item*)b;
//     return strcmp(pa->name, pb->name);
// }

// int addr_compare(const void* a, const void* b){
//     item **pa = (item**)a;
//     item **pb = (item**)b;
//     return strcmp((*pa)->name, (*pb)->name);
// }

// int main(int argc, char** argv){
//     // item arr_items[10] = { 0, "abc",
//     //                        1, "bcd",
//     //                        2, "cde",
//     //                        3, "def",
//     //                        4, "ffg",
//     //                        5, "fgh",
//     //                        6, "ffi",
//     //                        7, "hij",
//     //                        8, "ijk",
//     //                        9, "jkl"};

//     // printf("------------------------------------\n");
//     // for(int i=0; i<10; i++){
//     //     printf("age : %d, name : %s\n", arr_items[i].age, arr_items[i].name);
//     // }
//     // printf("------------------------------------\n");

//     // qsort(arr_items, 10, sizeof(item), val_compare);
    
//     // printf("------------------------------------\n");
//     // for(int i=0; i<10; i++){
//     //     printf("age : %d, name : %s\n", arr_items[i].age, arr_items[i].name);
//     // }
//     // printf("------------------------------------\n");
    

//     item i0 = {0, "abc"};
//     item i1 = {1, "bcd"};
//     item i2 = {2, "cde"};
//     item i3 = {3, "def"};
//     item i4 = {4, "ffg"};
//     item i5 = {5, "fgh"};
//     item i6 = {6, "ffi"};
//     item i7 = {7, "hij"};
//     item i8 = {8, "ijk"};
//     item i9 = {9, "jkl"};
//     item* arr_pitem[10] = {&i0, &i1, &i2, &i3, &i4, &i5, &i6, &i7, &i8, &i9 };

//     printf("------------------------------------\n");
//     for(int i=0; i<10; i++){
//         printf("age : %d, name : %s\n", arr_pitem[i]->age, arr_pitem[i]->name);
//     }
//     printf("------------------------------------\n");

//     qsort(arr_pitem,10,sizeof(item*),addr_compare);

//     printf("------------------------------------\n");
//     for(int i=0; i<10; i++){
//         printf("age : %d, name : %s\n", arr_pitem[i]->age, arr_pitem[i]->name);
//     }
//     printf("------------------------------------\n");

//     return 0;
// }

// #include <stdlib.h>

// int main(){
//     system("ls");
//     return 0;
// }





// #include <sys/types.h>
// #include <regex.h>
// #include <stdio.h>
// #define MAX_NUM 10



// int main(int argc, char *argv[])
// {
//   regex_t state;
//   const char *urls[] = {
//     "https://www.naver.com/",
//     "sasdfsf",
//     "httpa://www.naver.com/asdf"
//   };
//   const char *pattern = "^(file|gopher|news|nntp|telnet|https?|ftps?|sftp):\/\/([a-z0-9-]+\.)+[a-z0-9]{2,4}.*$";

//   int index;
//   //compile
//   regcomp(&state, pattern, REG_EXTENDED);

//   for (index = 0; index < 3; index++) {
//     regmatch_t nm[MAX_NUM];


//     //check
//     int status = regexec(&state, urls[index], MAX_NUM, nm, 0);
//     printf("S_offset=[%d],E_offset[%d]\n", nm[0].rm_so, nm[0].rm_eo);
//     if(status==0)
//         printf("match : %s\n", urls[index]);
//     else
//         printf("unmatch : %s\n", urls[index]);
//   }

//   return 0;
// }

// #include <sys/types.h>
// #include <regex.h>
// #include <stdio.h>
// #include <stdlib.h>
// #define        NUMBER        10
// int main(int argc, char *argv[]){
//     regex_t mregex;
//     regmatch_t mt[NUMBER];
//     int reti;
//     char msgbuf[100];

//     /* Compile regular expression */
//     const char formats[2][50] = {"\n[^:]*:x:1000:1000",
//                                 "x:1000:1000:[^,]*"   };
//     for(int i=0; i<2; i++){
//         reti = regcomp(&mregex, formats[i], 0);
//         if( reti ){ fprintf(stderr, "Could not compile regex\n"); exit(1); }


//         /* Execute regular expression */
//         char str[] = "rtkit:x:118:126:RealtimeKit,,,:/proc:/bin/false\nsaned:x:119:127::/var/lib/saned:/bin/false\nusbmux:x:120:46:usbmux daemon,,,:/var/lib/usbmux:/bin/false\nturtlog:x:1000:1000:turtlog,,,:/home/turtlog:/bin/bash";
//         reti = regexec(&mregex, str, NUMBER, mt, 0);
//         if( !reti ){
//             puts("Match");
//             printf("[%d][%d]\n",mt[0].rm_so, mt[0].rm_eo);
//             for(int i = mt[0].rm_so; i<mt[0].rm_eo; i++)
//                 printf("%c", str[i]);
//         }
//         else if( reti == REG_NOMATCH ){
//             puts("No match");
//         }
//     }

//     /* Free compiled regular expression if you want to use the regex_t again */
//     regfree(&mregex);

//     return 0;
// }

// #include <stdio.h>
 
// int main (void)
// {    
//     char buffer[256]="name:홍길동 num:12 age:20";
//     char name[30] = {0,};
//     int num = -1;
//     int age = -1;
    
//     //버퍼의 내용을 이름, 번호, 나이 변수에 설정
//     sscanf(buffer,"num:%d",&num);
//     //이름, 번호, 나이 출력
//     printf("이름:%s 번호:%d 나이:%d \n",name,num,age);
//     return 0;
// }


// #include <fcntl.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <sys/stat.h>
// int main(){
//     char reading[4096];
//     int fd;
//     if((fd = open("/etc/passwd", O_RDONLY)) < 0){
//         perror("open /etc/passwd");
//         exit(1);
//     }
//     int ret;
//     if((ret = read(fd, reading, 4096)) < 0){
//         perror("read /etc/passwd");
//         exit(1);
//     }
//     // printf("/*reading*/\n%s\n", reading);
//     printf("  test\n");
//     for(int i=30; i<33; i++){
//         printf("%d ", reading[i]);
//     }
//     printf("\n line-ending : %d\n", '\n');
//     return 0;
// }

// #include <stdio.h>
// #include <string.h>

// int main(){
//     char arr[255] = { 0, };
//     int ret = 0;
//     ret = sprintf(arr + ret, "├──");
//     printf("%s\n", arr);
//     ret = sprintf(arr + ret, "    ");
//     printf("%s\n", arr);
//     ret = sprintf(arr + ret, "├──");
//     printf("%s\n", arr);
//     ret = sprintf(arr + ret, "└──");
//     printf("%s\n", arr);
    
//     printf("├── hw\n");
//     printf("│   └── hw1\n");
//     printf("│       ├── a\n");
//     printf("│       ├── b\n");
//     printf("│       │   ├── c\n");


//     // for(int i=0; i<10; i++)
//     //     printf("%c", arr[i]);
//     char* cp = arr;
//     printf("%hhu ", cp[0]);
//     printf("%hhu ", cp[1]);
//     printf("%hhu ", cp[2]);
//     printf("%hhu\n", cp[3]);
//     // printf("%s\n", arr);

//     char arr1[] = "├──";
//     // char arr2[] = "    ";
//     // char arr3[] = "├──";
//     strcat(arr1, "    ");
//     strcat(arr1, "├──");
//     printf("%s\n", arr1);
//     return 0;
// }


#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <stdlib.h>

// ap_tree_struct를 아래처럼 만들어주는 함수
// ├──
// │   └──
// │       ├──
// │       ├──
// │       │   ├──
int SetTreeStruct(char* ap_tree_struct, char* ap_trace_depth, int a_depth){
    if(ap_tree_struct == NULL || ap_trace_depth == NULL)
        return 1;
    
    printf("[log] ap_tree_struct\t%s\n", ap_tree_struct);
    printf("[log] ap_trace_depth\t%s\n", ap_trace_depth);
    printf("[log] a_depth\t%d\n", a_depth);

    printf("[log] ap_tree_struct addr\t%x\n", ap_tree_struct);
    printf("[log] ap_trace_depth addr\t%x\n", ap_trace_depth);

    if(a_depth == 0){
        if(ap_trace_depth[a_depth] == 1)
            strcat(ap_tree_struct, "├──");
        else if(ap_trace_depth[a_depth] == 2)
            strcat(ap_tree_struct, "└──");
    }
    else{
        for(int i=0; i<=a_depth; i++){
            // ap_trace_depth[i] : ' '(0), '├'(1), '└'(2)
            // i와 i+1 검사
            if(ap_trace_depth[i] == 0){
                strcat(ap_tree_struct, "    ");
                // ret = sprintf(ap_tree_struct + ret, "    ");
            }
            else if(ap_trace_depth[i] == 1){
                if(ap_trace_depth[i + 1] == 0){
                    strcat(ap_tree_struct, "├   ");
                    // ret = sprintf(ap_tree_struct + ret, "├   ");
                }
                else{
                    strcat(ap_tree_struct, "├──");
                    // ret = sprintf(ap_tree_struct + ret, "├──");
                }
            }
            else if(ap_trace_depth[i] == 2){
                if(ap_trace_depth[i + 1] == 0){
                    strcat(ap_tree_struct, "└   ");
                    // ret = sprintf(ap_tree_struct + ret, "└   ");
                }
                else{
                    strcat(ap_tree_struct, "└──");
                    // ret = sprintf(ap_tree_struct + ret, "└──");
                }
            }
            else{
                fprintf(stderr, "#error# : unexpectd\n");
            }
        }
    }
    return 0;
}

// info를 "[%7lu %lu %10s %-8s %5s] %s"의 형태로 만들어주는 함수
int SetInfo(char* ap_info, const struct stat* ap_st, const char* ap_dname){
    if(ap_info == NULL || ap_st == NULL || ap_dname == NULL)
        return 1;
    
    // 4.3.퍼미션 변환  ap_st->st_mode
    char permision[11] = { 0, };
    // 4.3.1.파일종류확인
    if(S_ISLNK(ap_st->st_mode))          permision[0] = 'l';
    else if(S_ISREG(ap_st->st_mode))     permision[0] = '-';
    else if(S_ISDIR(ap_st->st_mode))     permision[0] = 'd';
    else if(S_ISCHR(ap_st->st_mode))     permision[0] = 'c';
    else if(S_ISBLK(ap_st->st_mode))     permision[0] = 'b';
    else if(S_ISFIFO(ap_st->st_mode))    permision[0] = 'p';
    else if(S_ISSOCK(ap_st->st_mode))    permision[0] = 's';
    else{
        fprintf(stderr, "#error# : unexpectd\n");
    }
    
    // 4.3.2.user 권한 설정
    if(ap_st->st_mode & S_IRUSR)         permision[1] = 'r';
    else                                 permision[1] = '-';
    if(ap_st->st_mode & S_IWUSR)         permision[2] = 'w';
    else                                 permision[2] = '-';
    if(ap_st->st_mode & S_IXUSR)         permision[3] = 'x';
    else                                 permision[3] = '-';

    // 4.3.3.group 권한설정
    if(ap_st->st_mode & S_IRGRP)         permision[4] = 'r';
    else                                 permision[4] = '-';
    if(ap_st->st_mode & S_IWGRP)         permision[5] = 'w';
    else                                 permision[5] = '-';
    if(ap_st->st_mode & S_IXGRP)         permision[6] = 'x';
    else                                 permision[6] = '-';
    
    // 4.3.4.others 권한설정
    if(ap_st->st_mode & S_IROTH)        permision[7] = 'r';
    else                                permision[7] = '-';
    if(ap_st->st_mode & S_IWOTH)        permision[8] = 'w';
    else                                permision[8] = '-';
    if(ap_st->st_mode & S_IXOTH)        permision[9] = 'x';
    else                                permision[9] = '-';
    
    // 4.3.5.이름 변환    ap_st->st_uid
    // reading으로 /etc/passwd의 파일을 전부 읽어옴
    // 직접 passwd파일을 열어서 읽고 정규표현식으로 필터링 해도 되지만
    // 만들어져 있는 getpwuid함수를 이용하자 ㅎㅎ
    char username[50] = { 0, };
    struct passwd* pw;
    pw = getpwuid(ap_st->st_uid);
    // printf("[log]\tpasswd->pw_name %s\n", passwd->pw_name);
    sprintf(username, "%s", pw->pw_name);

    // 4.3.6.사이즈 변환  ap_st->size
    char size[10] = { 0, };
    double s = ap_st->st_size;
    int cnt = 0;
    while(s > 1024){
        s /= 1024;
        cnt++;
    }
    if(cnt == 0)            sprintf(size, "%.1lf", s);
    else if(cnt == 1)       sprintf(size, "%.1lfK", s);
    else if(cnt == 2)       sprintf(size, "%.1lfM", s);
    else if(cnt == 3)       sprintf(size, "%.1lfG", s);
    else if(cnt == 4)       sprintf(size, "%.1lfT", s);
    else if(cnt == 5)       sprintf(size, "%.1lfP", s);
    else{
        fprintf(stderr, "#error# : unexpectd\n");
    }

    sprintf(ap_info, "[%7lu %lu %10s %-8s %5s] %s", ap_st->st_ino,
                                                    ap_st->st_dev,
                                                    permision, // st
                                                    username,  // st
                                                    size,      // st
                                                    ap_dname);
    return 0;
}

int main(int argc, char** argv){

    char tree_struct[512] = { 0, };
    char trace_depth[255] = { 0, };
    int depth = 0;

    trace_depth[0] = 1;
    SetTreeStruct(tree_struct, trace_depth, depth);
    // printf("%s\n", tree_struct);

    char info[255] = { 0, };
    struct stat st;
    int ret;
    char dname[] = "test.c";
    if(ret = stat(dname, &st) < 0){
        perror("stat");
        exit(1);
    }
    printf("?%s?\n", info);
    printf("?%x?\n", &st);
    printf("?%s?\n", dname);
    SetInfo(info, &st, dname);
    // printf("%s\n", info);

    char result[255] = { 0, };
    sprintf(result, "%s %s", tree_struct, info);
    printf("%s\n", result);
    return 0;
}