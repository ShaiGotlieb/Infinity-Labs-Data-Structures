#ifndef __H_PQUEUE_
#define __H_PQUEUE_
#include "dll.h"
/**************************************************************** 
 * This file contains the API of Priority Queue.
 *
 * The Priority Queue enables the user to add data to the queue
 * and removes an data according to its priority
 * as defined by the user.
 *                                                				
 * Written by: 		Shai Gotlieb    								
 * Last updated : 	9.1.2019 
 ***************************************************************/
typedef struct pqueue_s pqueue_t;

enum q_status {Q_SUCCESS, Q_MEMORY_ALLOCATION_ERROR};

typedef boolean_t (*has_higher_priority_t)(const void *data1, const void *data2);
typedef boolean_t (*is_match_q_t)(const void *data1, void *param);

pqueue_t *PQCreate(has_higher_priority_t has_higher_priority);
/**************************************************************** 
 * QueCreate - Creates a PQueue data structure.
 * 
 * has_higher_priority - a function that determines the priority of the 
 * queue.
 *
 * Return - returns a pointer to the queue.
 ***************************************************************/

void PQDestroy(pqueue_t *queue);
/**************************************************************** 
 * QueDestroy - frees memory of the allocated for the queue
 *
 * queue - a pointer to the queue . 
 * Return - returns a pointer to the queue.
 ***************************************************************/

enum q_status PQEnqueue(pqueue_t *queue, void *data);
/**************************************************************** 
 * Enqueue - adds an element to the queue.
 *
 * queue - a pointer to the queue. not NULL.
 * data - data to be added to the queue.
 * Return - Q_SUCCESS for succses or Q_MEMORY_ALLOCATION_ERROR 
 * for memory related failure, according to the q_status enum.
 ***************************************************************/

void *PQDequeue(pqueue_t *queue);
/**************************************************************** 
 * Dequeue - removes the highest priority data from the queue
 *
 *
 * queue - a pointer to the queue. not NULL.
 * Return - pointer to the data removed.
 ***************************************************************/

void *PQPeek(const pqueue_t *queue);
/**************************************************************** 
 * QuePeek - shows the next element to be Dequeue'd.
 *
 * queue - a pointer to the queue. not NULL. not empty.
 * Return - pointer to the element's data
 ***************************************************************/

boolean_t PQIsEmpty(const pqueue_t *queue);
/**************************************************************** 
 * QueIsEmpty - checks if the queue is empty. 
 *
 * queue - a pointer to the queue. not NULL.
 * Return - True if the queue is empty and false if not. 
 ***************************************************************/

size_t PQGetSize(const pqueue_t *queue);
/**************************************************************** 
 * QueGetSize - calculates the number of elments in the queue
 *
 * queue - a pointer to the queue. not NULL.
 * Return - number of elments in the queue
 ***************************************************************/

void *PQErase(pqueue_t *queue, is_match_q_t is_match, void *param);
/**************************************************************** 
 * QueErase - function receives a queue and erases the data
 * matching to is_match function.
 *
 * queue - a pointer to the queue.
 * 
 * param - an additional parameter for the use of is_match
 * function.
 ***************************************************************/
void PQClear(pqueue_t *queue);
/**************************************************************** 
 * PQClear - function receives a queue..... 
 * 
 *
 * queue - a pointer to the queue.
 * 
 * 
 * 
 ***************************************************************/



#endif