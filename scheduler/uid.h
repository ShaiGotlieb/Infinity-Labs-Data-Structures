#ifndef __H_UID__
#define __H_UID__

#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include "ol62_general.h"
/***********************************************************************
 * This file contains the API of UID a.k.a. 'Unique ID'.
 *
 * The UID is a unique, injective ID created by the system. 
 *                                                				
 * Written by: 		OL62    								
 * Last updated : 	13.1.2019 
 ***********************************************************************/

typedef struct task_uid_s
{
	size_t counter;
	time_t time_stamp;
	pid_t pid;
} task_uid_t;


task_uid_t UIDCreate();
/***********************************************************************
* Creates a unique id type.
* 
* returns - a unique id type.
*
***********************************************************************/

int UIDIsSame(const task_uid_t uid1, const task_uid_t uid2);
/***********************************************************************
* Compares 2 uid's.
* 
* returns - 1 if they are equal. 0 otherwise.
*
***********************************************************************/

#endif