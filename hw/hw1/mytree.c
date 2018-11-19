#include <stdio.h>              // fprintf, stderr
#include <stdlib.h>             // exit
#include <string.h>             // strcmp
#include <dirent.h>             // DIR, opendir
#include <unistd.h>             // getcwd
#include <sys/stat.h>           // struct stat, 메타데이터 매크로, open
#include <fcntl.h>              // open
#include <pwd.h>                // getpwuid
#include <string.h>
#define MAX_CNT_DIRENT      0xFFFF
#define MAX_SUB_DIR         0xFFFF

int compare(const void *a, const void *b){
    struct dirent** pa = (struct dirent **)a;
    struct dirent** pb = (struct dirent **)b;
    return strcmp((*pa)->d_name,(*pb)->d_name);
}
int DirentSort(struct dirent* ap_dirent, int a_cnt_dirent){
    qsort(ap_dirent, a_cnt_dirent, sizeof(struct dirent*), compare);
}

// ap_tree_struct를 아래처럼 만들어주는 함수
// trace_depth가 "1011"이라면
// │       │   ├──
int SetTreeStruct(char* ap_tree_struct, char* ap_trace_depth, int a_depth){
    if(ap_tree_struct == NULL || ap_trace_depth == NULL)
        return 1;

    // 처음 ~ 마지막 전
    for(int i=0; i<=a_depth - 1; i++){
        // 0이면 "    "
        if(ap_trace_depth[i] == '0')
            strcat(ap_tree_struct, "    ");
        // 1이면 "│   "
        else if(ap_trace_depth[i] == '1')
            strcat(ap_tree_struct, "│   ");
        // 2이면 "└   "
        else if(ap_trace_depth[i] == '2')
            strcat(ap_tree_struct, "└   ");
    }
    // 마지막
    if(ap_trace_depth[a_depth] == '1')
        strcat(ap_tree_struct, "├──");
    else if(ap_trace_depth[a_depth] == '2')
        strcat(ap_tree_struct, "└──");
    else
        fprintf(stderr, "#error# : unexpectd\n");
    
    return 0;
}

// info를 "[%7lu %lu %10s %-8s %5s] %s"의 형태로 만들어주는 함수
int SetInfo(char* ap_info, const struct stat* ap_st, const char* ap_dname){
    if(ap_info == NULL || ap_st == NULL || ap_dname == NULL)
        return 1;
    
    // 1.퍼미션 변환  ap_st->st_mode
    char permision[11] = { 0, };
    // 1.1.파일종류확인
    if(S_ISLNK(ap_st->st_mode))          permision[0] = 'l';
    else if(S_ISREG(ap_st->st_mode))     permision[0] = '-';
    else if(S_ISDIR(ap_st->st_mode))     permision[0] = 'd';
    else if(S_ISCHR(ap_st->st_mode))     permision[0] = 'c';
    else if(S_ISBLK(ap_st->st_mode))     permision[0] = 'b';
    else if(S_ISFIFO(ap_st->st_mode))    permision[0] = 'p';
    else if(S_ISSOCK(ap_st->st_mode))    permision[0] = 's';
    
    // 1.2.user 권한 설정
    if(ap_st->st_mode & S_IRUSR)         permision[1] = 'r';
    else                                 permision[1] = '-';
    if(ap_st->st_mode & S_IWUSR)         permision[2] = 'w';
    else                                 permision[2] = '-';
    if(ap_st->st_mode & S_IXUSR)         permision[3] = 'x';
    else                                 permision[3] = '-';

    // 1.3.group 권한설정
    if(ap_st->st_mode & S_IRGRP)         permision[4] = 'r';
    else                                 permision[4] = '-';
    if(ap_st->st_mode & S_IWGRP)         permision[5] = 'w';
    else                                 permision[5] = '-';
    if(ap_st->st_mode & S_IXGRP)         permision[6] = 'x';
    else                                 permision[6] = '-';
    
    // 1.4.others 권한설정
    if(ap_st->st_mode & S_IROTH)        permision[7] = 'r';
    else                                permision[7] = '-';
    if(ap_st->st_mode & S_IWOTH)        permision[8] = 'w';
    else                                permision[8] = '-';
    if(ap_st->st_mode & S_IXOTH)        permision[9] = 'x';
    else                                permision[9] = '-';
    
    // 1.5.이름 변환    ap_st->st_uid
    // reading으로 /etc/passwd의 파일을 읽어온 후 파싱해도 되지만
    // 만들어져 있는 getpwuid함수를 이용하자 ㅎㅎ
    char username[50] = { 0, };
    struct passwd* pw;
    pw = getpwuid(ap_st->st_uid);
    sprintf(username, "%s", pw->pw_name);

    // 1.6.사이즈 변환  ap_st->size
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

    sprintf(ap_info, "[%7lu %lu %10s %-8s %5s] %s", ap_st->st_ino,
                                                    ap_st->st_dev,
                                                    permision, // st
                                                    username,  // st
                                                    size,      // st
                                                    ap_dname);
    return 0;
}

