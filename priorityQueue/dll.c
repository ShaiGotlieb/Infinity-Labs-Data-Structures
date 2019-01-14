#include <stdlib.h> /* malloc, free, size_t */
#include <assert.h> /* assert */

#include "dll.h"

#define DEADBEEF (0xDEADBEEF)
#define DUMMY_ELEMENTS (2)

typedef struct dll_node_s
{
	void *data;
	struct dll_node_s *next;
	struct dll_node_s *prev;
}dll_node_t;

struct dll_s
{
	dll_node_t *head;
	dll_node_t *tail;
};

static dll_node_t *CreateNode(dll_node_t *prev, dll_node_t *next, void *data)
{
	dll_node_t *node = (dll_node_t *)malloc(sizeof(dll_node_t));
	
	if (node == NULL)
	{
		return (NULL);
	}

	node->prev = prev;
	node->next = next;
	node->data = data;

	return (node);
}

dll_t *DLLCreate()
{
	dll_t *dll = (dll_t *)malloc(sizeof(dll_t));
	dll_node_t *head_dummy;
	dll_node_t *tail_dummy;

	if (NULL == dll)
	{
		return (NULL);
	}

	head_dummy = CreateNode(dll->head, NULL, (void *)DEADBEEF);
	if (head_dummy == NULL)
	{
		free(dll);
		dll = NULL;

		return (NULL);
	}

	tail_dummy = CreateNode(NULL, dll->tail, (void *)DEADBEEF);
	if (tail_dummy == NULL)
	{
		free(head_dummy);
		head_dummy = NULL;
		free(dll);
		dll = NULL;

		return (NULL);
	}
	
	dll->head = head_dummy;
	dll->tail = tail_dummy;


	head_dummy->next = tail_dummy;
	tail_dummy->prev = head_dummy;
	
	dll->head->prev = NULL;
	dll->tail->next = NULL;
	
	return (dll);
}

void DLLDestroy(dll_t *list)
{
	dll_node_t *current_node;

	assert(NULL != list);

	current_node = list->head;

	while(current_node != NULL)
	{
		dll_node_t *next_node = current_node->next;

		current_node->data = NULL;
		current_node->next = NULL;
		current_node->prev = NULL;
		free(current_node);
		current_node = next_node;
	}

	free(list);
	list = NULL;
}

size_t DLLGetSize(const dll_t *list)
{
	dll_node_t *next_node;
	size_t count = 0;

	assert(NULL != list);

	next_node = list->head;

	while(next_node != NULL)
	{
		count++;
		next_node = next_node->next;
	}

	return (count - DUMMY_ELEMENTS);
}

boolean_t DLLIsEmpty(const dll_t *list)
{
	assert(NULL != list);

	return (list->head->next == list->tail);
}

dll_iterator_t DLLBegin(const dll_t *list)
{
	dll_iterator_t iterator;

	assert(NULL != list);

	iterator.info = list->head->next;

	return (iterator);
}

dll_iterator_t DLLEnd(const dll_t *list)
{
	dll_iterator_t iterator;

	assert(NULL != list);

	iterator.info = list->tail;

	return (iterator);
}

void *DLLGetData(const dll_iterator_t iterator)
{
	dll_node_t *node = (dll_node_t *)iterator.info;

	assert(NULL != node);

	return (node->data);
}

dll_iterator_t DLLGetNext(const dll_iterator_t iterator)
{
	dll_node_t *node = (dll_node_t *)iterator.info;
	dll_iterator_t it;

	assert(NULL != node);

	it.info = node->next;
	
	return (it);
}

dll_iterator_t DLLGetPrevious(const dll_iterator_t iterator)
{
	dll_node_t *node = (dll_node_t *)iterator.info;
	dll_iterator_t it;
	
	assert(NULL != node);

	it.info = node->prev;

	return (it);
}


