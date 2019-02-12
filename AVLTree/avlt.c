#include <stdlib.h> /* malloc, size_t, free */
#include <assert.h> /* assert */
#include "avlt.h"

#define CHILDREN_SIZE (2)
#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAILURE (1)

typedef enum {LEFT = 0, RIGHT = 1} DIRECTION; 
typedef enum {LL = 0, RR = 1, LR = 2, RL = 3, BALANCED = 4} BALANCE_TYPE; 

typedef struct tree_node_s
{
	void *data;
	struct tree_node_s *children[CHILDREN_SIZE];
	long height;
		
}tree_node_t;

struct avlt_s
{
	tree_node_t *root;
	void *param;
	is_before_avlt_t is_before;
};

static tree_node_t *InsertRecursive(avlt_t *tree, tree_node_t *current_node, void *data);
static tree_node_t *RotateLeft(tree_node_t *root);
static tree_node_t *RotateRight(tree_node_t *root);
static tree_node_t *RemoveNode(avlt_t *tree, tree_node_t *node, const void *data);
static tree_node_t *CreateNode(void *data);
static tree_node_t *FindNode(tree_node_t *node, const void *data, cmp_func_avlt_t cmp_func, void* param);
static tree_node_t *MostLeftChild(tree_node_t *node);
static BALANCE_TYPE InsertCheckBalanceType(tree_node_t *node, long balance_factor ,void *data, is_before_avlt_t is_before);
static BALANCE_TYPE RemoveCheckBalanceType(tree_node_t *node, long balance_factor);
static long CalculateBalance(tree_node_t *node);
static long GetMaxHeight(long left_height, long right_height);
static long GetHeight(tree_node_t *node);
static void DestroyNode(tree_node_t *node);
static void Destroy(tree_node_t *node);
static size_t GetSize(tree_node_t *node);
static int ForEach(tree_node_t *node, action_func_avlt_t action_func, void *param);

avlt_t *AVLTCreate(is_before_avlt_t is_before, void *param)
{
	avlt_t *tree = (avlt_t*)malloc(sizeof(avlt_t));
	
	if (NULL == tree)
	{
		return (NULL);
	}

	tree->is_before = is_before;
	tree->param = param;
	tree->root = NULL;

	return (tree);
}

int AVLTInsert(avlt_t *tree, const void *data)
{
	assert(NULL != tree);

	if (NULL == tree->root)
	{
		tree->root = CreateNode((void*)data);

		return (SUCCESS);
	}
	else
	{
		tree->root = InsertRecursive(tree, tree->root, (void *)data);
		
		if (NULL == tree->root)
		{
			return (FAILURE);
		}
	}

	return (SUCCESS);
}

long AVLTHeight(const avlt_t *tree)
{
	assert(NULL != tree);

	return (GetHeight(tree->root));
}

int AVLTIsEmpty(const avlt_t *tree)
{
	assert(NULL != tree);

	return (NULL == tree->root);
}

size_t AVLTGetSize(const avlt_t *tree)
{
	assert(NULL != tree);

	return (GetSize(tree->root));
}

void *AVLTFind(const avlt_t *tree, const void *data, cmp_func_avlt_t cmp_func, void *param)
{
	tree_node_t *node = NULL;

	assert(NULL != tree);

	node = tree->root;

	node = FindNode(node, data, cmp_func, param);
	if (NULL == node)
	{
		return (NULL);
	}

	return (node->data);
}

int AVLTForEach(avlt_t *tree, action_func_avlt_t action_func, void *param)
{
	assert(NULL != tree);

	return (ForEach(tree->root, action_func, param));
}

void AVLTDestroy(avlt_t *tree)
{
	Destroy(tree->root);
	
	tree->param = NULL;
	tree->is_before = NULL;
	tree->root = NULL;
	
	free(tree);
	tree = NULL;
}

void AVLTRemove(avlt_t *tree, const void *data)
{
	assert(NULL != tree);

	tree->root = RemoveNode(tree, tree->root, data);
}

