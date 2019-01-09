#include <stdlib.h>
#include "test.h"
#include "sorted_list.h"
#include "dll.h"

#define EMPTY (0)
#define RANDOM (rand())
#define UNUSED(x) (void)(x)

TestResult TestSLCreate();
TestResult TestSLGetSize();
TestResult TestSLIsEmpty();
TestResult TestSLInsert();
TestResult TestSLBegin();
TestResult TestSLEnd();
TestResult TestSLGetData();
TestResult TestSLGetNext();
TestResult TestSLGetPrevious();
TestResult TestSLIsSameIterator();
TestResult TestSLErase();
TestResult TestSLPopFront();
TestResult TestSLPopBack();
TestResult TestSLFind();
TestResult TestSLForEach();
TestResult TestSLMerge();

boolean_t is_before(const void *data1, const void *data2)
{
	int x = *(int*)(data1);
	int y = *(int*)(data2);
	
	if (x <= y)
	{
		return TRUE;
	}
	return FALSE;
}

boolean_t ismatch(const void *data1, const void *data2, void *param)
{
	int x;
	int y;

	UNUSED(param);

	x = *(int*)(data1);
	y = *(int*)(data2);

	if (x == y)
	{
		return TRUE;
	}

	return FALSE;
}

status_t ActionReturnSuccessForTest(void *data, void *param)
{
	data = param;
	param = data;
	return SUCCESS;
}

status_t ActionReturnFailForTest(void *data, void *param)
{
	data = param;
	param = data;
	return FAIL;
}

int main()
{
	RUN_TEST(TestSLCreate);
	RUN_TEST(TestSLGetSize);
	RUN_TEST(TestSLIsEmpty);
	RUN_TEST(TestSLInsert);
	RUN_TEST(TestSLBegin);
	RUN_TEST(TestSLEnd);
	RUN_TEST(TestSLGetData);
	RUN_TEST(TestSLGetNext);
	RUN_TEST(TestSLGetPrevious);
	RUN_TEST(TestSLIsSameIterator);
	RUN_TEST(TestSLErase);
	RUN_TEST(TestSLPopFront);
	RUN_TEST(TestSLPopBack);
	RUN_TEST(TestSLFind);
	RUN_TEST(TestSLForEach);
	RUN_TEST(TestSLMerge);

	return (EXIT_SUCCESS);
}

