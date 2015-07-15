#include "includes.h"

OS_STK MyTaskStack[1024];
OS_STK MyChildStack[1024];
OS_STK MyChildStack2[1024];
OS_STK MyChildStack3[1024];

void MyTask(void* pdata);
void KeyTask(void* pdata);
void SoundTask(void* pdata);
void AlgoTask(void* pdata);

int res;
OS_EVENT* sync;

int  main (void)
{
	int a;
	printf("main address = %d\n",&a);
	OSInit();
	OSTaskCreate(MyTask, (void *)0, &MyTaskStack[1023], 40);
	OSStart();
	return 0;
}


void  MyTask (void *pdata)
{

	INT8U err;
	printf("MyTask start\n");

	sync = OSMboxCreate(0);

	printf("MyTask end\n");

	//SoundTask甫 刚历 积己秦具窃.
	OSTaskCreate(SoundTask, (void*) 30, &MyChildStack2[1023], 10);
	OSTaskCreate(KeyTask, (void*) 20, &MyChildStack[1023], 11);
//	OSTaskCreate(AlgoTask, (void*) 20, &MyChildStack3[1023], 12);

}
void KeyTask(void* pdata){
	INT8U err;
	while(1){
		OSTimeDly(1);
		printf("Key input!\n");
		OSMboxPost(sync,100);
	}
}
void SoundTask(void* pdata){
	INT8U err;
	int msg;
	while(1){
		msg = OSMboxPend(sync,0,&err);
		printf("Sound Executing msg = %d\n", msg);
	}
}
void AlgoTask(void* pdata){
	INT8U err;
	while(1){
		OSTimeDly(1);
		printf("AlgoTask post!!\n");

	}

}
