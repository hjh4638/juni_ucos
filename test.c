#include "includes.h"

OS_STK MyTaskStack[1024];
OS_STK MyChildStack[1024];

void MyTask(void* pdata);
void KeyTask(void* pdata);
void SoundTask(void* pdata);

int res;
OS_EVENT* sync;

int  main (void)
{
	int a;
	printf("main address = %d\n",&a);
	OSInit();
	OSTaskCreate(MyTask, (void *)0, &MyTaskStack[1023], 10);
	OSTaskCreate(KeyTask, (void*) 20, &MyChildStack[1023], 20);
	OSTaskCreate(SoundTask, (void*) 30, &MyChildStack[1023], 30);
	OSStart();
	return 0;
}


void  MyTask (void *pdata)
{
	sync = OSSemCreate(0);
	while(1){
	}

}
void KeyTask(void* pdata){
	while(1){
		printf("Key input!\n");
		OSSemPost(sync);
	}
}
void SoundTask(void* pdata){
	INT8U err;
	while(1){
		OSSemPend(sync,0,&err);
		printf("Sound Executing\n");
	}
}
