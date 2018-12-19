// @ test for signal handler
// #include <stdio.h>
// #include <signal.h>
// void handler(int signo){
//     printf("  handler called\n");
// }
// int main(){
//     sigset_t set;
//     sigemptyset(&set);
//     sigaddset(&set, SIGUSR1);

//     struct sigaction act;
//     act.sa_handler = handler;
//     sigaction(SIGUSR1, &act, NULL);
//     while(1){
//         int signum;
//         printf("waiting...\n");
//         sigwait(&set, &signum);
//         printf("pass!\n");
//     }
//     return 0;
// }

// @ test for #define
// #include <stdio.h>
// #define LOG_THREAD(thread, func, msg)   
// int main(){
//     LOG_THREAD(parent, thread_create, 6.unlock mutex);
//     LOG_THREAD(child, __wrapperFunc, 0.lock mutex);
//     printf("%p\n", NULL);
// }

// // @ test for pthread_join
// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #define TOTAL_THREAD_NUM    3

// void* Tc2ThreadProc(void* param)
// {
//     printf("Tc2ThreadProc\n");
//     pthread_t tid = 0;
//     int* retVal;
//     tid = pthread_self();
//     int cnt;
//     if((int)param == 0) cnt = 10;
//     else                cnt = 1;
//     for(int i=0; i<=cnt; i++){
//         sleep(1);
//         printf("Tc1ThreadProc: my thread id (%d), arg is (%d)\n", (int)tid, (int)param);
        
//     }             /* sleep for 1 seconds */
//     retVal = (int*)param;
//     pthread_exit(retVal);
//     for(int i=0; i<=cnt; i++){
//         sleep(1);
//         printf("Tc1ThreadProc: my thread id (%d), arg is (%d)\n", (int)tid, (int)param);
        
//     }             /* sleep for 1 seconds */
    
//     return NULL;
// }


// /* 
//  * - Testcase2 tests thread_join works successfully.
//  * - 
//  */
// void TestCase2(void)
// {
//     printf("TestCase2\n");
// 	pthread_t tid[TOTAL_THREAD_NUM];
// 	int result[TOTAL_THREAD_NUM];

// 	int i = 0;
//     for(int i=0; i<TOTAL_THREAD_NUM; i++){
//         pthread_create(&tid[i], NULL, (void*)Tc2ThreadProc, (void*)i);
//     }
// 	// pthread_create(&tid[0], NULL, (void*)Tc2ThreadProc,(void*) 1);	
// 	// pthread_create(&tid[1], NULL, (void*)Tc2ThreadProc,(void*) 2);	
// 	// pthread_create(&tid[2], NULL, (void*)Tc2ThreadProc,(void*) 3);	
// 	// pthread_create(&tid[3], NULL, (void*)Tc2ThreadProc,(void*) 4);	
// 	// pthread_create(&tid[4], NULL, (void*)Tc2ThreadProc,(void*) 5);
	
// 	for(i=0;i<TOTAL_THREAD_NUM;i++)
// 	{
// 		int retVal;
// 		pthread_join(tid[i],(void **)&retVal);

// 		printf("Thread [ %d ] is finish Return : [ %d ] \n",(int)tid[i], retVal);
// 	}

// 	return ;
// }

// int main(){
//     pthread_t tid;
//     pthread_create(&tid, NULL, TestCase2, (void*)0);
//     int ret;
//     pthread_join(tid, (void**)&ret);
//     printf("TestCase2 exit %d\n", ret);
//     return 0;
//     // pthread_exit후에 작동하는지 확인.
// }



// // @ test for Queue
// #include "Queue.h"
// #include <stdlib.h>
// #define PUSH        1
// #define POP         2
// #define GETSTATUS   3
// void Manual(){
//     printf("1.Push(Head)\t2.Pop()\t3.GetStatus\n");
// }
// int main(){
//     srand(time(NULL));
//     while(1){
//         Manual();
//         int p;
//         scanf("%d", &p);
//         if(p == PUSH){
//             if(Size(ReadyQHead) == 0){
//                 Thread* tcb = (Thread*)malloc(sizeof(Thread));
//                 tcb->status = rand() % 4;
//                 tcb->parentTid = rand() % 10000;
//                 tcb->tid = rand() % 10000;
//                 tcb->bRunnable = 0;
//                 tcb->pPrev = 0;
//                 tcb->pNext = 0;
//                 Push(&ReadyQHead, &ReadyQTail, &tcb);
//             }
//             else{
//                 Push(&ReadyQHead, &ReadyQTail, &ReadyQHead);
//             }
//         }
//         else if(p == POP){
//             if(Size(ReadyQHead) == 0){
//                 printf("Queue is empty\n");
//             }
//             else{
//                 Pop(&ReadyQHead, &ReadyQTail);
//             }
//         }
//         else if(p == GETSTATUS){
//             GetStatus(ReadyQHead);
//         }
//         else{
//             printf("wrong manual\n");
//         }
//     }

// }

// @ test for system_call of thread_exit 
#include <pthread.h>

int main(){
    pthread_exit(NULL);
    printf("h\n");
    return 0;
}