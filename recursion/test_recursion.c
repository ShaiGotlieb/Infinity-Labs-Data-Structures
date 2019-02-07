#include <stdlib.h> /* EXIT_SUCCESS , malloc */
#include <string.h> /* strlen, strcpy, strcmp */

#include "test.h"
#include "recursion.h"
#include "sllist.h"
#include "stack.h"

#define ARRAY_SIZE_TEST (11)
#define STRING_ARRAY_SIZE_TEST (6)
#define RANDOM (rand())
#define MAX (100)
#define TRUE (1)
#define FALSE (0)

TestResult TestFibonacciRecursive();
TestResult TestFibonacciIterative();
TestResult TestStrlenRecursive();
TestResult TestStrcmpRecursive();
TestResult TestStrcpyRecursive();
TestResult TestSLLFlipRecursive();
TestResult TestStackSortRecursive();

sllist_node_t *nodes_for_test[MAX];

int main()
{
	RUN_TEST(TestFibonacciIterative);
	RUN_TEST(TestFibonacciRecursive);
	RUN_TEST(TestStrlenRecursive);
	RUN_TEST(TestStrcmpRecursive);
	RUN_TEST(TestStrcpyRecursive);
	RUN_TEST(TestSLLFlipRecursive);
	RUN_TEST(TestStackSortRecursive);

	return (EXIT_SUCCESS);
}

static int is_before(const void *data1, const void *data2)
{
	if (*(int*)data1 < *(int*)data2)
	{
		return (TRUE);
	}

	return (FALSE);
}

static void CreateNodesForTest()
{
	int element = RANDOM;
	int i = 0;

	for (i = 0; i < MAX; i += 2)
	{
		nodes_for_test[i] = SLLCreateNode(NULL, &element);
		nodes_for_test[i+1] = SLLCreateNode(NULL, &element);
		nodes_for_test[i+2] = SLLCreateNode(NULL, &element);
		SLLInsertAfter(nodes_for_test[i], nodes_for_test[i+1]);
		SLLInsertAfter(nodes_for_test[i+1], nodes_for_test[i+2]);
	}
}

TestResult TestFibonacciIterative()
{
	int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int results[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
	int i;

	for (i = 0; i < ARRAY_SIZE_TEST; ++i)
	{
		REQUIRE(results[i] == FibonacciIterative(numbers[i]));
	}

	return (TEST_PASS);
}

TestResult TestFibonacciRecursive()
{
	int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int results[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
	int i;

	for (i = 0; i < ARRAY_SIZE_TEST; ++i)
	{
		REQUIRE(results[i] == FibonacciRecursive(numbers[i]));
	}	

	return (TEST_PASS);
}

TestResult TestStrlenRecursive()
{
	char *strings[] = {"", "S","sh", "sha", "shai", "Hello"};
	size_t i;

	for (i = 0; i < STRING_ARRAY_SIZE_TEST; ++i)
	{
		REQUIRE(strlen(strings[i]) == StrlenRecursive(strings[i]));
	}

	return (TEST_PASS);
}

TestResult TestStrcmpRecursive()
{
	char *strings[] = {"", "S","sh", "sha", "shai", "Hello"};
	size_t i, j;

	for (i = 0; i < STRING_ARRAY_SIZE_TEST; ++i)
	{
		REQUIRE(strcmp(strings[i], strings[i]) == StrcmpRecursive(strings[i], strings[i]));
	}

	for (i = STRING_ARRAY_SIZE_TEST - 1, j = 0; i > j; --i, j++)
	{
		REQUIRE(strcmp(strings[i], strings[j]) == StrcmpRecursive(strings[i], strings[j]));
	}

	return (TEST_PASS);
}

TestResult TestStrcpyRecursive()
{
	char *src1 = "Hi! I am Lindsay Lohan!";
	char *src2 = "";
	char *src3 = "1";
	char *dest1 = malloc(24);
	char *dest2 = malloc(1);
	char *dest3 = malloc(2);

	REQUIRE(0 == strcmp(src1, StrcpyRecursive(dest1, src1)));
	REQUIRE(0 == strcmp(src2, StrcpyRecursive(dest2, src2)));
	REQUIRE(0 == strcmp(src3, StrcpyRecursive(dest3, src3)));

	free(dest1);
	free(dest2);
	free(dest3);
	
	return (TEST_PASS);
}

TestResult TestSLLFlipRecursive()
{
	int i;

	CreateNodesForTest();

	SLLFlipRecursive(nodes_for_test[MAX-1]);

	for (i = 0; i < MAX; ++i)
	{
		REQUIRE(nodes_for_test[i]->next = nodes_for_test[i+1]);
	}

	return ((TEST_PASS));
}

TestResult TestStackSortRecursive()
{
	stack_t *stack = StackCreate(sizeof(int), 3);
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	void *x1_ptr = &x1;
	void *x2_ptr = &x2;
	void *x3_ptr = &x3;

	StackPush(stack, x3_ptr);
	StackPush(stack, x2_ptr);
	StackPush(stack, x1_ptr);

	StackSortRecursive(stack, is_before);

	REQUIRE(*(int*)StackPop(stack) == x1);
	REQUIRE(*(int*)StackPop(stack) == x2);
	REQUIRE(*(int*)StackPop(stack) == x3);

	return ((TEST_PASS));
}
