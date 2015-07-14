#include "includes.h"

OS_STK MyTaskStack[1024];
OS_STK MyChildStack[1024];

void MyTask(void* pdata);
void MyChildTask(void* pdata);

int res;
OS_EVENT* mu;

int  main (void)
{
	int a;
	printf("main address = %d\n",&a);
	OSInit();
	OSTaskCreate(MyTask, (void *)0, &MyTaskStack[1023], 10);
	OSTaskCreate(MyChildTask, (void*) 20, &MyChildStack[1023], 20);
	OSStart();
	return 0;
}


void  MyTask (void *pdata)
{
	INT8U err;
	mu = OSMutexCreate(2,&err);
	
	while(1){
		OSTimeDly(1);
		OSMutexPend(mu,0,&err);
		res = 0;
		OSMutexPost(mu);
		OSTimeDly(1);
	}

}
void MyChildTask(void* pdata){
	INT8U err;
	while(1){
		OSMutexPend(mu,0,&err);
		res = 3;
		OSTimeDly(1);
		res+=5;
		printf("Result = %d\n", res);
		OSMutexPost(mu);
	}
}
