#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#define LOG_THREAD(thread,func,msg) fprintf(stderr, "[%-15s]  [%-15s]  %s\n", #thread, #func, #msg)
#define LOG_FUNC(func,msg)          fprintf(stderr, "%19s[%-15s]  %s\n", "",#func, #msg)
#define true 1;
#define false 0
typedef int bool;

bool g_child_first;
bool g_parent_first;
pthread_mutex_t g_mutex;
pthread_cond_t g_cond;


typedef struct __WrapperArg{
    void*(*funcPtr)(void*);
    void* funcArg;
} wrapperArg;

void* thread_proc(void* arg){
    int i = (int)arg;
    while(1){
        printf("arg : %d\n", i++);
        sleep(1);
    }
}


void* WrapperFunc(void* arg){
    LOG_THREAD(child, WrapperFunc, 0.lock mutex);
    pthread_mutex_lock(&g_mutex);

    // 1.스택 변수 복사
    LOG_THREAD(child, WrapperFunc, 1.cpy stack variable);
    wrapperArg* wa = (wrapperArg*)arg;
    void* funcPtr = wa->funcPtr;
    void* funcArg = wa->funcArg;

    // 2.핸들러 등록
    LOG_THREAD(child, WrapperFunc, 2.register signal handler);

    LOG_THREAD(child, WrapperFunc, 3.cond_signal);
    pthread_cond_signal(&g_cond);


    LOG_THREAD(child, WrapperFunc, 4.unlock mutex);
    pthread_mutex_unlock(&g_mutex);

    sleep(3);
    // 3.wait_handler 호출
    LOG_THREAD(child, WrapperFunc, 5.wait_handler call);

    // 4.스레드 시작
    LOG_THREAD(child, WrapperFunc, 6.start Thread_Proc);
    (*((void*(*)(void*))funcPtr))(funcArg);
}

int thread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine) (void *), void *arg){
    LOG_THREAD(parent, thread_create, 0.lock mutex);
    pthread_mutex_lock(&g_mutex);
    wrapperArg wa;
    wa.funcPtr = start_routine;
    wa.funcArg = arg;
    pthread_create(thread, attr, WrapperFunc, &wa);
    LOG_THREAD(parent, thread_create, 1.TCB_Alloc);
    LOG_THREAD(parent, thread_create, 2.TCB_Init);
    LOG_THREAD(parent, thread_create, 3.Push TCB);
    LOG_THREAD(parent, thread_create, 4.cond_wait);
    pthread_cond_wait(&g_cond, &g_mutex);
    LOG_THREAD(parent, thread_create, 5.cond_wait return);
    LOG_THREAD(parent, thread_create, 6.unlock mutex);
    pthread_mutex_unlock(&g_mutex);
    return 0;
}
int main(){
    pthread_t tid;
    g_child_first = false;
    g_parent_first = false;

    LOG_THREAD(parent, main, thread_create call);
    thread_create(&tid, NULL, thread_proc, 0);
    LOG_THREAD(parent, main, thread_create return);
    while(1);
    return 0;
}