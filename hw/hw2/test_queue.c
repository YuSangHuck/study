#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Init.h"
#include "Queue.h"
#include "Thread.h"
void Manual(){
    printf("/*\n * %-10s%-10s\n * %-10s%-10s\n * %-10s%-10s\n * %-10s%-10s\n*/\n", "1.Size", "2.Empty",
                                                                            "3.Front", "4.Back",
                                                                            "5.Push", "6.Pop",
                                                                            "7.Search", "8.Remove");
}
int main(){
    srand(time(NULL));
    
    Init();

    queue* q = Queue(READY_QUEUE);
    queue*  Queue(int a_type);
    
    while(1){
        Manual();
        int n;
        scanf("%d", &n);
        if(n == 1){
            int size = Size(q);
            if(size == -1)
                printf("Size error\n");
            else
                printf("Size : %d\n", size);
        }
        else if(n == 2){
            int empty = Empty(q);
            if(empty == -1)
                printf("Empty error\n");
            else
                printf("Empty : %d\n", empty);
        }
        else if(n == 3){
            Thread* tcb = Front(q);
            if(tcb == NULL)
                printf("Front error\n");
            else
                printf("Front : %d\n", tcb);
        }
        else if(n == 4){
            Thread* tcb = Back(q);
            if(tcb == NULL)
                printf("Back error\n");
            else
                printf("Back : %d\n", tcb);
        }
        else if(n == 5){
            Thread* tcb = (Thread*)malloc(sizeof(Thread));
            tcb->status = rand() % 4;
            tcb->tid = rand();
            tcb->bRunnable = rand();
            tcb->parentTid = rand();
            tcb->pPrev = NULL;
            tcb->pNext = NULL;
            int ret = Push(q, tcb);
            if(ret == -1)
                printf("Push error\n");
            else
                printf("Push Success\n");
        }
        else if(n == 6){
            Thread* tcb = Front(q);
            if(tcb == NULL)
                printf("Front error in Pop Func\n");
            int ret = Pop(q);
            free(tcb);
            if(ret == -1)
                printf("Pop error\n");
            else
                printf("Pop Success\n");
        }
        else if(n == 7){
            thread_t tid;
            printf("thread_t : ");
            scanf("%lu", &tid);
            Thread* tcb = Search(q, tid);
            if(tcb == NULL)
                printf("Search error\n or \nThere is no TCB\n");
            else
                printf("Search : %d\n", tcb);
        }
        else{
            int tcb;
            printf("Thread* : ");
            scanf("%d", &tcb);
            int ret = Remove(q, (Thread*)tcb);
            if(ret == -1)
                printf("Remove error\n");
            else
                printf("Remove Success\n");
        }
        GetStatus(q);
    }
    return 0;
}
