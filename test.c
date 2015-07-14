#include "includes.h"

#define  TASK_STK_SIZE 512

OS_STK TaskStk[TASK_STK_SIZE];

void  TaskStart(void *data);

int  main (void)
{
    OSInit();
    PC_DOSSaveReturn();
    //PC_VectSet(uCOS, OSCtxSw);
    OSTaskCreate(TaskStart, (void*)0, (void*)&TaskStk[TASK_STK_SIZE-1], 0);
    OSStart();
    return 0;
}


void  TaskStart (void *pdata)
{
//	OS_ENTER_CRITICAL();
	PC_VectSet(0x08, OSTickISR);
	PC_SetTickRate(OS_TICKS_PER_SEC);
//	OS_EXIT_CRITICAL();

	for(;;)
	{
		printf("Task Run");
		OSTimeDly(100);
	}

}

