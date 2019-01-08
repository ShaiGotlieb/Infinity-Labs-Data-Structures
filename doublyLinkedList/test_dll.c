#include "test.h"
#include "dll.h"

#define UNUSED(x) (void)(x)
#define NUM_OF_ELEMENTS(arr) (sizeof(arr) / sizeof(arr[0]))


static boolean_t IsMatchInt(const void *data1, const void *data2, void *param);
static status_t MultiInts(void *data, void *param);
TestResult TestDLLCreate();
TestResult TestDLLPushFront();
TestResult TestDLLPushBack();
TestResult TestDLLGetSize();
TestResult TestDllIsEmpty();
TestResult TestDLLIsSameIterator();
TestResult TestDLLErase();
TestResult TestDLLBegin();
TestResult TestDLLGetData();
TestResult TestDLLGetNext();
TestResult TestDLLGetPrevious();
TestResult TestDLLInsert();
TestResult TestDLLPopFront();
TestResult TestDLLPopBack();
TestResult TestDLLFind();
TestResult TestDLLForEach();
TestResult TestDLLSplice();

int main()
{
	RUN_TEST(TestDLLCreate);
	RUN_TEST(TestDLLPushFront);
	RUN_TEST(TestDLLPushBack);
	RUN_TEST(TestDLLGetSize);
	RUN_TEST(TestDllIsEmpty);
	RUN_TEST(TestDLLIsSameIterator);
	RUN_TEST(TestDLLErase);
	RUN_TEST(TestDLLBegin);
	RUN_TEST(TestDLLGetData);
	RUN_TEST(TestDLLGetNext);
	RUN_TEST(TestDLLGetPrevious);
	RUN_TEST(TestDLLInsert);
	RUN_TEST(TestDLLPopFront);
	RUN_TEST(TestDLLPopBack);
	RUN_TEST(TestDLLFind);
	RUN_TEST(TestDLLForEach);
	RUN_TEST(TestDLLSplice);
		
	return (0);
}

TestResult TestDLLCreate()
{
	dll_t *new_dll = DLLCreate();
	REQUIRE(NULL != new_dll);
	DLLDestroy(new_dll);

	return (TEST_PASS);
}

TestResult TestDLLGetSize()
{
	int a = 5;
	dll_t *list = DLLCreate();
	
	REQUIRE(0 == DLLGetSize(list));
	DLLPushFront(list, &a);
	REQUIRE(1 == DLLGetSize(list));
	DLLPushFront(list, &a);	
	REQUIRE(2 == DLLGetSize(list));
	
	DLLDestroy(list);

	return (TEST_PASS);
}

TestResult TestDllIsEmpty()
{
	int a = 5;
	dll_t *list = DLLCreate();
	
	REQUIRE(TRUE == DllIsEmpty(list));
	DLLPushFront(list, &a);
	REQUIRE(FALSE == DllIsEmpty(list));
		
	DLLDestroy(list);

	return (TEST_PASS);
}

TestResult TestDLLBegin()
{
	int a = 5;
	dll_t *list = DLLCreate();
	dll_iterator_t iterator = DLLPushFront(list, &a);
	
	REQUIRE(TRUE == DLLIsSameIterator(iterator, DLLBegin(list)));
		
	DLLDestroy(list);

	return (TEST_PASS);
}

TestResult TestDLLGetData()
{
	int a = 5;
	int b = 3;
	int c = 7;
	dll_t *list = DLLCreate();
	dll_iterator_t iterator1 = DLLPushFront(list, &a);
	dll_iterator_t iterator2 = DLLPushFront(list, &b);	
	dll_iterator_t iterator3 = DLLPushFront(list, &c);	
	
	REQUIRE(&a == DLLGetData(iterator1));
	REQUIRE(&b == DLLGetData(iterator2));
	REQUIRE(&c == DLLGetData(iterator3));

	DLLDestroy(list);

	return (TEST_PASS);
}

TestResult TestDLLGetNext()
{
	int a = 5;
	int b = 3;
	int c = 7;
	dll_t *list = DLLCreate();
	dll_iterator_t iterator1 = DLLPushFront(list, &a);
	dll_iterator_t iterator2 = DLLPushFront(list, &b);	
	dll_iterator_t iterator3 = DLLPushFront(list, &c);	

	REQUIRE(TRUE == DLLIsSameIterator(iterator2, DLLGetNext(iterator3)));
	REQUIRE(TRUE == DLLIsSameIterator(iterator1, DLLGetNext(iterator2)));
	REQUIRE(TRUE == DLLIsSameIterator(DLLEnd(list), DLLGetNext(iterator1)));

	DLLDestroy(list);

	return (TEST_PASS);
}

