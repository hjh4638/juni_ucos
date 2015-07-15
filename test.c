#include "includes.h"

OS_STK MyTaskStack[1024];
OS_STK MyChildStack[1024];

void MyTask(void* pdata);
void MyChildTask(void* pdata);

int  main (void)
{
	int a;
	printf("main address = %d\n",&a);
    OSInit();
    OSTaskCreate(MyTask, (void *)0, &MyTaskStack[1023], 10);
    OSStart();
    return 0;
}


void  MyTask (void *pdata)
{
	OSTaskCreate(MyChildTask, (void*) 20, &MyChildStack[1023], 20);
	printf("start address = %d, end address = %d\n", MyTaskStack, &MyTaskStack[1023]);
	while(1){
		printf("10task\n");
		OSTaskSuspend(10);
	}
}
void MyChildTask(void* pdata){
	while(1){
		printf("20 task\n");
		OSTaskResume(10);
		OSTimeDly(1);
	}
}
