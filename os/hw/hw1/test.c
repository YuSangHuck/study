// // // #include <string.h>
// // // #include <stdlib.h>     // qsort
// // // #include <stdio.h>

// // // typedef struct item{
// // //     int age;
// // //     char name[100];
// // // } item;

// // // int val_compare(const void* a, const void* b){
// // //     item *pa = (item*)a;
// // //     item *pb = (item*)b;
// // //     return strcmp(pa->name, pb->name);
// // // }

// // // int addr_compare(const void* a, const void* b){
// // //     item **pa = (item**)a;
// // //     item **pb = (item**)b;
// // //     return strcmp((*pa)->name, (*pb)->name);
// // // }

// // // int main(int argc, char** argv){
// // //     // item arr_items[10] = { 0, "abc",
// // //     //                        1, "bcd",
// // //     //                        2, "cde",
// // //     //                        3, "def",
// // //     //                        4, "ffg",
// // //     //                        5, "fgh",
// // //     //                        6, "ffi",
// // //     //                        7, "hij",
// // //     //                        8, "ijk",
// // //     //                        9, "jkl"};

// // //     // printf("------------------------------------\n");
// // //     // for(int i=0; i<10; i++){
// // //     //     printf("age : %d, name : %s\n", arr_items[i].age, arr_items[i].name);
// // //     // }
// // //     // printf("------------------------------------\n");

// // //     // qsort(arr_items, 10, sizeof(item), val_compare);
    
// // //     // printf("------------------------------------\n");
// // //     // for(int i=0; i<10; i++){
// // //     //     printf("age : %d, name : %s\n", arr_items[i].age, arr_items[i].name);
// // //     // }
// // //     // printf("------------------------------------\n");
    

// // //     item i0 = {0, "abc"};
// // //     item i1 = {1, "bcd"};
// // //     item i2 = {2, "cde"};
// // //     item i3 = {3, "def"};
// // //     item i4 = {4, "ffg"};
// // //     item i5 = {5, "fgh"};
// // //     item i6 = {6, "ffi"};
// // //     item i7 = {7, "hij"};
// // //     item i8 = {8, "ijk"};
// // //     item i9 = {9, "jkl"};
// // //     item* arr_pitem[10] = {&i0, &i1, &i2, &i3, &i4, &i5, &i6, &i7, &i8, &i9 };

// // //     printf("------------------------------------\n");
// // //     for(int i=0; i<10; i++){
// // //         printf("age : %d, name : %s\n", arr_pitem[i]->age, arr_pitem[i]->name);
// // //     }
// // //     printf("------------------------------------\n");

// // //     qsort(arr_pitem,10,sizeof(item*),addr_compare);

// // //     printf("------------------------------------\n");
// // //     for(int i=0; i<10; i++){
// // //         printf("age : %d, name : %s\n", arr_pitem[i]->age, arr_pitem[i]->name);
// // //     }
// // //     printf("------------------------------------\n");

// // //     return 0;
// // // }

// // // #include <stdlib.h>

// // // int main(){
// // //     system("ls");
// // //     return 0;
// // // }





// // // #include <sys/types.h>
// // // #include <regex.h>
// // // #include <stdio.h>
// // // #define MAX_NUM 10



// // // int main(int argc, char *argv[])
// // // {
// // //   regex_t state;
// // //   const char *urls[] = {
// // //     "https://www.naver.com/",
// // //     "sasdfsf",
// // //     "httpa://www.naver.com/asdf"
// // //   };
// // //   const char *pattern = "^(file|gopher|news|nntp|telnet|https?|ftps?|sftp):\/\/([a-z0-9-]+\.)+[a-z0-9]{2,4}.*$";

// // //   int index;
// // //   //compile
// // //   regcomp(&state, pattern, REG_EXTENDED);

// // //   for (index = 0; index < 3; index++) {
// // //     regmatch_t nm[MAX_NUM];


// // //     //check
// // //     int status = regexec(&state, urls[index], MAX_NUM, nm, 0);
// // //     printf("S_offset=[%d],E_offset[%d]\n", nm[0].rm_so, nm[0].rm_eo);
// // //     if(status==0)
// // //         printf("match : %s\n", urls[index]);
// // //     else
// // //         printf("unmatch : %s\n", urls[index]);
// // //   }

// // //   return 0;
// // // }

