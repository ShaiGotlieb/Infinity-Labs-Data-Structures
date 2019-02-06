#ifndef __H_STACK__
#define __H_STACK__

#include <stdio.h>

/**************************************************************** 
 * This file handles a STACK data structure 				*
 * This data structure usses LIFO.
 * the dta supporets any type of elment 
 *                                                				*
 * Written by: 		OL62										*
 * Last updated : 	25.12.2018									* 	                                                            *
 ***************************************************************/
typedef struct stack_s stack_t;

stack_t *StackCreate(size_t element_size, size_t capacity);
/*************************************************************** 
 * StackCreate - creates a stack data structure with a maximum
 * size of capacity. each element is of maximun size of size_t.
 * capacity should greater than 0. element_size should be greater 
 * than 0.
 *                                                             
 * elment size - determines the size of each element in the stack
 * capacity - max number of elments in the stack 
 *                                                             
 * Return - a pointer to the stack. if it fails to create a stack, 
 * it will return a NULL pointer    
 ***************************************************************/

void StackDestroy(stack_t *stack);
/* removes stack from memory */
/* stack - a pointer to the stack*/
/*************************************************************** 
 * DestroyStack - removes stack from memory                                           
 *                                                             
 * stack - a pointer to the stack stack_t
  *	Return - void
  ***************************************************************/

void StackPush(stack_t *stack, void *element);
/*adds an elment to the top of the struct*/
/* stack - a pointer to the stack*/
/* elmant - a ponter to the elmant to be added to the stack */
/*return zero if seccess and non zero value if fails */

void *StackPop(stack_t *stack); 
/*removes the last elment added to the stack*/
/*stack - a pointer to the stack*/
/* returns a pointer to the ement last added with removing*/


void *StackPeek(stack_t *stack);
/* show elment last added to the stack
stack - a pointer to the stack*/
/* returns a pointer to the ement last added without removing*/


size_t StackSize(stack_t *stack);
/*calculates the current size of the stack*/
/*stack - a pointer to the stack*/
/*Return- number of elments in the stack*/

#endif