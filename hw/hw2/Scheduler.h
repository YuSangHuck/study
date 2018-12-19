#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__
// #include "Init.h"
#include "Thread.h"
#include "Queue.h"
#include "Common.h"
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

void    __ContextSwitch(Thread* pCurThread, Thread* pNewThread);
int		RunScheduler( void );


#endif
