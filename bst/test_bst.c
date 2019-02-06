#include <stdlib.h>

#include "bst.h"
#include "test.h"

#define EMPTY (0)
#define RANDOM (rand() % 30)
#define UNUSED(x) (void)(x)
#define TRUE (1)
#define FALSE (0)
#define CHILDREN_SIZE (2)
#define DEADBEEF (0xdeadbeef)
#define DATA_SIZE (10)
#define SUCCESS (0)

TestResult TestBSTCreate();
TestResult TestBSTInsert();
TestResult TestBSTGetSize();
TestResult TestBSTGetNext();
TestResult TestBSTFind();
TestResult TestBSTForEach();
TestResult TestBSTRemove();

int data[DATA_SIZE];

typedef struct tree_node_s
{
	void *data;
	struct tree_node_s *parent;
	struct tree_node_s *children[CHILDREN_SIZE];
		
}tree_node_t;

struct bst_s
{
	struct tree_node_s *root;
	size_t size;
	void *param;
	cmp_func_t cmp_func;
};

void printInorder(tree_node_t *node);
int cmp_func(void *data1, void *data2, void *param)
{	
	int x = *(int*)(data1);
	int y = *(int*)(data2);

	UNUSED(param);

	return (x - y);
}

int action_func(void *data, void *param)
{
	UNUSED(param);

	printf("data: %d\n", *(int *)data);

	return (SUCCESS);
}

int main()
{
	RUN_TEST(TestBSTCreate);
	RUN_TEST(TestBSTInsert);
	RUN_TEST(TestBSTGetSize);
	RUN_TEST(TestBSTGetNext);
	RUN_TEST(TestBSTFind);
	RUN_TEST(TestBSTForEach);
	RUN_TEST(TestBSTRemove);

	return (EXIT_SUCCESS);
}

static void InitData()
{
	int i;

	for (i = 0; i < DATA_SIZE; ++i)
	{
		int random = RANDOM;
		data[i] = random + i;
	}
}

TestResult TestBSTCreate()
{
	void *param = NULL;
	bst_t *bst = BSTCreate(cmp_func, param);

	REQUIRE(NULL != bst);

	free(bst);
	
	return (TEST_PASS);
}

TestResult TestBSTInsert()
{
	void *param = NULL;
	bst_t *bst = BSTCreate(cmp_func, param);
	bst_iterator_t it;

	InitData();

	REQUIRE(EMPTY == BSTGetSize(bst));

	it = BSTInsert(bst, &data[0]);
	it = BSTInsert(bst, &data[1]);

	REQUIRE(EMPTY != BSTGetSize(bst));

	free(bst);
	
	return (TEST_PASS);
}

TestResult TestBSTGetSize()
{
	void *param = NULL;
	bst_t *bst = BSTCreate(cmp_func, param);
	int i;
	
	InitData();

	REQUIRE(EMPTY == BSTGetSize(bst));
	for (i = 0; i < DATA_SIZE; ++i)
	{
		BSTInsert(bst, &data[i]);
		REQUIRE((size_t)(i+1) == BSTGetSize(bst));
	}

	free(bst);
	
	return (TEST_PASS);
}

TestResult TestBSTGetNext()
{
	void *param = NULL;
	bst_iterator_t iterator;
	bst_t *bst = BSTCreate(cmp_func, param);
	int i;
	
	InitData();

	REQUIRE(EMPTY == BSTGetSize(bst));
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		iterator = BSTInsert(bst, &data[i]);
	}

	free(bst);
	
	return (TEST_PASS);
}

TestResult TestBSTFind()
{
	void *param = NULL;
	bst_iterator_t iterator;
	bst_t *bst = BSTCreate(cmp_func, param);
	int i;
	
	InitData();
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		iterator = BSTInsert(bst, &data[i]);
	}

	iterator = BSTFind(bst, &data[2]);

	REQUIRE(data[2] == *(int*)BSTGetData(iterator));

	free(bst);
	
	return (TEST_PASS);
}

TestResult TestBSTForEach()
{
	void *param = NULL;
	bst_iterator_t iterator;
	bst_t *bst = BSTCreate(cmp_func, param);
	int i;
	
	InitData();
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		iterator = BSTInsert(bst, &data[i]);
	}

	REQUIRE(SUCCESS == BSTForEach(bst, action_func, param));

	free(bst);
	
	return (TEST_PASS);
}

TestResult TestBSTRemove()
{
	void *param = NULL;
	bst_iterator_t iterator;
	bst_t *bst = BSTCreate(cmp_func, param);
	int i;
	
	InitData();
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		iterator = BSTInsert(bst, &data[i]);
	}

	for (i = 1; i < DATA_SIZE; ++i)
	{
		BSTRemove(bst, &data[i]);
	}

	BSTDestroy(bst);
	
	return (TEST_PASS);
}
