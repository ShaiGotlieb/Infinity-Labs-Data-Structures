#ifndef __H_SORT__
#define __H_SORT__

#include <stddef.h>

void BubbleSort(int *base, size_t num_elements);
/********************************************************************
 * The BubbleSort function uses the bubble sort algorithm 
 * to sort an array of ints of num_elements number of elements.
 * The contents of the array are sorted in ascending order.
 *
 * base - a pointer to the base of the array to be sorted.
 *
 * num_elements - the number of elements in the array.
 *
 * Time complexity of this function is O(n^2)
 *******************************************************************/

void InsertionSort(int *base, size_t num_elements);
/********************************************************************
 * The InsertionSort function uses the insertion sort algorithm 
 * to sort an array of ints of num_elements number of elements.
 * The contents of the array are sorted in ascending order.
 *
 * base - a pointer to the base of the array to be sorted.
 *
 * num_elements - the number of elements in the array.
 *
 * Time complexity of this function is O(n^2)
 *******************************************************************/

void SelectionSort(int *base, size_t num_elements);
/********************************************************************
 * The SelectionSort function uses the selection sort algorithm 
 * to sort an array of ints of num_elements number of elements.
 * The contents of the array are sorted in ascending order.
 *
 * base - a pointer to the base of the array to be sorted.
 *
 * num_elements - the number of elements in the array.
 *
 * Time complexity of this function is O(n^2)
 *******************************************************************/

#endif