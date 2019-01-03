#ifndef __H_SLLIST_
#define __H_SLLIST_

#include <stdlib.h> /* size_t */

/**************************************************************** 
 * This file handles a Singly Linked List
 *
 * the Singly Linked List enables the user to create data nodes, 
 * and link them to the next node.
 * 
 *                                                				
 * Written by: 		Shai Gotlieb   								
 * Last updated : 	3.1.2019 								 	                                                            *
 ***************************************************************/
enum return_value{SUCCESS, FAILED};

typedef struct sllist_node
{
	void *data;
	struct sllist_node *next;
} sllist_node_t;

typedef int (*is_match_t)(const void *data1, const void *data2, void *param);
typedef int (*action_t)(void *data, void *param);

sllist_node_t *SLLCreateNode(sllist_node_t *next, void *data);
/***************************************************************** 
 * SLLCreateNode - creates a single node
 * with data. It is possible to create & insert the node.
 *	
 * *next - a pointer to the next node in the list. 
 * if next == NULL, the function will only create a node,
 * without linking to the next node.
 *
 * *data - a pointer to the node's data.
 *
 * Return - a pointer to the current node.
 *****************************************************************/

void SLLDestroyNodes(sllist_node_t *list);
/****************************************************************
 * SLLDestroyNodes- frees memory from current node until end 
 * of list.                                                              
 ****************************************************************/

sllist_node_t *SLLInsert(sllist_node_t *where, sllist_node_t *node_to_insert);
/****************************************************************
 * SLLInsert - inserts a node pointing to the "where" node 
 *
 * where - a pointer to the node which will be pointed 
 * to by *node_to_insert.  Not NULL.
 *
 * node_to_insert - a pointer to the node to be inserted. Not NULL.
 *
 * Return - a pointer to the inserted node
 ****************************************************************/

sllist_node_t *SLLInsertAfter(sllist_node_t *where, sllist_node_t *node_to_insert);
/****************************************************************
 * SLLInsertAfter - inserts a node following the node "where".
 *
 * where - a pointer to the node after which node_to_insert will be inserted. Not NULL.
 * 
 * *node_to_insert - a pointer to the node to be inserted. Not NULL.
 *
 * Return - a pointer to node_to_insert. 
 ****************************************************************/

sllist_node_t *SLLRemove(sllist_node_t *node_to_remove);
/****************************************************************
 * SLLRemoveBeforeNode - unlinks node_to_remove from the list, and re-connects the list,
 * may affect the position of the following node.
 *
 * *node_to_remove - a pointer to the node to be unlinked. Not NULL. 
 * can't remove last node.
 *
 * Return - a pointer to node_to_remove.  
 ****************************************************************/

sllist_node_t *SLLRemoveAfter(sllist_node_t *parent_node);
/****************************************************************
 * SLLRemoveAfter - removes node linked by parent_node
 *
 * parent_node - a pointer to the node which points to node
 * to be removed. Not NULL. can't remove last node.
 *
 * Return - the node removed.
 ****************************************************************/

size_t SLLCount(const sllist_node_t *list);

/****************************************************************
 * SLLCount - counts number of linked nodes.
 * 
 * list - a pointer to the node from which the counting starts 
 *
 * Return - number of nodes in the list.
 ****************************************************************/

sllist_node_t *SLLFind(sllist_node_t *list, is_match_t is_match,
									void *data_for_cmp, void *param);
/****************************************************************
 * SLLFind - find a node for which the is_match(data_for_cmp) returns true. 
 *
 * list - a pointer to a node in the list, the find will search all 
 * nodes untill it reaches last node. Not NULL.
 * 
 * is_match -  an is_match_t function, should be supplied by the user, 
 * for each data type used in the list. 
 * 
 * data_for_cmp - the data value that is searched.
 * 
 * param - an additional parameter, could be used by the is_match() function.
 *
 * Return - a pointer to the found node, or NULL if a node wasn't found.
 ****************************************************************/

int SLLForEach(sllist_node_t *list, action_t action, void *param);
/****************************************************************
 * SLLForEach - execute an action for each of the elements in the list. 
 * if an action fails for one of the nodes, the function will stop, 
 * and the return status received for this node.
 *
 * list - a pointer to a node in the list, the SLLForEach will search all 
 * nodes untill it reaches last node. Not NULL.
 * 
 * action -  an action_t function, should be supplied by the user, 
 * for each data type used in the list. 
 * 
 * param - an additional parameter, could be used by the action() function.
 *
 * Return - an enum return_value. The status returned by the action() function 
 * must be also enum return_value. This value will be returned "as is" from  SLLForEach().
 ****************************************************************/

sllist_node_t *SLLFindIntersection(sllist_node_t *list1, sllist_node_t *list2);
/****************************************************************
 * SLLFindIntersection - finds if there's intersection
 * between the 2 nodes: list1 and list2, or their child nodes.
 * 
 * Return - a pointer to the node which was found as an intersection, 
 * or NULL if such a node does not exist.
 ****************************************************************/

int SLLHasLoop(const sllist_node_t *list);
/****************************************************************
 * SLLHasLoop - checks if there is a loop in the list. Not NULL.
 *
 * list - a pointer to a node  
 *
 * Returns - 1 if true. 0 if false.
 ****************************************************************/

sllist_node_t *SLLFlip(sllist_node_t *list);
/****************************************************************
 * SLLFlip - Reverses the order of the list.
 *
 * list - a pointer to a node 
 * 
 * Return - a pointer to the node which was last and now is first.
 ****************************************************************/

#endif