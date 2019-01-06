#ifndef __H_QUEUE_
#define __H_QUEUE_

/**************************************************************** 
 * This file handles a Queue using FIFO memroy managment.
 *
 * The Queue enable the user to add elment to the end of the queue 
 *	and removes an elment from the beginning.
 * 
 *                                                				
 * Written by: 		Shai Gotlieb    								
 * Last updated : 	3.1.2019 
 ***************************************************************/
typedef struct queue_s queue_t;

enum q_status {Q_SUCCESS, Q_MEMORY_ALLOCATION_ERROR};

queue_t *QueCreate();
/**************************************************************** 
 * QueCreat - Creats a Queue data structure.
 *
 * Return - returns a pointer to the queue.
 ***************************************************************/

void QueDestroy(queue_t *queue);
/**************************************************************** 
 * QueDestroy - frees memory of the allocated for the queue
 *
 * queue - a pointer to the queue . 
 * Return - returns a pointer to the queue.
 ***************************************************************/

enum q_status Enqueue(queue_t *queue, void *data);
/**************************************************************** 
 * Enqueue - adds an elment to the end of the queue. 
 *
 * queue - a pointer to the queue. not NULL.
 * data - data to be added to the queue.
 * Return - Q_SUCCESS for succses or Q_MEMORY_ALLOCATION_ERROR 
 * for memory related failure, according to the q_status enum.
 ***************************************************************/

void *Dequeue(queue_t *queue);
/**************************************************************** 
 * Dequeue - removes an element from the beginning of the queue. 
 *
 * queue - a pointer to the queue. not NULL.
 * Return - pointer to the data removed
 ***************************************************************/

void *QuePeek(const queue_t *queue);
/**************************************************************** 
 * Dequeue - returns the data of the element at the beginning of the queue. 
 *
 * queue - a pointer to the queue. not NULL.
 * Return - pointer to the element's data
 ***************************************************************/

int QueIsEmpty(const queue_t *queue);
/**************************************************************** 
 * QueIsEmpty - checks if the queue is empty. 
 *
 * queue - a pointer to the queue. not NULL.
 * Return - True if the queue is empty and faule if not. 
 ***************************************************************/

size_t QueGetSize(const queue_t *queue);
/**************************************************************** 
 * QueGetSize - calculates the number of elments in the queue
 *
 * queue - a pointer to the queue. not NULL.
 * Return - number of elments in the queue
 ***************************************************************/

void QueAppend(queue_t *first_queue, queue_t *last_queue);
/**************************************************************** 
 * QueAppend - recives two queues and adds the "last_queue" to the 
 * end of the "first_queue" 
 *
 * first_queue - a pointer to the queue. Not NULL.
 * last_queue - a pointer to the queue. Not NULL.
 ***************************************************************/
#endif