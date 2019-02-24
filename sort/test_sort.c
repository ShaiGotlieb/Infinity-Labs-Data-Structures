#include <stdlib.h> /* size_t*/
#include "test.h"
#include "sort.h"

#define RANDOM (rand() % 99)
#define ARRAY_SIZE (20)

static int IntCompare(const void *data1, const void *data2, void *param);

TestResult TestBubbleSort();
TestResult TestInsertionSort();
TestResult TestSelectionSort();
TestResult TestMergeSort();
TestResult TestQuickSort();
TestResult TestHeapSort();

int unsorted_array[ARRAY_SIZE];
int sorted_array[ARRAY_SIZE];
int reverse_sorted_array[ARRAY_SIZE];
int smallest_arr_to_sort[2];

int main()
{
	RUN_TEST(TestBubbleSort);
	RUN_TEST(TestInsertionSort);
	RUN_TEST(TestSelectionSort);
	RUN_TEST(TestMergeSort);
	RUN_TEST(TestQuickSort);
	RUN_TEST(TestHeapSort);
	
	return (EXIT_SUCCESS);
}

static int IntCompare(const void *data1, const void *data2, void *param)
{
	return (*(int*)data1 - *(int*)data2);
}

void InitArray()
{
	int i;

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		int random = RANDOM;
		unsorted_array[i] = random + 1;
		sorted_array[i] = i;
		reverse_sorted_array[i] = ARRAY_SIZE - i;
	}

	smallest_arr_to_sort[0] = RANDOM + 1;
	smallest_arr_to_sort[1] = RANDOM + 2;
}

TestResult TestBubbleSort()
{
	int i;

	InitArray();

	BubbleSort(sorted_array, ARRAY_SIZE);
	BubbleSort(reverse_sorted_array, ARRAY_SIZE);
	BubbleSort(unsorted_array, ARRAY_SIZE);
	BubbleSort(smallest_arr_to_sort, 2);

	REQUIRE(smallest_arr_to_sort[0] <= smallest_arr_to_sort[1]);


	for (i = 0; i < ARRAY_SIZE - 1; ++i)
	{
		REQUIRE(sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(reverse_sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(unsorted_array[i] <= unsorted_array[i+1]);
	}

	return (TEST_PASS);
}

TestResult TestInsertionSort()
{
	int i;

	InitArray();

	InsertionSort(unsorted_array, ARRAY_SIZE);
	InsertionSort(sorted_array, ARRAY_SIZE);
	InsertionSort(reverse_sorted_array, ARRAY_SIZE);
	InsertionSort(smallest_arr_to_sort, 2);

	REQUIRE(smallest_arr_to_sort[0] <= smallest_arr_to_sort[1]);

	for (i = 0; i < ARRAY_SIZE - 1; ++i)
	{
		REQUIRE(sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(reverse_sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(unsorted_array[i] <= unsorted_array[i+1]);
	}

	return (TEST_PASS);
}

TestResult TestSelectionSort()
{
	int i;

	InitArray();

	SelectionSort(smallest_arr_to_sort, 2);
	SelectionSort(unsorted_array, ARRAY_SIZE);
	SelectionSort(sorted_array, ARRAY_SIZE);
	SelectionSort(reverse_sorted_array, ARRAY_SIZE);

	REQUIRE(smallest_arr_to_sort[0] <= smallest_arr_to_sort[1]);

	for (i = 0; i < ARRAY_SIZE - 1; ++i)
	{
		REQUIRE(sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(reverse_sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(unsorted_array[i] <= unsorted_array[i+1]);
	}

	return (TEST_PASS);
}

TestResult TestMergeSort()
{
	int i;

	InitArray();

	MergeSort(smallest_arr_to_sort, 2);
	MergeSort(unsorted_array, ARRAY_SIZE);
	MergeSort(sorted_array, ARRAY_SIZE);
	MergeSort(reverse_sorted_array, ARRAY_SIZE);

	REQUIRE(smallest_arr_to_sort[0] <= smallest_arr_to_sort[1]);

	for (i = 0; i < ARRAY_SIZE - 1; ++i)
	{
		REQUIRE(sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(reverse_sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(unsorted_array[i] <= unsorted_array[i+1]);
	}

	return (TEST_PASS);
}

TestResult TestQuickSort()
{
	int i;

	InitArray();

	QuickSort(smallest_arr_to_sort, 2);
	QuickSort(unsorted_array, ARRAY_SIZE);
	QuickSort(sorted_array, ARRAY_SIZE);
	QuickSort(reverse_sorted_array, ARRAY_SIZE);

	REQUIRE(smallest_arr_to_sort[0] <= smallest_arr_to_sort[1]);

	for (i = 0; i < ARRAY_SIZE - 1; ++i)
	{					
		REQUIRE(sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(reverse_sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(unsorted_array[i] <= unsorted_array[i+1]);
	}

	return (TEST_PASS);
}

TestResult TestHeapSort()
{
	int i;

	InitArray();

	HeapSort(smallest_arr_to_sort, 2, sizeof(int), IntCompare, NULL);
	HeapSort(unsorted_array, ARRAY_SIZE, sizeof(int), IntCompare, NULL);
	HeapSort(sorted_array, ARRAY_SIZE, sizeof(int), IntCompare, NULL);
	HeapSort(reverse_sorted_array, ARRAY_SIZE, sizeof(int), IntCompare, NULL);

	REQUIRE(smallest_arr_to_sort[0] <= smallest_arr_to_sort[1]);

	for (i = 0; i < ARRAY_SIZE - 1; ++i)
	{				
		REQUIRE(sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(reverse_sorted_array[i] <= unsorted_array[i+1]);
		REQUIRE(unsorted_array[i] <= unsorted_array[i+1]);
	}

	return (TEST_PASS);
}
