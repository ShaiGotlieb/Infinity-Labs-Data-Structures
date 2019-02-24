#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memmove */

#include "sort.h"

static void MergeSortRecursive(int *arr, int begin, int end);
static void Merge(int *arr, int begin, int mid, int end);
static void Swap(int *x, int *y);
static void SwapHeapSort(void *x, void *y, size_t element_size);
static void Insert(int *arr, int pos, int value);
static void QuickSortRecursive(int *arr, int begin, int end);
static int Partition(int *arr, int begin, int end);
static void Heapify(void *base, int index, int max, size_t element_size, cmp_fun_t compare_func);


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

void MergeSort(int *base, size_t num_elements)
{
	int begin = 0;
	int end = num_elements - 1;
	MergeSortRecursive(base, begin, end);
}

void QuickSort(int *base, size_t num_elements)
{
	int begin = 0;
	int end = num_elements - 1;

	QuickSortRecursive(base, begin, end);
}

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

static void MergeSortRecursive(int *arr, int begin, int end)
{
	if (begin < end)
	{
		int mid = (begin + end) / 2;
		MergeSortRecursive(arr, begin, mid);
		MergeSortRecursive(arr, mid + 1, end);
		Merge(arr, begin, mid, end);
	}
}

static void Merge(int *arr, int begin, int mid, int end)
{
	int left_arr_length = mid - begin + 1;
	int right_arr_length = end - mid;
	int *left_arr = malloc((left_arr_length + 1) * sizeof(int));
	int *right_arr = malloc((right_arr_length + 1) * sizeof(int));
	int i, j, k;

	for (i = 0; i < left_arr_length; ++i)
	{
		left_arr[i] = arr[begin + i - 1]; 
	}

	for (j = 0; i < right_arr_length; ++i)
	{
		right_arr[j] = arr[mid + j];
	}

	for (k = begin,  i = 0, j = 0; k < end; k++)
	{
		if (left_arr[i] <= right_arr[j])
		{
			arr[k] = left_arr[i];
			i++;
		}
		else 
		{
			arr[k] = right_arr[j];
			j++;
		}
	}

	free(left_arr);
	free(right_arr);
}

static void QuickSortRecursive(int *arr, int begin, int end)
{
	if (begin < end)
	{
		int mid = Partition(arr, begin, end);
		QuickSortRecursive(arr, begin, mid - 1);
		QuickSortRecursive(arr, mid + 1, end);
	}
}

static int Partition(int *arr, int begin, int end)
{
	int pivot = arr[end];
	int i = begin - 1;
	int j;

	for (j = begin; j <= end - 1; ++j)
	{
		if (arr[j] <= pivot)
		{
			i++;
			Swap(&arr[i], &arr[j]);
		}
	}

	Swap(&arr[i + 1], &arr[end]);

	return (i + 1);
}

void HeapSort(void *base, size_t num_elements, size_t element_size, cmp_fun_t compare_func, void *param)
{
	int i;

	for (i = (num_elements / 2) - 1; i >= 0; i--) 
	{
        Heapify(base, i, num_elements, element_size, compare_func); 
	}

	for (i = num_elements - 1; i >= 0; --i)
	{
		SwapHeapSort((void*)base, (void *)((char*)base + (element_size * i)), element_size);
		Heapify(base, 0, i, element_size, compare_func);
	}
}

static void Heapify(void *base, int index, int max, size_t element_size, cmp_fun_t compare_func)
{
	int left_child_index = (2 * index) + 1;
	int right_child_index = (2 * index) + 2;
	int largest = index;

	if (left_child_index < max && 0 < compare_func((void*)((char*)base + (left_child_index * element_size)), (void*)((char*)base + (largest * element_size)), NULL))
	{
		largest = left_child_index;
	}
	else
	{
		largest = index;
	}

	if ((right_child_index < max && 0 < compare_func((void*)((char*)base + (right_child_index * element_size)), (void*)((char*)base + (largest * element_size)), NULL)))
	{
		largest = right_child_index;
	}

	if (largest != index)
	{
		SwapHeapSort((void*)((char *)base + (element_size * index)), (void*)((char *)base + (element_size * largest)), element_size);
		Heapify(base, largest, max, element_size, compare_func);
	}
}

static void SwapHeapSort(void *x, void *y, size_t element_size)
{
	void *temp = malloc(sizeof(void *));

	memmove(temp, x, element_size);
	memmove(x, y, element_size);
	memmove(y, temp, element_size);

	free(temp);
	temp = NULL;
	
}