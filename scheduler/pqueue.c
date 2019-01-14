#include <stdlib.h> /* size_t */
#include <assert.h> /* assert */

#include "pqueue.h"
#include "sorted_list.h"

#define DEADBEEF (0xDEADBEEF)

struct pqueue_s
{
	sorted_list_t *list;
};


pqueue_t *PQCreate(has_higher_priority_t has_higher_priority)
{
	pqueue_t *queue = (pqueue_t *)malloc(sizeof(pqueue_t));

	if (NULL == queue)
	{
		return (NULL);
	}

	queue->list = SLCreate(has_higher_priority);

	if (NULL == queue->list)
	{
		free(queue);
		queue = NULL;

		return (NULL);
	}

	return (queue);
}

void PQDestroy(pqueue_t *queue)
{
	assert(NULL != queue);

	SLDestroy(queue->list);

	free(queue);
	queue = NULL;
}

enum q_status PQEnqueue(pqueue_t *queue, void *data)
{
	sorted_list_iterator_t iterator;

	assert(NULL != queue);

	iterator = SLInsert(queue->list, data);

	if (SLIsSameIterator(SLEnd(queue->list), iterator))
	{
		return (Q_MEMORY_ALLOCATION_ERROR);
	}

	return (Q_SUCCESS);
}

void *PQDequeue(pqueue_t *queue)
{
	sorted_list_iterator_t iterator;
	void *return_data;

	assert(NULL != queue);

	iterator = SLBegin(queue->list);
	return_data = SLGetData(iterator);

	SLPopFront(queue->list);

	return return_data;
}

void *PQPeek(const pqueue_t *queue)
{
	sorted_list_iterator_t iterator;
	void *return_data;

	assert(NULL != queue);
	assert(!PQIsEmpty(queue));

	iterator = SLBegin(queue->list);
	return_data = SLGetData(iterator);

	return return_data;
}

boolean_t PQIsEmpty(const pqueue_t *queue)
{
	assert(NULL != queue);

	return SLIsEmpty(queue->list);
}

size_t PQGetSize(const pqueue_t *queue)
{
	assert(NULL != queue);

	return (SLGetSize(queue->list));
}

void *PQErase(pqueue_t *queue, is_match_q_t is_match, void *param)
{
	sorted_list_iterator_t from_iterator;
	sorted_list_iterator_t to_iterator;
	sorted_list_iterator_t to_erase;
	void *return_data = NULL;

	assert(NULL != queue);

	from_iterator = SLBegin(queue->list);
	to_iterator = SLEnd(queue->list);
	to_erase = SLFind(queue->list, from_iterator, to_iterator, (is_match_t)is_match, param, param);

	while (!SLIsSameIterator(to_erase, to_iterator))
	{
		return_data = SLGetData(to_erase);
		from_iterator = SLErase(to_erase);
		to_erase = SLFind(queue->list, from_iterator, to_iterator, (is_match_t)is_match, param, param);
	}
	
	return return_data;
}

void PQClear(pqueue_t *queue)
{
	while (!SLIsEmpty(queue->list))
	{
		PQDequeue(queue);
	}
}