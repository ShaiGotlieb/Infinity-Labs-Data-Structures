#include <stdlib.h> /* malloc() */
#include <string.h> /* memcpy() */
#include <assert.h> /* assert() */
#include "stack.h"

struct stack_s 
{ 
	void *stack_base;
	size_t element_size;
	size_t capacity;	
	void *stack_top; 
};

stack_t *StackCreate(size_t element_size, size_t capacity)
{
	stack_t *stack;

	assert(capacity > 0);
	assert(element_size > 0);

	stack = malloc(sizeof(stack_t));
	if (stack == NULL)
	{
		perror("Allocation Failed!");
		return NULL;
	}

	stack->element_size = element_size;
	stack->capacity = capacity;

	stack->stack_base = malloc(element_size * capacity);
	if (stack->stack_base == NULL)
	{
		perror("Allocation Failed!");
		return NULL;
	}

	stack->stack_top = stack->stack_base;

	return stack;
}

void StackDestroy(stack_t *stack)
{
	free(stack->stack_base);
	stack->stack_base = NULL;
	stack->stack_top = NULL;
	free(stack);
	stack = NULL;
}

void StackPush(stack_t *stack, void *element)
{
	assert(stack != NULL);
	assert(element != NULL);
	assert(StackSize(stack) < stack->capacity);

	memcpy(stack->stack_top, element, stack->element_size); 
	stack->stack_top = (char*)stack->stack_top + stack->element_size;
}


void *StackPop(stack_t *stack)
{	
	assert(stack != NULL);
	assert(StackSize(stack) > 0);

	stack->stack_top = (char*)stack->stack_top - stack->element_size;
	
	return stack->stack_top;
}

void *StackPeek(stack_t *stack)
{
	assert(stack != NULL);
	assert(StackSize(stack) > 0);

	return (char*)stack->stack_top - stack->element_size;
}

size_t StackSize(stack_t *stack)
{
	assert(stack != NULL);

	return ((char *)stack->stack_top - (char*)stack->stack_base) / stack->element_size;
}