TestResult TestDLLGetPrevious()
{
	int a = 5;
	int b = 3;
	int c = 7;
	dll_t *list = DLLCreate();
	dll_iterator_t iterator1 = DLLPushFront(list, &a);
	dll_iterator_t iterator2 = DLLPushFront(list, &b);	
	dll_iterator_t iterator3 = DLLPushFront(list, &c);	

	REQUIRE(TRUE == DLLIsSameIterator(iterator1, DLLGetPrevious(DLLEnd(list))));
	REQUIRE(TRUE == DLLIsSameIterator(iterator2, DLLGetPrevious(iterator1)));
	REQUIRE(TRUE == DLLIsSameIterator(iterator3, DLLGetPrevious(iterator2)));

	DLLDestroy(list);

	return (TEST_PASS);
}

TestResult TestDLLIsSameIterator()
{
	int a = 5;
	int b = 5;
	dll_t *list = DLLCreate();
	dll_iterator_t iterator1 = DLLPushFront(list, &a);
	dll_iterator_t iterator2 = DLLPushFront(list, &b);	
	
	REQUIRE(TRUE == DLLIsSameIterator(iterator1, iterator1));
	REQUIRE(FALSE == DLLIsSameIterator(iterator1, iterator2));

	DLLDestroy(list);

	return (TEST_PASS);
}

TestResult TestDLLInsert()
{
	size_t pushed_elements = 0;
	int a = 5;
	dll_t *list = DLLCreate();
	
	dll_iterator_t iterator1 = DLLPushFront(list, &a);
	dll_iterator_t iterator2 = DLLPushFront(list, &a);
	DLLPushFront(list, &a);
	
	pushed_elements = DLLGetSize(list);

	
	DLLInsert(list, iterator1, &a); /* insert to end */
	REQUIRE(++pushed_elements == DLLGetSize(list));
	DLLInsert(list, iterator2, &a); /* insert to middle */
	REQUIRE(++pushed_elements == DLLGetSize(list));
	DLLInsert(list, DLLBegin(list), &a); /* insert to begin */
	REQUIRE(++pushed_elements == DLLGetSize(list));

	DLLDestroy(list);

	return (TEST_PASS);

}

