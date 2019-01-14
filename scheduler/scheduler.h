#ifndef __H_SCHEDULER__
#define __H_SCHEDULER__

#include "ol62_general.h"

/***********************************************************************
 * This file contains the API of The Task Scheduler
 *
 *                                                				
 * Written by: 		Shai Gotlieb    								
 * Last updated : 	14.1.2019 
 ***********************************************************************/

typedef enum {RESCHEDULE = 0, DONT_RESCHEDULE = 1} task_status_t;
typedef task_status_t (*task_f_t)(void *params);

typedef struct scheduler_s scheduler_t;
typedef enum {STOPPED_SCHEDULER = 0, EMPTY_SCHEDULER = 1, FAILED_SCHEDULER = 2} scheduler_status_t;

extern const task_uid_t BAD_UID;

/*timeval*/

scheduler_t *TSCreate(void);
/********************************************************************
* TSCreate - Creates a scheduler.
*
* Return - a pointer to scheduler_t if successful, NULL otherwise.
********************************************************************/

void TSDestroy(scheduler_t *scheduler);
/********************************************************************
* TSDestroy - Destroys a scheduler. Frees all memory allocated when
* scheduler is created.
*
* scheduler - a scheduler to destroy. NOT NULL.
*
********************************************************************/

task_uid_t TSAddTask(scheduler_t *scheduler, size_t interval,
					 task_f_t task_func, void *params);
/********************************************************************
* TSAddTask  - Adds a task to a scheduler. The scheduler is responsible 
* that the task will execute the task_func every 'interval' seconds. 
* TSAddTask calculates the next time to run for the task, when a task
* is added.
* 
* scheduler - a scheduler to which the task will be added. NOT NULL.
*
* interval - the time interval, in seconds, which defines the 
* frequency in which the task will be performed.
*
* task_func - the function that will be performed when it is time
* to perform the task. The return value must be of type task_status_t
*
* params - parameters for the task_func, which the user provides.
*
* Return - the uid of the task added. If unsuccessful, returns BAD_UID.
********************************************************************/

status_t TSRemoveTask(scheduler_t *scheduler, task_uid_t id);
/********************************************************************
* Removes a task from a scheduler.
* 
* scheduler - a scheduler from which the task will be removed. 
* NOT NULL.
*
* id - the unique id of the task to be removed.

* Return - TBD
********************************************************************/

scheduler_status_t TSRun(scheduler_t *scheduler);
/********************************************************************
* TSRun - Runs the task scheduler. Blocking - The scheduler will run until
* it is empty or until the user will call the TSStop function. 
* For more information: TSStop(). 
* The tasks are executed according to their scheduled time.
* if the time for task has passed, task will be performed according
* to the order and not by scheduled time.
*
* scheduler - the scheduler from which the tasks will be performed.
* NOT NULL.
*
* Return - scheduler_status_t which describes why the scheduler
* stopped running. If the task failed to re-insert to scheduler, 
* 'FAILED_SCHEDULER' will be returned.
********************************************************************/

void TSStop(scheduler_t *scheduler);
/********************************************************************
* TSStop - By calling TSStop() from within a task function, the scheduler will
* stop running, after performing the task. It is possible to call TSRun
* after it was stopped.
*
* scheduler - the scheduler from which the tasks will be performed.
* NOT NULL.
********************************************************************/

size_t TSGetSize(const scheduler_t *scheduler);
/********************************************************************
* TSGetSize - Calculates the number of tasks in scheduler.
*
* scheduler - the scheduler in which the number of tasks will
* be calculated.
*
* Return - the number of tasks in scheduler.
********************************************************************/

boolean_t TSIsEmpty(const scheduler_t *scheduler);
/********************************************************************
* TSIsEmpty - Checks whether the scheduler is empty of tasks.
*
* scheduler - the scheduler which will be checked if it is empty.
*
* returns - TRUE if scheduler is empty. FALSE otherwise.
********************************************************************/
#endif