// // // #include <sys/types.h>
// // // #include <regex.h>
// // // #include <stdio.h>
// // // #include <stdlib.h>
// // // #define        NUMBER        10
// // // int main(int argc, char *argv[]){
// // //     regex_t mregex;
// // //     regmatch_t mt[NUMBER];
// // //     int reti;
// // //     char msgbuf[100];

// // //     /* Compile regular expression */
// // //     const char formats[2][50] = {"\n[^:]*:x:1000:1000",
// // //                                 "x:1000:1000:[^,]*"   };
// // //     for(int i=0; i<2; i++){
// // //         reti = regcomp(&mregex, formats[i], 0);
// // //         if( reti ){ fprintf(stderr, "Could not compile regex\n"); exit(1); }


// // //         /* Execute regular expression */
// // //         char str[] = "rtkit:x:118:126:RealtimeKit,,,:/proc:/bin/false\nsaned:x:119:127::/var/lib/saned:/bin/false\nusbmux:x:120:46:usbmux daemon,,,:/var/lib/usbmux:/bin/false\nturtlog:x:1000:1000:turtlog,,,:/home/turtlog:/bin/bash";
// // //         reti = regexec(&mregex, str, NUMBER, mt, 0);
// // //         if( !reti ){
// // //             puts("Match");
// // //             printf("[%d][%d]\n",mt[0].rm_so, mt[0].rm_eo);
// // //             for(int i = mt[0].rm_so; i<mt[0].rm_eo; i++)
// // //                 printf("%c", str[i]);
// // //         }
// // //         else if( reti == REG_NOMATCH ){
// // //             puts("No match");
// // //         }
// // //     }

// // //     /* Free compiled regular expression if you want to use the regex_t again */
// // //     regfree(&mregex);

// // //     return 0;
// // // }

// // // #include <stdio.h>
 
// // // int main (void)
// // // {    
// // //     char buffer[256]="name:홍길동 num:12 age:20";
// // //     char name[30] = {0,};
// // //     int num = -1;
// // //     int age = -1;
    
// // //     //버퍼의 내용을 이름, 번호, 나이 변수에 설정
// // //     sscanf(buffer,"num:%d",&num);
// // //     //이름, 번호, 나이 출력
// // //     printf("이름:%s 번호:%d 나이:%d \n",name,num,age);
// // //     return 0;
// // // }


// // // #include <fcntl.h>
// // // #include <stdlib.h>
// // // #include <stdio.h>
// // // #include <sys/stat.h>
// // // int main(){
// // //     char reading[4096];
// // //     int fd;
// // //     if((fd = open("/etc/passwd", O_RDONLY)) < 0){
// // //         perror("open /etc/passwd");
// // //         exit(1);
// // //     }
// // //     int ret;
// // //     if((ret = read(fd, reading, 4096)) < 0){
// // //         perror("read /etc/passwd");
// // //         exit(1);
// // //     }
// // //     // printf("/*reading*/\n%s\n", reading);
// // //     printf("  test\n");
// // //     for(int i=30; i<33; i++){
// // //         printf("%d ", reading[i]);
// // //     }
// // //     printf("\n line-ending : %d\n", '\n');
// // //     return 0;
// // // }

// // // #include <stdio.h>
// // // #include <string.h>

// // // int main(){
// // //     char arr[255] = { 0, };
// // //     int ret = 0;
// // //     ret = sprintf(arr + ret, "├──");
// // //     printf("%s\n", arr);
// // //     ret = sprintf(arr + ret, "    ");
// // //     printf("%s\n", arr);
// // //     ret = sprintf(arr + ret, "├──");
// // //     printf("%s\n", arr);
// // //     ret = sprintf(arr + ret, "└──");
// // //     printf("%s\n", arr);
    
// // //     printf("├── hw\n");
// // //     printf("│   └── hw1\n");
// // //     printf("│       ├── a\n");
// // //     printf("│       ├── b\n");
// // //     printf("│       │   ├── c\n");


// // //     // for(int i=0; i<10; i++)
// // //     //     printf("%c", arr[i]);
// // //     char* cp = arr;
// // //     printf("%hhu ", cp[0]);
// // //     printf("%hhu ", cp[1]);
// // //     printf("%hhu ", cp[2]);
// // //     printf("%hhu\n", cp[3]);
// // //     // printf("%s\n", arr);

