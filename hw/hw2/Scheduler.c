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
// @ ap_curTCB : 재울놈
// @ ap_newTCB : 깨울놈
void    _ContextSwitch(Thread* ap_curTCB, Thread* ap_newTCB){
    LOG_THREAD(parent, _ContextSwitch, start);
    // 1.sleep ap_curTCB
    LOG_THREAD(parent, _ContextSwitch, pthread_kill -> wait_handler);
    pthread_kill(ap_curTCB->tid, SIGUSR1);
    
    // 2.wakeup ap_newTCB
    LOG_THREAD(parent, _ContextSwitch, thread_wakeup);
    __thread_wakeup(ap_newTCB);
}
 
 // g_curRun ���������� ����
int		RunScheduler( void ){
    while(1){
        LOG_THREAD(parent, RunScheduler, start);
        printf("scheduler start\n");
        #ifdef LOG
        GetStatus(ReadyQHead);
        #endif


        // 1.status->Ready || status->Run 처리
        // 1.1.레디큐가 비었을 때
        if(Empty(ReadyQHead)){
            LOG_THREAD(parent, RunScheduler, readyQ is empty -> sleep);
            printf("Scheduler rdq size == 0 -> sleep\n");
            sleep(TIMESLICE);
        }
        // 1.2.레디큐에 무언가 있을 떄
        else{
            // 1.2.1.ReadyQHead만 꺠워야 할 때
            // if((Size(ReadyQHead) == 1) &&
            //     (ReadyQHead->status == THREAD_STATUS_READY || ReadyQHead->status == THREAD_STATUS_RUN)){
            if( (ReadyQHead->status == THREAD_STATUS_READY) ||
                ( (Size(ReadyQHead) == 1) && (ReadyQHead->status == THREAD_STATUS_RUN) )){
                LOG_THREAD(parent, RunScheduler, readyQ size == 1);
                printf("Scheduler rdq size == 1\n");
                // GetStatus(ReadyQHead);
                printf("Scheduler wakeup(rdqhead)\n");
                __thread_wakeup(ReadyQHead);
                // GetStatus(ReadyQHead);
                printf("Scheduler sleep\n");
                sleep(TIMESLICE);
                // GetStatus(ReadyQHead);
                // GetStatus(WaitQHead);
            }
            // 1.2.2.__ContextSwitch가 호출되어야 할 때
            else{
                LOG_THREAD(parent, RunScheduler, readyQ size > 1);
                printf("Scheduler rdq size > 1\n");
                // 1.p_curTCB[재울놈], p_newTCB[깨울놈] 설정
                Thread* p_curTCB = ReadyQHead;
                Thread* p_newTCB = ReadyQHead->pNext;

                printf("Scheduler before __ContextSwitch\n");
                // GetStatus(ReadyQHead);
                
                // 2._ContextSwitch(p_curTCB, p_newTCB)
                LOG_THREAD(parent, RunScheduler, call _ContextSwitch);
                printf("Scheduler __ContextSwitch\n");
                _ContextSwitch(p_curTCB, p_newTCB);
                #ifdef LOG
                // GetStatus(ReadyQHead);
                #endif
                
                printf("Scheduler before rdq Queueing\n");
                // GetStatus(ReadyQHead);

                // 3.sleep
                printf("Scheduler sleep\n");
                sleep(TIMESLICE);
                // GetStatus(WaitQHead);

                // p_curTCB[재워놈], p_newTCB[깨워진놈]

                // 4.ReadyQ 큐잉
                // tmp = head 하고
                // pop; push(tmp); 진행
                LOG_THREAD(parent, RunScheduler, call rdq.Pop);
                if(Pop(&ReadyQHead, &ReadyQTail) == -1){
                    LOG_THREAD(parent, RunScheduler, rdq.Pop() fail);
                }
                #ifdef LOG
                printf("head : %p\ntail : %p\np_curTCB : %p\n", ReadyQHead, ReadyQTail, p_curTCB);
                #endif
                LOG_THREAD(parent, RunScheduler, call rdq.Push);
                if(Push(&ReadyQHead, &ReadyQTail, &p_curTCB) == -1){
                    LOG_THREAD(parent, RunScheduler, rdq.Push(p_curTCB) fail);
                }
                printf("Scheduler after rdq Queueing\n");
            }
        }


        // 2.status->Zombie 처리
        // Zombie면 waitQ에 Push
        // ReadyQHead의 상태가 ZOMBIE라면 Pop하고 WaitQ에 Push
        printf("Scheduler before wtq Queueing\n");
        if(ReadyQHead->status == THREAD_STATUS_ZOMBIE){
            Thread* tmp = ReadyQHead;
            LOG_THREAD(parent, RunScheduler, call rdq.Pop);
            if(Pop(&ReadyQHead, &ReadyQTail) == -1){
                LOG_THREAD(parent, RunScheduler, rdq.Pop() fail);
            }
            LOG_THREAD(parent, RunScheduler, call wtq.Push);
            if(Push(&WaitQHead, &WaitQTail, &tmp) == -1){
                LOG_THREAD(parent, RunScheduler, rdq.Push(tmp) fail);
            }
        }
        printf("Scheduler after wtq Queueing\n");

        // 3.결과 확인
        // GetStatus(ReadyQHead);
        // GetStatus(WaitQHead);
        // printf("\n\n\n");

        #ifdef LOG
        #endif
        LOG_THREAD(parent, RunScheduler, sleep TIME_SLICE);
    }
}


