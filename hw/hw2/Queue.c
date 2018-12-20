#include "Queue.h"
#ifdef WITH_QUEUE
queue*  Queue(int a_type){
    // ?��?��처리. ?��못된 type
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
    // ?��?��처리. ?��못된 주소
    if(ap_queue == NULL)
        return -1;

    return ap_queue->m_size;
}
int     Empty(queue* ap_queue){
    // ?��?��처리. ?��못된 주소
    if(ap_queue == NULL)
        return -1;

    if(ap_queue->m_size == 0)
        return 1;
    else
        return 0;
}
Thread* Front(queue* ap_queue){
    // ?��?��처리. ?��못된 주소
    if(ap_queue == NULL)
        return NULL;

    return ap_queue->m_head;
}
Thread* Back(queue* ap_queue){
    // ?��?��처리. ?��못된 주소
    if(ap_queue == NULL)
        return NULL;

    return ap_queue->m_tail;
}
int     Push(queue* ap_queue, Thread* ap_thread){
    // 0.?��?��처리. ?��못된 주소
    if(ap_queue == NULL || ap_thread == NULL){
        return -1;
    }

    // 1.?��?�� �??�?? ?���??. queue.tail�?? thread?��?��?�� �??�??
    // 비어?���?? ?��?���??
    if(!Empty(ap_queue)){
        ap_queue->m_tail->pNext = ap_thread;
        ap_thread->pPrev = ap_queue->m_tail;
    }
    // 비어?��?���??
    else{
        // tail?�� 존재?���?? ?��?��?�� ?��?�� 불�??
    }

    // 2.?�� 구조 ?���??
    ap_queue->m_tail = ap_thread;
    // 비어?��?���??
    if(Empty(ap_queue)){
        ap_queue->m_head = ap_thread;
    }
    ap_queue->m_size++;
}
int     Pop(queue* ap_queue){
    // 0.?��?��처리. ?��못된 주소 ?��??? 비어?��?�� ?��
    if(ap_queue == NULL || Empty(ap_queue))
        return -1;

    ap_queue->m_size--;
    // 1.?�� 구조 ?���??
    ap_queue->m_head = ap_queue->m_head->pNext;
    if(Empty(ap_queue)){
        ap_queue->m_tail = NULL;
    }

    // 2.?��?�� �??�?? ?���??
    if(!Empty(ap_queue)){
        ap_queue->m_head->pPrev =NULL;
    }
    else{
        // head�?? 존재?���?? ?��?��?�� ?��?�� 불�??
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

#else
int     Size(Thread* ap_queue_head){
    int cnt = 0;
    Thread* p_cursor = ap_queue_head;
    while(p_cursor){
        cnt++;
        p_cursor = p_cursor->pNext;
    }
    return cnt;
}
int     Empty(Thread* ap_queue_head){
    if(ap_queue_head)
        return 0;
    else
        return 1;
}
int     Push(Thread** ap_queue_head, Thread** ap_queue_tail, Thread** ap_thread){
    // 0.?��?��처리. ?��못된 주소
    if(*ap_thread == NULL){
        return -1;
    }

    // 1. relationship between nodes
    // 1.?��?�� �??�?? ?���??. queue.tail�?? thread?��?��?�� �??�??
    // 비어?���?? ?��?���??
    if(!Empty(*ap_queue_head)){
        (*ap_queue_tail)->pNext = *ap_thread;
        (*ap_thread)->pPrev = *ap_queue_tail;
        (*ap_thread)->pNext = NULL;
    }
    // 비어?��?���??
    else{
        // tail?�� 존재?���?? ?��?��?�� ?��?�� 불�??
        (*ap_thread)->pPrev = NULL;
        (*ap_thread)->pNext = NULL;
    }

    // 2. struct of Queue(Head,Tail)
    // 2.?�� 구조 ?���??
    *ap_queue_tail = *ap_thread;
    // 비어?��?���??
    if(Empty(*ap_queue_head)){
        *ap_queue_head = *ap_thread;
    }
    return 0;
}
int     Pop(Thread** ap_queue_head, Thread** ap_queue_tail){
    // 0.?��?��처리. ?��못된 주소 ?��??? 비어?��?�� ?��
    if(*ap_queue_head == NULL)
        return -1;

    // 1.?�� 구조 ?���??
    *ap_queue_head = (*ap_queue_head)->pNext;
    if(Empty(*ap_queue_head)){
        *ap_queue_tail = NULL;
    }

    // 2.?��?�� �??�?? ?���??
    if(!Empty(*ap_queue_head)){
        (*ap_queue_head)->pPrev =NULL;
    }
    else{
        // head�?? 존재?���?? ?��?��?�� ?��?�� 불�??
    }
    return 0;
}
Thread* Search(Thread* ap_queue_head, thread_t a_tid){
    if(ap_queue_head == NULL || (void*)a_tid == NULL)
        return NULL;

    Thread* p_cursor = ap_queue_head;
    while(p_cursor){
        if(p_cursor->tid == a_tid)
            break;
        p_cursor = p_cursor->pNext;
    }
    return p_cursor;
}
int     Remove(Thread** ap_queue_head, Thread** ap_queue_tail, Thread* ap_thread){
    if(*ap_queue_head == NULL || ap_thread == NULL)
        return -1;

    int ret = -1;
    Thread* p_cursor = *ap_queue_head;
    while(p_cursor){
        if(p_cursor == ap_thread){
            if(p_cursor->pPrev != NULL && p_cursor->pNext != NULL){
                p_cursor->pPrev->pNext = p_cursor->pNext;
                p_cursor->pNext->pPrev = p_cursor->pPrev;
            }
            else if(p_cursor->pPrev == NULL && p_cursor->pNext != NULL){
                *ap_queue_head = p_cursor->pNext;
                (*ap_queue_head)->pPrev = NULL;
            }
            else if(p_cursor->pPrev != NULL && p_cursor->pNext == NULL){
                *ap_queue_tail = p_cursor->pPrev;
                (*ap_queue_tail)->pNext = NULL;
            }
            else{
                *ap_queue_head = NULL;
                *ap_queue_tail = NULL;
            }

            ret = 0;
            break;
        }
        p_cursor = p_cursor->pNext;
    }
    
    return ret;
}

Thread* __GetTCB(thread_t a_tid){
    fprintf(stderr, "__GetTCB tid : %p\n", a_tid);
    Thread* p_tcb;
    if((p_tcb = Search(ReadyQHead, a_tid)) != NULL){
        fprintf(stderr, "__GetTCB Search in rdq\n");
        printf("__GetTCB tcb : %p\n__GetTCB p_tcb->tid : %p\n", p_tcb, p_tcb->tid);
    }
    else if((p_tcb = Search(WaitQHead, a_tid)) != NULL){
        fprintf(stderr, "__GetTCB Search in wtq\n");
        printf("__GetTCB tcb : %p\n__GetTCB p_tcb->tid : %p\n", p_tcb, p_tcb->tid);
    }
    else{
        fprintf(stderr, "__GetTCB fail\n");
    }
    return p_tcb;
}


void    GetStatus(Thread* ap_queue_head){
// #define PPREV
// #define PNEXT
#define STATUS
#define BRUNNABLE
// #define JOINFLAG
#define EXITFLAG
#define pExitCode
// #define PARENTTID
#define TID
    char buf[100] = { 0, };
    int offset;
    Thread* p_cursor;
    int size = Size(ap_queue_head);

    if(ap_queue_head == ReadyQHead){
        sprintf(buf, "ReadyQ, size : %d\n", Size(ap_queue_head));
    }
    else if(ap_queue_head == WaitQHead){
        sprintf(buf, "WaitQ, size : %d\n", Size(ap_queue_head));
    }
    printf("%s", buf);
    if(size > 0){
        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|---------------");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);


        // Thread* adress
        p_cursor = ap_queue_head;
        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|-%-14s", "Thread*");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
        for(offset = 0; offset < size; offset++){
            sprintf(buf + (16 * offset), "| %14p", p_cursor);
            p_cursor = p_cursor->pNext;
        }
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);


        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|---------------");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);


        // Thread* pPrev
#ifdef PPREV
        p_cursor = ap_queue_head;
        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|-%-14s", "pPrev");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
        for(offset = 0; offset < size; offset++){
            sprintf(buf + (16 * offset), "| %14p", p_cursor->pPrev);
            p_cursor = p_cursor->pNext;
        }
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
#else
#endif


        // Thread* pNext
#ifdef PNEXT
        p_cursor = ap_queue_head;
        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|-%-14s", "pNext");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
        for(offset = 0; offset < size; offset++){
            sprintf(buf + (16 * offset), "| %14p", p_cursor->pNext);
            p_cursor = p_cursor->pNext;
        }
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
#else
#endif


        // ThreadStatus status
#ifdef STATUS
        p_cursor = ap_queue_head;
        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|-%-14s", "status");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
        for(offset = 0; offset < size; offset++){
            if(p_cursor->status == 0){
                sprintf(buf + (16 * offset), "| %14s", "RUN");
            }
            else if(p_cursor->status == 1){
                sprintf(buf + (16 * offset), "| %14s", "READY");
            }
            else if(p_cursor->status == 2){
                sprintf(buf + (16 * offset), "| %14s", "BLOCKED");
            }
            else{
                sprintf(buf + (16 * offset), "| %14s", "ZOMBIE");
            }
            p_cursor = p_cursor->pNext;
        }
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
#else
#endif


        // BOOL bRunnable
#ifdef BRUNNABLE
        p_cursor = ap_queue_head;
        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|-%-14s", "bRunnable");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
        for(offset = 0; offset < size; offset++){
            sprintf(buf + (16 * offset), "| %14d", p_cursor->bRunnable);
            p_cursor = p_cursor->pNext;
        }
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
#else
#endif


        // BOOL joinFlag
#ifdef JOINFLAG
        p_cursor = ap_queue_head;
        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|-%-14s", "joinFlag");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
        for(offset = 0; offset < size; offset++){
            sprintf(buf + (16 * offset), "| %14d", p_cursor->joinFlag);
            p_cursor = p_cursor->pNext;
        }
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
#else
#endif


        // BOOL exitFlag
#ifdef EXITFLAG
        p_cursor = ap_queue_head;
        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|-%-14s", "exitFlag");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
        for(offset = 0; offset < size; offset++){
            sprintf(buf + (16 * offset), "| %14d", p_cursor->exitFlag);
            p_cursor = p_cursor->pNext;
        }
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
#else
#endif


        // void* pExitCode
#ifdef PEXITCODE
        p_cursor = ap_queue_head;
        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|-%-14s", "pExitCode");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
        for(offset = 0; offset < size; offset++){
            sprintf(buf + (16 * offset), "| %14d", (int)(p_cursor->pExitCode));
            p_cursor = p_cursor->pNext;
        }
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
#else
#endif

        
        // thread_t parentTid
#ifdef PARENTTID
        p_cursor = ap_queue_head;
        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|-%-14s", "parentTid");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
        for(offset = 0; offset < size; offset++){
            sprintf(buf + (16 * offset), "| %14p", (void*)(p_cursor->parentTid));
            p_cursor = p_cursor->pNext;
        }
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
#else
#endif


        // thread_t tid
#ifdef TID
        p_cursor = ap_queue_head;
        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|-%-14s", "tid");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
        for(offset = 0; offset < size; offset++){
            sprintf(buf + (16 * offset), "| %14p", (void*)(p_cursor->tid));
            p_cursor = p_cursor->pNext;
        }
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
#else
#endif


        for(offset = 0; offset < size; offset++)
            sprintf(buf + (16 * offset), "|---------------");
        sprintf(buf + (16 * offset), "|\n");
        printf("%s", buf);
    }

    return;
}

#endif
