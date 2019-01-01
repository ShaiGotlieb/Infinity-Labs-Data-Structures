#include <stdlib.h>
#include "test.h"
#include "cbuffer.h"

#define TRUE 1
#define FALSE 0

struct cbuffer_s
{
	void *data;
	size_t capacity;
	size_t head;
	size_t tail;
};

TestResult TestCBufferCreate()
{
	cbuffer_t *buffer = CBufferCreate(10);
	REQUIRE(buffer != NULL);
	REQUIRE(CBufferIsEmpty(buffer) == TRUE);

	CBufferDestroy(buffer);

	return TEST_PASS;
}


TestResult TestCBufferWrite()
{
	cbuffer_t *buffer = CBufferCreate(20);
	char *element = "Hi, i am a nice string please give me money!";
	size_t result_bytes = 11;
	size_t result_bytes1 = 9;
	size_t written_bytes = CBufferWrite(buffer, element, result_bytes);

	REQUIRE(written_bytes == result_bytes);
	written_bytes = CBufferWrite(buffer, element, result_bytes);
	
	REQUIRE(written_bytes == result_bytes1);

	written_bytes = CBufferWrite(buffer, element, result_bytes);
	
	REQUIRE(written_bytes == 0);

	CBufferDestroy(buffer);
	return TEST_PASS;
}



TestResult TestCBufferRead()
{
	cbuffer_t *buffer = CBufferCreate(20);
	char *element = "Hi, i am a nice string please give me money!";
	char read_element[11];
	size_t read_bytes = 11;
	size_t result_bytes = 0;

	CBufferWrite(buffer, element, 3);
	result_bytes = CBufferRead(buffer, read_element, read_bytes);
	REQUIRE(3 == result_bytes);
	CBufferWrite(buffer, element, 11);
	result_bytes = CBufferRead(buffer, read_element, 11);
	REQUIRE(11 == result_bytes);
	result_bytes = CBufferRead(buffer, read_element, 11);
	REQUIRE(0 == result_bytes);

	CBufferDestroy(buffer);
	return TEST_PASS;
}

TestResult TestCBufferIsEmpty()
{
	cbuffer_t *buffer = CBufferCreate(40);
	char *element = "And remember: respect is everything!";

	REQUIRE(CBufferIsEmpty(buffer) == TRUE);
	CBufferWrite(buffer, element, 36);
	REQUIRE(CBufferIsEmpty(buffer) == FALSE);

	CBufferDestroy(buffer);
	return TEST_PASS;
}

TestResult TestCBufferGetCapacity()
{
	cbuffer_t *buffer = CBufferCreate(20);
	REQUIRE(CBufferGetCapacity(buffer) == 20);
	CBufferDestroy(buffer);
	buffer = CBufferCreate(200);
	REQUIRE(CBufferGetCapacity(buffer) == 200);
	CBufferDestroy(buffer);
	buffer = CBufferCreate(0);
	REQUIRE(CBufferGetCapacity(buffer) == 0);

	CBufferDestroy(buffer);
	return TEST_PASS;
}

TestResult TestCBufferGetSize()
{
	cbuffer_t *buffer = CBufferCreate(20);
	REQUIRE(CBufferGetSize(buffer) == 0);
	CBufferWrite(buffer, "hell", 1);
	REQUIRE(CBufferGetSize(buffer) == 1);

	CBufferDestroy(buffer);
	return TEST_PASS;
}

TestResult TestCBufferClear()
{
	cbuffer_t *buffer = CBufferCreate(20);
	CBufferWrite(buffer, "hell", 1);
	CBufferClear(buffer);
	REQUIRE(CBufferGetSize(buffer) == 0);

	CBufferDestroy(buffer);
	return TEST_PASS;
}


int main()
{
	RUN_TEST(TestCBufferCreate);
	RUN_TEST(TestCBufferWrite);
	RUN_TEST(TestCBufferRead);
	RUN_TEST(TestCBufferIsEmpty);
	RUN_TEST(TestCBufferGetCapacity);
	RUN_TEST(TestCBufferGetSize);
	RUN_TEST(TestCBufferClear);

	return EXIT_SUCCESS;
}