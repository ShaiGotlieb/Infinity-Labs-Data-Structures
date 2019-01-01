#ifndef __H_CBUFFER_
#define __H_CBUFFER_

#include <stdio.h> /**/

/**************************************************************** 
 * This file handles a Circular Buffer.
 *
 * the Circular Buffer enables the reader to read from the buffer, 
 * and the writer to write to the buffer in a way that the writer 
 * never overwrites data that the reader hasn't already read,  
 * and the reader can only read data that has been written by 
 * the writer. The Circular Buffer recycles the memory that was 
 * already read by the reader, and can re-use it for future writes.
 * 
 *                                                				
 * Written by: 		Shai Gotlieb         								
 * Last updated : 	30.12.2018									 	                                                            *
 ***************************************************************/
typedef struct cbuffer_s cbuffer_t;

           
cbuffer_t *CBufferCreate(size_t capacity);
/***************************************************************** 
 * CBufferCreate - creates a circular buffer data structure 
 * with a size of 'capacity' bytes. 
 *                                                              
 * capacity - cbuffer size in bytes. 
 *                                                              
 *	Return - a pointer to the cbuffer. NULL if the function was 
 *  unable to create the cbuffer 
 *****************************************************************/

void CBufferDestroy(cbuffer_t *cbuffer);
/****************************************************************
 * CBufferDestroy - Removes the circular buffer from memory            
 *                               
 *                                                              
 * cbuffer - a pointer to the cbuffer with type cbuffer_t. Not NULL.
 ****************************************************************/

size_t CBufferWrite(cbuffer_t *cbuffer, const void *src, size_t num_bytes_to_write); 
/****************************************************************
 * CBufferWrite - Writes num_bytes_to_write from src to buffer. 
 *
 * cbuffer - a pointer to the buffer. Not NULL
 * src - a pointer to the source to be read. Should be at least num_bytes_to_write
 * size. Otherwise, behaviour is undefined.
 * num_bytes_to_write- number of bytes requested to be written.
 * Return - number of bytes succesfully written. 
 ****************************************************************/

size_t CBufferRead(cbuffer_t *cbuffer, void *dest, size_t num_bytes_to_read);
/************************************************************************
 * CBufferRead - Reads num_bytes_to_read from buffer to dest. 
 *
 * cbuffer - a pointer to the buffer. Not NULL.
 * dest - destination pointer to be written. Should be at least bytes_to_read
 * size. Otherwise, behaviour is undefined.  
 * num_bytes_to_read - number of bytes requested to be read.
 * Return - number of bytes succesfully read.
 *************************************************************************/

int CBufferIsEmpty(const cbuffer_t *cbuffer);
/****************************************************************
 * CBufferIsEmpty - checks if the buffer is empty
 *
 * cbuffer - a pointer to the buffer. Not NULL
 * Return - 1 if the buffer is empty, 0 otherwise
 ****************************************************************/

size_t CBufferGetCapacity(const cbuffer_t *cbuffer);
/****************************************************************
 * CBufferGetCapacity - Returns the capacity
 *
 * cbuffer - a pointer to the buffer. Not NULL
 * Return- the capacity                        
 ****************************************************************/

size_t CBufferGetSize(const cbuffer_t *cbuffer);
/****************************************************************
 * CBufferGetSize - calculate the current buffer non-read data size 
 *
 * cbuffer - a pointer to the buffer. Not NULL
 * Return- the current buffer non-read data size 
 ****************************************************************/


void CBufferClear(cbuffer_t *cbuffer);
/****************************************************************
 * CBufferClear - clears the buffer.
 *
 * cbuffer - a pointer to the buffer. Not NULL
 *                              
 * Return- void.
 *******************************************************************/
#endif