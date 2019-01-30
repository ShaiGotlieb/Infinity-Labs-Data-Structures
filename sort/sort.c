#include "sort.h"

static void Swap(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

static void Insert(int *arr, int pos, int value)
{
	int i = pos - 1;

	while (i >= 0 && arr[i] > value)
	{
		arr[i + 1] = arr[i];
		i--;
	}

	arr[i + 1] = value;
}

void BubbleSort(int *base, size_t num_elements)
{
	size_t i, j;

	for (i = 0; i < num_elements; ++i)
	{
		for (j = 0; j < num_elements - i - 1; ++j)
		{
			if (base[j] > base[j+1])
			{
				Swap(&base[j], &base[j+1]);
			}
		}
	}
}

void InsertionSort(int *base, size_t num_elements)
{
	size_t i;

	for (i = 1; i < num_elements; ++i)
	{
		Insert(base, i, base[i]);
	}
}

void SelectionSort(int *base, size_t num_elements)
{
    size_t i, j, min; 
  
    for (i = 0; i < num_elements - 1; i++) 
    { 
        min = i; 

        for (j = i + 1; j < num_elements; j++)
        {
        	if (base[j] < base[min]) 
        	{
        		min = j; 
        	}
        } 
  
        Swap(&base[min], &base[i]); 
    } 
}

