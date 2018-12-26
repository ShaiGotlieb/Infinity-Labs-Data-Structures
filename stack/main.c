#include "stack.h"
#include "test.h"
#include <stdlib.h>

struct stack_s 
{ 
	void *stack_base;
	size_t element_size;
	size_t capacity;	
	void *stack_top; 
};

TestResult TestStackCreate()
{
	size_t capacity[] = {10000, 1, 2, 10, 5};
	size_t types[] = {sizeof(int), sizeof(char), sizeof(double), sizeof(long), sizeof(char *)};
	int i;

	for (i = 0; i < 5; i++)
	{
		stack_t *s1 = StackCreate(types[i], capacity[i]);
		REQUIRE(s1 != NULL);
	}

	return TEST_PASS;
}

TestResult TestStackPush()
{
	stack_t *s1 = StackCreate(sizeof(int), 5);
	stack_t *s2 = StackCreate(sizeof(double), 65);
	stack_t *s3 = StackCreate(sizeof(float), 1000000);
	int i;

	/*check int */
	for (i = 0; i < 5; i++)
	{
		int *to_push = &i;
		int *to_pop; 
		size_t size = i+1;
		StackPush(s1, to_push);
		to_pop = StackPeek(s1);
		REQUIRE(StackSize(s1) == size);
		REQUIRE(*to_pop == *to_push);
	}

	/*check double */
	for (i = 0; i < 65; i++)
	{
		double number = 2.5;
		double *to_push = &number;
		double *to_pop; 
		size_t size = i+1;
		StackPush(s2, to_push);
		to_pop = StackPeek(s2);
		REQUIRE(StackSize(s2) == size);
		REQUIRE(*to_pop == *to_push);
	}

	/*check float */
	for (i = 0; i < 1000000; i++)
	{
		float number = 2.5234;
		float *to_push = &number;
		float *to_pop; 
		size_t size = i+1;
		StackPush(s3, to_push);
		to_pop = StackPeek(s3);
		REQUIRE(StackSize(s3) == size);
		REQUIRE(*to_pop == *to_push);
	}

	return TEST_PASS;
}

TestResult TestStackPop()
{
	stack_t *s1 = StackCreate(sizeof(int), 5);
	int i;

	for (i = 0; i < 5; i++)
	{
		int *to_push = &i;
		StackPush(s1, to_push);
	}

	for (i = 0; i < 5; i++)
	{
		size_t size_check = 5-(i+1);
		int *to_pop = StackPop(s1);
		REQUIRE(StackSize(s1) == size_check);
	}

	return TEST_PASS;
}

TestResult TestStackPeek()
{
	stack_t *s1 = StackCreate(sizeof(int), 5);
	int i;

	for (i = 0; i < 5; i++)
	{
		int *to_push = &i;
		int *to_peek;
		StackPush(s1, to_push);
		to_peek = StackPeek(s1);
		REQUIRE(*to_peek == *to_push);
	}

	return TEST_PASS;
}

TestResult TestStackSize()
{
	stack_t *s1 = StackCreate(sizeof(int), 1555);
	int i;

	for (i = 0; i < 1555; i++)
	{
		int *to_push = &i;
		StackPush(s1, to_push);
	}
	REQUIRE(StackSize(s1) == 1555);

	for (i = 0; i < 1555; i++)
	{
		int *to_pop = StackPop(s1);
	}
	REQUIRE(StackSize(s1) == 0);

	return TEST_PASS;
}

int main()
{
	RUN_TEST(TestStackCreate);
	RUN_TEST(TestStackPush);
	RUN_TEST(TestStackPop);
	RUN_TEST(TestStackPeek);

	return EXIT_SUCCESS;
}