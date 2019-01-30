#include <stdlib.h> /* calloc, size_t */
#include <stdio.h>
#include "linear_sort.h"

#define SUCCESS (0)
#define FAILURE (1)
#define BYTES_IN_INT (4)
#define BYTE_SIZE (8)
#define BYTE_RANGE (256)
#define MASK (0xff)

int CountingSort(int *base, size_t num_elements,
					int from, int to)
{
	size_t *count = calloc(to - from, sizeof(size_t));
	int *result = calloc(num_elements, sizeof(int));
	size_t i;
	size_t range = to - from;

	if (NULL == count)
	{
		return (FAILURE);
	}

	if (NULL == result)
	{
		free(count);
		count = NULL;

		return (FAILURE);
	}

	for (i = 0; i < num_elements; ++i)
	{
		count[base[i] - from]++;
	}

	for (i = 1; i < range; ++i)
	{
		count[i] += count[i - 1]; 
	}

	for (i = num_elements; i > 0; --i)
	{
		count[base[i - 1] - from]--;
		result[count[base[i - 1] - from]] = base[i - 1];
	}

	for (i = 0; i < num_elements; ++i)
	{
		base[i] = result[i];
	}

	free(count);
	count = NULL;
	free(result);
	result = NULL;

	return (SUCCESS);
}

static int GetNumberFromByte(unsigned int num, int shift)
{
	unsigned int mask = MASK;
	unsigned int result = num >> shift;

	return (mask & result);
}

static int CountingSortForRadix(unsigned int *base, int num_elements, int shift)
{
	unsigned int *count = calloc(BYTE_RANGE, sizeof(int));
	unsigned int *result = calloc(num_elements, sizeof(int));
	int i;

	if (NULL == count)
	{
		return (FAILURE);
	}

	if (NULL == result)
	{
		free(count);
		count = NULL;

		return (FAILURE);
	}

	for (i = 0; i < num_elements; ++i)
	{
		count[GetNumberFromByte(base[i] ,shift)]++;
	}

	for (i = 1; i < BYTE_RANGE; ++i)
	{
		count[i] += count[i - 1]; 
	}

	for (i = num_elements; i > 0; --i)
	{
		count[GetNumberFromByte(base[i - 1] ,shift)]--;
		result[count[GetNumberFromByte(base[i - 1] ,shift)]] = base[i - 1];
	}

	for (i = 0; i < num_elements; ++i)
	{
		base[i] = result[i];
	}

	free(count);
	count = NULL;
	free(result);
	result = NULL;

	return (SUCCESS);
}

int RadixSort(unsigned int *base, size_t num_elements)
{
	int status = SUCCESS;
	int i;

	for (i = 0; i < BYTES_IN_INT; ++i)
	{
		status = CountingSortForRadix(base, num_elements, i * BYTE_SIZE);
	}

	return (status);
}

