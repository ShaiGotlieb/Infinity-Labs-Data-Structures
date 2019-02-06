#ifndef __H_BST__
#define __H_BST__

typedef struct bst_iterator_s
{
	void *info;
} bst_iterator_t;

typedef struct bst_s bst_t;

typedef int (* cmp_func_t)(void *data1, void *data2, void *param);
typedef int (* action_func_t)(void *data, void *param);

bst_t *BSTCreate(cmp_func_t cmp_func, void *param);
/********************************************************************
 * BSTCreate - Creates a binary search tree.
 * 
 * cmp_func - a comparison function to sort the data.
 * 
 * param - an additional parameter for the use of cmp_func.
 *
 * Return - a pointer to bst_t data type. NULL if failed to create.
 *******************************************************************/

void BSTDestroy(bst_t *tree);
/********************************************************************
 * BSTDestroy - Destroys a binary search tree.
 * 
 * tree - a pointer to bst_t data type to be destroyed.
 *******************************************************************/

size_t BSTGetSize(const bst_t *tree);
/********************************************************************
 * BSTGetSize - calculates the size of the tree.
 * 
 * tree - a pointer to bst_t data type to be destroyed. NOT NULL.
 *
 * Return - the number of data values in the tree.
 *******************************************************************/

int BSTIsEmpty(const bst_t *tree);
/********************************************************************
 * BSTIsEmpty - calculates whether the tree is empty.
 * 
 * tree - a pointer to bst_t data type to be destroyed. NOT NULL.
 *
 * Return - 1 if tree is empty. 0 otherwise.
 *******************************************************************/

bst_iterator_t BSTInsert(bst_t *tree, void *data);
/********************************************************************
 * BSTInsert - inserts a new datum to the tree.
 * 
 * tree - a pointer to bst_t data type to be destroyed. NOT NULL.
 *
 * data - a pointer to the data to be inserted to the tree.
 * the data inserted must be unique (not formerly found in the tree).
 * The data needs to have uniqe value.
 *
 * Return - an iterator to the new data.
 *******************************************************************/

void BSTRemove(bst_t *tree, void *data);
/********************************************************************
 * BSTRemove - removes a datum from the tree.
 * 
 * tree - a pointer to bst_t data type to be destroyed. NOT NULL.
 *
 * data - a pointer to the data to be removed from the tree.
 *******************************************************************/


bst_iterator_t BSTGetNext(bst_iterator_t iterator);
/********************************************************************
 * BSTGetNext - returns an iterator to the next datum.
 * When this function is performed on the last datum, the iterator
 * returned will be the same as BSTEnd().
 * 
 * When this function is performed on an iterator which equals
 * BSTEnd(), the function behaviour is undefined.
 *
 * iterator - an iterator to which the next datum will be returned.
 * NOT NULL. 
 *
 * Return - an iterator to the next datum.
 *******************************************************************/

bst_iterator_t BSTGetPrevious(bst_iterator_t iterator);
/********************************************************************
 * BSTGetPrevious - returns an iterator to the previous datum.
 * When this function is performed on the first iterator, the 
 * behaviour is undefined.
 *
 * iterator - an iterator to which the previous datum will be
 * returned NOT NULL.
 *
 * Return - an iterator to the previous datum.
 *******************************************************************/

void *BSTGetData(bst_iterator_t iterator);
/********************************************************************
 * BSTGetData - returns the datum of the iterator provided.
 * 
 * iterator - an iterator 
 *
 * Return - an iterator to the next datum.
 *******************************************************************/

bst_iterator_t BSTBegin(const bst_t *tree);
/********************************************************************
 * BSTBegin - returns iterator to the beginning of the tree.
 * (inclusive).
 *
 * tree - a pointer to a bst_t type. NOT NULL.
 *
 * Return - an iterator to the beginning of the tree.
 *******************************************************************/

bst_iterator_t BSTEnd(const bst_t *tree);
/********************************************************************
 * BSTEnd - returns iterator to the end of the tree.
 * (exclusive).
 * 
 * tree - a pointer to a bst_t type. NOT NULL.
 *
 * Return - an iterator to the end of the tree.
 *******************************************************************/

bst_iterator_t BSTFind(const bst_t *tree, void *data);
/********************************************************************
 * BSTFind - searches datum in the tree.
 * 
 * tree - a pointer to a bst_t type. NOT NULL.
 *
 * data - the data to be found in the tree.
 *
 * Return - an iterator to the data in the tree, if found.
 * Otherwise - returns BSTEnd().
 *******************************************************************/

int BSTForEach(bst_t *tree, action_func_t action_func, void *param);
/********************************************************************
 * BSTForEach - performs an action on every datum in the tree.
 * The function will be performed via action_func.
 * 
 * tree - a pointer to a bst_t type. NOT NULL.
 *
 * action_func - action_func_t type, that will perform
 * the action on each datum.
 *
 * param - an additional parameter for the use of action_func.
 *
 * Return - 0 for success, 1 for failure.
 *******************************************************************/

int BSTIsSameIterator(bst_iterator_t iterator1, bst_iterator_t iterator2);
/********************************************************************
 * BSTISSameIterator - compares between 2 iterators.
 * 
 * iterator1 - the first iterator to be compared..
 * iterator2 - the second iterator to be compared.
 *
 * Return - 1 if the iterators are equal. 0 otherwise.
 *******************************************************************/

#endif