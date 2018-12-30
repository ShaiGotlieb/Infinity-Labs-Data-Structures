#include "dvector.h"
#include "test.h"
#include <stdlib.h>

struct d_vector_s
{
	void *data;
	size_t original_capacity;
	size_t capacity;
	size_t element_size;
	int top;
};

TestResult TestDVectorCreate()
{
	size_t types[] = {sizeof(int), sizeof(char), sizeof(double), sizeof(long), sizeof(char *)};
	size_t capacity[] = {10000, 1, 2, 10, 5};
	int i;

	for (i = 0; i < 5; i++)
	{
		dvector_t *v1 = DVectorCreate(types[i], capacity[i]);
		REQUIRE(v1 != NULL);
		DVectorDestroy(v1);
	}

	return TEST_PASS;
}

TestResult TestDVectorPushEnd()
{
	dvector_t *v1 = DVectorCreate(sizeof(int), 5);
	dvector_t *v2 = DVectorCreate(sizeof(double), 65);
	dvector_t *v3 = DVectorCreate(sizeof(float), 1000000);
	int i;

	/*check int */
	for (i = 0; i < 5; i++)
	{
		int *to_push = &i;
		size_t size = i+1;
		DVectorPushEnd(v1, to_push);
		REQUIRE(DVectorGetSize(v1) == size);
	}

	/*check double */
	for (i = 0; i < 65; i++)
	{
		double number = 2.5;
		double *to_push = &number;
		size_t size = i+1;
		DVectorPushEnd(v2, to_push);
		REQUIRE(DVectorGetSize(v2) == size);
	}

	/*check float */
	for (i = 0; i < 1000000; i++)
	{
		float number = 2.5234;
		float *to_push = &number;
		size_t size = i+1;
		DVectorPushEnd(v3, to_push);
		REQUIRE(DVectorGetSize(v3) == size);
	}
	DVectorDestroy(v1);
	DVectorDestroy(v2);
	DVectorDestroy(v3);

	return TEST_PASS;
}

TestResult TestDVectorPopEnd()
{
	dvector_t *v1 = DVectorCreate(sizeof(int), 5);
	int i;

	for (i = 0; i < 5; i++)
	{
		int *to_push = &i;
		DVectorPushEnd(v1, to_push);
	}

	for (i = 0; i < 5; i++)
	{
		size_t size_check = 5-(i+1);
		size_t size = DVectorGetSize(v1);
		int *to_pop = DVectorPopEnd(v1);
		REQUIRE( size == size_check);
	}
	DVectorDestroy(v1);

	return TEST_PASS;
}

TestResult TestDVectorGetSize()
{
	dvector_t *v1 = DVectorCreate(sizeof(int), 1555);
	int i;

	for (i = 0; i < 1555; i++)
	{
		int *to_push = &i;
		DVectorPushEnd(v1, to_push);
	}
	REQUIRE(DVectorGetSize(v1) == 1555);

	for (i = 0; i < 1555; i++)
	{
		int *to_pop = DVectorPopEnd(v1);
	}
	REQUIRE(DVectorGetSize(v1) == 0);
	DVectorDestroy(v1);

	return TEST_PASS;
}

TestResult TestDVectorFindItemIndex()
{
	dvector_t *v1 = DVectorCreate(sizeof(int), 1555);
	size_t size;	
	size_t i;

	for (i = 0; i < 1555; i++)
	{
		size_t *to_push = &i;
		DVectorPushEnd(v1, to_push);
	}

	size = DVectorGetSize(v1);

	for (i = 0; i < size; ++i)
	{
		size_t *to_push_find = &i;
		REQUIRE(DVectorFindItemIndex(v1, to_push_find) == i);
	}

	DVectorDestroy(v1);

	return TEST_PASS;
}

TestResult TestDVectorGetCapacity()
{
	dvector_t *v1 = DVectorCreate(sizeof(int), 888888);

	REQUIRE(DVectorGetSize(v1) == 0);
	REQUIRE(DVectorGetCapacity(v1) == 888888);

	DVectorDestroy(v1);

	return TEST_PASS;
}

TestResult TestDVectorSetCapacity()
{
	dvector_t *v1 = DVectorCreate(sizeof(int), 888888);
	dvector_t *v2 = DVectorCreate(sizeof(int), 10);
	size_t i;
	size_t *to_push = 0;
	size_t *to_pop = 0;
	DVectorSetCapacity(v1, 888888/2);
	REQUIRE(DVectorGetCapacity(v1) == 444444);
	DVectorSetCapacity(v1, 1000000);
	REQUIRE(DVectorGetCapacity(v1) == 1000000);

	for (i = 0; i < 10; i++)
	{
		to_push = &i;
		DVectorPushEnd(v2, to_push);
	}
	to_push = &i;
	DVectorPushEnd(v2, to_push);
	REQUIRE(DVectorGetCapacity(v2) == 20);


	DVectorDestroy(v1);
	DVectorDestroy(v2);

	return TEST_PASS;
}

int main()
{
	RUN_TEST(TestDVectorCreate);
	RUN_TEST(TestDVectorPushEnd);
	RUN_TEST(TestDVectorPopEnd);
	RUN_TEST(TestDVectorGetSize);
	RUN_TEST(TestDVectorFindItemIndex);
	RUN_TEST(TestDVectorGetCapacity);
	RUN_TEST(TestDVectorSetCapacity);


	return EXIT_SUCCESS;
}
