#include <stdlib.h> /* malloc() */
#include <string.h> /* memcpy() */
#include <assert.h> /* assert() */
#include <limits.h> /* ULONG_MAX */
#include "dvector.h"

#define SUCCESS 0
#define FAILED 1

struct dvector_s
{
	void *data;
	size_t capacity;
	size_t element_size;
	void *top;
};

dvector_t *DVectorCreate(size_t element_size, size_t capacity)
{
	dvector_t *vector;

	assert(element_size >= 0);
	assert(capacity >= 0);

	vector = (dvector_t*)malloc(sizeof(dvector_t));
	if (vector == NULL)
	{
		perror("Allocation Failed!");
		return NULL;
	}

	vector->capacity = capacity;
	vector->element_size = element_size;

	vector->data = (void*)malloc(element_size * capacity);
	if (vector->data == NULL)
	{
		perror("Allocation Failed!");
		return NULL;
	}

	vector->top = vector->data;

	return vector;
}

void DVectorDestroy(dvector_t *vector)
{
	free(vector->data);
	vector->data = NULL;
	vector->top = NULL;
	free(vector);
	vector = NULL;
}

int DVectorPushEnd(dvector_t *dvector,const void *element)
{
	assert(dvector != NULL);
	assert(element != NULL);

	if (dvector->capacity == DVectorGetSize(dvector))
	{
		if (FAILED == DVectorSetCapacity(dvector, dvector->capacity * 2))
		{
			return FAILED;
		}
	}
	memcpy(dvector->top, element, dvector->element_size); 
	dvector->top = (char*)dvector->top + dvector->element_size;

	return SUCCESS;
}

void *DVectorPopEnd(dvector_t *dvector)
{
	size_t size;

	assert(dvector != NULL);
	assert(DVectorGetSize(dvector) > 0);

	size = DVectorGetSize(dvector);

	/* resize array 'data' when it's 75% empty */
	if ((size-1 <= (dvector->capacity*0.25))) 
	{
		DVectorSetCapacity(dvector, dvector->capacity/2);
	}
	dvector->top = (char*)dvector->top - dvector->element_size;

	return dvector->top;
}

size_t DVectorFindItemIndex(const dvector_t *dvector,const void *element)
{
	size_t size;
	size_t index;

	assert(dvector != NULL);
	assert(element != NULL);

	size = DVectorGetSize(dvector);
	for (index = 1; index <= size; ++index)
	{
		if (0 == memcmp(((char*)dvector->top - index*dvector->element_size), element, dvector->element_size))
		{
			return size-index;
		}
	}

	return ULONG_MAX;
}

size_t DVectorGetSize(const dvector_t *dvector)
{
	assert(dvector != NULL);

	return ((char *)dvector->top - (char*)dvector->data) / dvector->element_size;
}

size_t DVectorGetCapacity(const dvector_t *dvector)
{
	assert(dvector != NULL);

	return dvector->capacity;
}

 int DVectorSetCapacity(dvector_t *dvector, size_t new_capacity)
 {
 	void *ptr_memory = NULL;
 	assert(NULL != dvector);

 	ptr_memory = realloc(dvector->data, new_capacity*dvector->element_size);
 	if (ptr_memory == NULL)
	{
		perror("Allocation Failed!");
		return FAILED;
	}

	dvector->data = ptr_memory;
	dvector->capacity = new_capacity;

	return SUCCESS;
 }