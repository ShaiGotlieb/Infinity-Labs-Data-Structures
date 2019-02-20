#ifndef __H__HASH__
#define __H__HASH__


typedef struct hash_s hash_t;
typedef size_t (*hash_func_t)(const void *key);
typedef int (*hash_action_func_t)(void *value, const void *param);
typedef int (*hash_is_match_func_t)(const void *data1, const void *data2, void *param);


hash_t *HashCreate(size_t capacity, hash_func_t hash_func, 
				   hash_is_match_func_t is_match, void *param);
/********************************************************************
 *
 *
 *
 *
 * capacity = 0 ->undefined.
 *******************************************************************/

void HashDestroy(hash_t *hash);

int HashInsert(hash_t *hash, void const *key, void const *value);
/********************************************************************
 *
 *
 *
 *
 * key not NULL. hash not NULL.
 *
 * returns - 0 if successful - 1 if failed
 *******************************************************************/

void *HashRemove(hash_t *hash, void const *key, void const *param);
/********************************************************************
 *
 *
 *
 *
 * key not NULL. hash not NULL.
 * returns - pointer to value.
 *******************************************************************/

void *HashFind(hash_t *hash, void const *key, void const *param);
/********************************************************************
 *
 *
 *
 *
 * key not NULL. hash not NULL.
 * returns - pointer to value.
 *******************************************************************/

size_t HashSize(hash_t const *hash);
/********************************************************************
 *
 *
 *
 *
 * 
 * hash not NULL. O(N).
 *******************************************************************/

int HashIsEmpty(hash_t const *hash);
/********************************************************************
 *
 *
 *
 *
 * 
 * hash not NULL. O(K)
 *******************************************************************/

int HashForEach(hash_t *hash, hash_action_func_t action_func, void *param);
/********************************************************************
 *
 *
 *
 *
 * 
 * returns - 0 if successful - 1 if failed.
 *******************************************************************/

double HashLoadFactor(hash_t const *hash);
/********************************************************************
 *
 *
 *
 *
 * hash not NULL. 
 * 
 *******************************************************************/

double HashStandardDeviation(hash_t const *hash);
/********************************************************************
 *
 *
 *
 *
 * hash not NULL. 
 *
 *******************************************************************/

#endif