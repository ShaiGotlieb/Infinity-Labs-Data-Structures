#ifndef __H_AVLT__
#define __H_AVLT__

typedef struct avlt_s avlt_t;

typedef int (*is_before_avlt_t)(const void *data1, const void *data2); 
typedef int (*cmp_func_avlt_t)(const void *data1, const void *data2, void *param);
typedef int (*action_func_avlt_t)(void *data, void *param);

avlt_t *AVLTCreate(is_before_avlt_t is_before, void *param);
/********************************************************************
 * AVLTCreate - Creates a self-balancing binary search tree.
 *
 * is_before - a comparison function to sort the data.
 * 
 * param - an additional parameter for the use of is_before function.
 *
 * Return - a pointer to avlt_t data type. NULL if failed to create.
 *******************************************************************/

void AVLTDestroy(avlt_t *tree);
/********************************************************************
 * AVLTDestroy - Destroys a binary search tree. order of O(nlog n)
 * 
 * tree - a pointer to avlt_t data type to be destroyed.
 *******************************************************************/

size_t AVLTGetSize(const avlt_t *tree);
/********************************************************************
 * AVLTGetSize - Calculates the size of the tree (number of nodes). O(nlog n)
 * 
 * tree - a pointer to avlt_t data type. NOT NULL.
 *
 * Return - the number of data values in the tree.
 *******************************************************************/

int AVLTIsEmpty(const avlt_t *tree);
/********************************************************************
 * AVLTIsEmpty - calculates whether the tree is empty. O(1)
 * 
 * tree - a pointer to avlt_t data type. NOT NULL.
 *
 * Return - 1 if tree is empty. 0 otherwise.
 *******************************************************************/

int AVLTInsert(avlt_t *tree, const void *data);
/********************************************************************
 * AVLTInsert - inserts a new datum to the tree. O(log n)
 * 
 * tree - a pointer to avlt_t data type. NOT NULL.
 *
 * data - a pointer to the data to be inserted to the tree.
 * the data inserted must be unique (not formerly found in the tree).
 * The data needs to have unique value.
 *
 *  Return - 0 for success, 1 for failure.
 *******************************************************************/

void AVLTRemove(avlt_t *tree, const void *data);
/********************************************************************
 * AVLTRemove - removes a datum from the tree. O(log n)
 * 
 * tree - a pointer to avlt_t data type. NOT NULL.
 *
 * data - a pointer to the data to be removed from the tree.
 *******************************************************************/

void *AVLTFind(const avlt_t *tree, const void *data, cmp_func_avlt_t cmp_func, void *param);
/********************************************************************
 * AVLTFind - searches datum in the tree. O(log n)
 * 
 * tree - a pointer to a avlt_t type. NOT NULL.
 *
 * data - the data to be found in the tree.
 *
 * Return - pointer to data and NULL if not found.
 *******************************************************************/

int AVLTForEach(avlt_t *tree, action_func_avlt_t action_func, void *param);
/********************************************************************
 * AVLTForEach - performs an action on every datum in the tree.
 * The function will be performed via action_func.
 *	The action is prformed "in-order" and can be used to retrieve insreted 
 *	data sorted. O(nlog n).
 * 
 * tree - a pointer to a avlt_t type. NOT NULL.
 *
 * action_func - action_func_t type, that will perform
 * the action on each datum.
 *
 * param - an additional parameter for the use of action_func.
 *
 * Return - 0 for success, 1 for failure.
 *******************************************************************/

long AVLTHeight(const avlt_t *tree);
/********************************************************************
 * AVLTHeight - returns the height of the tree. O(1)
 * (the height a leaf is 0)
 * 
 * tree - a pointer to a avlt_t type. NOT NULL.
 *
 * Return - height of the tree (or sub-tree). 
 *			For an empty tree, -1 will be returned.
 *******************************************************************/
#endif