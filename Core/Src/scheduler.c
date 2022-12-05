/*
 * scheduler.c
 *
 *  Created on: Dec 5, 2022
 *      Author: PC PHUONG
 */
#include "scheduler.h"
sTask SCH_tasks_G[SCH_MAX_TASKS] ;

void SCH_Init(void){
	unsigned char i ;
	for ( i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_Delete_Task(i) ;
	}
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*−
SCH_Add_Task () Causes a task ( function ) to be executed at regular intervals
or after a user−defined delay
−*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/
unsigned char SCH_Add_Task( void(* pFunction)() , unsigned int DELAY, unsigned int PERIOD){
	unsigned char Index = 0;
	// First find a gap in the array ( i f there i s one)
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)){
		Index++;
	}
	// Have we reached the end of the list ?
	if(Index >= SCH_MAX_TASKS){
		return SCH_MAX_TASKS;
	}
	//If we’re here , there is a space in the task array
	SCH_tasks_G[Index].pTask = pFunction ;
	SCH_tasks_G[Index].Delay = DELAY;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe = 0;

	SCH_tasks_G[Index].TaskID = Index;
	//return position of task (to allow later deletion)
	return Index;
}

void SCH_Update(void){
	unsigned char Index ;
	// NOTE: calculations are in *TICKS* ( not milliseconds )
	for ( Index = 0; Index < SCH_MAX_TASKS; Index++) {
		// Check if there is a task at this location
		if (SCH_tasks_G[Index].pTask){
			if(SCH_tasks_G[Index].Delay == 0){
				// The task is due to run
				// Inc . the ’RunMe’ flag
				SCH_tasks_G[Index].RunMe++;
				if (SCH_tasks_G[Index].Period > 0){
					// Schedule periodic tasks to run again
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			} else{
				// Not yet ready to run : just decrement the delay
				SCH_tasks_G[Index].Delay -= 1;
			}
		}
	}
}


void SCH_Dispatch_Tasks(void){
	unsigned char Index;
	//Dispatches (runs) the next task (if one is ready)
	for(Index = 0; Index < SCH_MAX_TASKS; Index++){
		if(SCH_tasks_G[Index].RunMe > 0){
			(*SCH_tasks_G[Index].pTask)() ; // Run the task
			SCH_tasks_G[Index].RunMe--; // Reset / reduce RunMe flag
			//Periodic tasks will automatically run again
			// - if this is a 'one shot' task, remove it from the array
			if(SCH_tasks_G[Index].Period == 0){
				SCH_Delete_Task(Index);
			}
		}
	}
}

int SCH_Delete_Task(uint32_t TASK_INDEX) {
	if(!SCH_tasks_G[TASK_INDEX].pTask){
		return -1;
	}
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	SCH_tasks_G[TASK_INDEX].TaskID = 0;

	return 0; //return status

}

