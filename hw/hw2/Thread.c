#include "Thread.h"
#include "Common.h"
void* __wrapperFunc(void* arg){
    // 0.lock mutex
    LOG_THREAD(child, __wrapperFunc, 0.lock mutex);
    pthread_mutex_lock(&g_mutex);
    
    // 1.스택 변수 복사
    LOG_THREAD(child, __wrapperFunc, 1.cpy stack variable);
    WrapperArg* p_Arg = (WrapperArg*)arg;
    void* funcPtr = p_Arg->funcPtr;
    void* funcArg = p_Arg->funcArg;
    // fprintf(stderr, "\t[__wrapperFunc]  funcptr %p, funcarg %p\n", funcPtr, funcArg);

    // 2.핸들러 등록
    LOG_THREAD(child, __wrapperFunc, 2.register signal handler);
    struct sigaction sa;
    // sigemptyset(&sa.sa_mask);
    // sa.sa_flags = 0;
    sa.sa_handler = __thread_wait_handler;
    sigaction(SIGUSR1, &sa, NULL);
    
    // 3.parent에게 cond_signal
    LOG_THREAD(child, __wrapperFunc, 3.cond_signal);
    pthread_cond_signal(&g_cond);

    // 4.unlock mutex
    LOG_THREAD(child, __wrapperFunc, 4.unlock mutex);
    pthread_mutex_unlock(&g_mutex);
    
    // 5.call wait_handler
    LOG_THREAD(child, __wrapperFunc, 5.call wait_handler);
    __thread_wait_handler(0);

    // 6.child wakeup
    LOG_THREAD(child, __wrapperFunc, 6.child wakeup);

    void* ret;

    LOG_THREAD(child, __wrapperFunc, thread_proc start);
    ret = (*(void*(*)(void*))funcPtr)(funcArg);
    
    return ret;
}

int 	thread_create(thread_t *thread, thread_attr_t *attr, void *(*start_routine) (void *), void *arg){
    // 0.lock mutex
    LOG_THREAD(parent, thread_create, 0.lock mutex);
    pthread_mutex_lock(&g_mutex);
    WrapperArg wrapper_arg;
    wrapper_arg.funcPtr = start_routine;
    wrapper_arg.funcArg = arg;
    #ifdef LOG
    fprintf(stderr, "[%-15s]  [%-15s]   arg : %d\n", "parent", "thread_create", (int)arg);
    #endif

    if(pthread_create(thread, attr, __wrapperFunc, &wrapper_arg) != 0)
        LOG_THREAD(parent, thread_create, pthread_create fail);
    
    // 1.TCB Alloc
    LOG_THREAD(parent, thread_create, 1.TCB_Alloc);
    Thread* p_tcb = (Thread*)malloc(sizeof(Thread));
    
    // 2.TCB Init
    LOG_THREAD(parent, thread_create, 2.TCB_Init);
	p_tcb->status = THREAD_STATUS_READY;
	p_tcb->bRunnable = FALSE;
	p_tcb->pPrev = NULL;
	p_tcb->pNext = NULL;
	p_tcb->parentTid = thread_self();
	p_tcb->tid = *thread;
    pthread_cond_init(&(p_tcb->readyCond), NULL);
    pthread_mutex_init(&(p_tcb->readyMutex), NULL);
    
    // 3.Push TCB
    LOG_THREAD(parent, thread_create, 3.Push TCB);
    if(Push(&ReadyQHead, &ReadyQTail, &p_tcb) != 0)
        LOG_THREAD(parent, thread_create, Push(readyQ) fail);
    
    // 4.child를 cond_wait
    LOG_THREAD(parent, thread_create, 4.cond_wait);
    pthread_cond_wait(&g_cond, &g_mutex);
    // 5.child로부터 cond_signal 받음
    LOG_THREAD(parent, thread_create, 5.receive cond_signal from child);

    // 6.unlock mutex
    LOG_THREAD(parent, thread_create, 6.unlock mutex);
    pthread_mutex_unlock(&g_mutex);
    return 0;
}


int 	thread_join(thread_t thread, void **retval)
{
    Thread* p_tcb = Search(ReadyQHead, thread);
    if(p_tcb == NULL)
        fprintf(stderr, "thread_join :: Search error!\n");
    pthread_mutex_lock(&g_mutex);
    // exit이 호출될떄까지 잠
    pthread_cond_wait(&g_cond, &g_mutex);
    // exit이 호출되면 pExitCode를 복사
    *((int*)retval) = p_tcb->pExitCode;
    
    // 자원정리
    // free(g_curRun);

    pthread_mutex_unlock(&g_mutex);
}


int 	thread_suspend(thread_t tid)
{

}


int	thread_resume(thread_t tid)
{

}


int 		thread_cancel(thread_t tid)
{

}


int thread_exit(void* retval)
{
    printf("thead_exit called with %d\n", (int)retval);
    Thread* p_tcb = Search(ReadyQHead, pthread_self());
    if(p_tcb == NULL)
        fprintf(stderr, "thread_exit :: Search error!\n");

    pthread_mutex_lock(&g_mutex);
    // 반환값 정리.
    p_tcb->pExitCode = retval;
    // join을 호출한 함수를 깨움.
    pthread_cond_signal(&g_cond);
    pthread_mutex_unlock(&g_mutex);
    
    // 자원 정리는 thread_join에서
    
    return 0;
}

thread_t	thread_self()
{
    return pthread_self();
}	
