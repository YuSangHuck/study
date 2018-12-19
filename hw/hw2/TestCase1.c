#include "TestCase1.h"

 
void* Tc1ThreadProc(void* param)
{
    #ifdef LOG
    printf(" Tc1ThreadProc\n");   
    #endif 
    thread_t tid = 0;
    int count = 0;
    int* retVal;

    tid = thread_self();

    count = 3;
    while (count > 0)
    {
        // for(int i=0; i<99999999; i++);
        // fprintf(stderr, "Tc1ThreadProc: my thread id (%p), arg is (%d)\n", tid, (int)param);
        printf("Tc1ThreadProc: my thread id (%p), arg is (%d)\n", tid, (int)param);
        count--;
        /* sleep for 1 seconds */
        sleep(2);
    }
    retVal = (int*)param;
    thread_exit(retVal);
    return NULL;
}

/* 
 * - TestCase1 tests a round-robin scheduling of thread  
 * - Testing API scopes: thread_create
 */
void TestCase1(void)
{
    printf("TestCase1\n");
	thread_t tid[TOTAL_THREAD_NUM];
	
	thread_create(&tid[0], NULL, (void*)Tc1ThreadProc, (void*)1);
	thread_create(&tid[1], NULL, (void*)Tc1ThreadProc, (void*)2);
	thread_create(&tid[2], NULL, (void*)Tc1ThreadProc, (void*)3);
	thread_create(&tid[3], NULL, (void*)Tc1ThreadProc, (void*)4);
	thread_create(&tid[4], NULL, (void*)Tc1ThreadProc, (void*)5);

    // GetStatus(ReadyQHead);
    #ifdef LOG
	LOG_THREAD(child,TestCase1,TestCase1 while(1));
    #endif
	while(1){}
	
    return ;
}