// // //     char arr1[] = "├──";
// // //     // char arr2[] = "    ";
// // //     // char arr3[] = "├──";
// // //     strcat(arr1, "    ");
// // //     strcat(arr1, "├──");
// // //     printf("%s\n", arr1);
// // //     return 0;
// // // }


// #include <stdio.h>
// #include <string.h>
// #include <sys/stat.h>
// #include <pwd.h>
// #include <stdlib.h>
// #include <fcntl.h>

// // ap_tree_struct를 아래처럼 만들어주는 함수
// // ├──
// // │   └──
// // │       ├──
// // │       ├──
// // │       │   ├──
// int SetTreeStruct(char* ap_tree_struct, char* ap_trace_depth, int a_depth){
//     if(ap_tree_struct == NULL || ap_trace_depth == NULL)
//         return 1;
    
//     printf("[log] ap_tree_struct\t%s\n", ap_tree_struct);
//     printf("[log] ap_trace_depth\t%s\n", ap_trace_depth);
//     printf("[log] a_depth\t%d\n", a_depth);

//     printf("[log] ap_tree_struct addr\t%x\n", ap_tree_struct);
//     printf("[log] ap_trace_depth addr\t%x\n", ap_trace_depth);

//     if(a_depth == 0){
//         if(ap_trace_depth[a_depth] == 1)
//             strcat(ap_tree_struct, "├──");
//         else if(ap_trace_depth[a_depth] == 2)
//             strcat(ap_tree_struct, "└──");
//     }
//     else{
//         for(int i=0; i<=a_depth; i++){
//             // ap_trace_depth[i] : ' '(0), '├'(1), '└'(2)
//             // i와 i+1 검사
//             if(ap_trace_depth[i] == 0){
//                 strcat(ap_tree_struct, "    ");
//                 // ret = sprintf(ap_tree_struct + ret, "    ");
//             }
//             else if(ap_trace_depth[i] == 1){
//                 if(ap_trace_depth[i + 1] == 0){
//                     strcat(ap_tree_struct, "├   ");
//                     // ret = sprintf(ap_tree_struct + ret, "├   ");
//                 }
//                 else{
//                     strcat(ap_tree_struct, "├──");
//                     // ret = sprintf(ap_tree_struct + ret, "├──");
//                 }
//             }
//             else if(ap_trace_depth[i] == 2){
//                 if(ap_trace_depth[i + 1] == 0){
//                     strcat(ap_tree_struct, "└   ");
//                     // ret = sprintf(ap_tree_struct + ret, "└   ");
//                 }
//                 else{
//                     strcat(ap_tree_struct, "└──");
//                     // ret = sprintf(ap_tree_struct + ret, "└──");
//                 }
//             }
//             else{
//                 fprintf(stderr, "#error# : unexpectd\n");
//             }
//         }
//     }
//     return 0;
// }

// // info를 "[%7lu %lu %10s %-8s %5s] %s"의 형태로 만들어주는 함수
// int SetInfo(char* ap_info, const struct stat* ap_st, const char* ap_dname){
//     if(ap_info == NULL || ap_st == NULL || ap_dname == NULL)
//         return 1;
    
//     // 4.3.퍼미션 변환  ap_st->st_mode
//     char permision[11] = { 0, };
//     // 4.3.1.파일종류확인
//     if(S_ISLNK(ap_st->st_mode))          permision[0] = 'l';
//     else if(S_ISREG(ap_st->st_mode))     permision[0] = '-';
//     else if(S_ISDIR(ap_st->st_mode))     permision[0] = 'd';
//     else if(S_ISCHR(ap_st->st_mode))     permision[0] = 'c';
//     else if(S_ISBLK(ap_st->st_mode))     permision[0] = 'b';
//     else if(S_ISFIFO(ap_st->st_mode))    permision[0] = 'p';
//     else if(S_ISSOCK(ap_st->st_mode))    permision[0] = 's';
//     else{
//         fprintf(stderr, "#error# : unexpectd\n");
//     }
    
//     // 4.3.2.user 권한 설정
//     if(ap_st->st_mode & S_IRUSR)         permision[1] = 'r';
//     else                                 permision[1] = '-';
//     if(ap_st->st_mode & S_IWUSR)         permision[2] = 'w';
//     else                                 permision[2] = '-';
//     if(ap_st->st_mode & S_IXUSR)         permision[3] = 'x';
//     else                                 permision[3] = '-';

