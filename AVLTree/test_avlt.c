#include <stdlib.h> /* free */
#include <math.h> /* log */

#include "avlt.h"
#include "test.h"

#define EMPTY (0)
#define RANDOM (rand() % 99)
#define UNUSED(x) (void)(x)
#define TRUE (1)
#define FALSE (0)
#define CHILDREN_SIZE (2)
#define DEADBEEF (0xdeadbeef)
#define DATA_SIZE (10)
#define SUCCESS (0)
#define FAILURE (1)

TestResult TestAVLTCreate();
TestResult TestAVLTInsert();
TestResult TestAVLTIsEmpty();
TestResult TestAVLTGetSize();
TestResult TestAVLTFind();
TestResult TestAVLTForEach();
TestResult TestAVLTRemove();

int data[DATA_SIZE];
int data_only_left[DATA_SIZE];
int data_only_right[DATA_SIZE];

int main()
{
	RUN_TEST(TestAVLTCreate);
	RUN_TEST(TestAVLTInsert);
	RUN_TEST(TestAVLTIsEmpty);
	RUN_TEST(TestAVLTGetSize);
	RUN_TEST(TestAVLTFind);
	RUN_TEST(TestAVLTForEach);
	RUN_TEST(TestAVLTRemove);

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

static int cmp_func(const void *data1, const void *data2, void *param)
{	
	int x = *(int*)(data1);
	int y = *(int*)(data2);

	UNUSED(param);

	return (x - y);
}

static int action_func(void *data, void *param)
{
	UNUSED(param);
	if (NULL == data)
	{
		return (FAILURE);
	}

	 *(int *)data *= 2;

	return (SUCCESS);
}

static void InitData()
{
	int i;

	for (i = 0; i < DATA_SIZE; ++i)
	{
		int random = RANDOM;
		data[i] = random + i;
		data_only_right[i] = i;
		data_only_left[i] = -i;
	}
}


TestResult TestAVLTCreate()
{
	void *param = NULL;
	avlt_t *tree = AVLTCreate(is_before, param);

	REQUIRE(NULL != tree);

	AVLTDestroy(tree);
	
	return (TEST_PASS);
}

TestResult TestAVLTInsert()
{
	void *param = NULL;
	avlt_t *tree_random = AVLTCreate(is_before, param);
	avlt_t *tree_only_left = AVLTCreate(is_before, param);
	avlt_t *tree_only_right = AVLTCreate(is_before, param);
	size_t i;

	InitData();

	REQUIRE	(TRUE == AVLTIsEmpty(tree_random));
	REQUIRE	(TRUE == AVLTIsEmpty(tree_only_right));
	REQUIRE	(TRUE == AVLTIsEmpty(tree_only_left));

	for (i = 0; i < DATA_SIZE; ++i)
	{
		REQUIRE(SUCCESS == AVLTInsert(tree_random, &data[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_right, &data_only_right[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_left, &data_only_left[i]));
		
		REQUIRE(i + 1 == AVLTGetSize(tree_random));
		REQUIRE(i + 1 == AVLTGetSize(tree_only_right));
		REQUIRE(i + 1 == AVLTGetSize(tree_only_left));
	}

	REQUIRE	(FALSE == AVLTIsEmpty(tree_random));
	REQUIRE	(FALSE == AVLTIsEmpty(tree_only_right));
	REQUIRE	(FALSE == AVLTIsEmpty(tree_only_left));

	AVLTDestroy(tree_random);
	AVLTDestroy(tree_only_right);
	AVLTDestroy(tree_only_left);
	
	return (TEST_PASS);
}

TestResult TestAVLTIsEmpty()
{
	void *param = NULL;
	avlt_t *tree_random = AVLTCreate(is_before, param);
	avlt_t *tree_only_left = AVLTCreate(is_before, param);
	avlt_t *tree_only_right = AVLTCreate(is_before, param);
	int i;

	InitData();

	REQUIRE	(TRUE == AVLTIsEmpty(tree_random));
	REQUIRE	(TRUE == AVLTIsEmpty(tree_only_right));
	REQUIRE	(TRUE == AVLTIsEmpty(tree_only_left));

	for (i = 0; i < DATA_SIZE; ++i)
	{
		REQUIRE(SUCCESS == AVLTInsert(tree_random, &data[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_right, &data_only_right[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_left, &data_only_left[i]));
	}

	REQUIRE	(FALSE == AVLTIsEmpty(tree_random));
	REQUIRE	(FALSE == AVLTIsEmpty(tree_only_right));
	REQUIRE	(FALSE == AVLTIsEmpty(tree_only_left));

	AVLTDestroy(tree_random);
	AVLTDestroy(tree_only_right);
	AVLTDestroy(tree_only_left);
	
	return (TEST_PASS);
}

TestResult TestAVLTGetSize()
{
	void *param = NULL;
	avlt_t *tree_random = AVLTCreate(is_before, param);
	avlt_t *tree_only_left = AVLTCreate(is_before, param);
	avlt_t *tree_only_right = AVLTCreate(is_before, param);
	size_t i;

	InitData();

	REQUIRE(EMPTY == AVLTGetSize(tree_random));
	REQUIRE(EMPTY == AVLTGetSize(tree_only_right));
	REQUIRE(EMPTY == AVLTGetSize(tree_only_left));

	for (i = 0; i < DATA_SIZE; ++i)
	{
		REQUIRE(SUCCESS == AVLTInsert(tree_random, &data[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_right, &data_only_right[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_left, &data_only_left[i]));
		
		REQUIRE(i + 1 == AVLTGetSize(tree_random));
		REQUIRE(i + 1 == AVLTGetSize(tree_only_right));
		REQUIRE(i + 1 == AVLTGetSize(tree_only_left));
	}

	AVLTDestroy(tree_random);
	AVLTDestroy(tree_only_right);
	AVLTDestroy(tree_only_left);
	
	return (TEST_PASS);
}

TestResult TestAVLTFind()
{
	void *param = NULL;
	size_t i;
	int not_in_tree = 520;
	avlt_t *tree_random = AVLTCreate(is_before, param);
	avlt_t *tree_only_left = AVLTCreate(is_before, param);
	avlt_t *tree_only_right = AVLTCreate(is_before, param);

	InitData();

	for (i = 0; i < DATA_SIZE; ++i)
	{
		REQUIRE(SUCCESS == AVLTInsert(tree_random, &data[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_right, &data_only_right[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_left, &data_only_left[i]));
	}

	REQUIRE(NULL == AVLTFind(tree_random, &not_in_tree, cmp_func, param));
	REQUIRE(NULL == AVLTFind(tree_only_right, &not_in_tree, cmp_func, param));
	REQUIRE(NULL == AVLTFind(tree_only_left, &not_in_tree, cmp_func, param));
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		REQUIRE(data[i] == *(int*)AVLTFind(tree_random, &data[i], cmp_func, param));
		REQUIRE(data_only_right[i] == *(int*)AVLTFind(tree_only_right, &data_only_right[i], cmp_func, param));
		REQUIRE(data_only_left[i] == *(int*)AVLTFind(tree_only_left, &data_only_left[i], cmp_func, param));
	}

	AVLTDestroy(tree_random);
	AVLTDestroy(tree_only_right);
	AVLTDestroy(tree_only_left);
	
	return (TEST_PASS);
}

TestResult TestAVLTForEach()
{
	void *param = NULL;
	avlt_t *tree_random = AVLTCreate(is_before, param);
	avlt_t *tree_only_left = AVLTCreate(is_before, param);
	avlt_t *tree_only_right = AVLTCreate(is_before, param);
	int expected_random[DATA_SIZE];
	int expected_right[DATA_SIZE];
	int expected_left[DATA_SIZE];
	size_t i;

	InitData();

	for (i = 0; i < DATA_SIZE; ++i)
	{
		REQUIRE(SUCCESS == AVLTInsert(tree_random, &data[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_right, &data_only_right[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_left, &data_only_left[i]));

		expected_random[i] = data[i] * 2;
		expected_left[i] = data_only_left[i] * 2;
		expected_right[i] = data_only_right[i] * 2;
	}

	REQUIRE(SUCCESS == AVLTForEach(tree_random, action_func, param));
	REQUIRE(SUCCESS == AVLTForEach(tree_only_right, action_func, param));
	REQUIRE(SUCCESS == AVLTForEach(tree_only_left, action_func, param));
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		REQUIRE(expected_random[i] == *(int*)AVLTFind(tree_random, &expected_random[i], cmp_func, param));
		REQUIRE(expected_right[i] == *(int*)AVLTFind(tree_only_right, &expected_right[i], cmp_func, param));
		REQUIRE(expected_left[i] == *(int*)AVLTFind(tree_only_left, &expected_left[i], cmp_func, param));
	}

	AVLTDestroy(tree_random);
	AVLTDestroy(tree_only_right);
	AVLTDestroy(tree_only_left);
	
	return (TEST_PASS);
}

TestResult TestAVLTRemove()
{
	int not_in_tree = 520;
	void *param = NULL;
	size_t i, j;
	avlt_t *tree_random = AVLTCreate(is_before, param);
	avlt_t *tree_only_left = AVLTCreate(is_before, param);
	avlt_t *tree_only_right = AVLTCreate(is_before, param);

	InitData();

	REQUIRE	(TRUE == AVLTIsEmpty(tree_random));
	REQUIRE	(TRUE == AVLTIsEmpty(tree_only_right));
	REQUIRE	(TRUE == AVLTIsEmpty(tree_only_left));

	for (i = 0; i < DATA_SIZE; ++i)
	{
		REQUIRE(SUCCESS == AVLTInsert(tree_random, &data[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_right, &data_only_right[i]));
		REQUIRE(SUCCESS == AVLTInsert(tree_only_left, &data_only_left[i]));
		
		REQUIRE(i + 1 == AVLTGetSize(tree_random));
		REQUIRE(i + 1 == AVLTGetSize(tree_only_right));
		REQUIRE(i + 1 == AVLTGetSize(tree_only_left));
	}

	REQUIRE	(FALSE == AVLTIsEmpty(tree_random));
	REQUIRE	(FALSE == AVLTIsEmpty(tree_only_right));
	REQUIRE	(FALSE == AVLTIsEmpty(tree_only_left));

	AVLTRemove(tree_random, &not_in_tree);
	AVLTRemove(tree_only_right, &not_in_tree);
	AVLTRemove(tree_only_left, &not_in_tree);
	
	REQUIRE(DATA_SIZE == AVLTGetSize(tree_random));
	REQUIRE(DATA_SIZE == AVLTGetSize(tree_only_right));
	REQUIRE(DATA_SIZE == AVLTGetSize(tree_only_left));

	for (i = 0, j = 1; i < DATA_SIZE; ++i, j++)
	{
		AVLTRemove(tree_random, &data[i]);
		AVLTRemove(tree_only_right, &data_only_right[i]);
		AVLTRemove(tree_only_left, &data_only_left[i]);
		
		REQUIRE(DATA_SIZE - j == AVLTGetSize(tree_random));
		REQUIRE(DATA_SIZE - j == AVLTGetSize(tree_only_right));
		REQUIRE(DATA_SIZE - j == AVLTGetSize(tree_only_left));
		
		REQUIRE(NULL == AVLTFind(tree_random, &data[i], cmp_func, param));
		REQUIRE(NULL == AVLTFind(tree_only_right, &data_only_right[i], cmp_func, param));
		REQUIRE(NULL == AVLTFind(tree_only_left, &data_only_left[i], cmp_func, param));
	}

	AVLTDestroy(tree_random);
	AVLTDestroy(tree_only_right);
	AVLTDestroy(tree_only_left);
	
	return (TEST_PASS);
}