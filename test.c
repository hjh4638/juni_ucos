#include "includes.h"

OS_STK MyTaskStack[1024];

void MyTask(void* pdata);

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
	printf("start address = %d, end address = %d\n", MyTaskStack, &MyTaskStack[1023]);
	while(1);
}

