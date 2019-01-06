#include <stdlib.h> /*size_t, EXIT_SUCCESS*/
#include <string.h> /*strcmp, memcmp*/

#include "test.h"
#include "queue.h"

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))


TestResult TestQueCreateDestroy(void);
TestResult TestEnqueue(void);
TestResult TestDequeue(void);
TestResult TestQuePeek(void);
TestResult TestQueIsEmpty(void);
TestResult TestQueGetSize(void);
TestResult TestQueAppend(void);

static int g_test_data[] = {1,2,3,4,5,6,7,8,9,10};

int main(void) 
{

	RUN_TEST(TestQueCreateDestroy);
	RUN_TEST(TestEnqueue);
	RUN_TEST(TestDequeue);
	RUN_TEST(TestQuePeek);
	RUN_TEST(TestQueIsEmpty);
	RUN_TEST(TestQueGetSize);
	RUN_TEST(TestQueAppend);

   	return EXIT_SUCCESS;
}

static void FillQueueWithData(queue_t *new_test_queue)
{
	size_t i = 0;

	for (i = 0; i < ARRAY_SIZE(g_test_data); ++i)	
	{
		Enqueue(new_test_queue, &g_test_data[i]);
	}
	
}

TestResult TestQueCreateDestroy(void)
{
	queue_t *test_queue;
	
	test_queue = QueCreate();
	REQUIRE	(NULL != test_queue);

	QueDestroy(test_queue);

	return (TEST_PASS);	
}


TestResult TestEnqueue(void)
{
	queue_t *test_queue;

	test_queue = QueCreate();
	REQUIRE	(NULL != test_queue);
	
	REQUIRE	(Q_SUCCESS == Enqueue(test_queue, &g_test_data[0]));

	QueDestroy(test_queue);

	return (TEST_PASS);	
}


TestResult TestDequeue(void)
{
	queue_t *test_queue;
	void *data_dequeued ;

	test_queue = QueCreate();
	REQUIRE	(NULL != test_queue);
	
	REQUIRE	(Q_SUCCESS == Enqueue(test_queue, &g_test_data[0]));
	data_dequeued = Dequeue(test_queue);
	REQUIRE	(g_test_data[0] == *(int *)data_dequeued);

	QueDestroy(test_queue);

	return (TEST_PASS);	
}

TestResult TestQueIsEmpty(void)
{
	queue_t *test_queue;
	
	test_queue = QueCreate();
	
	REQUIRE	(1 == QueIsEmpty(test_queue));
	REQUIRE	(Q_SUCCESS == Enqueue(test_queue, &g_test_data[0]));
	REQUIRE	(0 == QueIsEmpty(test_queue));
	REQUIRE	(g_test_data[0] == *(int *)Dequeue(test_queue));
	REQUIRE	(1 == QueIsEmpty(test_queue));

	QueDestroy(test_queue);

	return (TEST_PASS);	
}

TestResult TestQueGetSize(void)
{
	queue_t *test_queue;
	void *data_dequeued ;
	size_t i;
	
	test_queue = QueCreate();
	
	REQUIRE	(0 == QueGetSize(test_queue));
	REQUIRE	(Q_SUCCESS == Enqueue(test_queue, &g_test_data[0]));
	REQUIRE	(1 == QueGetSize(test_queue));
	REQUIRE	(g_test_data[0] == *(int *)Dequeue(test_queue));
	REQUIRE	(0 == QueGetSize(test_queue));

	for (i = 0; i < ARRAY_SIZE(g_test_data); ++i) 
	{
		REQUIRE	(Q_SUCCESS == Enqueue(test_queue, &g_test_data[i]));
		REQUIRE	((i + 1) == QueGetSize(test_queue));
	}

	for (i = ARRAY_SIZE(g_test_data); i > 0; --i) 
	{
		data_dequeued = Dequeue(test_queue);
		REQUIRE	(i-1 == QueGetSize(test_queue));
		REQUIRE	(g_test_data[ARRAY_SIZE(g_test_data)-i] == *(int *)data_dequeued);
	}
	
	REQUIRE	(1 == QueIsEmpty(test_queue));

	REQUIRE	(Q_SUCCESS == Enqueue(test_queue, &g_test_data[0]));
	REQUIRE	(1 == QueGetSize(test_queue));
	REQUIRE	(0 == QueIsEmpty(test_queue));
	REQUIRE	(g_test_data[0] == *(int *)Dequeue(test_queue));
	REQUIRE	(0 == QueGetSize(test_queue));
	REQUIRE	(1 == QueIsEmpty(test_queue));

	QueDestroy(test_queue);

	return (TEST_PASS);	
}


