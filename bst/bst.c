#include <stdlib.h> /* size_t, malloc */
#include <assert.h> 

#include "bst.h"

#define DUMMY_ROOT (void *)(0xDEADBEEF)
#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAILURE (1)

typedef struct tree_node_s
{
	void *data;
	struct tree_node_s *parent;
	struct tree_node_s *children[2];

} tree_node_t;

struct bst_s
{
	tree_node_t *root;
	cmp_func_t cmp_func;
	void *param;
	size_t size;
};
typedef enum {LEFT = 0, RIGHT = 1} DIRECTION;

static bst_iterator_t BSTGetParentConv(bst_iterator_t iterator)
{
	bst_iterator_t parent_it;
	tree_node_t *parent_node = (tree_node_t *)(iterator.info);
	parent_node = parent_node->parent;
	parent_it.info = parent_node;

	return (parent_it);
}

static bst_iterator_t BSTGetLeftChildConv(bst_iterator_t iterator)
{
	bst_iterator_t left_child_it;
	tree_node_t *left_child_node = (tree_node_t *)(iterator.info);
	left_child_node = left_child_node->children[LEFT];
	left_child_it.info = left_child_node;

	return (left_child_it);
}

static bst_iterator_t BSTGetRightChildConv(bst_iterator_t iterator)
{
	bst_iterator_t right_child_it;
	tree_node_t *right_child_node = (tree_node_t *)(iterator.info);
	right_child_node = right_child_node->children[RIGHT];
	right_child_it.info = right_child_node;

	return (right_child_it);
}

static int HasRightChildConv(bst_iterator_t it)
{
	tree_node_t *node = (tree_node_t *)it.info;

	return (node->children[RIGHT] != NULL ? TRUE : FALSE);
}

static int HasLeftChildConv(bst_iterator_t it)
{
	tree_node_t *node = (tree_node_t *)it.info;

	return (node->children[LEFT] != NULL ? TRUE : FALSE);
}

static int IsLeftLeafConv(tree_node_t *node)
{
	return ((node->parent)->children[LEFT] == node);
}

static int IsRightLeafConv(tree_node_t *node)
{
	return ((node->parent)->children[RIGHT] == node);
}

static int IsLeafConv(tree_node_t *node)
{
	return ((node->children[LEFT] == NULL) && (node->children[RIGHT] == NULL));
}

static int IsRightChildConv(bst_iterator_t it)
{
	tree_node_t *node = (tree_node_t *)it.info;
	bst_iterator_t parent_it;
	parent_it.info = node->parent;

	return (BSTIsSameIterator(BSTGetRightChildConv(parent_it), it) ? TRUE : FALSE);
}

static int IsLeftChildConv(bst_iterator_t it)
{
	tree_node_t *node = (tree_node_t *)it.info;
	bst_iterator_t parent_it;
	parent_it.info = node->parent;

	return (BSTIsSameIterator(BSTGetLeftChildConv(parent_it), it) ? TRUE : FALSE);
}

static void DeleteNodeConv(bst_t *tree, tree_node_t *node)
{
	node->data = NULL;
	node->parent = NULL;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	tree->size--;
	
	free(node);
	node = NULL;
}

