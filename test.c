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
OS_FLAG_GRP* sync;

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
	sync = OSFlagCreate(0,&err);
	
	printf("MyTask end\n");

	//SoundTask甫 刚历 积己秦具窃.
	OSTaskCreate(SoundTask, (void*) 30, &MyChildStack2[1023], 10);
	OSTaskCreate(KeyTask, (void*) 20, &MyChildStack[1023], 11);
	OSTaskCreate(AlgoTask, (void*) 20, &MyChildStack3[1023], 12);

}
void KeyTask(void* pdata){
	INT8U err;
	while(1){
		OSTimeDly(1);
		printf("Key input!\n");
		OSFlagPost(sync,0x01,OS_FLAG_SET,&err);
	}
}
void SoundTask(void* pdata){
	INT8U err;
	while(1){
		OSFlagPend(sync,0x03,OS_FLAG_WAIT_SET_ALL+OS_FLAG_CONSUME,0,&err);
		printf("Sound Executing\n");
	}
}
void AlgoTask(void* pdata){
	INT8U err;
	while(1){
		OSTimeDly(1);
		printf("AlgoTask post!!\n");
		OSFlagPost(sync,0x02,OS_FLAG_SET,&err);

	}

}
