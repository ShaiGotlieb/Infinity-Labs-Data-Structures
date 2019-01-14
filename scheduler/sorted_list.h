#ifndef __H_SORTED_LIST__
#define __H_SORTED_LIST__
#include <stdlib.h>
#include "dll.h"

/***********************************************************************
* This file contains the API of a sorted list.
* 
* The sorted list enables the user to create and manage
* a sorted list.
*
* Written by: Shai Gotlieb
* Last updated : 9.1.2019
***********************************************************************/

typedef struct sorted_list_s sorted_list_t;

typedef struct sorted_list_iterator_s
{
	void *info;
} sorted_list_iterator_t;

typedef boolean_t(*is_new_before_exist_t)(const void *exist_data, const void *new_data);


sorted_list_t *SLCreate(is_new_before_exist_t is_before);
/***********************************************************************
* DLLCreate - Creates a sorted list data stracture.
*
* Returns - a pointer to the sorted list. 
* if memory allocation failed, NULL is returned.
*
***********************************************************************/

void SLDestroy(sorted_list_t *list);
/***********************************************************************
* SLDestroy - Frees the memory allocated for the sorted list.
*
* list - pointer to the sorted list. not NULL.
*
***********************************************************************/

size_t SLGetSize(const sorted_list_t *list);
/***********************************************************************
* SLGetSize - calculates the number of list members.
*
* list - pointer to the sorted list. not NULL.
*
* Returns - the number of list members.
*
***********************************************************************/

boolean_t SLIsEmpty(const sorted_list_t *list);
/**************************************************************** 
 * SLIsEmpty - checks if the list is empty.  O(1)
 *
 * list - a pointer to the list. not NULL.
 * Return - TRUE if the queue is empty and FALSE if not. 
 ***************************************************************/

sorted_list_iterator_t SLBegin(const sorted_list_t *list);
/***********************************************************************
* SLBegin - returns iterator to the first user data in the sorted list.
*
* list - a pointer to the sorted list. not NULL.
*
* Returns - iterator to the first user data in the list.
***********************************************************************/

sorted_list_iterator_t SLEnd(const sorted_list_t *list);
/***********************************************************************
* SLEnd - returns iterator to beyond the last user data.
*
* list - a pointer to the sorted list. not NULL.
*
* Returns -iterator to beyond the last user data.
***********************************************************************/

void *SLGetData(sorted_list_iterator_t iterator);
/***********************************************************************
* SLGetData - returns the data stored in the position provided by
* iterator
*
* iterator - a position in a sorted list. If iterator is
* not found in the list, the function behaviour is undefined. 
*
* Returns - data in the position specified by iterator.
***********************************************************************/

sorted_list_iterator_t SLGetNext(sorted_list_iterator_t iterator);
/***********************************************************************
* SLGetNext - returns the iterator position to the next member
* in the list.
*
* iterator - a position in a sorted list. If iterator is
* not found in the list, the function behaviour is undefined. 
* iterator - should not be the iterator pointing to the end of the list.
*
* Returns - an iterator to the next position.
***********************************************************************/

sorted_list_iterator_t SLGetPrevious(sorted_list_iterator_t iterator);

/***********************************************************************
* SLGetPrevious - returns the iterator position to the previous member
* in the list.
*
* iterator - a position in a sorted list. If iterator is
* not found in the list, the function behaviour is undefined. 
* iterator - should not be the first member of the list.
*
* Returns - an iterator to the previous position.
***********************************************************************/

boolean_t SLIsSameIterator(sorted_list_iterator_t iterator1,
							sorted_list_iterator_t iterator2);

/***********************************************************************
* SLIsSameIterator - compares between two iterators, determines
* if they point to the same position.
*
* iterator1 - a position in a sorted list.
* iterator2 - a position in a sorted list
*
* Returns - boolean_t: TRUE - if iterators point to same position.
* FALSE - if otherwise.
***********************************************************************/

sorted_list_iterator_t SLInsert(sorted_list_t *list, void *data);
/***********************************************************************
* SLInsert - function receives a list and user data.
* inserts data to the list, in a position according
* to the function 'is_before'.
*
* list - a sorted list.
*
* data - the data to be inserted.
*
* Returns - iterator - pointing to the position of the inserted data
* If failed, an iterator pointing to END will be returned.
***********************************************************************/

sorted_list_iterator_t SLErase(sorted_list_iterator_t iterator);
/***********************************************************************
* SLErase - function receives iterator in a list, and removes
* the data in that position in that list.
*
* iterator - a position to a data in the list. If iterator is
* not found in the list, the function behaviour is undefined.
*
* Returns - iterator - pointing to the position of the next data.
* if the last data of a list is removed, the function will return
* an iterator of DLLEnd.
***********************************************************************/

void SLPopFront(sorted_list_t *list);
/***********************************************************************
* SLPopFront - function receives a list, and removes
* the data in the front position in that list.
*
* list - a pointer to a list. Cannot be NULL. Cannot be empty list.
*
***********************************************************************/

void SLPopBack(sorted_list_t *list);
/***********************************************************************
* SLPopBack - function receives a list, and removes
* the data in the last position in that list.
*
* list - a pointer to a list. Cannot be NULL. Cannot be empty list.
*
***********************************************************************/

sorted_list_iterator_t SLFind(sorted_list_t *list,const sorted_list_iterator_t from,
const sorted_list_iterator_t to, is_match_t ismatch, void *data_for_cmp, void *param);

/***********************************************************************
* SLFind - function receives a pointer list and a range in the list,
* data for comparison and a function for comparison.
* The function will look for the data in the range specified.
*
* list - a pointer to a list. Cannot be NULL. Cannot be empty list.
*
* from - an iterator to the data from which the search will be
* started (inclusive). Must be before to in the list order.
*
* to - an interator to the data until which the search will be
* conducted (exclusive). Must be after from in the list order.
*
* ismatch - a function of type is_match_t provided by the user.
*
* data_for_cmp - the data which will be compared to the data in the
* range.
*
* param - an additional parameter that can be utilized by the search
* function.
*
* Returns - iterator. If ismatch function returns true, iterator
* will point to the first data matching the parameters for comparison.
* Otherwise, the function will return an iterator of SLEnd.
*
***********************************************************************/

status_t SLForEach(sorted_list_iterator_t from, sorted_list_iterator_t to,
										action_t action, void *param);
/***********************************************************************
* SLForEach - function receives a range in a sorted list.
* The function will perform an action for each data in the range.
*
* from - an iterator to the data from which the action will be
* started (inclusive). Must be before to in the list order.
*
* to - an interator to the data until which the action will be
* conducted (exclusive). Must be after from in the list order.
*
* action - a function of type action_t provided by the user.
*
* param - an additional parameter that can be utilized by the action
* function.
*
* Returns - type status_t : SUCCESS if action function returned success
* for all members in the range. FAIL if otherwise. 
***********************************************************************/

void SLMerge(sorted_list_t *list_dest, sorted_list_t *list_src);
/***********************************************************************
* SLMerge - the function receives a member position in a sorted
* list and inserts a range of members from another sorted list.
*
* src - an iterator to the position of the member in the list
* from which and to the end of the list, the members will be merged
* with the members in dest. The members from position src in 
* the source list to the end will be removed from source list.
*
* dest - a member location in the destination list.
* the members copied from the source list in location src to the end
* will be merged into the destination list (which contains
* iterator dest).
*
* the data pointed to by the void *data in each node of each list
* should be of valid input to the is_before function, provided
* by the user.
***********************************************************************/

#endif