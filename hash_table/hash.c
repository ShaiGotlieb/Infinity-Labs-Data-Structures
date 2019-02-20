#include <assert.h>
#include <math.h> /* pow , sqrt */
#include <stdlib.h> /* malloc, free, size_t */

#include "hash.h"
#include "dll.h"

#define SUCCESS (0)
#define FAILURE (1)
#define TRUE (1)
#define FALSE (0)

struct hash_s{

	dll_t **lists;
	hash_func_t hash_func;
	hash_is_match_func_t is_match; 
	void *param;
	size_t capacity; 

};

hash_t *HashCreate(size_t capacity, hash_func_t hash_func, hash_is_match_func_t is_match, void *param)
{
	size_t i;
	hash_t *hash_table = (hash_t*)malloc(sizeof(hash_t));
	if (NULL == hash_table)
	{
		return (NULL);
	}

	hash_table->lists = (dll_t **)malloc(capacity * sizeof( dll_t*));
	if (NULL == hash_table->lists)
	{
		free(hash_table);
		hash_table = NULL;

		return (NULL);
	}

	for (i = 0; i < capacity; ++i)
	{
		hash_table->lists[i] = DLLCreate();
		if (NULL == hash_table->lists[i])
		{
			HashDestroy(hash_table);

			return (NULL);
		}
	}

	hash_table->hash_func = hash_func;
	hash_table->is_match = is_match;
	hash_table->capacity = capacity;
	hash_table->param = param;

	return (hash_table);
}

void HashDestroy(hash_t *hash)
{
	size_t i;

	assert(NULL != hash);

	for (i = 0; i < hash->capacity; ++i)
	{
		DLLDestroy(hash->lists[i]);
		hash->lists[i] = NULL;
	}

	free(hash->lists);
	hash->lists = NULL;

	free(hash);
	hash = NULL;
}

int HashInsert(hash_t *hash, void const *key, void const *value)
{
	size_t insert_index = 0;
	dll_iterator_t iterator;

	assert(NULL != hash);
	assert(NULL != key);

	insert_index = hash->hash_func(key);
	insert_index %= hash->capacity;

	iterator = DLLPushBack(hash->lists[insert_index], (void*)value);

	if (DLLIsSameIterator(iterator, DLLEnd(hash->lists[insert_index])))
	{
		return (FAILURE);
	}

	return (SUCCESS);
}

void *HashRemove(hash_t *hash, void const *key, void const *param)
{
	dll_iterator_t iterator;
	void *data_to_remove = NULL;
	size_t find_index = 0;

	assert(NULL != hash);
	assert(NULL != key);

	data_to_remove = HashFind(hash, key, param);
	find_index = hash->hash_func(key);
	find_index %= hash->capacity;
	iterator = DLLFind(hash->lists[find_index], DLLBegin(hash->lists[find_index]), DLLEnd(hash->lists[find_index]), (is_match_t)hash->is_match, (void*)param, NULL);
	
	if (DLLIsSameIterator(iterator, DLLEnd(hash->lists[find_index])))
	{
		return (data_to_remove);
	}

	DLLErase(iterator);

	return (data_to_remove);
}

size_t HashSize(hash_t const *hash)
{
	size_t size = 0;
	size_t i;

	assert(NULL != hash);

	for (i = 0; i < hash->capacity; ++i)
	{
		size += DLLGetSize(hash->lists[i]);
	}

	return (size);
}

int HashIsEmpty(hash_t const *hash)
{
	return (HashSize(hash) > 0 ? FALSE : TRUE);
}

void *HashFind(hash_t *hash, void const *key, void const *param)
{
	size_t find_index = 0;
	dll_iterator_t iterator;

	assert(NULL != hash);
	assert(NULL != key);

	find_index = hash->hash_func(key);
	find_index %= hash->capacity;

	iterator = DLLFind(hash->lists[find_index], DLLBegin(hash->lists[find_index]), DLLEnd(hash->lists[find_index]), (is_match_t)hash->is_match, (void*)param, hash->param);

	if (DLLIsSameIterator(iterator, DLLEnd(hash->lists[find_index])))
	{
		return (NULL);
	}

	return (DLLGetData(iterator));
}

int HashForEach(hash_t *hash, hash_action_func_t action_func, void *param)
{
	size_t i;

	assert(NULL != hash);

	for (i = 0; i < hash->capacity; ++i)
	{
		if (SUCCESS != DLLForEach(DLLBegin(hash->lists[i]), DLLEnd(hash->lists[i]), (action_t)action_func, param))
		{
			return (FAILURE);
		}
	}

	return (SUCCESS);
}

double HashLoadFactor(hash_t const *hash)
{
	assert(NULL != hash);

	return (HashSize(hash) / hash->capacity);
}

double HashStandardDeviation(hash_t const *hash)
{
	double sum = 0;
	double load_factor = 0;
	size_t i;

	assert(NULL != hash);

	load_factor = HashLoadFactor(hash);

	for (i = 0; i < hash->capacity; ++i)
	{
		sum += pow(DLLGetSize(hash->lists[i]) - load_factor, 2);  
	}

	return (sqrt(sum * (1 / hash->capacity)));
}