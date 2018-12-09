#include "Queue.h"
#include <stdio.h>


queue*  Queue(int a_type){
    // ?—?Ÿ¬ì²˜ë¦¬. ?ž˜ëª»ëœ type
    if(a_type != READY_QUEUE && a_type != WAIT_QUEUE)
        return NULL;

    queue* tmp = malloc(sizeof(queue));
    if(a_type == READY_QUEUE){
        tmp->m_head = ReadyQHead;
        tmp->m_tail = ReadyQTail;
        tmp->m_type = READY_QUEUE;
    }
    else if(a_type == WAIT_QUEUE){
        tmp->m_head = WaitQHead;
        tmp->m_tail = WaitQTail;
        tmp->m_type = WAIT_QUEUE;
    }
    tmp->m_size = 0;

    return tmp;
}
int     Size(queue* ap_queue){
    // ?—?Ÿ¬ì²˜ë¦¬. ?ž˜ëª»ëœ ì£¼ì†Œ
    if(ap_queue == NULL)
        return -1;

    return ap_queue->m_size;
}
int     Empty(queue* ap_queue){
    // ?—?Ÿ¬ì²˜ë¦¬. ?ž˜ëª»ëœ ì£¼ì†Œ
    if(ap_queue == NULL)
        return -1;

    if(ap_queue->m_size == 0)
        return 1;
    else
        return 0;
}
Thread* Front(queue* ap_queue){
    // ?—?Ÿ¬ì²˜ë¦¬. ?ž˜ëª»ëœ ì£¼ì†Œ
    if(ap_queue == NULL)
        return NULL;

    return ap_queue->m_head;
}
Thread* Back(queue* ap_queue){
    // ?—?Ÿ¬ì²˜ë¦¬. ?ž˜ëª»ëœ ì£¼ì†Œ
    if(ap_queue == NULL)
        return NULL;

    return ap_queue->m_tail;
}
int     Push(queue* ap_queue, Thread* ap_thread){
    // 0.?—?Ÿ¬ì²˜ë¦¬. ?ž˜ëª»ëœ ì£¼ì†Œ
    if(ap_queue == NULL || ap_thread == NULL){
        return -1;
    }

    // 1.?…¸?“œ ê´?ê³? ? •ë¦?. queue.tailê³? thread?‚¬?´?˜ ê´?ê³?
    // ë¹„ì–´?žˆì§? ?•Š?‹¤ë©?
    if(!Empty(ap_queue)){
        ap_queue->m_tail->pNext = ap_thread;
        ap_thread->pPrev = ap_queue->m_tail;
    }
    // ë¹„ì–´?žˆ?‹¤ë©?
    else{
        // tail?´ ì¡´ìž¬?•˜ì§? ?•Š?œ¼?‹ˆ ? •?˜ ë¶ˆê??
    }

    // 2.? êµ¬ì¡° ? •ë¦?
    ap_queue->m_tail = ap_thread;
    // ë¹„ì–´?žˆ?‹¤ë©?
    if(Empty(ap_queue)){
        ap_queue->m_head = ap_thread;
    }
    ap_queue->m_size++;
}
int     Pop(queue* ap_queue){
    // 0.?—?Ÿ¬ì²˜ë¦¬. ?ž˜ëª»ëœ ì£¼ì†Œ ?˜¹??? ë¹„ì–´?žˆ?Š” ?
    if(ap_queue == NULL || Empty(ap_queue))
        return -1;

    ap_queue->m_size--;
    // 1.? êµ¬ì¡° ? •ë¦?
    ap_queue->m_head = ap_queue->m_head->pNext;
    if(Empty(ap_queue)){
        ap_queue->m_tail = NULL;
    }

    // 2.?…¸?“œ ê´?ê³? ? •ë¦?
    if(!Empty(ap_queue)){
        ap_queue->m_head->pPrev =NULL;
    }
    else{
        // headê°? ì¡´ìž¬?•˜ì§? ?•Š?œ¼?‹ˆ ? •?˜ ë¶ˆê??
    }
}
Thread* Search(queue* ap_queue, thread_t a_tid){
    if(ap_queue == NULL)
        return NULL;

    Thread* p_cursor = ap_queue->m_head;
    while(p_cursor){
        if(p_cursor->tid == a_tid)
            break;
        p_cursor = p_cursor->pNext;
    }
    return p_cursor;
}
int     Remove(queue* ap_queue, Thread* ap_thread){
    if(ap_queue == NULL || ap_thread == NULL)
        return -1;

    int ret = -1;
    Thread* p_cursor = ap_queue->m_head;
    while(p_cursor){
        if(p_cursor == ap_thread){
            ap_queue->m_size--;
            if(p_cursor->pPrev != NULL && p_cursor->pNext != NULL){
                p_cursor->pPrev->pNext = p_cursor->pNext;
                p_cursor->pNext->pPrev = p_cursor->pPrev;
            }
            else if(p_cursor->pPrev == NULL && p_cursor->pNext != NULL){
                ap_queue->m_head = p_cursor->pNext;
                ap_queue->m_head->pPrev = NULL;
            }
            else if(p_cursor->pPrev != NULL && p_cursor->pNext == NULL){
                ap_queue->m_tail = p_cursor->pPrev;
                ap_queue->m_tail->pNext = NULL;
            }
            else{
                ap_queue->m_head = NULL;
                ap_queue->m_tail = NULL;
            }

            ret = 0;
            break;
        }
        p_cursor = p_cursor->pNext;
    }
    
    return ret;
}
void    GetStatus(queue* ap_queue){
    printf("size : %d\n", Size(ap_queue));
    Thread* p_cursor;

    for(int i = 0; i < Size(ap_queue); i++)
        printf("|---------------");
    printf("|\n");



    // Thread* adress
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("|-%-14s", "Thread*");
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("| %14d", p_cursor);
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");



    for(int i = 0; i < Size(ap_queue); i++)
        printf("|---------------");
    printf("|\n");



    // ThreadStatus status
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("|-%-14s", "status");
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        if(p_cursor->status == 0){
            printf("| %14s", "RUN");
        }
        else if(p_cursor->status == 1){
            printf("| %14s", "READY");
        }
        else if(p_cursor->status == 2){
            printf("| %14s", "BLOCKED");
        }
        else{
            printf("| %14s", "ZOMBIE");
        }
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");



    // thread_t parentTid
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("|-%-14s", "parentTid");
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("| %14lu", p_cursor->parentTid);
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");



     // thread_t tid
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("|-%-14s", "tid");
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("| %14lu", p_cursor->tid);
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");



     // BOOL bRunnable
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("|-%-14s", "bRunnable");
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("| %14d", p_cursor->bRunnable);
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");



     // Thread* pPrev
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("|-%-14s", "pPrev");
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("| %14d", p_cursor->pPrev);
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");


     // Thread* pNext
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("|-%-14s", "pNext");
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");
    p_cursor = ap_queue->m_head;
    while(p_cursor){
        printf("| %14d", p_cursor->pNext);
        p_cursor = p_cursor->pNext;
    }
    printf("|\n");

    return;
}
