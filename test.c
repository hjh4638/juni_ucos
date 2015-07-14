#include "includes.h"

#define  TASK_STK_SIZE 512

OS_STK TaskStk[TASK_STK_SIZE];

void  TaskStart(void *data);

int  main (void)
{
    OSInit();
    OSTaskCreate(TaskStart, (void *)0, &TaskStk[TASK_STK_SIZE - 1], 1);
    OSStart();
    return 0;
}


void  TaskStart (void *pdata)
{
	INT16U i;
	for(i = 0; ; i++){
		printf("test : %d\n", i);
	}	
}

