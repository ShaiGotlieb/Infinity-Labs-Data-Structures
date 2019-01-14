#include <stdlib.h> /* size_t */

#include "uid.h"
#include "test.h"
#include "scheduler.h"
#include "ol62_general.h"
#include "task.h"

#define EMPTY (0)

TestResult TestTaskCreate();
TestResult TestTaskUpdateNextTimeToRun();
TestResult TestTaskCalcTimeToSleep();
TestResult TestTaskExecute();
TestResult TestTaskGetUID();

struct task_s
{
	void *params;
	time_t next_time_to_run;
	size_t interval;
	task_f_t func;
	task_uid_t uid;
};

int main()
{
	RUN_TEST(TestTaskCreate);
	RUN_TEST(TestTaskUpdateNextTimeToRun);
	RUN_TEST(TestTaskCalcTimeToSleep);
	RUN_TEST(TestTaskExecute);
	RUN_TEST(TestTaskGetUID);

	return (EXIT_SUCCESS);
}
task_status_t is_match_q(void *params)
{
	int *x;
	int *y;

	x = (int *)params;
	x++;
	y = x;


	if (*x == *y)
	{
		printf("TRUE\n");
		return RESCHEDULE;
	}

	printf("FALSE\n");
	return DONT_RESCHEDULE;
}

TestResult TestTaskCreate()
{
	int params[] = {1,1};
	task_t *task = TaskCreate(10, is_match_q, params);

	REQUIRE(NULL != task);

	TaskDestroy(task);

	return (TEST_PASS);
}

TestResult TestTaskUpdateNextTimeToRun()
{
	int params[] = {1,1};
	task_t *task = TaskCreate(10, is_match_q, params);

	task = TaskUpdateNextTimeToRun(task);

	REQUIRE(task->next_time_to_run = task->next_time_to_run+10);

	TaskDestroy(task);

	return (TEST_PASS);
}

TestResult TestTaskCalcTimeToSleep()
{
	int params[] = {1,1};
	task_t *task = TaskCreate(10, is_match_q, params);
	time_t now = time(NULL);
	size_t result;

	task = TaskUpdateNextTimeToRun(task);
	result = (task->next_time_to_run - now);

	REQUIRE(result == TaskCalcTimeToSleep(task));

	TaskDestroy(task);

	return (TEST_PASS);
}

TestResult TestTaskExecute()
{
	int params[] = {1,1};
	task_t *task = TaskCreate(10, is_match_q, params);
	task_status_t status = RESCHEDULE;

	task = TaskUpdateNextTimeToRun(task);
	status = TaskExecute(task);

	REQUIRE(status == RESCHEDULE);

	TaskDestroy(task);

	return (TEST_PASS);
}

TestResult TestTaskGetUID()
{
	int params[] = {1,1};
	task_t *task = TaskCreate(10, is_match_q, params);
	task_uid_t uid;

	uid = TaskGetUID(task);

	REQUIRE(1 == UIDIsSame(uid, task->uid));

	TaskDestroy(task);

	return (TEST_PASS);
}




