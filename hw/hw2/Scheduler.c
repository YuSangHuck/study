// @ ReadyQ + g_curRun
// #include "Scheduler.h"
// void    _ContextSwitch(Thread* ap_curTCB, Thread* ap_newTCB){
//     LOG_THREAD(parent, _ContextSwitch, start);
//     if(ap_curTCB == NULL && ap_newTCB == NULL)
//         LOG_THREAD(parent, _ContextSwitch, cur & new TCB is NULL error);
//     // 1.sleep curTCB��
//     if(ap_curTCB != NULL){
//         LOG_THREAD(parent, _ContextSwitch, pthread_kill -> wait_handler);
//         pthread_kill(ap_curTCB->tid, SIGUSR1);
//     }
//     // 2.wakeup newTCB��
//     LOG_THREAD(parent, _ContextSwitch, thread_wakeup);
//     __thread_wakeup(ap_newTCB);
// }

 
//  // g_curRun ���������� ����
// int		RunScheduler( void ){
//     while(1){
//         // GetStatus(ReadyQHead);
//         LOG_THREAD(parent, RunScheduler, start);
//         #ifdef LOG
//         #endif
//         if(Empty(ReadyQHead)){
//             LOG_THREAD(parent, RunScheduler, readyQ is empty -> sleep);
//         } 
//         else{
//             LOG_THREAD(parent, RunScheduler, readyQ is not empty);
//             // 1.p_curTCB, p_newTCB 변경
//             Thread* p_curTCB = g_curRun;
//             Thread* p_newTCB = ReadyQHead;
//             if(p_curTCB == NULL && p_newTCB == NULL)
//                 LOG_THREAD(parent, RunScheduler, cur & new TCB is NULL error);
//             LOG_THREAD(parent, RunScheduler, call _ContextSwitch);
//             // 2._ContextSwitch(p_curTCB, p_newTCB)
//             _ContextSwitch(p_curTCB, p_newTCB);
            
//             // 3.Pop : Remove p_newTCB
//             LOG_THREAD(parent, RunScheduler, call Pop);
//             if(Pop(&ReadyQHead, &ReadyQTail) == -1){
//                 LOG_THREAD(parent, RunScheduler, Pop() fail);
//             }
            
//             // 4.Push(p_curTCB)
//             LOG_THREAD(parent, RunScheduler, call Push);
//             if(Push(&ReadyQHead, &ReadyQTail, &p_curTCB) == -1){
//                 LOG_THREAD(parent, RunScheduler, Push(p_curTCB) fail);
//             }

//             // 5.update g_curRun
//             g_curRun = p_newTCB;
//         }
//         sleep(TIMESLICE);
//     }
// }


// @ only ReadyQ
#include "Scheduler.h"
void    _ContextSwitch(Thread* ap_curTCB, Thread* ap_newTCB){
    LOG_THREAD(parent, _ContextSwitch, start);
    // size==1일때, 즉, p_newTCB == NULL일때 처리해줘야 됨
    if(ap_newTCB == NULL){
        LOG_THREAD(parent, _ContextSwitch, thread_wakeup);
        __thread_wakeup(ap_curTCB);
    }
    else{
        // 1.sleep curTCB��
        LOG_THREAD(parent, _ContextSwitch, pthread_kill -> wait_handler);
        pthread_kill(ap_curTCB->tid, SIGUSR1);
        // 2.wakeup newTCB��
        LOG_THREAD(parent, _ContextSwitch, thread_wakeup);
        __thread_wakeup(ap_newTCB);
    }
}
 
 // g_curRun ���������� ����
int		RunScheduler( void ){
    while(1){
        LOG_THREAD(parent, RunScheduler, start);
        // printf("scheduler start\n");
        #ifdef LOG
        GetStatus(ReadyQHead);
        #endif
        #ifdef LOG
        #endif
        if(Empty(ReadyQHead)){
            LOG_THREAD(parent, RunScheduler, readyQ is empty -> sleep);
        }
        else{
            LOG_THREAD(parent, RunScheduler, readyQ is not empty);
            // 1.p_curTCB, p_newTCB 변경
            Thread* p_curTCB = ReadyQHead;
            Thread* p_newTCB = ReadyQHead->pNext;

            // 2._ContextSwitch(p_curTCB, p_newTCB)
            // size==1일때, 즉, p_newTCB == NULL일때 처리해줘야 됨
            LOG_THREAD(parent, RunScheduler, call _ContextSwitch);
            _ContextSwitch(p_curTCB, p_newTCB);
            #ifdef LOG
            GetStatus(ReadyQHead);
            #endif
            
            // 3.Pop : Remove p_newTCB
            LOG_THREAD(parent, RunScheduler, call Pop);
            if(Pop(&ReadyQHead, &ReadyQTail) == -1){
                LOG_THREAD(parent, RunScheduler, Pop() fail);
            }
            #ifdef LOG
            printf("head : %p\ntail : %p\np_curTCB : %p\n", ReadyQHead, ReadyQTail, p_curTCB);
            #endif

            // 4.Push(p_curTCB)
            LOG_THREAD(parent, RunScheduler, call Push);
            if(Push(&ReadyQHead, &ReadyQTail, &p_curTCB) == -1){
                LOG_THREAD(parent, RunScheduler, Push(p_curTCB) fail);
            }
        }
        #ifdef LOG
        GetStatus(ReadyQHead);
        #endif
        LOG_THREAD(parent, RunScheduler, sleep TIME_SLICE);
        sleep(TIMESLICE);
    }
}


