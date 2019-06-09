#include "Common.h"
// Pthread_kill(SIGUSR1) : Run -> Ready
void __thread_wait_handler(int signo){
    LOG_FUNC(__thread_wait_handler, called);
    Thread* p_TCB;
    if((p_TCB = Search(ReadyQHead, pthread_self())) == NULL){
        LOG_FUNC(__thread_wait_handler, Serch(readyQ) fail);
        exit(0);
    }
    pthread_mutex_lock(&(p_TCB->readyMutex));
    p_TCB->bRunnable = FALSE;
    p_TCB->status = THREAD_STATUS_READY;
    while(p_TCB->bRunnable == FALSE){
        pthread_cond_wait(&(p_TCB->readyCond), &(p_TCB->readyMutex));
        // pthread_kill(p_TCB->tid, SIGSTOP);
    }
    pthread_mutex_unlock(&(p_TCB->readyMutex));
}
// __thread_wakeup(ap_TCP) : Ready -> Run
void __thread_wakeup(Thread* ap_TCB){
    LOG_FUNC(__thread_wakeup, called);
    pthread_mutex_lock(&(ap_TCB->readyMutex));
    ap_TCB->bRunnable = TRUE;
    ap_TCB->status = THREAD_STATUS_RUN;
    pthread_cond_signal(&(ap_TCB->readyCond));
    // pthread_kill(ap_TCB->tid, SIGCONT);
    pthread_mutex_unlock(&(ap_TCB->readyMutex));
}