static dll_iterator_t DLLInsertNode(dll_t *list, dll_iterator_t where, void *data)
{
	dll_iterator_t iterator;
	dll_node_t *node_where = (dll_node_t *)where.info;
	dll_node_t *node_to_insert = CreateNode(node_where->prev, node_where, data);

	if (node_to_insert == NULL)
	{
		iterator.info = list->tail;
		return (iterator);
	}
	node_where->prev->next = node_to_insert;
	
	node_where->prev = node_to_insert;
	where.info = node_to_insert;
	
	return (where);
}

dll_iterator_t DLLInsert(dll_t *list, dll_iterator_t where, void *data)
{
	dll_iterator_t iterator;

	iterator.info = NULL;

	if (!DLLIsEmpty(list))
	{
		iterator = DLLInsertNode(list, where, data);
	}

	return (iterator);
}

dll_iterator_t DLLPushFront(dll_t *list, void *data)
{
	dll_iterator_t it;

	assert(NULL != list);

	it.info = list->head->next;
	it = DLLInsertNode(list, it, data);

	return (it);
}

dll_iterator_t DLLPushBack(dll_t *list, void *data)
{
	dll_iterator_t it;

	assert(NULL != list);

	it.info = list->tail;
	it = DLLInsertNode(list, it, data);

	return (it);
}

dll_iterator_t DLLErase(dll_iterator_t iterator)
{
	dll_node_t *node_to_remove = (dll_node_t *)iterator.info;

	node_to_remove->prev->next = node_to_remove->next;
	node_to_remove->next->prev = node_to_remove->prev;
	iterator.info = node_to_remove->next;

	free(node_to_remove);

	return (iterator);
}

boolean_t DLLIsSameIterator(const dll_iterator_t iterator1, const dll_iterator_t iterator2)
{
	return (iterator1.info == iterator2.info);
}

void DLLPopFront(dll_t *list)
{
	assert(NULL != list);
	assert(!DLLIsEmpty(list));

	DLLErase(DLLBegin(list));
}

void DLLPopBack(dll_t *list)
{
	assert(NULL != list);
	assert(!DLLIsEmpty(list));

	DLLErase(DLLGetPrevious(DLLEnd(list)));
}

dll_iterator_t DLLFind(dll_t *list, const dll_iterator_t from, const dll_iterator_t to,
									is_match_t ismatch, void *data_for_cmp, void *param)
{
	dll_iterator_t iterator = DLLEnd(list);
	dll_node_t *node_to_find = (dll_node_t *)from.info;

	assert(NULL != list);

	while(node_to_find != to.info)
	{
		if (TRUE == ismatch(node_to_find->data, data_for_cmp, param))
		{
			iterator.info = node_to_find;

			return (iterator);
		}
		node_to_find = node_to_find->next;
	}

	return (iterator);
}

status_t DLLForEach(dll_iterator_t from, dll_iterator_t to,
										action_t action, void *param)
{
	dll_node_t *node_to_action = (dll_node_t *)from.info;
	status_t status = SUCCESS;

	while(node_to_action != to.info)
	{
		status = action(node_to_action->data, param);
		if (FAIL == status)
		{
			return (status);
		}
		node_to_action = node_to_action->next;
	}
	return (status);
}

void DLLSplice(dll_iterator_t where, dll_iterator_t from, dll_iterator_t to)
{
	dll_node_t *node_where = (dll_node_t *)where.info;
	dll_node_t *node_from = (dll_node_t *)from.info;
	dll_node_t *node_to = (dll_node_t *)to.info;
	dll_node_t *node_where_prev = node_where->prev;
	dll_node_t *node_from_prev = node_from->prev;
	dll_node_t *node_to_prev = node_to->prev;

	node_from_prev->next = node_to;
	node_to->prev = node_from_prev;

	node_where_prev->next = node_from;
	node_from->prev = node_where_prev;

	node_to_prev->next = node_where;
	node_where->prev = node_to_prev;
}

