#ifndef __H_RECURSION__
#define __H_RECURSION__

#include <stddef.h> /* size_t */
#include "sllist.h"
#include "stack.h"

typedef int (*is_before_t)(const void *data1, const void *data2);

int FibonacciIterative(int num);
int FibonacciRecursive(int num);
size_t StrlenRecursive(const char *str);
int StrcmpRecursive(const char *str1, const char *str2);
char *StrcpyRecursive(char *dest, const char *src);
sllist_node_t *SLLFlipRecursive(sllist_node_t *list);
void StackSortRecursive(stack_t *stack, is_before_t is_before);

#endif