TestResult TestQuePeek(void)
{
	queue_t *test_queue;
	void *data_dequeued ;
	size_t i;
	
	test_queue = QueCreate();

/*printf("peek empty = %p\n",QuePeek(test_queue) );
*/
	REQUIRE	(0 == QueGetSize(test_queue));
	REQUIRE	(Q_SUCCESS == Enqueue(test_queue, &g_test_data[0]));
	REQUIRE	(1 == QueGetSize(test_queue));
	REQUIRE	(g_test_data[0] == *(int *)QuePeek(test_queue));
	REQUIRE	(1 == QueGetSize(test_queue));
	REQUIRE	(g_test_data[0] == *(int *)Dequeue(test_queue));
	REQUIRE	(0 == QueGetSize(test_queue));

	for (i = 0; i < ARRAY_SIZE(g_test_data); ++i) 
	{
		REQUIRE	(Q_SUCCESS == Enqueue(test_queue, &g_test_data[i]));
		REQUIRE	(g_test_data[0] == *(int *)QuePeek(test_queue));
		REQUIRE	((i + 1) == QueGetSize(test_queue));
	}

	for (i = ARRAY_SIZE(g_test_data); i > 0; --i) 
	{
		REQUIRE	(g_test_data[ARRAY_SIZE(g_test_data)-i] == *(int *)QuePeek(test_queue));
		data_dequeued = Dequeue(test_queue);
		REQUIRE	(i-1 == QueGetSize(test_queue));
		REQUIRE	(g_test_data[ARRAY_SIZE(g_test_data)-i] == *(int *)data_dequeued);

	}

	REQUIRE	(1 == QueIsEmpty(test_queue));

	QueDestroy(test_queue);

	return (TEST_PASS);	
}




TestResult TestQueAppend(void)
{
	queue_t *test_queue_first;
	queue_t *test_queue_last;
	void *data_dequeued;
	size_t i;
	
	test_queue_first = QueCreate();
	test_queue_last = QueCreate();
	
	REQUIRE	(1 == QueIsEmpty(test_queue_first));
	REQUIRE	(1 == QueIsEmpty(test_queue_last));

	/* append 2 empty queues*/
 	QueAppend(test_queue_first, test_queue_last);

	REQUIRE	(1 == QueIsEmpty(test_queue_first));
	REQUIRE	(1 == QueIsEmpty(test_queue_last));

	/*fill first_q */
	FillQueueWithData(test_queue_first);

	REQUIRE	(ARRAY_SIZE(g_test_data) == QueGetSize(test_queue_first) + QueGetSize(test_queue_last));
	/* append  full first with empty last queues*/
 	QueAppend(test_queue_first, test_queue_last);
	REQUIRE	(0 == QueIsEmpty(test_queue_first));
	REQUIRE	(1 == QueIsEmpty(test_queue_last));
	REQUIRE	(ARRAY_SIZE(g_test_data) == QueGetSize(test_queue_first) );
	QueDestroy(test_queue_first);

	test_queue_first = QueCreate();
	/*fill first_q */
	FillQueueWithData(test_queue_first);
	REQUIRE	(ARRAY_SIZE(g_test_data)  == QueGetSize(test_queue_first) + QueGetSize(test_queue_last));

	/*fill last_q*/
	FillQueueWithData(test_queue_last);

	REQUIRE	(ARRAY_SIZE(g_test_data) == QueGetSize(test_queue_first));
	REQUIRE	(ARRAY_SIZE(g_test_data) == QueGetSize(test_queue_last));

	/* append 2 full queues*/
 	QueAppend(test_queue_first, test_queue_last);
	REQUIRE	(0 == QueIsEmpty(test_queue_first));
	REQUIRE	(1 == QueIsEmpty(test_queue_last));
	REQUIRE	(ARRAY_SIZE(g_test_data) * 2 == QueGetSize(test_queue_first) );

	for (i = ARRAY_SIZE(g_test_data); i > 0; --i) 
	{
		data_dequeued = Dequeue(test_queue_first);
		REQUIRE	(g_test_data[ARRAY_SIZE(g_test_data)-i] == *(int *)data_dequeued);
	}
	REQUIRE	(ARRAY_SIZE(g_test_data) == QueGetSize(test_queue_first) );

	QueDestroy(test_queue_first);
	QueDestroy(test_queue_last);

	return (TEST_PASS);	
}
