#include <stdlib.h> /* EXIT_SUCCESS */
#include <string.h> /* memcmp */
#include "test.h"
#include "sllist.h"

#define UNSUSED(x) (void)(x)
#define TRUE (1)
#define FALSE (0)
#define INT_SIZE (4)
#define RANDOM (rand())
#define MAX (100)
#define SUCCESS (0)
#define FAILURE (1)
#define SLLIST_SIZE (3)


static int ActionSuccess(void *data, void* param);
static int ActionFailure(void *data, void* param);
static void CreateNodesForTest();
static int CmpInt(const void *data1, const void *data2, void *param);

TestResult TestSLLCreateNode();
TestResult TestSLLInsert();
TestResult TestSLLInsertAfter();
TestResult TestSLLRemove();
TestResult TestSLLRemoveAfter();
TestResult TestSLLCount();
TestResult TestSLLFlip();
TestResult TestSLLFindIntersection();
TestResult TestSLLFind();
TestResult TestSLLForEach();
TestResult TestSLLHasLoop();

sllist_node_t *nodes_for_test[MAX];

int main()
{
	RUN_TEST(TestSLLCreateNode);
	RUN_TEST(TestSLLInsert);
	RUN_TEST(TestSLLInsertAfter);
	RUN_TEST(TestSLLRemove);
	RUN_TEST(TestSLLRemoveAfter);
	RUN_TEST(TestSLLCount);
	RUN_TEST(TestSLLFlip);
	RUN_TEST(TestSLLFindIntersection);
	RUN_TEST(TestSLLFind);
	RUN_TEST(TestSLLForEach);
	RUN_TEST(TestSLLHasLoop);

	return EXIT_SUCCESS;
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

static int CmpInt(const void *data1, const void *data2, void *param)
{
	UNSUSED(data1);
	UNSUSED(data2);
	UNSUSED(param);

	return (TRUE);
}

static int ActionSuccess(void *data, void* param)
{
	UNSUSED(data);
	UNSUSED(param);

	return (SUCCESS);
}

static int ActionFailure(void *data, void* param)
{
	UNSUSED(data);
	UNSUSED(param);

	return (FAILURE);
}

TestResult TestSLLCreateNode()
{
	int element = RANDOM;
	sllist_node_t *node = SLLCreateNode(NULL, &element);
	
	REQUIRE(node != NULL);
	REQUIRE(memcmp(node->data, &element, INT_SIZE) == 0);

	SLLDestroyNodes(node);

	return (TEST_PASS);
}

TestResult TestSLLInsert()
{
	int element1 = RANDOM;
	int element2 = RANDOM;
	int element3 = RANDOM;
	void *data1 = &element1;
	void *data2 = &element2;
	void *data3 = &element3;

	nodes_for_test[0] = SLLCreateNode(NULL, data1);
	nodes_for_test[1] = SLLCreateNode(NULL, data2);
	nodes_for_test[2] = SLLCreateNode(NULL, data3);

	SLLInsert(nodes_for_test[2], nodes_for_test[1]);
	SLLInsert(nodes_for_test[1], nodes_for_test[0]);

	REQUIRE(nodes_for_test[1]->next->data == data3);

	SLLDestroyNodes(nodes_for_test[0]);

	return (TEST_PASS);
}

TestResult TestSLLInsertAfter()
{
	int i;

	CreateNodesForTest();

	for (i = 0; i < MAX; i += 2)
	{
		REQUIRE(nodes_for_test[i]->next == nodes_for_test[i+1]);
	}

	SLLDestroyNodes(nodes_for_test[0]);

	return (TEST_PASS);
}

TestResult TestSLLRemove()
{
	CreateNodesForTest();

	nodes_for_test[3] = SLLRemove(nodes_for_test[3]);

	REQUIRE(nodes_for_test[3]->next == NULL);


	SLLDestroyNodes(nodes_for_test[0]);

	return (TEST_PASS);
}

TestResult TestSLLRemoveAfter()
{
	CreateNodesForTest();

	REQUIRE(nodes_for_test[0]->next == nodes_for_test[1]);
	nodes_for_test[1] = SLLRemoveAfter(nodes_for_test[2]);
	REQUIRE(nodes_for_test[3]->next == NULL);	

	REQUIRE(nodes_for_test[4]->next == nodes_for_test[5]);
	nodes_for_test[5] = SLLRemoveAfter(nodes_for_test[6]);
	REQUIRE(nodes_for_test[7]->next == NULL);

	SLLDestroyNodes(nodes_for_test[0]);

	return (TEST_PASS);
}

TestResult TestSLLCount()
{
	CreateNodesForTest();

	REQUIRE(SLLCount(nodes_for_test[0]) == SLLIST_SIZE);
	REQUIRE(SLLCount(nodes_for_test[MAX-1]) == SLLIST_SIZE-1);
	REQUIRE(SLLCount(nodes_for_test[MAX]) == SLLIST_SIZE-2);

	SLLDestroyNodes(nodes_for_test[0]);

	return (TEST_PASS);
}

TestResult TestSLLFindIntersection()
{
	CreateNodesForTest();

	REQUIRE(SLLFindIntersection(nodes_for_test[0], nodes_for_test[3]) == NULL);

	nodes_for_test[3]->next = nodes_for_test[1];
	REQUIRE(SLLFindIntersection(nodes_for_test[0], nodes_for_test[3]) == nodes_for_test[1]);

	SLLDestroyNodes(nodes_for_test[0]);

	return (TEST_PASS);
}

TestResult TestSLLFind()
{
	int value = RANDOM;
	int *element = &value;
	sllist_node_t *node1;
	sllist_node_t *node2;
	sllist_node_t *node3;

	node1 = SLLCreateNode(NULL, element);
	node2 = SLLCreateNode(NULL, element);
	node3 = SLLCreateNode(NULL, element);

	node1 = SLLInsertAfter(node1, node2);
	node2 = SLLInsertAfter(node2, node3);

	REQUIRE((SLLFind(node1, CmpInt, element, NULL)) == node1);
	REQUIRE((SLLFind(node1, CmpInt, element, NULL)) != node2);

	SLLDestroyNodes(node3);

	return (TEST_PASS);
}

TestResult TestSLLForEach()
{
	int value = 912;
	int *element = &value;
	sllist_node_t *node1;
	sllist_node_t *node2;
	sllist_node_t *node3;

	node1 = SLLCreateNode(NULL, element);
	node2 = SLLCreateNode(NULL, element);
	node3 = SLLCreateNode(NULL, element);

	node1 = SLLInsertAfter(node1, node2);
	node2 = SLLInsertAfter(node2, node3);

	REQUIRE((SLLForEach(node1, ActionFailure, NULL)) != 0);
	REQUIRE((SLLForEach(node1, ActionSuccess, NULL)) == 0);

	return (TEST_PASS);
}

TestResult TestSLLFlip()
{
	int i;

	CreateNodesForTest();

	SLLFlip(nodes_for_test[MAX-1]);

	for (i = 0; i < MAX; ++i)
	{
		REQUIRE(nodes_for_test[i]->next = nodes_for_test[i+1]);
	}

	return ((TEST_PASS));
}

TestResult TestSLLHasLoop()
{
	int value = RANDOM;
	int *element = &value;
	sllist_node_t *node1 = SLLCreateNode(NULL, element);
	sllist_node_t *node2 = SLLCreateNode(NULL, element);
	sllist_node_t *node3 = SLLCreateNode(NULL, element);
	sllist_node_t *node4 = SLLCreateNode(NULL, element);
	sllist_node_t *node5 = SLLCreateNode(NULL, element);
	sllist_node_t *node6 = SLLCreateNode(NULL, element);
	sllist_node_t *node7 = SLLCreateNode(NULL, element);
	sllist_node_t *node8 = SLLCreateNode(NULL, element);

	SLLInsertAfter(node1, node2);
	SLLInsertAfter(node2, node3);
	SLLInsertAfter(node3, node4);
	SLLInsertAfter(node4, node5);
	SLLInsertAfter(node5, node6);
	SLLInsertAfter(node6, node7);
	SLLInsertAfter(node7, node8);

	REQUIRE(SLLHasLoop(node1) == FALSE);

	SLLInsert(node3, node8);

	REQUIRE(SLLHasLoop(node1) == TRUE);
	REQUIRE(SLLHasLoop(node3) == TRUE);

	return (TEST_PASS);
}


