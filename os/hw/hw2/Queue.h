#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stdio.h>
#include <stdlib.h>
#include "Thread.h"
// #define WITH_QUEUE

#ifdef WITH_QUEUE
#define READY_QUEUE 1
#define WAIT_QUEUE  2
typedef struct _queue{
    Thread* m_head;
    Thread* m_tail;
    int m_size;
    int m_type;
} queue;
queue*  Queue(int a_type);
int     Size(queue* ap_queue);
int     Empty(queue* ap_queue);
Thread* Front(queue* ap_queue);
Thread* Back(queue* ap_queue);
int     Push(queue* ap_queue, Thread* ap_thread);
int     Pop(queue* ap_queue);
Thread* Search(queue* ap_queue, thread_t a_tid);
int     Remove(queue* ap_queue, Thread* ap_thread);
void    GetStatus(queue* ap_queue);

#else
int     Size(Thread* ap_queue_head);
int     Empty(Thread* ap_queue_head);
int     Push(Thread** ap_queue_head, Thread** ap_queue_tail, Thread** ap_thread);
int     Pop(Thread** ap_queue_head, Thread** ap_queue_tail);
Thread* Search(Thread* ap_queue_head, thread_t a_tid);
int     Remove(Thread** ap_queue_head, Thread** ap_queue_tail, Thread* ap_thread);
void    GetStatus(Thread* ap_queue_head);

#endif

#endif
