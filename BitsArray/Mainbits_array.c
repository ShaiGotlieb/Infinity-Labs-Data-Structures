#include "bits_array.h"
#include "test.h"

#define TRUE 1
#define FALSE 0

TestResult TestSetBitOn()
{
	unsigned long numbers[] = {0, 1, 0xf, 0x7, 200};
	unsigned long results[] = {32, 33, 47, 39, 232};
	int i;

	for (i = 0; i < 5; i++)
	{
		REQUIRE(results[i] == SetBitOn(numbers[i], 5));
	}

	return TEST_PASS;
}

TestResult TestSetBitOff()
{
	unsigned long numbers[] = {0, 1, 0xf, 0x7, 201};
	unsigned long results[] = {0, 0, 14, 6, 200};
	int i;

	for (i = 0; i < 5; i++)
	{
		REQUIRE(results[i] == SetBitOff(numbers[i], 0));
	}

	return TEST_PASS;
}

TestResult TestIsBitOn()
{
	unsigned long numbers[] = {0, 20, 0xf, 0x7, 27};
	int results[] = {FALSE, TRUE, TRUE, TRUE, FALSE};
	int i;

	for (i = 0; i < 5; i++)
	{
		REQUIRE(results[i] == IsBitOn(numbers[i], 2));
	}

	return TEST_PASS;
}

TestResult TestIsBitOff()
{
	unsigned long numbers[] = {0, 20, 0xf, 0x7, 27};
	int results[] = {TRUE, FALSE, FALSE, FALSE, TRUE};
	int i;

	for (i = 0; i < 5; i++)
	{
		REQUIRE(results[i] == IsBitOff(numbers[i], 2));
	}

	return TEST_PASS;
}

TestResult TestSetAllBitsOn()
{
	unsigned long numbers[] = {0, 20, 0xf, 0x7, 27};
	int i;

	for (i = 0; i < 5; i++)
	{
		REQUIRE(ULONG_MAX == SetAllBitsOn(numbers[i]));
	}

	return TEST_PASS;
}

TestResult TestSetAllBitsOff()
{
	unsigned long numbers[] = {0, 20, 0xf, 0x7, 27};
	int i;

	for (i = 0; i < 5; i++)
	{
		REQUIRE(0 == SetAllBitsOff(numbers[i]));
	}

	return TEST_PASS;
}

TestResult TestCountBitsOn()
{
	unsigned long numbers[] = {0, 20, 0xf, 0x7, ULONG_MAX};
	size_t results[] = {0, 2, 4, 3, 64};
	int i;

	for (i = 0; i < 5; i++)
	{
		REQUIRE(results[i] == CountBitsOn(numbers[i]));
	}

	return TEST_PASS;
}

TestResult TestCountBitsOff()
{
	unsigned long numbers[] = {0, 20, 0xf, 0x7, ULONG_MAX};
	size_t results[] = {64, 62, 60, 61, 0};
	int i;

	for (i = 0; i < 5; i++)
	{
		REQUIRE(results[i] == CountBitsOff(numbers[i]));
	}

	return TEST_PASS;
}

TestResult TestFlipBit()
{
	unsigned long numbers[] = {0, 1, 0xf, 0x7, 128};
	unsigned long results[] = {8, 9, 7, 15, 136};
	int i;

	for (i = 0; i < 5; i++)
	{
		REQUIRE(results[i] == FlipBit(numbers[i], 3));
	}

	return TEST_PASS;
}

TestResult TestRotateBitArrayLeft()
{
	unsigned long numbers[] = {70, 0, 1, 128, ULONG_MAX, ULONG_MAX-1};
	unsigned long results[] = {560, 0, 8, 1024, ULONG_MAX, ULONG_MAX-8};
	int i;

	for (i = 0; i < 6; i++)
	{
		REQUIRE (results[i] == RotateBitArrayLeft(numbers[i], 3));
	}

	return TEST_PASS;
}

TestResult TestRotateBitArrayRight()
{
	unsigned long numbers[] = {4, 0, 128, 48, ULONG_MAX};
	unsigned long results[] = {0x8000000000000000, 0, 16, 6, ULONG_MAX};
	int i;

	for (i = 0; i < 5; i++)
	{
		REQUIRE(results[i] == RotateBitArrayRight(numbers[i], 3));

	}

	return TEST_PASS;
}

TestResult TestMirrorBitArray()
{
	unsigned long numbers[] = {1, 0, 2, 4, ULONG_MAX};
	unsigned long results[] = {0x8000000000000000, 0, (0x8000000000000000/2), (0x8000000000000000/4), ULONG_MAX};
	int i;

	for (i = 0; i < 5; i++)
	{
		REQUIRE(results[i] == MirrorBitArray(numbers[i]));
	}

	return TEST_PASS;
}

TestResult TestPrintBitArray()
{
	unsigned long numbers[] = {1, 0, 2, 4, ULONG_MAX};
	int i;

	for (i = 0; i < 5; i++)
	{
		PrintBitArray(numbers[i]);
	}

	return TEST_PASS;
}

int main()
{
	RUN_TEST(TestSetBitOn);
	RUN_TEST(TestSetBitOff);
	RUN_TEST(TestIsBitOn);
	RUN_TEST(TestIsBitOff);
	RUN_TEST(TestSetAllBitsOn);
	RUN_TEST(TestSetAllBitsOff);
	RUN_TEST(TestCountBitsOn);
	RUN_TEST(TestCountBitsOff);
	RUN_TEST(TestSetBitOff);
	RUN_TEST(TestFlipBit);
	RUN_TEST(TestRotateBitArrayLeft);
	RUN_TEST(TestRotateBitArrayRight);
	RUN_TEST(TestMirrorBitArray);
	RUN_TEST(TestPrintBitArray);


	return 0;
}