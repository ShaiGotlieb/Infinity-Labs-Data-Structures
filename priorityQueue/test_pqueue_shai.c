#include <stdlib.h> /* size_t */

#include "pqueue.h"
#include "sorted_list.h"
#include "test.h"

#define EMPTY (0)


TestResult TestPQCreate();
TestResult TestSLGetSize();
TestResult TestSLIsEmpty();
TestResult TestPQEnqueue();
TestResult TestPQDequeue();
TestResult TestPQPeek();
TestResult TestPQClear();
TestResult TestPQErase();

boolean_t has_higher_priority(const void *data1, const void *data2)
{
	int x = *(int*)(data1);
	int y = *(int*)(data2);

	if (x <= y)
	{
		return TRUE;
	}
	return FALSE;
}

boolean_t is_match_q(const void *data1, void *param)
{
	int x;
	int y;

	x = *(int*)(data1);
	y = *(int*)(param);

	if (x == y)
	{
		return TRUE;
	}

	return FALSE;
}

int main()
{
	RUN_TEST(TestPQCreate);
	RUN_TEST(TestSLGetSize);
	RUN_TEST(TestSLIsEmpty);
	RUN_TEST(TestPQEnqueue);
	RUN_TEST(TestPQDequeue);
	RUN_TEST(TestPQPeek);
	RUN_TEST(TestPQClear);
	RUN_TEST(TestPQErase);

	return (EXIT_SUCCESS);
}

TestResult TestPQCreate()
{
	pqueue_t *queue = PQCreate(has_higher_priority);

	REQUIRE(NULL != queue);

	PQDestroy(queue);
	
	return (TEST_PASS);
}

TestResult TestSLGetSize()
{
	pqueue_t *queue = PQCreate(has_higher_priority);

	REQUIRE(EMPTY == PQGetSize(queue));

	PQDestroy(queue);
	
	return (TEST_PASS);
}

TestResult TestSLIsEmpty()
{
	pqueue_t *queue = PQCreate(has_higher_priority);

	REQUIRE(NULL != queue);
	REQUIRE(EMPTY == PQGetSize(queue));
	REQUIRE(TRUE == PQIsEmpty(queue));

	PQDestroy(queue);
	
	return (TEST_PASS);
}

TestResult TestPQEnqueue()
{
	int random = 1;
	void *data = &random;
	pqueue_t *queue = PQCreate(has_higher_priority);

	REQUIRE(EMPTY == PQGetSize(queue));
	PQEnqueue(queue, data);
	REQUIRE(1 == PQGetSize(queue));
	PQEnqueue(queue, data);
	REQUIRE(2 == PQGetSize(queue));
	PQEnqueue(queue, data);
	REQUIRE(3 == PQGetSize(queue));

	PQDestroy(queue);
	
	return (TEST_PASS);
}

TestResult TestPQDequeue()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	pqueue_t *queue = PQCreate(has_higher_priority);

	PQEnqueue(queue, data1);
	PQDequeue(queue);
	REQUIRE(EMPTY == PQGetSize(queue));

	PQEnqueue(queue, data1);
	PQEnqueue(queue, data2);
	PQEnqueue(queue, data3);
	PQDequeue(queue);
	PQDequeue(queue);
	REQUIRE(1 == PQGetSize(queue));
	PQDequeue(queue);
	REQUIRE(EMPTY == PQGetSize(queue));

	PQDestroy(queue);
	
	return (TEST_PASS);
}

TestResult TestPQPeek()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	pqueue_t *queue = PQCreate(has_higher_priority);

	PQEnqueue(queue, data1);
	REQUIRE(data1 == PQPeek(queue));
	REQUIRE(1 == PQGetSize(queue));

	PQEnqueue(queue, data2);
	REQUIRE(data2 == PQPeek(queue));
	REQUIRE(2 == PQGetSize(queue));

	PQEnqueue(queue, data3);
	REQUIRE(data3 == PQPeek(queue));
	REQUIRE(3 == PQGetSize(queue));

	PQDestroy(queue);
	
	return (TEST_PASS);
}

TestResult TestPQClear()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	pqueue_t *queue = PQCreate(has_higher_priority);

	REQUIRE(TRUE == PQIsEmpty(queue));
	PQClear(queue);
	REQUIRE(TRUE == PQIsEmpty(queue));
	
	PQEnqueue(queue, data1);
	PQEnqueue(queue, data2);
	PQEnqueue(queue, data3);

	PQClear(queue);

	REQUIRE(TRUE == PQIsEmpty(queue));

	PQDestroy(queue);
	
	return (TEST_PASS);
}

TestResult TestPQErase()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	int random4 = 4;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	void *not_in_queue = &random4;
	pqueue_t *queue = PQCreate(has_higher_priority);

	PQErase(queue, is_match_q, data3);
	REQUIRE(TRUE == PQIsEmpty(queue));
	REQUIRE(EMPTY == PQGetSize(queue));

	PQEnqueue(queue, data1);
	PQEnqueue(queue, data2);
	PQEnqueue(queue, data3);
	PQEnqueue(queue, data3);
	PQEnqueue(queue, data1);
	PQEnqueue(queue, data3);
	PQEnqueue(queue, data3);
	PQEnqueue(queue, data2);

	PQErase(queue, is_match_q, not_in_queue);
	REQUIRE(8 == PQGetSize(queue));
	PQErase(queue, is_match_q, data3);

	REQUIRE(FALSE == PQIsEmpty(queue));
	REQUIRE(4 == PQGetSize(queue));

	PQDestroy(queue);
	
	return (TEST_PASS);
}