TestResult TestSLCreate()
{
	sorted_list_t *list = SLCreate(is_before);
	REQUIRE(NULL != list);

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLGetSize()
{
	sorted_list_t *list = SLCreate(is_before);

	REQUIRE(EMPTY == SLGetSize(list));

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLIsEmpty()
{
	sorted_list_t *list = SLCreate(is_before);

	REQUIRE(NULL != list);
	REQUIRE(EMPTY == SLGetSize(list));
	REQUIRE(TRUE == SLIsEmpty(list));

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLInsert()
{
	int random = 1;
	void *data = &random;
	sorted_list_t *list = SLCreate(is_before);

	REQUIRE(EMPTY == SLGetSize(list));
	SLInsert(list, data);
	REQUIRE(1 == SLGetSize(list));
	SLInsert(list, data);
	REQUIRE(2 == SLGetSize(list));
	SLInsert(list, data);
	REQUIRE(3 == SLGetSize(list));

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLBegin()
{
	int random = 1;
	void *data = &random;
	sorted_list_t *list = SLCreate(is_before);

	REQUIRE(TRUE == SLIsSameIterator(SLBegin(list),SLEnd(list)));
	SLInsert(list, data);
	REQUIRE(FALSE == SLIsSameIterator(SLBegin(list),SLEnd(list)));
	REQUIRE(SLGetData(SLBegin(list)) == data);

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLEnd()
{
	int random = 1;
	void *data = &random;
	sorted_list_t *list = SLCreate(is_before);

	REQUIRE(TRUE == SLIsSameIterator(SLBegin(list),SLEnd(list)));
	SLInsert(list, data);
	REQUIRE(FALSE == SLIsSameIterator(SLBegin(list),SLEnd(list)));
	REQUIRE(SLGetData(SLBegin(list)) == data);

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLGetData()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	sorted_list_iterator_t begin;
	sorted_list_iterator_t middle;
	sorted_list_iterator_t end;
	sorted_list_t *list = SLCreate(is_before);

	begin = SLInsert(list, data1);
	middle = SLInsert(list, data2);
	end = SLInsert(list, data3);
	
	REQUIRE(SLGetData(begin) == data1);
	REQUIRE(SLGetData(middle) == data2);
	REQUIRE(SLGetData(end) == data3);

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLGetNext()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	sorted_list_iterator_t begin;
	sorted_list_iterator_t middle;
	sorted_list_iterator_t end;
	sorted_list_t *list = SLCreate(is_before);

	begin = SLInsert(list, data1);
	middle = SLInsert(list, data2);
	end = SLInsert(list, data3);
	
	REQUIRE(SLIsSameIterator(SLGetNext(begin), middle));
	REQUIRE(SLIsSameIterator(SLGetNext(middle), end));
	REQUIRE(SLIsSameIterator(SLGetNext(end), SLEnd(list)));

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLGetPrevious()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	sorted_list_iterator_t begin;
	sorted_list_iterator_t middle;
	sorted_list_iterator_t end;
	sorted_list_t *list = SLCreate(is_before);

	begin = SLInsert(list, data1);
	middle = SLInsert(list, data2);
	end = SLInsert(list, data3);
	
	REQUIRE(SLIsSameIterator(SLGetPrevious(middle), begin));
	REQUIRE(SLIsSameIterator(SLGetPrevious(end), middle));

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLIsSameIterator()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	sorted_list_iterator_t begin;
	sorted_list_iterator_t middle;
	sorted_list_iterator_t end;
	sorted_list_t *list = SLCreate(is_before);

	begin = SLInsert(list, data1);
	middle = SLInsert(list, data2);
	end = SLInsert(list, data3);
	
	REQUIRE(SLIsSameIterator(begin, SLBegin(list)));
	REQUIRE(SLIsSameIterator(SLGetNext(begin), middle));
	REQUIRE(SLIsSameIterator(SLGetNext(middle), end));
	REQUIRE(SLIsSameIterator(SLGetNext(end), SLEnd(list)));

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLErase()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	sorted_list_iterator_t begin;
	sorted_list_iterator_t middle;
	sorted_list_iterator_t end;
	sorted_list_t *list = SLCreate(is_before);

	begin = SLInsert(list, data1);
	begin = SLErase(begin);
	REQUIRE(EMPTY == SLGetSize(list));

	begin = SLInsert(list, data1);
	middle = SLInsert(list, data2);
	end = SLInsert(list, data3);
	middle = SLErase(middle);
	REQUIRE(2 == SLGetSize(list));

	begin = SLInsert(list, data1);
	middle = SLInsert(list, data2);
	end = SLInsert(list, data3);
	end = SLErase(end);
	REQUIRE(4 == SLGetSize(list));

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLPopFront()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	sorted_list_t *list = SLCreate(is_before);

	SLInsert(list, data1);
	SLPopFront(list);
	REQUIRE(EMPTY == SLGetSize(list));

	SLInsert(list, data1);
	SLInsert(list, data2);
	SLInsert(list, data3);
	SLPopFront(list);
	SLPopFront(list);
	REQUIRE(1 == SLGetSize(list));
	SLPopFront(list);
	REQUIRE(EMPTY == SLGetSize(list));

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLPopBack()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	sorted_list_t *list = SLCreate(is_before);

	SLInsert(list, data1);
	SLPopBack(list);
	REQUIRE(EMPTY == SLGetSize(list));

	SLInsert(list, data1);
	SLInsert(list, data2);
	SLInsert(list, data3);
	SLPopBack(list);
	SLPopBack(list);
	REQUIRE(1 == SLGetSize(list));
	SLPopBack(list);
	REQUIRE(EMPTY == SLGetSize(list));

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLFind()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	sorted_list_t *list = SLCreate(is_before);
	sorted_list_iterator_t begin = SLInsert(list, data1);
	sorted_list_iterator_t middle = SLInsert(list, data2);
	sorted_list_iterator_t end = SLInsert(list, data3);

	REQUIRE(SLIsSameIterator(SLFind(list, begin, end, ismatch, data2, NULL), middle));
	REQUIRE(SLIsSameIterator(SLFind(list, begin, end, ismatch, data1, NULL), begin));
	REQUIRE(!SLIsSameIterator(SLFind(list, begin, end, ismatch, data3, NULL), end));

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLForEach()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 3;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	sorted_list_t *list = SLCreate(is_before);
	sorted_list_iterator_t begin = SLInsert(list, data1);
	sorted_list_iterator_t middle = SLInsert(list, data2);
	sorted_list_iterator_t end = SLInsert(list, data3);

	REQUIRE(SUCCESS == SLForEach(begin, end, ActionReturnSuccessForTest, data1));
	REQUIRE(SUCCESS == SLForEach(begin, middle, ActionReturnSuccessForTest, data1));
	REQUIRE(FAIL == SLForEach(begin, end, ActionReturnFailForTest, data1));

	SLDestroy(list);
	
	return (TEST_PASS);
}

TestResult TestSLMerge()
{
	int random1 = 1;
	int random2 = 2;
	int random3 = 5;
	int random4 = 8;
	int random5 = 10;
	int random6 = 3;
	int random7 = 4;
	int random8 = 6;
	int random9 = 7;
	
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	void *data4 = &random4;
	void *data5 = &random5;
	void *data6 = &random6;
	void *data7 = &random7;
	void *data8 = &random8;
	void *data9 = &random9;


	sorted_list_t *dest_list = SLCreate(is_before);
	sorted_list_t *src_list = SLCreate(is_before);
	sorted_list_iterator_t begin1 = SLInsert(dest_list, data1);
	sorted_list_iterator_t middle1 = SLInsert(dest_list, data2);
	sorted_list_iterator_t end1 = SLInsert(dest_list, data3);
	sorted_list_iterator_t end11 = SLInsert(dest_list, data4);
	sorted_list_iterator_t end12 = SLInsert(dest_list, data5);
	sorted_list_iterator_t begin2 = SLInsert(src_list, data6);
	sorted_list_iterator_t middle2 = SLInsert(src_list, data7);
	sorted_list_iterator_t end2 = SLInsert(src_list, data8);
	sorted_list_iterator_t end22 = SLInsert(src_list, data9);

	UNUSED(begin1);
	UNUSED(end12);

	SLMerge(dest_list, src_list);

	REQUIRE(9 == SLGetSize(dest_list));
	REQUIRE(EMPTY == SLGetSize(src_list));
	REQUIRE(TRUE == SLIsSameIterator(SLGetPrevious(begin2), middle1));
	REQUIRE(TRUE == SLIsSameIterator(SLGetPrevious(end1), middle2));
	REQUIRE(TRUE == SLIsSameIterator(SLGetNext(end1), end2));
	REQUIRE(TRUE == SLIsSameIterator(SLGetNext(end22), end11));

	SLDestroy(dest_list);
	SLDestroy(src_list);
	
	return (TEST_PASS);
}