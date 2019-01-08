#include <stdlib.h>
#include "dll.h"
#include "test.h"

#define RANDOM (rand())
#define EMPTY (0)

TestResult TestDLLCreate();
TestResult TestDLLGetSize();
TestResult TestDLLIsEmpty();
TestResult TestDLLInsert();
TestResult TestDLLPushFront();
TestResult TestDLLPushBack();
TestResult TestDLLBegin();
TestResult TestDLLEnd();
TestResult TestDLLGetData();
TestResult TestDLLGetNext();
TestResult TestDLLGetPrevious();
TestResult TestDLLIsSameIterator();
TestResult TestDLLErase();
TestResult TestDLLPopFront();
TestResult TestDLLPopBack();
TestResult TestDLLFind();
TestResult TestDLLForEach();
TestResult TestDLLSplice();

typedef struct dll_node_s
{
	void *data;
	struct dll_node_s *next;
	struct dll_node_s *prev;
}dll_node_t;

dll_node_t *CreateNode(dll_node_t *prev, dll_node_t *next, void *data);

boolean_t ismatch(const void *data1, const void *data2, void *param)
{
	if (param == param)
	{
		return data1 == data2;
	}
	return data1 == data2;
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
	RUN_TEST(TestDLLCreate);
	RUN_TEST(TestDLLGetSize);
	RUN_TEST(TestDLLIsEmpty);
	RUN_TEST(TestDLLInsert);
	RUN_TEST(TestDLLPushFront);
	RUN_TEST(TestDLLPushBack);
	RUN_TEST(TestDLLBegin);
	RUN_TEST(TestDLLEnd);
	RUN_TEST(TestDLLGetData);
	RUN_TEST(TestDLLGetNext);
	RUN_TEST(TestDLLGetPrevious);
	RUN_TEST(TestDLLIsSameIterator);
	RUN_TEST(TestDLLErase);
	RUN_TEST(TestDLLPopFront);
	RUN_TEST(TestDLLPopBack);
	RUN_TEST(TestDLLFind);
	RUN_TEST(TestDLLForEach);
	RUN_TEST(TestDLLSplice);

	return (EXIT_SUCCESS);
}

