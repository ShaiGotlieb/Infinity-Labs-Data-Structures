#include <assert.h>

#include "sorted_list.h"
#include "dll.h"

struct sorted_list_s
{
	dll_t *dllist;
	is_new_before_exist_t is_before;

};

sorted_list_t *SLCreate(is_new_before_exist_t is_before)
{
	sorted_list_t *sorted_list = (sorted_list_t*)malloc(sizeof(sorted_list_t));

	if (NULL == sorted_list)
	{
		return (NULL);
	}

	sorted_list->dllist = DLLCreate();

	if (NULL == sorted_list->dllist)
	{
		free(sorted_list);

		return (NULL);
	}

	sorted_list->is_before = is_before;

	return (sorted_list);
}

void SLDestroy(sorted_list_t *list)
{
	assert(NULL != list);

	DLLDestroy(list->dllist);
	free(list);
	list = NULL;
}

size_t SLGetSize(const sorted_list_t *list)
{
	assert(NULL != list);

	return (DLLGetSize(list->dllist));
}

boolean_t SLIsEmpty(const sorted_list_t *list)
{
	assert(NULL != list);

	return (DLLIsEmpty(list->dllist));
}

sorted_list_iterator_t SLBegin(const sorted_list_t *list)
{
	sorted_list_iterator_t sorted_iterator;
	sorted_iterator.info = DLLBegin(list->dllist).info;

	return (sorted_iterator);
}

sorted_list_iterator_t SLEnd(const sorted_list_t *list)
{
	sorted_list_iterator_t sorted_iterator;

	assert(NULL != list);

	sorted_iterator.info = DLLEnd(list->dllist).info;

	return (sorted_iterator);
}

void *SLGetData(sorted_list_iterator_t iterator)
{
	dll_iterator_t sent_iterator;
	sent_iterator.info = iterator.info;

	return (DLLGetData(sent_iterator));
}

sorted_list_iterator_t SLGetNext(sorted_list_iterator_t iterator)
{
	dll_iterator_t sent_iterator;
	sent_iterator.info = iterator.info;
	iterator.info = (DLLGetNext(sent_iterator)).info;

	return iterator;
}

sorted_list_iterator_t SLGetPrevious(sorted_list_iterator_t iterator)
{
	dll_iterator_t sent_iterator;
	sent_iterator.info = iterator.info;
	iterator.info = (DLLGetPrevious(sent_iterator)).info;

	return iterator;
}

boolean_t SLIsSameIterator(sorted_list_iterator_t iterator1,
							sorted_list_iterator_t iterator2)
{
	dll_iterator_t sent_iterator1;
	dll_iterator_t sent_iterator2;

	sent_iterator1.info = iterator1.info;
	sent_iterator2.info = iterator2.info;

	return DLLIsSameIterator(sent_iterator1, sent_iterator2);
}

sorted_list_iterator_t SLInsert(sorted_list_t *list, void *data)
{
	sorted_list_iterator_t runner_iterator = SLBegin(list);
	sorted_list_iterator_t end = SLEnd(list);
	dll_iterator_t where_iterator;

	assert(NULL != list);
	
	while(runner_iterator.info != end.info)
	{
		if (TRUE == list->is_before(data, SLGetData(runner_iterator)))
		{
			where_iterator.info = runner_iterator.info;
	 		runner_iterator.info = DLLInsert(list->dllist, where_iterator, data).info;

	 		return (runner_iterator);
		}
		runner_iterator = SLGetNext(runner_iterator);
	}

	runner_iterator.info = DLLPushBack(list->dllist, data).info;

	return (runner_iterator);
}

sorted_list_iterator_t SLErase(sorted_list_iterator_t iterator)
{
	dll_iterator_t erase_iterator;
	erase_iterator.info = iterator.info;

	iterator.info = DLLErase(erase_iterator).info;

	return (iterator);
}

void SLPopFront(sorted_list_t *list)
{
	assert(NULL != list);

	DLLPopFront(list->dllist);
}

void SLPopBack(sorted_list_t *list)
{
	assert(NULL != list);

	DLLPopBack(list->dllist);
}

sorted_list_iterator_t SLFind(sorted_list_t *list, const sorted_list_iterator_t from,
							const sorted_list_iterator_t to, is_match_t ismatch, 
							void *data_for_cmp, void *param)
{
	sorted_list_iterator_t return_iterator;
	dll_iterator_t from_iterator;
	dll_iterator_t to_iterator;

	assert(NULL != list);

	from_iterator.info = from.info;
	to_iterator.info = to.info;
	return_iterator.info = DLLFind(list->dllist, from_iterator, to_iterator, ismatch, data_for_cmp, param).info;

	return (return_iterator);
}

status_t SLForEach(sorted_list_iterator_t from, sorted_list_iterator_t to, action_t action, void *param)
{
	dll_iterator_t from_iterator;
	dll_iterator_t to_iterator;

	from_iterator.info = from.info;
	to_iterator.info = to.info;

	return (DLLForEach(from_iterator, to_iterator, action, param));
}

void SLMerge(sorted_list_t *list_dest, sorted_list_t *list_src)
{
	dll_iterator_t src_iterator = DLLBegin(list_src->dllist); 
	dll_iterator_t src_runner_iterator = DLLBegin(list_src->dllist);
	dll_iterator_t dest_iterator = DLLBegin(list_dest->dllist);

	if (DLLIsEmpty(list_dest->dllist) || DLLIsEmpty(list_src->dllist) )
	{
		DLLSplice(dest_iterator, src_iterator, DLLEnd(list_src->dllist));
	}
	else
	{
		while(FALSE == DLLIsSameIterator(src_runner_iterator, DLLEnd(list_src->dllist)))
		{
			
			while (TRUE == list_dest->is_before(DLLGetData(dest_iterator), DLLGetData(src_runner_iterator)))
			{
				if (TRUE == DLLIsSameIterator(DLLGetNext(dest_iterator), DLLEnd(list_dest->dllist)))
				{
					dest_iterator = DLLGetNext(dest_iterator);
					break;
				}
				dest_iterator = DLLGetNext(dest_iterator);
			}

			if (TRUE == DLLIsSameIterator(dest_iterator, DLLEnd(list_dest->dllist)))
			{
				src_runner_iterator = DLLEnd(list_src->dllist);
				DLLSplice(dest_iterator, src_iterator, src_runner_iterator);
				break;
			}
			while (FALSE == list_dest->is_before(DLLGetData(dest_iterator), DLLGetData(src_runner_iterator))) 
			{
				if (TRUE == DLLIsSameIterator(DLLGetNext(src_runner_iterator), DLLEnd(list_src->dllist)))
				{
					src_runner_iterator = DLLGetNext(src_runner_iterator);
					break;
				}
				src_runner_iterator = DLLGetNext(src_runner_iterator);
			}

			DLLSplice(dest_iterator, src_iterator, src_runner_iterator);
			src_iterator = src_runner_iterator;
		}
	}
}


