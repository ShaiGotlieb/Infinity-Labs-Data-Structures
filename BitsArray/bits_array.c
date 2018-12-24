#include "bits_array.h"

#define UNUSED(x) (void)(x)
#define MASK 1
#define MAX_BITS 64

unsigned long SetBitOn(const unsigned long bits_arr, const size_t bit_index)
{
	assert(bit_index < MAX_BITS);

	return bits_arr | (MASK << bit_index);
}

unsigned long SetBitOff(const unsigned long bits_arr, const size_t bit_index)
{
	assert(bit_index < MAX_BITS);

	return bits_arr & ~(MASK << bit_index);
}

int IsBitOn(const unsigned long bits_arr, const size_t bit_index)
{
	assert(bit_index < MAX_BITS);

	return !!(bits_arr & (MASK << bit_index)); /* use '!!' to return '1' or '0' */
}

int IsBitOff(const unsigned long bits_arr, const size_t bit_index)
{
	assert(bit_index < MAX_BITS);

	return !IsBitOn(bits_arr, bit_index);
}

unsigned long SetAllBitsOn(const unsigned long bits_arr)
{
	UNUSED(bits_arr);

	return ULONG_MAX;
}

unsigned long SetAllBitsOff(const unsigned long bits_arr)
{
	UNUSED(bits_arr);

	return 0;
}

size_t CountBitsOn(const unsigned long bits_arr)
{
	unsigned long bits_arr_result = bits_arr;
	size_t counter = 0;

	while (bits_arr_result != 0)
	{
		if (bits_arr_result & MASK)
		{
			counter++;
		}
		bits_arr_result >>= 1;
	}
	return counter;
}

size_t CountBitsOff(const unsigned long bits_arr)
{
	return MAX_BITS - CountBitsOn(bits_arr);
}

unsigned long FlipBit(const unsigned long bits_arr, const size_t bit_index)
{
	assert(bit_index < MAX_BITS);

	return bits_arr ^ (MASK << bit_index);
}

unsigned long RotateBitArrayLeft(const unsigned long bits_arr, const size_t how_many_bits)
{
	size_t rotation_number = how_many_bits % MAX_BITS;
	unsigned long bits_arr_result = bits_arr;
	unsigned long left_bits = bits_arr >> (MAX_BITS - rotation_number);

	bits_arr_result <<= rotation_number;
	bits_arr_result |= left_bits;

	return bits_arr_result;
}

unsigned long RotateBitArrayRight(const unsigned long bits_arr, const size_t how_many_bits)
{
	size_t rotation_number = how_many_bits % MAX_BITS;
	unsigned long bits_arr_result = bits_arr;
	unsigned long right_bits = bits_arr << (MAX_BITS - rotation_number);

	bits_arr_result >>= rotation_number;
	bits_arr_result |= right_bits;

	return bits_arr_result;
}

unsigned long MirrorBitArray(const unsigned long bits_arr)
{
	unsigned long bits_arr_result = bits_arr;
	unsigned long mirror = 0;
	int i = 0;

	while(i < MAX_BITS)
	{	
		mirror = mirror << 1;
		mirror = mirror | (bits_arr_result & MASK); /* add LSD */			
		bits_arr_result = bits_arr_result >> 1;
		i++;
	}

	return mirror;
}

void PrintBitArray(const unsigned long bits_arr)
{
	unsigned long bits_arr_result = bits_arr;
	unsigned long mask = MASK;
	int i;

	mask <<= MAX_BITS-1;
	for (i = 0; i < MAX_BITS; ++i)
	{
		printf("%s", (mask & bits_arr_result) ? "1" : "0");
		mask >>= 1;
	}

	printf("\n");
}