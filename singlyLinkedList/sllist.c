#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include "sllist.h"

#define TRUE 1
#define FALSE 0
#define SUCCESS 0

sllist_node_t *SLLCreateNode(sllist_node_t *next, void *data)
{
	sllist_node_t *node = (sllist_node_t*)malloc(sizeof(sllist_node_t));
	if (NULL == node)
	{
		return (NULL);
	}

	node->data = data;
	node->next = next;

	return (node);
}

void SLLDestroyNodes(sllist_node_t *list)
{
	while (NULL != list)
	{	
		sllist_node_t *next_node = list->next;
		list->next = NULL;
		free(list);
		list = next_node;
	}
}

sllist_node_t *SLLInsert(sllist_node_t *insert_before, sllist_node_t *node_to_insert)
{
	void *tmp_data = NULL;
	
	assert(NULL != node_to_insert);

	tmp_data = node_to_insert->data;
	node_to_insert->next = insert_before->next;
	node_to_insert->data = insert_before->data;

	insert_before->data = tmp_data;
	insert_before->next = node_to_insert;

	return insert_before;
}

sllist_node_t *SLLInsertAfter(sllist_node_t *where, sllist_node_t *node_to_insert)
{
	assert(NULL != where);
	assert(NULL != node_to_insert);

	node_to_insert->next = where->next;
	where->next = node_to_insert;

	return (node_to_insert);
}

sllist_node_t *SLLRemove(sllist_node_t *node_to_remove)
{
	sllist_node_t *temp;
	void *data; 
	
	assert(NULL != node_to_remove);
	assert(NULL != node_to_remove->next);

	temp = node_to_remove->next;
	node_to_remove->next = temp->next;
	temp->next = NULL;

	data = temp->data;
	temp->data = node_to_remove->data;
	node_to_remove->data = data;

	return (temp);
}

sllist_node_t *SLLRemoveAfter(sllist_node_t *parent_node)
{
	sllist_node_t *temp_node_ptr = NULL;

	assert(NULL != parent_node);

	temp_node_ptr = parent_node->next; 
	if (parent_node->next == NULL)
	{
		return (NULL);
	}

	parent_node->next = temp_node_ptr->next;
	temp_node_ptr->next = NULL;

	return (temp_node_ptr);
}

size_t SLLCount(const sllist_node_t *node)
{
	size_t counter = 0;

	while(NULL != node)
	{
		node = node->next;
		counter++;
	}

	return (counter);
}

sllist_node_t *SLLFind(sllist_node_t *list, is_match_t is_match, void *data_for_cmp, void *param)
{
	assert(NULL != list);

	while(NULL != list && NULL != data_for_cmp)
	{
		if (is_match(list->data, data_for_cmp, param))
		{
			return (list);
		}

		list = list->next;
	}

	return (NULL);
}

int SLLForEach(sllist_node_t *list, action_t action, void *param)
{
	int status = 0;

	assert(NULL != list);

	while(status == SUCCESS && list != NULL )
	{
		status = action(list->data, param);
		list = list->next;
	}

	return (status);
}

int SLLHasLoop(const sllist_node_t *list)
{
	sllist_node_t *slow_ptr = NULL;
	sllist_node_t *fast_ptr = NULL;

	assert(NULL != list);

	slow_ptr = (sllist_node_t *)list;
	fast_ptr = (sllist_node_t *)list->next;

	while(fast_ptr != NULL)
	{
		if (slow_ptr == fast_ptr)
		{
			return (TRUE);
		}

		if (fast_ptr->next == NULL)
		{
			fast_ptr = fast_ptr->next;
		}
		else
		{
			fast_ptr = fast_ptr->next->next;
		}

		slow_ptr = slow_ptr->next;
	}
	return (FALSE);
}

sllist_node_t *SLLFindIntersection(sllist_node_t *list1, sllist_node_t *list2)
{
	sllist_node_t *ls1_runner = list1;
	sllist_node_t *ls2_runner = list2;
	int ls1_size = 0;
	int ls2_size = 0;

	assert(NULL != list1);
	assert(NULL != list2);

	ls1_size = SLLCount(list1);
	ls2_size = SLLCount(list2);

	while(ls1_runner != NULL && ls2_runner != NULL)
	{
		if (ls1_runner == ls2_runner)
		{
			return (ls1_runner);
		}

		if (ls1_size > ls2_size)
		{
			ls1_runner = ls1_runner->next;
			ls1_size--;
		}
		else if (ls1_size < ls2_size)
		{
			ls2_runner = ls2_runner->next;
			ls2_size--;	
		}
		else
		{
			ls1_runner = ls1_runner->next;
			ls2_runner = ls2_runner->next;
		}
	}

	return (NULL);
}

sllist_node_t *SLLFlip(sllist_node_t *list)
{
	sllist_node_t *prev;
	sllist_node_t *curr;
	sllist_node_t *next;

	if (NULL == list || NULL == list->next )
	{
		return (list);
	}

	prev = list;
	curr = list->next;
	prev->next = NULL;
	next = curr->next;

	while (NULL != next)
	{
		curr->next = prev;
		prev = curr;
		curr = next;
		next = next->next;
	}

	curr->next = prev;
	
	return (curr);
}