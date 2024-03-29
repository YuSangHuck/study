#include "TestCase2.h"

void* Tc2ThreadProc(void* param)
{
	thread_t tid = 0;
	int count = 5;
	int i;
	int* retVal;
	tid = thread_self();

	// if((int)param == 1)	count = 2;
	// else				count = 6;
	for(int i=0; i<count; i++){
		printf("Tc1ThreadProc: my thread id (%p), arg is (%d)\n", tid, (int)param);
		// count++;
		sleep(2);
		
	}             /* sleep for 1 seconds */
	retVal = (int*)param;
	thread_exit(retVal);
	return NULL;
}


/* 
 * - Testcase2 tests thread_join works successfully.
 * - 
 */
void
TestCase2(void)
{
	printf("TestCase2\n");
	thread_t tid[TOTAL_THREAD_NUM];
	int result[TOTAL_THREAD_NUM];

	int i = 0;
	thread_create(&tid[0], NULL, (void*)Tc2ThreadProc,(void*) 1);	
	thread_create(&tid[1], NULL, (void*)Tc2ThreadProc,(void*) 2);	
	thread_create(&tid[2], NULL, (void*)Tc2ThreadProc,(void*) 3);	
	thread_create(&tid[3], NULL, (void*)Tc2ThreadProc,(void*) 4);	
	thread_create(&tid[4], NULL, (void*)Tc2ThreadProc,(void*) 5);
	
	for(i=0;i<TOTAL_THREAD_NUM;i++)
	{
		int retVal;
		thread_join(tid[i], (void **)&retVal);

		printf("Thread [ %p ] is finish Return : [ %d ] \n", tid[i], retVal);
	}

	return ;
}