static tree_node_t *RemoveNode(avlt_t *tree, tree_node_t *node, const void *data)
{
	size_t balance_factor = 0;

	if (NULL == node)
	{
		return node;
	}

	if (tree->is_before(data, node->data))
	{
		node->children[LEFT] = RemoveNode(tree, node->children[LEFT], data);
	}
	else if (tree->is_before(node->data, data))
	{
		node->children[RIGHT] = RemoveNode(tree, node->children[RIGHT], data);
	}
	else
	{
		tree_node_t *node_to_delete = NULL;

		if (NULL == node->children[LEFT] || NULL == node->children[RIGHT])
		{
			node_to_delete = node->children[LEFT] ? node->children[LEFT] : node->children[RIGHT];

			if (NULL == node_to_delete)
			{
				node_to_delete = node;
				node = NULL;
			}
			else
			{
				*node = *node_to_delete;
			}

			DestroyNode(node_to_delete);
		}
		else
		{
			node_to_delete = MostLeftChild(node->children[RIGHT]);
			node->data = node_to_delete->data;
			node->children[RIGHT] = RemoveNode(tree, node->children[RIGHT], node_to_delete->data);
		}
	}

	if (NULL == node)
	{
		return (node); 
	}

	node->height = 1 + GetMaxHeight(GetHeight(node->children[LEFT]) , GetHeight(node->children[RIGHT]));
	balance_factor = CalculateBalance(node);

	switch (RemoveCheckBalanceType(node, balance_factor))
	{
		case LL:
			 return (RotateRight(node));

		case RR:
			return (RotateLeft(node));

		case LR:
			node->children[LEFT] = RotateLeft(node->children[LEFT]);
			return (RotateRight(node));

		case RL:
			node->children[RIGHT] = RotateRight(node->children[RIGHT]);
			return (RotateLeft(node));

		case BALANCED:
			break;
	}

	return (node);
}

static tree_node_t *MostLeftChild(tree_node_t *node)
{
	tree_node_t *current_node = node;

	while (NULL != current_node->children[LEFT])
	{
		current_node = current_node->children[LEFT];
	}

	return (current_node);
}

static void DestroyNode(tree_node_t *node)
{
	node->data = NULL;
	node->height = 0;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	free(node);
	node = NULL;
}

static void Destroy(tree_node_t *node)
{
	if (NULL != node)
	{
		Destroy(node->children[LEFT]);
		Destroy(node->children[RIGHT]);
		DestroyNode(node);
	}
}

static int ForEach(tree_node_t *node, action_func_avlt_t action_func, void *param)
{
	int return_status = SUCCESS;

	if (NULL != node && return_status == SUCCESS)
	{
		ForEach(node->children[LEFT], action_func, param);
		return_status = action_func(node->data, param);
		ForEach(node->children[RIGHT], action_func, param);
	}

	return (return_status);
}

static tree_node_t *FindNode(tree_node_t *node, const void *data, cmp_func_avlt_t cmp_func, void* param)
{
	if (NULL == node)
	{
		return (NULL);
	}

	if (0 == cmp_func(data, node->data, param))
	{
		return (node);
	}
	else if (0 > cmp_func(data, node->data, param))
	{
		return (FindNode(node->children[LEFT], data, cmp_func, param));
	}
	else
	{
		return (FindNode(node->children[RIGHT], data, cmp_func, param));
	}
}

static size_t GetSize(tree_node_t *node)
{
	if (NULL == node)
	{
		return (0);
	}
	else
	{
		return (GetSize(node->children[LEFT]) + GetSize(node->children[RIGHT]) + 1);
	}
}

static long CalculateBalance(tree_node_t *node)
{
	if (NULL == node)
	{
		return (0);
	}

	return (GetHeight(node->children[LEFT]) - GetHeight(node->children[RIGHT]));
}

