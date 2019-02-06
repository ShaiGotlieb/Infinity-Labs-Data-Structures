#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


struct stack_s
{
	void* stack_base;
	size_t element_size;
	size_t capacity;
	void* stack_top;
};

stack_t *StackCreate(size_t element_size, size_t capacity)
{
	stack_t *new_stack = NULL;

	assert(element_size > 0);
	assert(capacity > 0);

	new_stack = (stack_t*)malloc((capacity * element_size) + sizeof(stack_t));

	if(NULL == new_stack)
	{
		return (new_stack);
	}

	new_stack->stack_base = new_stack + 1;
	new_stack->capacity = capacity;
	new_stack->element_size = element_size;
	new_stack->stack_top = new_stack + 1;

	return (new_stack);
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	stack->stack_top = NULL;
	stack->stack_base = NULL;
	free(stack);
	stack = NULL;
}

void StackPush(stack_t *stack, void *element)
{
	assert(stack->capacity > StackSize(stack));
	assert(NULL != stack);
	assert(element);

	memmove(stack->stack_top, element, stack->element_size);
	stack->stack_top = (char *)stack->stack_top + stack->element_size;
}

void *StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(stack->stack_top != stack->stack_base);

	stack->stack_top = (char *)stack->stack_top - stack->element_size;

	return (stack->stack_top);
}


void *StackPeek(stack_t *stack)
{
	assert(NULL != stack);
	return ((char *)stack->stack_top - stack->element_size);
}


size_t StackSize(stack_t *stack)
{
	return (((*(size_t *)&stack->stack_top - *(size_t *)&stack->stack_base)) / (stack->element_size));
}
