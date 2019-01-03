#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "queue.h"
#include "sllist.h"

#define TRUE 1
#define FALSE 0


struct queue_s
{
	sllist_node_t *head;
	sllist_node_t *tail;
};

queue_t *QueCreate()
{
	queue_t *queue = NULL;
	sllist_node_t *dummy = NULL;
	
	queue = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return NULL;
	}
	
	dummy = SLLCreateNode(NULL, NULL); 
	if (NULL == dummy)
	{
		free(queue);
		return NULL;	
	}
	
	queue->head = dummy;
	queue->tail = dummy;
	
	return queue;
}

void QueDestroy(queue_t *queue)
{
	while(queue != NULL)
	{
		SLLDestroyNodes(queue->head);
		free(queue);
		queue = NULL;
	}

	free(queue);
}

enum q_status Enqueue(queue_t *queue, void *data)
{
	sllist_node_t *node_to_insert = SLLCreateNode(NULL, data);

	assert(queue != NULL);
	
	if (SLLInsert(queue->tail, node_to_insert) != NULL && node_to_insert != NULL)
	{
		queue->tail = queue->tail->next;
		return Q_SUCCESS;
	}

	return Q_MEMORY_ALLOCATION_ERROR;
}

void *Dequeue(queue_t *queue)
{
	void *return_data;
	sllist_node_t *removed_node;
	
	assert(queue != NULL);

	removed_node = SLLRemove(queue->head);
	return_data = removed_node->data;

	SLLDestroyNodes(removed_node);
	
	return return_data;	
}

void *QuePeek(const queue_t *queue)
{
	return queue->head->data;
}

int QueIsEmpty(const queue_t *queue)
{
	return SLLCount(queue->head) > 1 ? FALSE : TRUE;
}

size_t QueGetSize(const queue_t *queue)
{
	return SLLCount(queue->head) - 1; /* dummy is always inside */
}

void QueAppend(queue_t *first_queue, queue_t *last_queue)
{
	assert(NULL != first_queue);
	assert(NULL != last_queue);

	first_queue->tail->next = last_queue->head->next;
	
	if (NULL != last_queue->head->next)
	{
		first_queue->tail = last_queue->tail;
	}
	
	last_queue->head->next = NULL;

}