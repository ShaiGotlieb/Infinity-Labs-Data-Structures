#ifndef __H_SORT__
#define __H_SORT__

typedef int (*cmp_fun_t)(const void *data1, const void *data2, void *param);

void BubbleSort(int *base, size_t num_elements);
/********************************************************************
 * The BubbleSort function uses the bubble sort algorithm 
 * to sort an array of ints of num_elements number of elements.
 * The contents of the array are sorted in ascending order.
 *
 * base - a pointer to the base of the array to be sorted. not NULL.
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
 * base - a pointer to the base of the array to be sorted. not NULL.
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
 * base - a pointer to the base of the array to be sorted. not NULL.
 *
 * num_elements - the number of elements in the array.
 *
 * Time complexity of this function is O(n^2)
 *******************************************************************/

void MergeSort(int *base, size_t num_elements);
/********************************************************************
 * The MergeSort function uses the merge sort algorithm 
 * to sort an array of ints of num_elements number of elements.
 * The contents of the array are sorted in ascending order.
 *
 * base - a pointer to the base of the array to be sorted. not NULL.
 *
 * num_elements - the number of elements in the array.
 *
 * Time complexity of this function is O(nlogn)
 *******************************************************************/

void QuickSort(int *base, size_t num_elements);
/********************************************************************
 * The QuickSort function uses the quick sort algorithm 
 * to sort an array of ints of num_elements number of elements.
 * The contents of the array are sorted in ascending order.
 *
 * base - a pointer to the base of the array to be sorted. not NULL.
 *
 * num_elements - the number of elements in the array.
 *
 * Time complexity of this function is O(nlogn)
 *******************************************************************/

void HeapSort(void *base, size_t num_elements, size_t element_size, cmp_fun_t compare_fun, void *param); 
/********************************************************************
 * The HeapSort function uses the heap sort algorithm 
 * to sort an array.
 * The contents of the array are sorted in ascending order.
 *
 * base - a pointer to the base of the array to be sorted. not NULL.
 *
 * num_elements - the number of elements in the array.
 *
 * element_size - size of each each elemnet in array.
 *
 * compare_fun - a function to compare element's value
 *
 * Time complexity of this function is O(nlogn)
 *******************************************************************/

#endif