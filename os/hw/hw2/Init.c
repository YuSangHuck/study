#include "Init.h"

void Init(){
    // Init.h�� ��������

    // Queue.h�� ��������

    // Scheduler.h�� ��������

    // TestCase1,2,3.h�� ��������

    // Thread.h�� ��������
    ReadyQHead = NULL;
    ReadyQTail = NULL;
    WaitQHead = NULL;
    WaitQTail = NULL;

    // Common.h
    pthread_mutex_init(&g_mutex, NULL);
    pthread_cond_init(&g_cond, NULL);
}