static BALANCE_TYPE InsertCheckBalanceType(tree_node_t *node, long balance_factor ,void *data, is_before_avlt_t is_before)
{
	if (balance_factor == 2 && is_before(data, node->children[LEFT]->data))
	{
		return (LL);
	}

	if (balance_factor == -2 && !is_before(data, node->children[RIGHT]->data))
	{
		return (RR);
	}

	if (balance_factor == 2 && !is_before(data, node->children[LEFT]->data))
	{
		return (LR);
	}
	if (balance_factor == -2 && is_before(data, node->children[RIGHT]->data))
	{
		return (RL);
	}

	return (BALANCED);
}

static BALANCE_TYPE RemoveCheckBalanceType(tree_node_t *node, long balance_factor)
{
	if (balance_factor == 2 && CalculateBalance(node->children[LEFT]) >= 0)
	{
		return (LL);
	}

	if (balance_factor == -2 && CalculateBalance(node->children[RIGHT]) <= 0)
	{
		return (RR);
	}

	if (balance_factor == 2 && CalculateBalance(node->children[LEFT]) < 0)
	{
		return (LR);
	}
	if (balance_factor == -2 && CalculateBalance(node->children[RIGHT]) > 0)
	{
		return (RL);
	}

	return (BALANCED);
}

static tree_node_t *RotateRight(tree_node_t *root)
{
	tree_node_t *pivot = root->children[LEFT];
	tree_node_t *right_child = pivot->children[RIGHT];

	pivot->children[RIGHT] = root;
	root->children[LEFT] = right_child;

	root->height = GetMaxHeight(GetHeight(root->children[LEFT]), GetHeight(root->children[RIGHT])) + 1;
	pivot->height = GetMaxHeight(GetHeight(pivot->children[LEFT]), GetHeight(pivot->children[RIGHT])) + 1;

	return (pivot);
}

static tree_node_t *RotateLeft(tree_node_t *root)
{
	tree_node_t *pivot = root->children[RIGHT];
	tree_node_t *left_child = pivot->children[LEFT];

	pivot->children[LEFT] = root;
	root->children[RIGHT] = left_child;

	root->height = GetMaxHeight(GetHeight(root->children[LEFT]), GetHeight(root->children[RIGHT])) + 1;
	pivot->height = GetMaxHeight(GetHeight(pivot->children[LEFT]), GetHeight(pivot->children[RIGHT])) + 1;

	return (pivot);
}

static long GetMaxHeight(long left_height, long right_height)
{
	return (left_height > right_height ? left_height : right_height);
}

static long GetHeight(tree_node_t *node)
{
	if (NULL == node)
	{
		return (0);
	}

	return (node->height);
}

static tree_node_t *InsertRecursive(avlt_t *tree, tree_node_t *current_node, void *data)
{
	long balance_factor = 0;
	int go_left = TRUE;

	if (NULL == current_node)
	{
		return (CreateNode(data));
	}

	go_left = tree->is_before(data, current_node->data);

	if (go_left)
	{
		current_node->children[LEFT] = InsertRecursive(tree, current_node->children[LEFT], data);
	}
	else
	{
		current_node->children[RIGHT] = InsertRecursive(tree, current_node->children[RIGHT], data);
	}

	current_node->height = GetMaxHeight(GetHeight(current_node->children[LEFT]),GetHeight(current_node->children[RIGHT])) + 1;
	
	balance_factor = CalculateBalance(current_node);

	switch (InsertCheckBalanceType(current_node, balance_factor, data, tree->is_before))
	{
		case LL:
			return (RotateRight(current_node));

		case RR:
			return (RotateLeft(current_node));

		case LR:
			current_node->children[LEFT] = RotateLeft(current_node->children[LEFT]);
			return (RotateRight(current_node));

		case RL:
			current_node->children[RIGHT] = RotateRight(current_node->children[RIGHT]);
			return (RotateLeft(current_node));

		case BALANCED:
			break;
	}

	return (current_node);
}

static tree_node_t *CreateNode(void *data)
{
	tree_node_t *node = (tree_node_t*)malloc(sizeof(tree_node_t));
	if (NULL == node)
	{
		return (NULL);
	}

	node->data = data;
	node->height = 0; 
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;

	return (node);
}