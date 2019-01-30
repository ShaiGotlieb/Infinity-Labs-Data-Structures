#include <stdlib.h> /* size_t*/
#include "test.h"
#include "sort.h"

#define RANDOM (rand())
#define ARRAY_SIZE (10)

TestResult TestBubbleSort();
TestResult TestInsertionSort();
TestResult TestSelectionSort();

int unsorted_array[10];
int smallest_arr_to_sort[2];

void InitArray()
{
	int i;

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		unsorted_array[i] = RANDOM;
	}

	smallest_arr_to_sort[0] = RANDOM;
	smallest_arr_to_sort[1] = RANDOM;
}

int main()
{
	RUN_TEST(TestBubbleSort);
	RUN_TEST(TestInsertionSort);
	RUN_TEST(TestSelectionSort);
	
	return (EXIT_SUCCESS);
}

TestResult TestBubbleSort()
{
	int i;

	InitArray();

	BubbleSort(unsorted_array, ARRAY_SIZE);
	BubbleSort(smallest_arr_to_sort, 2);

	REQUIRE(smallest_arr_to_sort[0] <= smallest_arr_to_sort[1]);


	for (i = 0; i < ARRAY_SIZE - 1; ++i)
	{
		REQUIRE(unsorted_array[i] <= unsorted_array[i+1]);
	}

	return (TEST_PASS);
}

TestResult TestInsertionSort()
{
	int i;

	InitArray();

	InsertionSort(unsorted_array, ARRAY_SIZE);
	InsertionSort(smallest_arr_to_sort, 2);

	REQUIRE(smallest_arr_to_sort[0] <= smallest_arr_to_sort[1]);

	for (i = 0; i < ARRAY_SIZE - 1; ++i)
	{
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

	REQUIRE(smallest_arr_to_sort[0] <= smallest_arr_to_sort[1]);

	for (i = 0; i < ARRAY_SIZE - 1; ++i)
	{
		REQUIRE(unsorted_array[i] <= unsorted_array[i+1]);
	}

	return (TEST_PASS);
}
