#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "queue.h"
#include "sllist.h"

#define TRUE 1
#define FALSE 0
#define QUEUE_SIZE_WITH_DUMMY 1

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
	
	dummy = SLLCreateNode(NULL, (void*)0xDEADBEEF); 
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
	SLLDestroyNodes(queue->head);
	free(queue);
	queue = NULL;
}

enum q_status Enqueue(queue_t *queue, void *data)
{
	sllist_node_t *node_to_insert = SLLCreateNode(NULL, data);

	assert(queue != NULL);
	
	if (NULL != node_to_insert)
	{
		SLLInsert(queue->tail, node_to_insert);
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

	return_data = queue->head->data;
	removed_node = queue->head;
	queue->head = queue->head->next;

	free(removed_node);

	return return_data;	
}

void *QuePeek(const queue_t *queue)
{
	assert(queue != NULL);
	return queue->head->data;
}

int QueIsEmpty(const queue_t *queue)
{
	assert(queue != NULL);
	return SLLCount(queue->head) > QUEUE_SIZE_WITH_DUMMY ? FALSE : TRUE;
}

size_t QueGetSize(const queue_t *queue)
{
	return SLLCount(queue->head) - QUEUE_SIZE_WITH_DUMMY; 
}

void QueAppend(queue_t *first_queue, queue_t *last_queue)
{
	sllist_node_t *dummy = NULL;

	assert(NULL != first_queue);
	assert(NULL != last_queue);

	if (!QueIsEmpty(last_queue))
	{
		first_queue->tail->next = last_queue->head;
		dummy = SLLRemove(first_queue->tail);
		first_queue->tail = last_queue->tail;
		last_queue->tail = dummy;
		last_queue->head = dummy;
	}
}