//     // 4.3.3.group 권한설정
//     if(ap_st->st_mode & S_IRGRP)         permision[4] = 'r';
//     else                                 permision[4] = '-';
//     if(ap_st->st_mode & S_IWGRP)         permision[5] = 'w';
//     else                                 permision[5] = '-';
//     if(ap_st->st_mode & S_IXGRP)         permision[6] = 'x';
//     else                                 permision[6] = '-';
    
//     // 4.3.4.others 권한설정
//     if(ap_st->st_mode & S_IROTH)        permision[7] = 'r';
//     else                                permision[7] = '-';
//     if(ap_st->st_mode & S_IWOTH)        permision[8] = 'w';
//     else                                permision[8] = '-';
//     if(ap_st->st_mode & S_IXOTH)        permision[9] = 'x';
//     else                                permision[9] = '-';
    
//     // 4.3.5.이름 변환    ap_st->st_uid
//     // reading으로 /etc/passwd의 파일을 전부 읽어옴
//     // 직접 passwd파일을 열어서 읽고 정규표현식으로 필터링 해도 되지만
//     // 만들어져 있는 getpwuid함수를 이용하자 ㅎㅎ
//     char username[50] = { 0, };
//     struct passwd* pw;
//     pw = getpwuid(ap_st->st_uid);
//     // printf("[log]\tpasswd->pw_name %s\n", passwd->pw_name);
//     sprintf(username, "%s", pw->pw_name);

//     // 4.3.6.사이즈 변환  ap_st->size
//     char size[10] = { 0, };
//     double s = ap_st->st_size;
//     int cnt = 0;
//     while(s > 1024){
//         s /= 1024;
//         cnt++;
//     }
//     if(cnt == 0)            sprintf(size, "%.1lf", s);
//     else if(cnt == 1)       sprintf(size, "%.1lfK", s);
//     else if(cnt == 2)       sprintf(size, "%.1lfM", s);
//     else if(cnt == 3)       sprintf(size, "%.1lfG", s);
//     else if(cnt == 4)       sprintf(size, "%.1lfT", s);
//     else if(cnt == 5)       sprintf(size, "%.1lfP", s);
//     else{
//         fprintf(stderr, "#error# : unexpectd\n");
//     }

//     sprintf(ap_info, "[%7lu %lu %10s %-8s %5s] %s", ap_st->st_ino,
//                                                     ap_st->st_dev,
//                                                     permision, // st
//                                                     username,  // st
//                                                     size,      // st
//                                                     ap_dname);
//     return 0;
// }

// int main(int argc, char** argv){

//     char tree_struct[512] = { 0, };
//     char trace_depth[255] = { 0, };
//     int depth = 0;

//     trace_depth[0] = 1;
//     SetTreeStruct(tree_struct, trace_depth, depth);
//     // printf("%s\n", tree_struct);

//     char info[255] = { 0, };
//     struct stat st;
//     int ret;
//     char dname[] = "a_b";
//     int fd = open(dname, O_RDONLY);
//     printf("fd : %d\n", fd);
//     // if(ret = lstat(dname, &st) < 0){
//     if(ret = fstat(fd, &st) < 0){
//         perror("stat");
//         exit(1);
//     }
//     printf("?%s?\n", info);
//     printf("?%x?\n", &st);
//     printf("?%s?\n", dname);
//     SetInfo(info, &st, dname);
//     // printf("%s\n", info);

//     char result[255] = { 0, };
//     sprintf(result, "%s %s", tree_struct, info);
//     printf("%s\n", result);
//     return 0;
// }

// // #include <sys/stat.h>
// // #include <dirent.h>
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <unistd.h>             // getcwd, chdir
// // #include <string.h>

// // #define MAX_CNT_DIRENT  0xfff
// // #define MAX_FILENAME    0xff
// // // int compare(const void *a, const void *b){
// // //     struct dirent** pa = (struct dirent **)a;
// // //     struct dirent** pb = (struct dirent **)b;
// // //     return strcmp((*pa)->d_name,(*pb)->d_name);
// // // }
// // // int DirentSort(struct dirent** ap_dirent, int a_cnt_dirent){
// // //     qsort(ap_dirent, a_cnt_dirent, sizeof(struct dirent*), compare);
// // // }
// // int compare(const void *a, const void *b){
// //     char* pa = (char*)a;
// //     char* pb = (char*)b;
    
