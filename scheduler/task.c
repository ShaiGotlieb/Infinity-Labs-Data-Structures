#include <stdlib.h> /* size_t, malloc */
#include <assert.h> /* assert */

#include "uid.h"
#include "scheduler.h"
#include "task.h"

struct task_s
{
	void *params;
	time_t next_time_to_run;
	size_t interval;
	task_f_t func;
	task_uid_t uid;
};

task_t *TaskCreate(size_t interval, task_f_t task_func, void *params)
{
	task_t *task = (task_t *)malloc(sizeof(task_t));

	if (NULL == task)
	{
		return (NULL);
	}

	task->uid = UIDCreate();
	task->next_time_to_run = time(NULL) + interval;
	task->interval = interval;
	task->params = params;
	task->func = task_func;

	return (task);
}

void TaskDestroy(task_t *task) 
{
	free(task);
	task = NULL;
}

task_t *TaskUpdateNextTimeToRun(task_t *task)
{
	assert(NULL != task);

	task->next_time_to_run = time(NULL) + task->interval;

	return (task);
}

size_t TaskCalcTimeToSleep(const task_t *task)
{
	time_t now = time(NULL);
	
	assert(NULL != task);

	return (task->next_time_to_run > now ? task->next_time_to_run - now : 0);
}

task_status_t TaskExecute(task_t *task)
{
	assert(NULL != task);

	return (task->func(task->params));
}

task_uid_t TaskGetUID(task_t *task)
{
	assert(NULL != task);

	return (task->uid);
}

size_t TaskGetInterval(task_t *task)
{
	return (task->interval);
}

time_t TaskGetNextTimeToRun(task_t *task)
{
	return (task->next_time_to_run);
}

task_f_t TaskGetFunc(task_t *task)
{
	return (task->func);
}

void *TaskGetparams(task_t *task)
{
	return (task->params);
}