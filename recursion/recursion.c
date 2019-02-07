#include <stddef.h> /* size_t */
#include <string.h> /* strlen */

#include "recursion.h"
#include "sllist.h"
#include "stack.h"

#define TRUE (1)
#define FALSE (0)

int FibonacciIterative(int num)
{
	int result = 1;
	int n1 = 0;
	int n2 = 0;
	int i;

	if (0 == num)
	{
		return (0);
	}

	for (i = 2; i <= num; ++i)
	{
		n2 = n1 + result;
		n1 = result;
		result = n2;
	}

	return (result);
}

int FibonacciRecursive(int num)
{
	if (0 == num)
	{
		return (0);
	}
	if (num < 2)
	{
		return (1);
	}

	return (FibonacciRecursive(num - 1) + FibonacciRecursive(num - 2));
}

size_t StrlenRecursive(const char *str)
{
	char *str_runner = (char *)str;

	if ('\0' == *str_runner)
	{
		return (0);
	}

	return (StrlenRecursive(str_runner + 1) + 1);
}

int StrcmpRecursive(const char *str1, const char *str2)
{
	char *str1_runner = (char*)str1;
	char *str2_runner = (char*)str2;

	if (*str1_runner == *str2_runner && *str2_runner == '\0')
	{
		return (0);
	}
	else if (*str1_runner == *str2_runner)
	{
		StrcmpRecursive(str1 + 1, str2 + 1);
	}
	else
	{
		return (*str1_runner - *str2_runner);
	}
}

char *StrcpyRecursive(char *dest, const char *src)
{
	if ('\0' == *src)
	{
		*dest = *src;

		return (dest);
	}

	StrcpyRecursive(dest + 1, src + 1);

	*dest = *src;

	return (dest);
}

sllist_node_t *SLLFlipRecursive(sllist_node_t *list)
{
	sllist_node_t *tmp_node = NULL;
	sllist_node_t *prev_node = list;
	sllist_node_t *curr_node = prev_node->next;

	if (curr_node == NULL)
	{
		return (prev_node);
	}

	if (curr_node->next == NULL)
	{
		curr_node->next = prev_node;

		return (curr_node);
	}

	prev_node = curr_node;
	curr_node = curr_node->next;

	SLLFlipRecursive(prev_node);

	tmp_node = curr_node->next;
	curr_node->next = prev_node;
	prev_node = curr_node;
	curr_node = tmp_node;

	return (curr_node);
}

static void StackInsertConv(stack_t *stack, void *value, is_before_t is_before)
{
	void *tmp_value;

	if (StackSize(stack) == 0 || TRUE == is_before(value, StackPeek(stack)))
	{
		StackPush(stack, value);

		return;
	}

	tmp_value = StackPop(stack);
	StackInsertConv(stack, value, is_before);
	StackPush(stack, tmp_value);
}

void StackSortRecursive(stack_t *stack, is_before_t is_before)
{
	if (StackSize(stack) > 0)
	{
		void *tmp_value = StackPop(stack);
		StackSortRecursive(stack, is_before);
		StackInsertConv(stack, tmp_value, is_before);
	}
}