// //     return strcmp(a, b);
// // }
// // int DirentSort(char** ap_dirent_name, int a_cnt_dirent){
// //     qsort(ap_dirent_name, a_cnt_dirent, sizeof(char[MAX_FILENAME]), compare);
// // }
// // int main(int argc, char** argv){
// //     char* start_dir;
// //     if(argc == 1)   start_dir = ".";
// //     if(argc == 2)   start_dir = argv[1];
    
// //     if((chdir(start_dir)) < 0){
// //         perror(start_dir);
// //         exit(1);
// //     }
// //     char pwd[255];
// //     getcwd(pwd, 255);


// //     DIR* p_dir;
// //     if((p_dir = opendir(pwd)) == NULL){
// //         perror("opendir");
// //         return 1;
// //     }

// //     // 1.dirent*의 주소를 저장하는 포인터 배열 선언 후 배열에 dirent*들을 저장.(".", ".."는 제외)
// //     //  배열의 개수도 카운트 해야 함.
// //     //  배열의 갯수가 너무 많아지면 주소 할당이 꼬이는듯?
// //     //   그래서 readdir 직후 p_dirent->d_name과 cnt_dirent 정상이지만
// //     //   p_arr_dirent의 각 요소에 접근해보면 엉망진창.
// //     //   이 엉망진창인걸 sorting하니 역시 엉망진창.
// //     //   그 뒤에가 다 꼬임. sprint("%s/%s")에서 뒤에 %s에 ""가 들어가는것.(line 170)
// //     // struct dirent* p_arr_dirent[MAX_CNT_DIRENT];
// //     char p_arr_dirent_name[MAX_CNT_DIRENT][MAX_FILENAME];
// //     int cnt_dirent = 0;
// //     struct dirent* p_dirent;
// //     while((p_dirent = readdir(p_dir)) != NULL){
// //         printf("[log] d_name(%d)\t%s\n", p_dirent, p_dirent->d_name);
// //         // getc(stdin);
// //         if(p_dirent->d_name[0] == '.')
// //             continue;
// //         // p_arr_dirent[cnt_dirent++] = p_dirent;
// //         strcpy(p_arr_dirent_name[cnt_dirent++], p_dirent->d_name);
// //         // printf("%d  %s\n", cnt_dirent, p_arr_dirent_name[cnt_dirent - 1]);
// //     }
// //     // printf(" [log] cnt_dirent\t%d\n", cnt_dirent);
// //     // 2.direct->name 기준으로 오름차순 정렬.
// //     printf(" [log] before sorting\n");
// //     for(int i=0; i<cnt_dirent; i++){
// //         // printf("   [log] d_name(%d)\t%s\n", p_arr_dirent[i], p_arr_dirent[i]->d_name);
// //         // printf("   [log] d_name(%d)\t%s\n", p_arr_dirent_name[i], p_arr_dirent_name[i]);
// //     }
// //     // DirentSort(p_arr_dirent, cnt_dirent);
// //     DirentSort(p_arr_dirent_name, cnt_dirent);
// //     printf(" [log] after sorting\n");
// //     for(int i=0; i<cnt_dirent; i++){
// //         // printf("   [log] d_name(%d)\t%s\n", p_arr_dirent[i], p_arr_dirent[i]->d_name);
// //         // printf("   [log] d_name(%d)\t%s\n", p_arr_dirent_name[i], p_arr_dirent_name[i]);
// //     }
// // }

// // #include <stdio.h>
// // #include <string.h>
// // int main(){
// //     printf("%d\n", strlen("a"));
// //     printf("%d\n", strlen("ㄱ"));
// //     printf("%d\n", strlen("/home/turtlog/study/1.SystmeSoftware/3.실습/2.스케쥴러/상혁/HW1_내가 하던거/Debug/HW1.tlog"));
// // }

// // #define _GNU_SOURCE
// // #include <dirent.h>     /* Defines DT_* constants */
// // #include <fcntl.h>
// // #include <stdio.h>
// // #include <unistd.h>
// // #include <stdlib.h>
// // #include <sys/stat.h>
// // #include <sys/syscall.h>

