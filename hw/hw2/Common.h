#ifndef __COMMON_H__
#define __COMMON_H__
#include <stdio.h>
#include <pthread.h>
#include "Thread.h"
#include "Queue.h"
#define TRUE    1
#define FALSE   0
// #define LOG
#ifdef LOG
#define LOG_THREAD(thread,func,msg) fprintf(stderr, "[%-15s]  [%-15s]  %s\n", #thread, #func, #msg)
#define LOG_FUNC(func,msg)          fprintf(stderr, "%19s[%-15s]  %s\n", "",#func, #msg)
#else
#define LOG_THREAD(thread,func,msg)
#define LOG_FUNC(func,msg)          
#endif
void __thread_wait_handler(int signo);
void __thread_wakeup(Thread* thread);

pthread_mutex_t g_mutex;
pthread_cond_t g_cond;

#endif