#ifndef __H_BITS_ARRAY__
#define __H_BITS_ARRAY__

#include <stdio.h> /* printf() */
#include <limits.h> /* ULONG_MAX */
#include <assert.h> /* assert() */


unsigned long SetBitOn(const unsigned long bits_arr, const size_t bit_index);
/*************************************************************** 
 * SetBitOn - turns on bit bit_index in bit array              *
 * bits_arr                                                    *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 * bit_index - the position of bit to be set on.               *
 * Valid input: 0-63.                                          *
 *                                                             *
 *	Return - unsigned long with index bit_index set to on      *
 ***************************************************************/

unsigned long SetBitOff(const unsigned long bits_arr, const size_t bit_index);
/*************************************************************** 
 * SetBitOff - turns off bit bit_index in bit array            *
 * bits_arr                                                    *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 * bit_index - the position of bit to be set off.              *
 * Valid input: 0-63.                                          *
 *                                                             *
 *	Return - unsigned long with index bit_index set to off     *
 ***************************************************************/

int IsBitOn(const unsigned long bits_arr, const size_t bit_index);
/*************************************************************** 
 * IsBitOn - checks if index bit_index is set on in bit array  *
 * bits_arr                                                    *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 * bit_index - the position of bit to be checked.              *
 * Valid input: 0-63.                                          *
 *                                                             *
 *	Return - 1 if bit is on. 0 if bit is off                   *
 ***************************************************************/

int IsBitOff(const unsigned long bits_arr, const size_t bit_index);
/*************************************************************** 
 * IsBitOff - checks if index bit_index is set off in bit      *
 * array bits_arr                                              *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 * bit_index - the position of bit to be checked.              *
 * Valid input: 0-63.                                          *
 *                                                             *
 *	Return - 1 if bit is off. 0 if bit is on                   *
 ***************************************************************/

unsigned long SetAllBitsOn(const unsigned long bits_arr);
/*************************************************************** 
 * SetAllBitsOn - sets on all bits in bit array bits_arr       *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 *                                                             *
 *	Return - unsigned long 0xFFFFFFFFFFFFFFFF                  *
 ***************************************************************/

unsigned long SetAllBitsOff(const unsigned long bits_arr);
/*************************************************************** 
 * SetAllBitsOff - sets off all bits in bit array bits_arr     *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 *                                                             *
 *	Return - unsigned long 0x0                                 *
 ***************************************************************/

size_t CountBitsOn(const unsigned long bits_arr);
/*************************************************************** 
 * CountBitsOn - counts all bits set on in bit array bits_arr  *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 *                                                             *
 *	Return - size_t, the number of bits set on in bits_arr     *
 ***************************************************************/

size_t CountBitsOff(const unsigned long bits_arr);
/*************************************************************** 
 * CountBitsOn - counts all bits set off in bit array bits_arr *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 *                                                             *
 *	Return - size_t, the number of bits set off in bits_arr    *
 ***************************************************************/

unsigned long FlipBit(const unsigned long bits_arr, const size_t bit_index);
/*************************************************************** 
 * FlipBit - toggle bit bit_index in bit array bits_arr        *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 * bit_index - the position of bit to be flipped.              *
 * Valid input: 0-63.                                          *
 *                                                             *
 *	Return - unsigned long with bit in bit_index flipped       *
 ***************************************************************/

unsigned long RotateBitArrayLeft(const unsigned long bits_arr, const size_t how_many_bits);
/*************************************************************** 
 * RotateBitArrayLeft - rotates bits in bit array bits_arry    *
 * how_many_bits times to the left (to the left)               *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 * how_many_bits - the number of rotations.                    *
 *                                                             *
 * Return - unsigned long after rotations                      * 
 ***************************************************************/

unsigned long RotateBitArrayRight(const unsigned long bits_arr, const size_t how_many_bits);
/*************************************************************** 
 * RotateBitArrayRight - rotates bits in bit array bits_arry   *
 * how_many_bits times to the right 	                       *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63 *    
 *                                                             *
 * how_many_bits - the number of rotations.                    *
 *                                                             *
 * Return - unsigned long after rotations                      * 
 ***************************************************************/

unsigned long MirrorBitArray(const unsigned long bits_arr);
/*************************************************************** 
 * MirrorBitArray - mirrors bits in bit array bits_arr         *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 * Return - unsigned long after being mirrored                 * 
 ***************************************************************/

void PrintBitArray(const unsigned long bits_arr);
/*************************************************************** 
 * PrintBitArray - prints bit array                            *
 *                                                             *
 * bits_arr - an implementation of an array of bits            *
 * using unsigned long.Maximum size - 64 elements indexed 0-63.*    
 *                                                             *
 ***************************************************************/

#endif /* __H_BITS_ARRAY__ */