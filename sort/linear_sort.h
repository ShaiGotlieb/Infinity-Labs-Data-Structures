#ifndef __H_LSORT__
#define __H_LSORT__


int CountingSort(int *base, size_t num_elements,
						int from, int to);
/********************************************************************
 * The CountSort function implements CountingSort using the linear sort 
 * algorithm.
 * To sort an array of positive ints with 'num_elements' size.
 * The contents of the array are sorted in ascending order.
 *
 * base - a pointer to the base of the array to be sorted. NOT NULL.
 *  
 * num_elements - the number of elements in the array.
 *
 * from - minimum value in the keys value range (inclusive)
 *
 * to - maximum value in the keys value range (exclusive)
 * 
 * Return - 0 on success, 1 if failed due to memory problems.
 *
 * Time complexity of this function is O(n+k)
  *******************************************************************/

int RadixSort(unsigned int *base, size_t num_elements);
/********************************************************************
 * The RadixSort function implements RadixSort algorithm using 
 * the linear sort algorithm. 
 * To sort an array of ints of num_elements number of elements.
 * The contents of the array are sorted in ascending order.
 *
 * base - a pointer to the base of the array to be sorted. NOT NULL.
 *
 * num_elements - the number of elements in the array.
 *
 * Return - 0 on success, 1 if failed due to memory problems.
 * 
 * Time complexity of this function is O(d*(n+k))  
 *******************************************************************/

#endif