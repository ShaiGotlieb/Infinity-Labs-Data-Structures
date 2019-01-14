#ifndef __H_TASK__
#define __H_TASK__
#include <time.h>
#include <stdlib.h>

#include "ol62_general.h"

/***********************************************************************
* This file contains the API of a task.
* 
* The task enables the user to create a task to be executed
*
* Written by: 		OL62
* Last updated : 	10.1.2019
***********************************************************************/

typedef struct task_s task_t;


task_t *TaskCreate(size_t interval, task_f_t task_func, void *params);
/***********************************************************************
* TaskCreate - creates a new task.
*
* interval - the time interval in which the task should run periodically.
* 			in seconds. if interval is set to 0, than the task should run only 
* 			once.
* task_func - the function that task is responsible for its execution.
* 			the function should be of type: task_f_t.
* params - additional parameters that can sent to the function. If params is 
*			not used, send NULL.
* 
* Returns - a pointer to the new task. 
* 			if memory allocation failed, NULL is returned.
*
***********************************************************************/

void TaskDestroy(task_t *task);
/***********************************************************************
* TaskDestroy - Frees the memory allocated for the task.
*
* task - pointer to the task. not NULL.
*
***********************************************************************/

task_t *TaskUpdateNextTimeToRun(task_t *task);
/***********************************************************************
* TaskUpdateNextTimeToRun - updates the time for next
* execution of the task. Adds the interval to the current time.
*
* task - pointer to the task. not NULL.
*
* returns - the updated task. 
***********************************************************************/
size_t TaskCalcTimeToSleep(const task_t *task);
/**************************************************************** 
 * TaskCalcTimeToSleep - calculates the time to the next execution
 * of a task.
 *
 * task - a pointer to the task. not NULL.
 *
 * return - the time in seconds to the next execution of
 * the task
 ***************************************************************/

task_status_t TaskExecute(task_t *task);
/***********************************************************************
* TaskExecute - executes the task.
*
* task - a pointer to the task. not NULL.
*
* Returns - task_status_t 
***********************************************************************/

task_uid_t TaskGetUID(task_t *task);

size_t TaskGetInterval(task_t *task);
time_t TaskGetNextTimeToRun(task_t *task);
task_f_t TaskGetFunc(task_t *task);
void *TaskGetparams(task_t *task);

#endif