static tree_node_t *CreateNodeConv(void *data, tree_node_t *children_l, tree_node_t *children_r, tree_node_t *parent)
{
	tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
	if(NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = data;
	new_node->children[LEFT] = children_l;
	new_node->children[RIGHT] = children_r;
	new_node->parent = parent;

	return (new_node);
}

static tree_node_t *RmoveNodesConv(tree_node_t *current_node)
{
	tree_node_t *removed_node = current_node->children[LEFT];
	bst_iterator_t iterator;
	iterator.info = removed_node;
		
	if (!HasRightChildConv(iterator))
	{
		current_node->data = removed_node->data;
		current_node->children[LEFT] = removed_node->children[LEFT];
		
		if (HasLeftChildConv(iterator))
		{
			removed_node->children[LEFT]->parent = current_node;
		}
	}
	else
	{ 
		while (HasRightChildConv(iterator))
		{
			removed_node = removed_node->children[RIGHT];
		}

		current_node->data = removed_node->data;
		removed_node->parent->children[RIGHT] = removed_node->children[LEFT];
		
		if (HasLeftChildConv(iterator))
		{
			removed_node->children[LEFT]->parent = removed_node->parent;
		}
	}

	return (removed_node);
}

bst_t *BSTCreate(cmp_func_t cmp_func, void *param)
{
	tree_node_t *root = NULL;
	bst_t *bst = NULL;

	root = CreateNodeConv(DUMMY_ROOT, NULL, NULL, NULL);
	if(NULL == root)
	{
		return (NULL);
	}

	bst = (bst_t *)malloc(sizeof(bst_t));
	if(NULL == bst)
	{
		free(root);
		return (NULL);
	}

	bst->root = root;
	bst->size = 0;
	bst->param = param;
	bst->cmp_func = cmp_func;

	return (bst);
}

void BSTDestroy(bst_t *tree)
{
	bst_iterator_t current_iterator = BSTBegin(tree);
	
	while (!BSTIsSameIterator(current_iterator, BSTEnd(tree)))
	{
		BSTRemove(tree, BSTGetData(current_iterator));
		current_iterator = BSTBegin(tree);
	}

	free(tree);
	tree = NULL;
}

size_t BSTGetSize(const bst_t *tree)
{
	return (tree->size);
}

int BSTIsEmpty(const bst_t *tree)
{
	return (tree->root->children[LEFT] == NULL ? TRUE : FALSE);
}

bst_iterator_t BSTInsert(bst_t *tree, void *data)
{
	bst_iterator_t insert_iterator;
	tree_node_t *tree_runner = tree->root->children[LEFT];
	tree_node_t *parent_node = tree->root;
	int direction = LEFT;

	while (NULL != tree_runner)
	{
		parent_node = tree_runner;

		if (0 < tree->cmp_func(tree_runner->data, data, tree->param))
		{
			direction = LEFT;
		}
		else
		{		
			direction = RIGHT;
		}

		tree_runner = tree_runner->children[direction];
	}

	tree_runner = CreateNodeConv(data, NULL, NULL, parent_node);
	parent_node->children[direction] = tree_runner;
	tree->size++;
	insert_iterator.info = tree_runner;

	return (insert_iterator);
}

void BSTRemove(bst_t *tree, void *data)
{
	bst_iterator_t iterator;
	tree_node_t *current_node = NULL;
	tree_node_t *node_to_remove = NULL;

	assert(NULL != tree);

	iterator = BSTFind(tree, data);
	if (BSTIsSameIterator(iterator, BSTEnd(tree)))
	{
		return;
	}

	current_node = (tree_node_t *)iterator.info;
	node_to_remove = current_node;

	if (IsLeafConv(current_node))
	{
		if (current_node->parent->children[LEFT] == current_node)
		{	
		current_node->parent->children[LEFT] = NULL;
		}
		else
		{
		current_node->parent->children[RIGHT] = NULL;
		}
	}

	else if (!HasLeftChildConv(iterator)) 		
	{
		if (current_node->parent->children[LEFT] == current_node)
		{	
		current_node->parent->children[LEFT] = current_node->children[RIGHT];
		}
		else
		{
		current_node->parent->children[RIGHT] = current_node->children[RIGHT];
		}
		
		current_node->children[RIGHT]->parent = current_node->parent;
	}
	else if (!HasRightChildConv(iterator))
	{
		if (current_node->parent->children[LEFT] == current_node)
		{	
		current_node->parent->children[LEFT] = current_node->children[LEFT];
		}
		else
		{
		current_node->parent->children[RIGHT] = current_node->children[LEFT];
		}
		
		current_node->children[LEFT]->parent = current_node->parent;
	}
	else
	{
		node_to_remove = RmoveNodesConv(current_node);
	}
	
	DeleteNodeConv(tree, node_to_remove);
	tree->size--;

	return;
}

bst_iterator_t BSTGetNext(bst_iterator_t iterator)
{
	bst_iterator_t return_iterator;
	tree_node_t *tree_runner = (tree_node_t *)iterator.info;

	if (NULL != tree_runner->children[RIGHT])
	{
		tree_runner = tree_runner->children[RIGHT];

		while (NULL != tree_runner->children[LEFT])
		{
			tree_runner = tree_runner->children[LEFT];
		}

		return_iterator.info = tree_runner;

		return (return_iterator);
	}
	else
	{
		while (!IsLeftLeafConv(tree_runner))
		{
			tree_runner = tree_runner->parent;
		}

		return_iterator.info = tree_runner->parent;

		return (return_iterator);
	}
}

bst_iterator_t BSTGetPrevious(bst_iterator_t iterator)
{
	bst_iterator_t return_iterator;
	tree_node_t *tree_runner = (tree_node_t *)iterator.info;

	if (NULL != tree_runner->children[LEFT])
	{
		tree_runner = tree_runner->children[LEFT];

		while (NULL != tree_runner->children[RIGHT])
		{
			tree_runner = tree_runner->children[RIGHT];
		}

		return_iterator.info = tree_runner;

		return (return_iterator);
	}
	else
	{
		while (!IsRightLeafConv(tree_runner))
		{
			tree_runner = tree_runner->parent;
		}

		return_iterator.info = tree_runner->parent;

		return (return_iterator);
	}
}

void *BSTGetData(bst_iterator_t iterator)
{
	void *data_to_return = NULL;
	tree_node_t *node_data = (tree_node_t *)iterator.info;

	return (data_to_return = node_data->data);
}

bst_iterator_t BSTBegin(const bst_t *tree)
{
	bst_iterator_t return_iterator;
	tree_node_t *tree_runner = tree->root->children[LEFT];

	if (TRUE == BSTIsEmpty(tree))
	{
		return_iterator.info = tree->root;

		return (return_iterator);
	}

	while (NULL != tree_runner->children[LEFT])
	{
		tree_runner = tree_runner->children[LEFT];
	}

	return_iterator.info = tree_runner;

	return (return_iterator);
}

bst_iterator_t BSTEnd(const bst_t *tree)
{
	bst_iterator_t return_iterator;

	return_iterator.info = tree->root;

	return (return_iterator);
}

bst_iterator_t BSTFind(const bst_t *tree, void *data)
{
	bst_iterator_t return_iterator;
	tree_node_t *tree_runner = tree->root->children[LEFT];

	while (NULL != tree_runner)
	{
		if ((tree->cmp_func)(tree_runner->data, data, tree->param) > 0)
		{
			tree_runner = tree_runner->children[LEFT];
		}
		else if ((tree->cmp_func)(tree_runner->data, data, tree->param) < 0)
		{
			tree_runner = tree_runner->children[RIGHT];
		}
		else if ((tree->cmp_func)(tree_runner->data, data, tree->param) == 0)
		{
			return_iterator.info = tree_runner;

			return (return_iterator);
		}
	}

	return (BSTEnd(tree));
}

int BSTForEach(bst_t *tree, action_func_t action_func, void *param)
{
	bst_iterator_t iterator = BSTBegin(tree);
	int status = SUCCESS;
	size_t i;

	for (i = 0; i < tree->size; ++i)
	{
		if(status != action_func(BSTGetData(iterator) , param))
		{
			return (status);
		}

		iterator = BSTGetNext(iterator);
	}

	return (status);
}

int BSTIsSameIterator(bst_iterator_t iterator1, bst_iterator_t iterator2)
{
	return (iterator1.info == iterator2.info);
}