// // #define handle_error(msg) \
// //         { perror(msg); exit(EXIT_FAILURE); }

// // struct linux_dirent {
// //     long           d_ino;
// //     off_t          d_off;
// //     unsigned short d_reclen;
// //     char           d_name[];
// // };
// // // struct dirent {
// // //     __ino_t d_ino;
// // //     __off_t d_off;
// // //     unsigned short int d_reclen;
// // //     unsigned char d_type;
// // //     char d_name[256];		/* We must not include limits.h! */
// // // };
// // #define BUF_SIZE 0xFFFF

// // int main(int argc, char *argv[])
// // {
// //     int fd, nread;
// //     char buf[BUF_SIZE] = { 0, };
// //     struct linux_dirent *d;
// //     // struct dirent *d;
// //     int bpos;
// //     char d_type;

// //     fd = open(argc > 1 ? argv[1] : ".", O_RDONLY | O_DIRECTORY);
// //     if (fd == -1)
// //         handle_error("open");

// //     for ( ; ; ) {
// //         nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
// //         if (nread == -1)
// //             handle_error("getdents");

// //         if (nread == 0)
// //             break;

// //         printf("--------------- nread=%d ---------------\n", nread);
// //         printf("inode#    file type  d_reclen  d_off   d_name\n");
// //         for (bpos = 0; bpos < nread;) {
// //             d = (struct linux_dirent *) (buf + bpos);
// //             if(d->d_name[0] == '.'){

// //             }
// //             else{
// //                 printf("%8ld  ", d->d_ino);
// //                 d_type = *(buf + bpos + d->d_reclen - 1);
// //                 // d_type = d->d_type;
// //                 printf("%-10s ", (d_type == DT_REG) ?  "regular" :
// //                                 (d_type == DT_DIR) ?  "directory" :
// //                                 (d_type == DT_FIFO) ? "FIFO" :
// //                                 (d_type == DT_SOCK) ? "socket" :
// //                                 (d_type == DT_LNK) ?  "symlink" :
// //                                 (d_type == DT_BLK) ?  "block dev" :
// //                                 (d_type == DT_CHR) ?  "char dev" : "???");
// //                 printf("%4d %10lld  %s\n", d->d_reclen,
// //                                         (long long) d->d_off, d->d_name);
// //             }
// //             bpos += d->d_reclen;
// //         }
// //     }

// //     exit(EXIT_SUCCESS);
// // }


// // 2.scandir과 alphasort를 이용하여 struct dirent**로 파일이름 정렬.
// // #define _GNU_SOURCE
// // #include <sys/types.h>
// // #include <sys/dir.h>
// // #include <sys/param.h>      // limits
// // #include <stdio.h>
// // #include <string.h>
// // #include <stdlib.h>         // exti
// // #include <unistd.h>         // getcwd
// // #include <dirent.h>
// // #include <fcntl.h>

// // #define FALSE 0
// // #define TRUE !FALSE
// // #define handle_error(msg) \
// //         { perror(msg); exit(EXIT_FAILURE); }
 
// // extern  int alphasort();
 
// // char pathname[MAXPATHLEN];
 
// // int file_select(struct direct *entry) {
// //     if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
// //     // if (entry->d_name[0]== ',')
// //         return (FALSE);
// //     else
// //         return (TRUE);
// // }

// // int main(int argc, char** argv) {
// //     char *start_dir = (argc > 1 ? argv[1] : ".");
// //     if((chdir(start_dir)) < 0){
// //         perror(start_dir);
// //         exit(1);
// //     }
// //     int count,i;
// //     struct dirent **files;
// //     // int file_select();

// //     if (getcwd(pathname, MAXPATHLEN) == NULL ){
// //         printf("Error getting path\n");
// //         exit(0);
// //     }
// //     printf("Current Working Directory = %s\n",pathname);
// //     count = scandir(pathname, &files, file_select, alphasort);

// //     /* If no files found, make a non-selectable menu item */
// //     if (count <= 0) {
// //         printf("No files in this directory\n");
// //         exit(0);
// //     }
// //     printf("Number of files = %d\n",count);
// //     for (i=0; i<count; i++){
// //         // printf("%s\n",files[i]->d_name);
// //         int fd;
// //         int o_flag = O_RDONLY;
// //         if(files[i]->d_type == DT_DIR){
// //             o_flag |= O_DIRECTORY;
// //         }
// //         fd = open(files[i]->d_name, o_flag);
// //         if (fd == -1)
// //             handle_error("open");
// //         printf("%s, %d\n", files[i]->d_name, fd);
// //         close(fd);
// //     }
// //     printf("\n"); /* flush buffer */
// // }