TestResult TestDLLPushFront()
{	size_t counter = 0;
	int a = 5;
	dll_t *list = DLLCreate();
	REQUIRE(NULL != DLLPushFront(list, &a).info);
	REQUIRE(++counter == DLLGetSize(list));
	REQUIRE(NULL != DLLPushFront(list, &a).info);
	REQUIRE(++counter == DLLGetSize(list));
	
	DLLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestDLLPushBack()
{
	size_t counter = 0;
	int a = 5;
	dll_t *list = DLLCreate();
	REQUIRE(NULL != DLLPushBack(list, &a).info);
	REQUIRE(++counter == DLLGetSize(list));
	REQUIRE(NULL != DLLPushBack(list, &a).info);
	REQUIRE(++counter == DLLGetSize(list));
	
	DLLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestDLLErase()
{
	int a = 5;
	int b = 3;
	dll_t *list = DLLCreate();
	dll_iterator_t iterator1 = DLLPushFront(list, &a);
	dll_iterator_t iterator2 = DLLPushFront(list, &b);	
	dll_iterator_t iterator3 = DLLPushFront(list, &b);	
	
	REQUIRE(TRUE == DLLIsSameIterator(iterator1, DLLErase(iterator2))); /* delete middle */
	REQUIRE(TRUE == DLLIsSameIterator(DLLEnd(list), DLLErase(iterator1))); /* delete last */
	DLLPushFront(list, &b);
	REQUIRE(TRUE == DLLIsSameIterator(iterator3, DLLErase(DLLBegin(list)))); /* delete begin */
	
	DLLDestroy(list);

	return (TEST_PASS);
}

TestResult TestDLLPopFront()
{
	size_t counter = 0;
	int a = 5;
	int b = 3;
	dll_t *list = DLLCreate();
	dll_iterator_t iterator1 = DLLPushFront(list, &a);
	dll_iterator_t iterator2 = DLLPushFront(list, &b);	
	dll_iterator_t iterator3 = DLLPushFront(list, &b);	

	UNUSED(iterator3);

	counter = DLLGetSize(list);
	DLLPopFront(list);
	REQUIRE(--counter == DLLGetSize(list));
	REQUIRE(TRUE == DLLIsSameIterator(DLLBegin(list), iterator2));
	DLLPopFront(list);
	REQUIRE(--counter == DLLGetSize(list));
	REQUIRE(TRUE == DLLIsSameIterator(DLLBegin(list), iterator1));
	DLLPopFront(list);
	REQUIRE(--counter == DLLGetSize(list));
	REQUIRE(TRUE == DLLIsSameIterator(DLLBegin(list), DLLEnd(list)));

	DLLDestroy(list);

	return (TEST_PASS);

}

TestResult TestDLLPopBack()
{
	size_t counter = 0;
	int a = 5;
	int b = 3;
	dll_t *list = DLLCreate();
	dll_iterator_t iterator1 = DLLPushFront(list, &a);
	dll_iterator_t iterator2 = DLLPushFront(list, &b);	
	dll_iterator_t iterator3 = DLLPushFront(list, &b);	

	UNUSED(iterator1);

	counter = DLLGetSize(list);
	DLLPopBack(list);
	REQUIRE(--counter == DLLGetSize(list));
	REQUIRE(TRUE == DLLIsSameIterator(DLLGetPrevious(DLLEnd(list)), iterator2));
	DLLPopBack(list);
	REQUIRE(--counter == DLLGetSize(list));
	REQUIRE(TRUE == DLLIsSameIterator(DLLGetPrevious(DLLEnd(list)), iterator3));
	DLLPopBack(list);
	REQUIRE(--counter == DLLGetSize(list));
	REQUIRE(TRUE == DLLIsSameIterator(DLLBegin(list), DLLEnd(list)));

	DLLDestroy(list);

	return (TEST_PASS);
}

static boolean_t IsMatchInt(const void *data1, const void *data2, void *param)
{
	boolean_t ans;

	UNUSED(param);

	if(NULL == data1 && NULL == data2)
	{
		ans = TRUE;
	}
	else if (NULL == data1 || NULL == data2)
	{
		ans = FALSE;
	}
	else
	{
		ans = (*(int*)data1 == *(int*)data2) ? TRUE : FALSE;
	}

	return (ans);
}

TestResult TestDLLFind()
{
	int a = 5;
	int b = 3;
	dll_t *list = DLLCreate();
	dll_iterator_t iterator1 = DLLPushFront(list, NULL);
	dll_iterator_t iterator2 = DLLPushFront(list, &b);	
	dll_iterator_t iterator3 = DLLPushFront(list, &a);	
	dll_iterator_t iterator4 = DLLPushFront(list, &b);	

	UNUSED(iterator2);

	REQUIRE(TRUE == DLLIsSameIterator(iterator4, 
		DLLFind(list, DLLBegin(list), DLLEnd(list), IsMatchInt, &b, NULL)));
	REQUIRE(FALSE == DLLIsSameIterator(iterator3, 
		DLLFind(list, DLLBegin(list), iterator3, IsMatchInt, &a, NULL)));
	REQUIRE(TRUE == DLLIsSameIterator(iterator1, 
		DLLFind(list, DLLBegin(list), DLLEnd(list), IsMatchInt, NULL, NULL)));

	DLLDestroy(list);

	return (TEST_PASS);

}
static status_t MultiInts(void *data, void *param)
{
	if (NULL == data || NULL == param)
	{
		return (FAIL);
	}

	*(int*)data *= *(int*)param;

	return (SUCCESS);
}

TestResult TestDLLForEach()
{
	int ints[] = {1, 2, 3, 4};
	int copy_of_ints[] = {1, 2, 3, 4};
	int multBy = 3;
	size_t i;
	dll_t *list = DLLCreate();
	
	for (i = 0; i < NUM_OF_ELEMENTS(ints); ++i)
	{
		DLLPushFront(list, &ints[i]);
	}
	
	REQUIRE(SUCCESS == DLLForEach(DLLBegin(list), DLLEnd(list), MultiInts, &multBy));
	
	for (i = 0; i < NUM_OF_ELEMENTS(ints); ++i)
	{
		REQUIRE(multBy * copy_of_ints[i] == ints[i]);
	}

	DLLDestroy(list);

	return (TEST_PASS);
}

TestResult TestDLLSplice()
{
	int ints[] = {1, 2, 3, 4};
	dll_iterator_t iterators1[4];
	dll_iterator_t iterators2[4];
	size_t i;
	dll_t *list1 = DLLCreate();
	dll_t *list2 = DLLCreate();
	
	for (i = 0; i < NUM_OF_ELEMENTS(ints); ++i)
	{
		DLLPushFront(list1, &ints[i]);
		DLLPushFront(list2, &ints[i]);
	}

	DLLSplice(DLLBegin(list1), DLLBegin(list2), DLLEnd(list2));

	REQUIRE(2 * NUM_OF_ELEMENTS(ints) == DLLGetSize(list1));
	REQUIRE(0 == DLLGetSize(list2));

	DLLDestroy(list1);
	DLLDestroy(list2);

	list1 = DLLCreate();
	list2 = DLLCreate();

	for (i = 0; i < NUM_OF_ELEMENTS(ints); ++i)
	{
		iterators1[i] = DLLPushFront(list1, &ints[i]);
		iterators2[i] = DLLPushFront(list2, &ints[i]);
	}

	DLLSplice(DLLEnd(list1), DLLBegin(list2), iterators2[1]);

	REQUIRE(NUM_OF_ELEMENTS(ints) + 2 == DLLGetSize(list1));
	REQUIRE(NUM_OF_ELEMENTS(ints) - 2 == DLLGetSize(list2));

	DLLSplice(iterators1[2], DLLBegin(list2), DLLEnd(list2));

	REQUIRE(2 * NUM_OF_ELEMENTS(ints) == DLLGetSize(list1));
	REQUIRE(0 == DLLGetSize(list2));

	DLLDestroy(list1);
	DLLDestroy(list2);

	return (TEST_PASS);
}