#ifndef __H_STACK__
#define __H_STACK__

#include <stdio.h>

/**************************************************************** 
 * This file handles a STACK data structure 				    *
 * This data structure usses LIFO.                              *
 * the dta supporets any type of elment                         *
 *						                                        *
 *                                                				*
 * Written by: 	 Shai Gotlieb   								*
 * Last updated: 25.12.2018				    					* 	                                                            *
 ***************************************************************/
typedef struct stack_s stack_t;

stack_t *StackCreate(size_t element_size, size_t capacity);
/***************************************************************** 
 * StackCreate - creates a stack data structure whith a maximum  *
 * size of capacity. each element is of maximun size of size_t   *
 *	in bytes                                                     *                                             
 * elment size - determines the size of each element in the stack*
 * capacity - max number of elments in the stack                 *
 *                                                               *
 *	Return - a pointer to the stack. if capacity is 0 or         *
 *  it fails to create a stack will, return a NULL pointer       *
 *****************************************************************/

void StackDestroy(stack_t *stack);
/****************************************************************
 * removes stack from memory                                    *
 * stack - a pointer to the stack                               *
 *                                                              *
 * DestroyStack - removes stack from memory                     *                     
 *                                                              *
 * stack - a pointer to the stack stack_t                       *
 ****************************************************************/

void StackPush(stack_t *stack, void *element);
/****************************************************************
 * adds an elment to the top of the struct                      *
 * stack - a pointer to the stack                               *
 * elemant - a ponter to the elmant to be added to the stack    * 
 ****************************************************************/

void *StackPop(stack_t *stack); 
/****************************************************************
 * removes the last elment added to the stack                   *
 * stack - a pointer to the stack                               *
 * returns a pointer to the ement last added with removing      * 
 ****************************************************************/

void *StackPeek(stack_t *stack);
/****************************************************************
 * show element last added to the stack                         *
 * stack - a pointer to the stack                               *
 * returns a pointer to the element last added without removing * 
 ****************************************************************/

size_t StackSize(stack_t *stack);
/****************************************************************
 * calculates the current size of the stack                     *
 * stack - a pointer to the stack                               *
 * Return- number of elments in the stack                       * 
 ****************************************************************/

#endif