// // // int main(){
// // //     int fd = open("a", O_RDONLY);
// // //     if (fd == -1)
// // //             handle_error("open");
// // // }


// // #include <stdio.h>
// // #include <string.h>
// // #include <stdlib.h>
// // #define ulli unsigned long long int
// // int main( void)
// // {
// //     char *ptr;
// //     char *tmp;
// //     ptr = malloc(10);

// //     while(1){
// //         ulli n;
// //         scanf("%llu", &n);
// //         printf("realloc size : %llu\n", n);
        
// //         tmp = ptr;
// //         printf( "realloc() 호출 전 ptr의 값: %x\n", ptr);
// //         ptr = realloc(ptr, n);
// //         printf( "realloc() 호출 후 ptr의 값: %x\n", ptr);

// //         if(ptr == NULL){
// //             ptr = tmp;
// //             perror("realloc");
// //         }
// //         // for(int i=0; i<n; i++)
// //         //     ptr[i] = 'a';
// //         // ptr[n - 1] = 0;
        
// //         // printf( "%s\n", ptr);   
// //     }
   
// //     free( ptr);
// //     return 0;
// // }


#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>

#define   TRUE	1
#define   FALSE	0


struct t_node
{
	char* name;
	int  ptd;		
	struct t_node *next_dfile;	
	struct t_node *next_file;
};

static struct t_node* create_tree(char *);
void print_tree(struct t_node *);
static struct t_node* create_tnode(char* );
int count;

int main(int args, char** argv)
{
	struct t_node *tstart=create_tnode(".");

	if(args>2)
	{
		printf("\n USAGE : ./a.out [PATH]");
		exit(0);
	}
	
	tstart->ptd=TRUE;
	(tstart->next_dfile)=create_tree(((args==2)? argv[1]:getcwd(0,0)));
	print_tree(tstart);

return 0;
}

static struct t_node* create_tree(char *root_name)
{
	DIR *dir=opendir(root_name);
	printf("\nrootname : %s",root_name);
	struct dirent *dr={NULL};
	struct t_node *ptr_tstart=NULL,*temp=NULL,*temp1=NULL;
	char *name=(char *)calloc(2000,sizeof(char));


	if(dir==NULL)
	{
		printf("\nFailed to open ..!!");
		printf(" : %s",root_name);
		return NULL;
	}

	while((dr=readdir(dir))!= NULL)
	{
			if(strcmp((dr->d_name),".")!=0 && strcmp((dr->d_name),"..")!=0) 
				temp=create_tnode(dr->d_name);
			else
			{
				temp=NULL;
				continue;
			}
			
			if(temp1!=NULL)
			{
				temp1->next_file=temp;
			
			}
			else
			{
				(ptr_tstart)=temp;
			}

			if((dr->d_type)==DT_DIR ) 
			{
				temp->ptd=TRUE;
				strcpy(name,root_name);
				(temp->next_dfile)=create_tree((strcat((strcat(name,"/")),dr->d_name)));
				strcpy(name,root_name);
			}
			else
			{
				(temp)->ptd=FALSE;
				(temp)->next_dfile=NULL;		
			}

		temp1=temp;
	}
return (ptr_tstart);
}

static struct t_node* create_tnode(char* n)
{
	struct t_node *temp=(struct t_node * )malloc(sizeof(struct t_node ));
	temp->name=n;
	temp->next_dfile=NULL;
	temp->next_file=NULL;
return temp;
}


void print_tree(struct t_node *start)
{
	char *s="|-----",*s1="|     ";
	struct t_node *temp=start;
	int i;

		if(start==NULL)
			return;

		printf("\n");
		for(i=0;i<(count-1);i++)
			printf("%s",s1);
		if(count>0)
			printf("%s",s);

		printf("%s",temp->name);
		
		if(temp->ptd==TRUE)
		{	
			count++;
			print_tree(temp->next_dfile);
			count--;
		}
		print_tree(temp->next_file);	

}