int Travalsal(const char* ap_pwd, char* ap_trace_depth, int a_depth, int* ap_cnt_dir, int* ap_cnt_reg){
    // 0.pwd를 저장(매개변수).
    // ap_pwd에 대해 directory pointer를 얻음.
    DIR* p_dir;
    if((p_dir = opendir(ap_pwd)) == NULL){
        perror("opendir");
        return 1;
    }

    // 1.dirent*의 주소를 저장하는 포인터 배열 선언 후 배열에 dirent*들을 저장.(".", ".."는 제외)
    //  배열의 개수도 카운트 해야 함.
    struct dirent* p_arr_dirent[MAX_CNT_DIRENT];
    int cnt_dirent = 0;
    struct dirent* p_dirent;
    while((p_dirent = readdir(p_dir)) != NULL){
        if(p_dirent->d_name[0] == '.')
            continue;
        p_arr_dirent[cnt_dirent++] = p_dirent;
    }

    // 2.direct->name 기준으로 오름차순 정렬.
    DirentSort((struct dirent *)p_arr_dirent, cnt_dirent);

    // 3.결과에서 파일들의 트리구조 출력을 위한 ap_trace_depth를 설정함.
    //  특정 directory의 dirent를 탐색 시작할때 depth번째 값을 set하고,
    //  특정 directory의 dirent를 탐색 끝낼때 depth번째 값을 clear한다.
    ap_trace_depth[a_depth] = '1';

    // 4.반복문으로 pwd + direct->name으로 stat을 이용해 출력.
    for(int i=0; i<cnt_dirent; i++){
        // 4.1.메타데이터를 읽어올 파일 설정.
        // pwd, filename을 알고있음.
        char filename[255];
        sprintf(filename, "%s/%s", ap_pwd, p_arr_dirent[i]->d_name);

        // 4.2.메타데이터 읽어옴.
        struct stat st;
        int ret;
        if((ret = stat(filename, &st)) == -1){
            perror("stat");
            return 1;
        }

        // 4.3.stdout에 한 줄 을 출력하기 위한 준비.
        // 트리 구조를 표현하는 tree_struct와
        // 파일의 메타데이터 정보를 표현하는 info를 선언
        char tree_struct[255] = { 0, };
        char info[255] = { 0, };

        // 4.3.1.마지막 dirent가 아닐 때
        if(i != (cnt_dirent - 1)){
            if(SetTreeStruct(tree_struct, ap_trace_depth, a_depth) == 1){
                fprintf(stderr, "SetTreeStruct return 1\n");
                return 1;
            }

            if(SetInfo(info, &st, p_arr_dirent[i]->d_name) == 1){
                fprintf(stderr, "SetInfo return 1\n");
                return 1;
            }
        }
        // 4.3.2.마지막 dirent일 때
        else{
            ap_trace_depth[a_depth] = '2';
            if(SetTreeStruct(tree_struct, ap_trace_depth, a_depth) == 1){
                fprintf(stderr, "SetTreeStruct return 1\n");
                return 1;
            }
            
            if(SetInfo(info, &st, p_arr_dirent[i]->d_name) == 1){
                fprintf(stderr, "SetInfo return 1\n");
                return 1;
            }
            ap_trace_depth[a_depth] = '0';
        }
        char result[512] = { 0, };
        sprintf(result, "%s %s", tree_struct, info);
        printf("%s\n", result);


        // file이 디렉토리라면
        if(S_ISDIR(st.st_mode)){
            (*ap_cnt_dir)++;
            Travalsal(filename, ap_trace_depth, a_depth + 1, ap_cnt_dir, ap_cnt_reg);
        }
        else{
            (*ap_cnt_reg)++;
        }
    }
    return 0;
}

int main(int argc, char** argv){
    // 탐색의 시작위치 설정.
    char* start_dir;
    if(argc == 1)   start_dir = ".";
    if(argc == 2)   start_dir = argv[1];
    
    if((chdir(start_dir)) < 0){
        perror(start_dir);
        exit(1);
    }
    char pwd[255];
    getcwd(pwd, 255);

    
    // 결과에서 파일들의 트리구조 출력을 위한 trace_depth를 선언
    // 결과에서 파일과 디렉토리 개수를 출력하기 위한 변수 선언
    int cnt_reg = 0, cnt_dir = 0;
    char trace_depth[MAX_SUB_DIR] = { 0, };

    // 탐색 시작.
    printf("%s\n", start_dir);
    if(Travalsal(pwd, trace_depth, 0, &cnt_dir, &cnt_reg) == -1){
        perror("Travalsal");
        exit(1);
    }

    char directory[255];
    if(cnt_dir == 1)    sprintf(directory, "directory");
    else                sprintf(directory, "directories");

    char file[255];
    if(cnt_reg == 1)    sprintf(file, "file");
    else                sprintf(file, "files");

    char result[255];
    sprintf(result,"%d %s, %d %s", cnt_dir, directory, cnt_reg, file);
    printf("\n%s\n", result);

    return 0;
}
