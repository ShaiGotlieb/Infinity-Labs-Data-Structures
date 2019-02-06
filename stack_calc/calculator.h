#ifndef __H_CALCULATOR__
#define __H_CALCULATOR__


/**************************************************************** 
 * This file handles a Calculator implementation for a string 
 * format mathematical expression.
 *						  
 * Written by: 		Shai Gotlieb  
 * Last updated : 	6.2.2019
 ***************************************************************/

typedef enum {	OK = 0, 
				ARITHMATIC_EXCEPTION = 1, 
				ILLEGAL_EXPRESSION = 2,
				ALLOCATION_ERROR} return_status_t;

double CalculateExpression(const char *expression, return_status_t *status);
/********************************************************************
 * CalculateExpression - this function will calculate a given string
 * expression - if it is valid. 
 * If the expression is a valid arithmatic expression, the 'status'
 * will have the value OK. Otherwise, one of the error values of 
 * the return_status_t.
 *
 * expression - a string format expression to calculate. 
 * Valid input for expression is any valid arithmatic expression using the operators:
 * + - * / ( ) and the operands: 0-9. 
 * This functions supports operations on real numbers.
 *
 * status - a pointer to an integer to which ca status of
 * execution will be updated.
 *
 * Returns - the result, in double type. 
 * If an error was detected, the value NaN (Not A Number)
 * will be returned. 
 * This value can be verified by the following expression: (result != result).  
 *	
 * In addition, the 'status' variable will be updated with the 
 * ARITHMATIC_EXCEPTION value or ILLEGAL_EXPRESSION if non valid 
 * expression was detected. The value ALLOCATION_ERROR will be set if 
 * a memory problem occured.
 *******************************************************************/

#endif