#include <stdlib.h> /* EXIT_SUCCESS */

#include "test.h"
#include "ip.h"
#include "trie.h"

#define HOST_SIZE (8)

TestResult TestTrieCreate();
TestResult TestTrieCountUsedLeaves();
TestResult TestGetPath();
TestResult TestGetNextFreeNode();

struct node_s 
{ 
    node_t *children[2]; 
    node_t *parent;
    int is_used;
}; 

struct trie_s
{
    node_t *root;
    int depth;

};

int main()
{
	RUN_TEST(TestTrieCreate);
	RUN_TEST(TestTrieCountUsedLeaves);
	RUN_TEST(TestGetPath);
	RUN_TEST(TestGetNextFreeNode);

	return (EXIT_SUCCESS);
}

TestResult TestTrieCreate()
{
	trie_t *trie = TrieCreate(HOST_SIZE);

	REQUIRE(NULL != trie);

	TrieDestroy(trie);
	
	return (TEST_PASS);
}

TestResult TestTrieCountUsedLeaves()
{
	trie_t *trie = TrieCreate(HOST_SIZE);

	REQUIRE(2 == TrieCountUsedLeaves(trie->root));

	TrieDestroy(trie);
	
	return (TEST_PASS);
}

TestResult TestGetPath()
{
	trie_t *trie = TrieCreate(HOST_SIZE);
	ip_t ip = {124, 10, 10, 12};

	REQUIRE(SUCCESS == GetPath(trie, ip));
	REQUIRE(FAILURE == GetPath(trie, ip));

	ip[3] = 0;
	REQUIRE(FAILURE == GetPath(trie, ip));

	TrieDestroy(trie);
	
	return (TEST_PASS);
}

TestResult TestGetNextFreeNode()
{
	trie_t *trie = TrieCreate(HOST_SIZE);
	ip_t ip = {124, 10, 10, 12};
	node_t *node = NULL;

	REQUIRE(SUCCESS == GetPath(trie, ip));

	REQUIRE(FAILURE == GetPath(trie, ip));

	if ( FAILURE == GetPath(trie, ip))
	{
		node = GetNextFreeNode(trie);
		SetPath(trie, node, ip);
	}
	if ( FAILURE == GetPath(trie, ip))
	{
		node = GetNextFreeNode(trie);
		SetPath(trie, node, ip);
	}



	if ( FAILURE == GetPath(trie, ip))
	{
		node = GetNextFreeNode(trie);
		SetPath(trie, node, ip);
	}


	TrieDestroy(trie);
	
	return (TEST_PASS);
}
