#include <stdlib.h>
#include "test.h"
#include "linear_sort.h"

#define RANDOM ((rand() % 50) + 50 )
#define ARRAY_SIZE (10)
#define FROM (50)
#define TO (100)

TestResult TestCountingSort();
TestResult TestRadixSort();

int unsorted_array[ARRAY_SIZE];
int nothing_to_sort[1];
int smallest_arr_to_sort[2];
unsigned int unsorted_array_radix[ARRAY_SIZE];
unsigned int nothing_to_sort_radix[1];
unsigned int smallest_arr_to_sort_radix[2];

static void PrintArray()
{
	int i;
	for (i = 0; i < 4; ++i)
	{
		printf("%d, ", unsorted_array_radix[i]);
	}
	printf("\n");
}

void InitArrays()
{
	int i;

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		unsorted_array[i] = RANDOM;
		unsorted_array_radix[i] = RANDOM;
	}

	smallest_arr_to_sort[0] = RANDOM;
	smallest_arr_to_sort[1] = RANDOM;
	smallest_arr_to_sort_radix[0] = RANDOM;
	smallest_arr_to_sort_radix[1] = RANDOM;
	nothing_to_sort_radix[0] = RANDOM;
	nothing_to_sort[0] = RANDOM;
}

int main()
{
	RUN_TEST(TestCountingSort);
	RUN_TEST(TestRadixSort);
	
	return (EXIT_SUCCESS);
}

TestResult TestCountingSort()
{
	int i;

	InitArrays();

	CountingSort(unsorted_array, ARRAY_SIZE, 50, 100);
	CountingSort(smallest_arr_to_sort, 2, 50, 100);
	CountingSort(nothing_to_sort, 1, 50, 100);

	REQUIRE(smallest_arr_to_sort[0] <= smallest_arr_to_sort[1]);
	REQUIRE(nothing_to_sort[0] <= nothing_to_sort[0]);

	for (i = 0; i < ARRAY_SIZE - 1; ++i)
	{
		REQUIRE(unsorted_array[i] <= unsorted_array[i+1]);
	}

	return (TEST_PASS);
}

TestResult TestRadixSort()
{
	int i;

	InitArrays();
	
	RadixSort(unsorted_array_radix, ARRAY_SIZE);
	RadixSort(smallest_arr_to_sort_radix, 2);
	RadixSort(nothing_to_sort_radix, 1);

	REQUIRE(smallest_arr_to_sort_radix[0] <= smallest_arr_to_sort_radix[1]);
	REQUIRE(nothing_to_sort_radix[0] <= nothing_to_sort_radix[0]);

	for (i = 0; i < ARRAY_SIZE - 1; ++i)
	{
		REQUIRE(unsorted_array_radix[i] <= unsorted_array_radix[i+1]);
	}

	return (TEST_PASS);
}