TestResult TestDLLCreate()
{
	dll_t *dll = DLLCreate();
	REQUIRE(NULL != dll);

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLGetSize()
{
	dll_t *dll = DLLCreate();

	REQUIRE(NULL != dll);
	REQUIRE(EMPTY == DLLGetSize(dll));

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLIsEmpty()
{
	dll_t *dll = DLLCreate();
	REQUIRE(NULL != dll);
	REQUIRE(EMPTY == DLLGetSize(dll));
	REQUIRE(TRUE == DLLIsEmpty(dll));

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLInsert()
{
	int random = RANDOM;
	void *data = &random;
	dll_iterator_t where;
	dll_t *dll = DLLCreate();

	where = DLLInsert(dll, where, data);
	REQUIRE(EMPTY == DLLGetSize(dll));
	where = DLLPushFront(dll, data);
	REQUIRE(1 == DLLGetSize(dll));
	where = DLLInsert(dll, where, data);
	REQUIRE(2 == DLLGetSize(dll));
	where = DLLInsert(dll, where, data);
	REQUIRE(3 == DLLGetSize(dll));

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLPushFront()
{
	int random = RANDOM;
	void *data = &random;
	dll_iterator_t where;
	dll_t *dll = DLLCreate();

	where = DLLPushFront(dll, data);
	REQUIRE(1 == DLLGetSize(dll));
	REQUIRE(DLLGetData(where) == data);
	
	random = RANDOM;
	data = &random;
	where = DLLPushFront(dll, data);
	REQUIRE(2 == DLLGetSize(dll));
	REQUIRE(DLLGetData(where) == data);
	
	random = RANDOM;
	data = &random;
	where = DLLInsert(dll, where, data);
	REQUIRE(3 == DLLGetSize(dll));
	REQUIRE(DLLGetData(where) == data);

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLPushBack()
{
	int random = RANDOM;
	void *data = &random;
	dll_iterator_t where;
	dll_t *dll = DLLCreate();

	where = DLLPushBack(dll, data);
	REQUIRE(1 == DLLGetSize(dll));
	REQUIRE(DLLGetData(where) == data);
	
	random = RANDOM;
	data = &random;
	where = DLLPushBack(dll, data);
	REQUIRE(2 == DLLGetSize(dll));
	REQUIRE(DLLGetData(where) == data);
	
	random = RANDOM;
	data = &random;
	where = DLLPushBack(dll, data);
	REQUIRE(3 == DLLGetSize(dll));
	REQUIRE(DLLGetData(where) == data);

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLBegin()
{
	int random = RANDOM;
	void *data = &random;
	dll_t *dll = DLLCreate();

	REQUIRE(TRUE == DLLIsSameIterator(DLLBegin(dll),DLLEnd(dll)));
	DLLPushFront(dll, data);
	REQUIRE(FALSE == DLLIsSameIterator(DLLBegin(dll),DLLEnd(dll)));
	REQUIRE(DLLGetData(DLLBegin(dll)) == data);

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLEnd()
{
	int random = RANDOM;
	void *data = &random;
	dll_t *dll = DLLCreate();

	REQUIRE(TRUE == DLLIsSameIterator(DLLBegin(dll),DLLEnd(dll)));
	DLLPushBack(dll, data);
	REQUIRE(FALSE == DLLIsSameIterator(DLLBegin(dll),DLLEnd(dll)));
	REQUIRE(DLLGetData(DLLBegin(dll)) == data);

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLGetData()
{
	int random1 = RANDOM;
	int random2 = RANDOM;
	int random3 = RANDOM;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	dll_iterator_t begin;
	dll_iterator_t middle;
	dll_iterator_t end;
	dll_t *dll = DLLCreate();

	begin = DLLPushFront(dll, data1);
	middle = DLLPushBack(dll, data2);
	end = DLLPushBack(dll, data3);
	
	REQUIRE(DLLGetData(begin) == data1);
	REQUIRE(DLLGetData(middle) == data2);
	REQUIRE(DLLGetData(end) == data3);

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLGetNext()
{
	int random1 = RANDOM;
	int random2 = RANDOM;
	int random3 = RANDOM;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	dll_iterator_t begin;
	dll_iterator_t middle;
	dll_iterator_t end;
	dll_t *dll = DLLCreate();

	begin = DLLPushFront(dll, data1);
	middle = DLLPushBack(dll, data2);
	end = DLLPushBack(dll, data3);
	
	REQUIRE(DLLIsSameIterator(DLLGetNext(begin), middle));
	REQUIRE(DLLIsSameIterator(DLLGetNext(middle), end));
	REQUIRE(DLLIsSameIterator(DLLGetNext(end), DLLEnd(dll)));

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLGetPrevious()
{
	int random1 = RANDOM;
	int random2 = RANDOM;
	int random3 = RANDOM;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	dll_iterator_t begin;
	dll_iterator_t middle;
	dll_iterator_t end;
	dll_t *dll = DLLCreate();

	begin = DLLPushFront(dll, data1);
	middle = DLLPushBack(dll, data2);
	end = DLLPushBack(dll, data3);
	
	REQUIRE(DLLIsSameIterator(DLLGetPrevious(middle), begin));
	REQUIRE(DLLIsSameIterator(DLLGetPrevious(end), middle));

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLIsSameIterator()
{
	int random1 = RANDOM;
	int random2 = RANDOM;
	int random3 = RANDOM;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	dll_iterator_t begin;
	dll_iterator_t middle;
	dll_iterator_t end;
	dll_t *dll = DLLCreate();

	begin = DLLPushFront(dll, data1);
	middle = DLLPushBack(dll, data2);
	end = DLLPushBack(dll, data3);
	
	REQUIRE(DLLIsSameIterator(begin, DLLBegin(dll)));
	REQUIRE(DLLIsSameIterator(DLLGetNext(begin), middle));
	REQUIRE(DLLIsSameIterator(DLLGetNext(middle), end));
	REQUIRE(DLLIsSameIterator(DLLGetNext(end), DLLEnd(dll)));

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLErase()
{
	int random1 = RANDOM;
	int random2 = RANDOM;
	int random3 = RANDOM;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	dll_iterator_t begin;
	dll_iterator_t middle;
	dll_iterator_t end;
	dll_t *dll = DLLCreate();

	begin = DLLPushFront(dll, data1);
	begin = DLLErase(begin);
	REQUIRE(EMPTY == DLLGetSize(dll));

	begin = DLLPushFront(dll, data1);
	middle = DLLPushBack(dll, data2);
	end = DLLPushBack(dll, data3);
	middle = DLLErase(middle);
	REQUIRE(2 == DLLGetSize(dll));

	begin = DLLPushFront(dll, data1);
	middle = DLLPushBack(dll, data2);
	end = DLLPushBack(dll, data3);
	end = DLLErase(end);
	REQUIRE(4 == DLLGetSize(dll));

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLPopFront()
{
	int random1 = RANDOM;
	int random2 = RANDOM;
	int random3 = RANDOM;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	dll_t *dll = DLLCreate();

	DLLPushFront(dll, data1);
	DLLPopFront(dll);
	REQUIRE(EMPTY == DLLGetSize(dll));

	DLLPushFront(dll, data1);
	DLLPushBack(dll, data2);
	DLLPushBack(dll, data3);
	DLLPopFront(dll);
	DLLPopFront(dll);
	REQUIRE(1 == DLLGetSize(dll));
	DLLPopFront(dll);
	REQUIRE(EMPTY == DLLGetSize(dll));

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLPopBack()
{
	int random1 = RANDOM;
	int random2 = RANDOM;
	int random3 = RANDOM;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	dll_t *dll = DLLCreate();

	DLLPushBack(dll, data1);
	DLLPopBack(dll);
	REQUIRE(EMPTY == DLLGetSize(dll));

	DLLPushBack(dll, data1);
	DLLPushBack(dll, data2);
	DLLPushBack(dll, data3);
	DLLPopBack(dll);
	DLLPopBack(dll);
	REQUIRE(1 == DLLGetSize(dll));
	DLLPopBack(dll);
	REQUIRE(EMPTY == DLLGetSize(dll));

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLFind()
{
	int random1 = RANDOM;
	int random2 = RANDOM;
	int random3 = RANDOM;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	dll_t *dll = DLLCreate();
	dll_iterator_t begin = DLLPushBack(dll, data1);
	dll_iterator_t middle = DLLPushBack(dll, data2);
	dll_iterator_t end = DLLPushBack(dll, data2);

	REQUIRE(DLLIsSameIterator(DLLFind(dll, begin, end, ismatch, data2, data2), middle));
	REQUIRE(DLLIsSameIterator(DLLFind(dll, begin, end, ismatch, data1, data1), begin));
	REQUIRE(!DLLIsSameIterator(DLLFind(dll, begin, end, ismatch, data3, data3), end));

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLForEach()
{
	int random1 = RANDOM;
	int random2 = RANDOM;
	int random3 = RANDOM;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	dll_t *dll = DLLCreate();
	dll_iterator_t begin = DLLPushBack(dll, data1);
	dll_iterator_t middle = DLLPushBack(dll, data2);
	dll_iterator_t end = DLLPushBack(dll, data3);

	REQUIRE(SUCCESS == DLLForEach(begin, end, ActionReturnSuccessForTest, data1));
	REQUIRE(SUCCESS == DLLForEach(begin, middle, ActionReturnSuccessForTest, data1));
	REQUIRE(FAIL == DLLForEach(begin, end, ActionReturnFailForTest, data1));

	DLLDestroy(dll);
	
	return (TEST_PASS);
}

TestResult TestDLLSplice()
{
	int random1 = RANDOM;
	int random2 = RANDOM;
	int random3 = RANDOM;
	void *data1 = &random1;
	void *data2 = &random2;
	void *data3 = &random3;
	void *data4 = &random3;
	void *data5 = &random3;
	void *data6 = &random3;
	dll_t *dll1 = DLLCreate();
	dll_t *dll2 = DLLCreate();
	dll_iterator_t begin1 = DLLPushBack(dll1, data1);
	dll_iterator_t middle1 = DLLPushBack(dll1, data2);
	dll_iterator_t end1 = DLLPushBack(dll1, data3);
	dll_iterator_t begin2 = DLLPushBack(dll2, data4);
	dll_iterator_t middle2 = DLLPushBack(dll2, data5);
	dll_iterator_t end2 = DLLPushBack(dll2, data6);

	DLLSplice(middle1, begin2, end2);

	REQUIRE(5 == DLLGetSize(dll1));
	REQUIRE(TRUE == DLLIsSameIterator(DLLGetPrevious(middle1), middle2));
	REQUIRE(TRUE == DLLIsSameIterator(DLLGetPrevious(end1), middle1));
	REQUIRE(TRUE == DLLIsSameIterator(DLLGetPrevious(middle2), begin2));
	REQUIRE(TRUE == DLLIsSameIterator(DLLGetNext(middle2), middle1));
	REQUIRE(TRUE == DLLIsSameIterator(DLLGetNext(begin1), begin2));
	REQUIRE(FALSE == DLLIsSameIterator(DLLGetNext(middle1), end2));

	DLLDestroy(dll1);
	DLLDestroy(dll2);
	
	return (TEST_PASS);
}

