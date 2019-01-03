#include "sllist.h"
#include "queue.h"
#include "test.h"

#define RANDOM (rand())
#define EMPTY (1)

TestResult TestQueCreate();
TestResult TestQueDestroy();
TestResult TestEnqueue();
TestResult TestDequeue();
TestResult TestQuePeek();
TestResult TestQueIsEmpty();
TestResult TestQueGetSize();
TestResult TestQueAppend();

int main()
{
	RUN_TEST(TestQueCreate);
	RUN_TEST(TestQueDestroy);
	RUN_TEST(TestEnqueue);
	RUN_TEST(TestDequeue);
	RUN_TEST(TestQuePeek);
	RUN_TEST(TestQueIsEmpty);
	RUN_TEST(TestQueGetSize);
	RUN_TEST(TestQueAppend);

	return (EXIT_SUCCESS);
}

struct queue_s
{
	sllist_node_t *head;
	sllist_node_t *tail;
};

TestResult TestQueCreate()
{
	queue_t *queue = QueCreate();
	REQUIRE(NULL != queue);

	QueDestroy(queue);
	
	return (TEST_PASS);
}

TestResult TestQueDestroy()
{
	queue_t *queue = QueCreate();
	
	REQUIRE(NULL != queue);
	QueDestroy(queue);

	return (TEST_PASS);
}

TestResult TestEnqueue()
{
	queue_t *queue = QueCreate();
	int random = RANDOM;
	void *data = &random;

	REQUIRE(0 == QueGetSize(queue));
	REQUIRE(0 == Enqueue(queue, data));
	REQUIRE(1 == QueGetSize(queue));
	REQUIRE(0 == Enqueue(queue, data));
	REQUIRE(2 == QueGetSize(queue));
	REQUIRE(Q_SUCCESS == Enqueue(queue, NULL));
	
	QueDestroy(queue);

	return (TEST_PASS);
}

TestResult TestDequeue()
{
	queue_t *queue = QueCreate();
	int random = RANDOM;
	void *data = &random;

	REQUIRE(Q_SUCCESS == Enqueue(queue, data));
	REQUIRE(Q_SUCCESS == Enqueue(queue, data));
	REQUIRE(Q_SUCCESS == Enqueue(queue, data));
	REQUIRE(Dequeue(queue) == data);
	REQUIRE(QueGetSize(queue) == 2);
	REQUIRE(Dequeue(queue) == data);
	REQUIRE(QueGetSize(queue) == 1);
	REQUIRE(Dequeue(queue) == data);
	REQUIRE(QueGetSize(queue) == 0);
	
	QueDestroy(queue);

	return (TEST_PASS);
}

TestResult TestQuePeek()
{
	queue_t *queue = QueCreate();
	int random = RANDOM;
	void *data = &random;

	REQUIRE(QuePeek(queue) == NULL);
	REQUIRE(Q_SUCCESS == Enqueue(queue, data));
	REQUIRE(QuePeek(queue) == data);
	
	QueDestroy(queue);

	return (TEST_PASS);
}

TestResult TestQueIsEmpty()
{
	queue_t *queue = QueCreate();
	int random = RANDOM;
	void *data = &random;

	REQUIRE(EMPTY == QueIsEmpty(queue));
	REQUIRE(Q_SUCCESS == Enqueue(queue, data));
	REQUIRE(EMPTY != QueIsEmpty(queue));
	REQUIRE(Dequeue(queue) == data);
	REQUIRE(EMPTY == QueIsEmpty(queue));

	QueDestroy(queue);

	return (TEST_PASS);
}

TestResult TestQueGetSize()
{
	queue_t *queue = QueCreate();
	int random = RANDOM;
	void *data = &random;

	REQUIRE(0 == QueGetSize(queue));
	REQUIRE(Q_SUCCESS == Enqueue(queue, data));
	REQUIRE(1 == QueGetSize(queue));
	REQUIRE(Dequeue(queue) == data);
	REQUIRE(0 == QueGetSize(queue));

	QueDestroy(queue);

	return (TEST_PASS);
}

TestResult TestQueAppend()
{
	queue_t *queue1 = QueCreate();
	queue_t *queue2 = QueCreate();
	int random = RANDOM;
	void *data = &random;

	REQUIRE(Q_SUCCESS == Enqueue(queue1, data));
	REQUIRE(Q_SUCCESS == Enqueue(queue1, data));
	REQUIRE(Q_SUCCESS == Enqueue(queue1, data));
	REQUIRE(Q_SUCCESS == Enqueue(queue2, data));
	REQUIRE(Q_SUCCESS == Enqueue(queue2, data));
	REQUIRE(Q_SUCCESS == Enqueue(queue2, data));
	QueAppend(queue1, queue2);
	REQUIRE(6 == QueGetSize(queue1));
	REQUIRE(Dequeue(queue1) == data);
	REQUIRE(5 == QueGetSize(queue1));

	QueDestroy(queue1);
	QueDestroy(queue2);

	return (TEST_PASS);
}
