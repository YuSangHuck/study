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
	p_tcb->pPrev = NULL;
	p_tcb->pNext = NULL;
	p_tcb->status = THREAD_STATUS_READY;
	p_tcb->bRunnable = FALSE;
    p_tcb->joinFlag = FALSE;
	p_tcb->exitFlag = FALSE;
    p_tcb->pExitCode = NULL;
	p_tcb->parentTid = thread_self();
	p_tcb->tid = *thread;
    pthread_cond_init(&(p_tcb->readyCond), NULL);
    pthread_mutex_init(&(p_tcb->readyMutex), NULL);
    pthread_cond_init(&(p_tcb->joinCond), NULL);
    pthread_mutex_init(&(p_tcb->joinMutex), NULL);
    
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


int 	thread_join(thread_t thread, void **retval){
    printf("thread_join called on tid %p\n", thread);
#ifdef LOG
#endif
    // Thread* p_tcb = Search(ReadyQHead, thread);
    Thread* p_tcb = __GetTCB(thread);
    if(p_tcb == NULL)
        fprintf(stderr, "thread_join :: Search error!\n");
    fprintf(stderr, "thread_join &(p_tcb->joinMutex) : %p\n", &(p_tcb->joinMutex));
#ifdef LOG
#endif
    printf("thread_join try to get mutex\n");
    pthread_mutex_lock(&(p_tcb->joinMutex));
    printf("thread_join get mutex\n");
#ifdef LOG
#endif

    // thread_exit과 동기화
    p_tcb->joinFlag = TRUE;
    if(p_tcb->exitFlag){
        // exit이 먼저 호출 된 경우
        // exit이 자고있으므로 깨워주고 join은 대기
        // pthread_cond_signal(&(p_tcb->joinCond));
        // pthread_cond_wait(&(p_tcb->joinCond), &(p_tcb->joinMutex));
        // 근데 아무것도 안해도 됨.
    }
    else{
        // join이 먼저 호출 된 경우
        // exit이 호출될떄까지 잠
#ifdef LOG
#endif
        printf("thread_join cond_wait\n");
        pthread_cond_wait(&(p_tcb->joinCond), &(p_tcb->joinMutex));
        printf("thread_join receive cond_sig\n");
#ifdef LOG
#endif
    }

    // exit이 호출되면 pExitCode를 복사
    *((int*)retval) = p_tcb->pExitCode;
    
    pthread_mutex_unlock(&(p_tcb->joinMutex));

    // 자원정리
    // free(p_tcb);

#ifdef LOG
    printf("thread_join %d resume mutex & cond\n", p_tcb->pExitCode);
#endif
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


int thread_exit(void* retval){
    // printf("thread_exit called with %d\n", (int)retval);
#ifdef LOG
#endif

    Thread* p_tcb = Search(ReadyQHead, pthread_self());
    if(p_tcb == NULL)
        fprintf(stderr, "thread_exit :: Search error!\n");

#ifdef LOG
    printf("thread_exit try to get mutex\n");
#endif
    pthread_mutex_lock(&(p_tcb->joinMutex));
#ifdef LOG
    printf("thread_exit get mutex\n");
#endif

    // thread_join과 동기화
    p_tcb->exitFlag = TRUE;
    if(p_tcb->joinFlag){
        // join이 먼저 호출 된 경우
        // join을 호출한 스레드를 깨움.
        pthread_cond_signal(&(p_tcb->joinCond));
    }
    else{
        // exit이 먼저 호출 된 경우
        // 대기
        // pthread_cond_wait(&(p_tcb->joinCond), &(p_tcb->joinMutex));
        // 대기하고 있으면 join이 exit 깨워주고 자는게 이론상으로 맞지만 아무것도 안해도 됨.
    }

    // 반환값 정리.
    p_tcb->pExitCode = retval;
    p_tcb->status = THREAD_STATUS_ZOMBIE;
    p_tcb->bRunnable = FALSE;
    
    // move ReadyQ to WaitQ
    // 아래의 내용은 scheduler에서 해주는게 맞음
    // GetStatus(ReadyQHead);
    // GetStatus(WaitQHead);
    // Remove(&ReadyQHead, &ReadyQTail, p_tcb);
    // Push(&WaitQHead, &WaitQTail, &p_tcb);
    // GetStatus(ReadyQHead);
    // GetStatus(WaitQHead);
    // printf("\n\n");

    pthread_mutex_unlock(&(p_tcb->joinMutex));
#ifdef LOG
    printf("thead_exit %d resume mutex & cond\n", (int)retval);
#endif

    // _Exit(0);
    pthread_exit(NULL);

    // 자원 정리는 thread_join에서
    
    return 0;
}

thread_t	thread_self(){
    return pthread_self();
}	
