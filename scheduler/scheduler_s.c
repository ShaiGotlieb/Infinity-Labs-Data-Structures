#include <assert.h>
#include <stdlib.h> /* size_t */

#include "ol62_general.h" /*RG dont need this*/
#include "pqueue.h"
#include "uid.h"
#include "scheduler.h"
#include "task.h"



struct scheduler_s
{
	pqueue_t *queue; /* RG better to change the variable order in the struct according to their sizes*/
	int exit_status;
	task_t *current_task;
};

static boolean_t is_task_match(const void *data, const void *param)
{
	return (1 == UIDIsSame(TaskGetUID((task_t *)data), (*(task_uid_t *)param)) ? TRUE : FALSE);
}

boolean_t has_higher_priority(const void *task1, const void *task2)
{
	time_t time1 = TaskGetNextTimeToRun((task_t*)task1);
	time_t time2 = TaskGetNextTimeToRun((task_t*)task2);

	return (time1 > time2 ? TRUE : FALSE); /*RG can do in one row - TaskGetNextTimeToRun((task_t *)data1) > TaskGetNextTimeToRun((task_t *)data2) */
}

scheduler_t *TSCreate()
{
	scheduler_t *scheduler = (scheduler_t*)malloc(sizeof(scheduler_t));

	if (NULL == scheduler)
	{
		return (NULL);
	}

	scheduler->queue = PQCreate(has_higher_priority);

	if (NULL == scheduler->queue)
	{
		free(scheduler);
		return (NULL);
	}

	scheduler->current_task = NULL;
	scheduler->exit_status = 0;

	return (scheduler);
}

void TSDestroy(scheduler_t *scheduler)
{
	while (!TSIsEmpty(scheduler))
	{
		TaskDestroy(PQDequeue(scheduler->queue));
	}

	PQDestroy(scheduler->queue);
	scheduler->queue = NULL;
	scheduler->current_task = NULL; /*RG need to do TaskDestroy to current_task */
	free(scheduler); /* RG add scheduler = NULL*/
}

task_uid_t TSAddTask(scheduler_t *scheduler, size_t interval, task_f_t task_func, void *params)
{
	assert(NULL != scheduler);
	assert(NULL != task_func); /*RG not sure you need this assert*/

	scheduler->current_task = TaskCreate(interval, task_func, params);
	if (NULL == scheduler->current_task)
	{
		return (BAD_UID);
	}
	
	if (Q_MEMORY_ALLOCATION_ERROR == PQEnqueue(scheduler->queue, scheduler->current_task))
	{
		return (BAD_UID);
	}

	return (TaskGetUID(scheduler->current_task)); /*RG - why save it in current task? it needs to be Null until dequeue in run func..*/
}


status_t TSRemoveTask(scheduler_t *scheduler, task_uid_t id)
{
	void *return_from_erase = NULL;

	assert(NULL != scheduler);

	return_from_erase = PQErase(scheduler->queue, (is_match_q_t)is_task_match, &id);

	if (return_from_erase != NULL)
	{
		TaskDestroy(return_from_erase);
		return_from_erase = NULL;

		return SUCCESS;
	}
	 
	return (FAIL);
}

void TSStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);

	scheduler->exit_status = 1;
	/*TSRun(scheduler);*/ /*RG - remove this - dont need to run after stop...*/
}

size_t TSGetSize(const scheduler_t *scheduler) 
{
	return (PQGetSize(scheduler->queue));/*RG add assert*/
}

boolean_t TSIsEmpty(const scheduler_t *scheduler)
{
	return (PQIsEmpty(scheduler->queue));/*RG add assert*/
}

scheduler_status_t TSRun(scheduler_t *scheduler)
{	
	task_status_t exe_status;

	scheduler->exit_status = 0;

	while (!scheduler->exit_status && !TSIsEmpty(scheduler))
	{
		scheduler->current_task = PQDequeue(scheduler->queue);

		while(0 != sleep(TaskCalcTimeToSleep(scheduler->current_task)));

		exe_status = TaskExecute(scheduler->current_task);

		if (exe_status == RESCHEDULE)
		{
			if (Q_MEMORY_ALLOCATION_ERROR == PQEnqueue(scheduler->queue, TaskUpdateNextTimeToRun(scheduler->current_task)))
			{
				return (FAILED_SCHEDULER); /*RG - need to define this in API.. not sure we want to stop scheduler if enqueue failed.*/
			}
		}
		else
		{
			TaskDestroy(scheduler->current_task);
		}
	}

	return (TSIsEmpty(scheduler) ? EMPTY_SCHEDULER : STOPPED_SCHEDULER);
}

