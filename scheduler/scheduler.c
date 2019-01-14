#include <assert.h>

#include "pqueue.h"
#include "uid.h"
#include "scheduler.h"
#include "task.h"

struct scheduler_s
{
	pqueue_t *queue;
	task_t *current_task;
	int exit_status;
};

static boolean_t is_task_match(const void *data, const void *param)
{
	return (1 == UIDIsSame(TaskGetUID((task_t *)data), (*(task_uid_t *)param)) ? TRUE : FALSE);
}

boolean_t has_higher_priority(const void *task1, const void *task2)
{
	return TaskGetNextTimeToRun((task_t *)task1) <= TaskGetNextTimeToRun((task_t *)task2);
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
	scheduler->current_task = NULL;
	free(scheduler);
	scheduler = NULL;
}

task_uid_t TSAddTask(scheduler_t *scheduler, size_t interval, task_f_t task_func, void *params)
{
	assert(NULL != scheduler);

	scheduler->current_task = TaskCreate(interval, task_func, params);
	if (NULL == scheduler->current_task)
	{
		return (BAD_UID);
	}
	
	if (Q_MEMORY_ALLOCATION_ERROR == PQEnqueue(scheduler->queue, scheduler->current_task))
	{
		return (BAD_UID);
	}

	return (TaskGetUID(scheduler->current_task));
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
}

size_t TSGetSize(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);

	return (PQGetSize(scheduler->queue));
}

boolean_t TSIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (PQIsEmpty(scheduler->queue));
}

scheduler_status_t TSRun(scheduler_t *scheduler)
{	
	task_status_t exe_status;
	scheduler->exit_status = 0;

	while (1 != scheduler->exit_status && !TSIsEmpty(scheduler))
	{
		scheduler->current_task = PQDequeue(scheduler->queue);

		while(0 != sleep(TaskCalcTimeToSleep(scheduler->current_task)));

		exe_status = TaskExecute(scheduler->current_task);

		if (exe_status == RESCHEDULE)
		{
			if (Q_MEMORY_ALLOCATION_ERROR == PQEnqueue(scheduler->queue, TaskUpdateNextTimeToRun(scheduler->current_task)))
			{
				return (FAILED_SCHEDULER);
			}
		}
		else
		{
			TaskDestroy(scheduler->current_task);
		}
	}

	return (TSIsEmpty(scheduler) ? EMPTY_SCHEDULER : STOPPED_SCHEDULER);
}

