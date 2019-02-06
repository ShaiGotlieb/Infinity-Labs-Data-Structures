#ifndef __H__INNER_CALC__
#define __H__INNER_CALC__

typedef struct calculator_s calculator_t;

calculator_t *CreateCalculator(size_t capacity, return_status_t *status);
/***************************************************************** 
 * CreateCalculator - creates a calculator data structure with 
 * a maximum size of capacity. If a a divide by 0 error will be 
 * detected by the calculator, the status will be updated with the 
 * ARITHMATIC_EXCEPTION value.
 *                            
 * capacity - max number of elements to be calculated (operators 
 * and operands).
 *
 * status - a pointer to an integer which contains the status of
 * execution.
 * Return - a pointer to the calculator. if it fails to create, 
 *  will return a NULL pointer   
 *****************************************************************/

void PushOperandToCalculator(calculator_t *calculator, double *num);
/********************************************************************
 *
 *******************************************************************/

void PushOperatorToCalculator(calculator_t *calculator, unsigned char *oper);
/********************************************************************
 *
 *******************************************************************/

double Calculate(calculator_t *calculator);
/********************************************************************
 * Calculate - this function will calculate a given string
 * expression. If a a divide by 0 error was detected, the status 
 *
 * expression - an expression to calculate. Valid input for expression
 * is any valid arithmatic expression using the operators:
 * + - * / ( ) and the operands: 0-9. This functions supports 
 * operations on real numbers.
 *
 * Returns - the result, in double type. If a divide by 0 error was detected, 
 * the value NaN (Not A Number) will be returned. This can be verified by
 * the following expression: (result != result).  
 *******************************************************************/

void DestroyCalculator(calculator_t  *calculator);
/********************************************************************
 * removes calculator from memory                      
 *
 * calculator - a pointer to the calculator            
 *******************************************************************/
#endif