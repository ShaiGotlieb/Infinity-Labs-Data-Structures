#ifndef __H_DVECTOR_
#define __H_DVECTOR_

#include <stdio.h>

/**************************************************************** 
 * This file handles a Dynamic Vector
 * 
 * The data structure supports any type of element. 
 * The dynamic vector can increase it's size according to the
 * user's requirements (by explicitly setting the capacity 
 * to a new size or by imlicitely adding elements beyond 
 * the dvector's current capacity).
 * 
 * Dynamic dvector growth policy - 
 * 	when the capcacity is reached - the capacity is doubled. 
 * (checked when dvectorPushEnd() is used.)  
 * 	when 75% of the capcacity is empty - the new capacity is 
 * 	set to 50% (checked only when dvectorPopEnd() is used), 
 * 
 *						                                        
 *                                                				
 * Written by: 		OL62         								
 * Last updated : 	26.12.2018									* 	                                                            *
 ***************************************************************/
typedef struct dvector_s dvector_t;

dvector_t *DVectorCreate(size_t element_size, size_t capacity);
/****************************************************************** 
 * DVectorCreate - creates a dynamic dvector data structure       *
 * whith a maximum size of capacity.                              *
 * each element is of maximun size of  size_t.                    *                           
 *                                                                *
 * elment size - determines the size of each element in the       * 
 * dvector in bytes - must be non-negative.                       * 
 * capacity - non-negative max number of elements in the dvector  *               
 *                                                                *
 *	Return - a pointer to the dvector. if capacity is 0 or        * 
 *  it fails to create a dvector, a NULL pointer will be returned *
 *****************************************************************/

void DVectorDestroy(dvector_t *dvector);
/******************************************************************
 * DVectorDestroy - Removes the dynamic vector from memory        *    
 *                                                                *
 *                                                                *
 * dvector - a pointer to the dvector with type dvector_t not NULL*
 ******************************************************************/

int DVectorPushEnd(dvector_t *dvector,const void *element);
/****************************************************************
 * DVectorPushEnd - Adds an element to the end of the vector    *
 * if the number of elements now exceeds the dvector's capacity,* 
 * the vector's size will be doubled automatically.             *
 *																*
 * dvector - a pointer to the vector - not NULL                 *
 * element - a pointer to the element to be added to the        *
 * stack - not NULL                                             * 
 * Return- an integer that describes the success of operation.  *
 *  0 will be return if the new capcacity was set successully,  *
 * and any other value if otherwise.                            *
****************************************************************/

void *DVectorPopEnd(dvector_t *dvector); 
/****************************************************************
 * DVectorPopEnd - Removes the last element from the vector     *         
 * dvector - a pointer to the vector not NULL and not empty     *
 * Return - a pointer to the element is returned                *
 ****************************************************************/

size_t DVectorFindItemIndex(const dvector_t *dvector,const void *element);
/****************************************************************
 * DVectorFindItemIndex - Find the index of the element         *
 * in the vector - not NULL                                     *
 * dvector - a pointer to the vector - not NULL                 *
 * Return - the index of the element. ULONG_MAX if not found.   *
 ****************************************************************/

size_t DVectorGetSize(const dvector_t *dvector);
/*****************************************************************
 * DVectorGetSize - Calculates the current size of the vector    *
 * (number of elements)                                          *
 *                                                               *
 * dvector - a pointer to the vector - not NULL                  *
 * Return- number of elments in the vector                       * 
 ****************************************************************/

size_t DVectorGetCapacity(const dvector_t *dvector);
/****************************************************************
 * DVectorGetCapacity - Return the current value of the vector's*
 * capacity (max. number of elements)                           *
 *                                                              *
 * dvector - a pointer to the vector - not NULL                 * 
 * Return- the current value of the vector's capacity           *
 ****************************************************************/


 int DVectorSetCapacity(dvector_t *dvector, size_t new_capacity);
/********************************************************************
 * DVectorSetCapacity - Sets the vector's capacity to the new value.* 
 * new_capacity can be more or less than the previous capacity.     *
 *                                                                  *
 * dvector - a pointer to the vector - not NULL                     *
 * new_capacity - a new value for the vector's capacity.            *
 *                                                                  *
 * Return- an integer that describes the success of operation.      *
 *  0 will be return if the new capcacity was set successully,      *
 * and any other value if otherwise.                                *
 *******************************************************************/
#endif