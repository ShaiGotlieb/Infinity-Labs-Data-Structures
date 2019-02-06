#include <stdlib.h> /* strtod */
#include <string.h> /* stlen */

#include "calculator.h"
#include "exp_parse.h"
#include "inner_calc.h"

#define NAN (0.0 / 0.0)

double CalculateExpression(const char *expression, return_status_t *status)
{
	calculator_t *calc = NULL;
	parser_t *parser = NULL;
	char *exp = (char *)expression;
	unsigned char *next_element = (unsigned char *)expression; 
	unsigned char *exp_runner = (unsigned char *)expression;
	double num = 0; 
	int is_end = 0;

	calc = CreateCalculator(strlen(expression), status);
	if (NULL == calc)
	{
		return (ALLOCATION_ERROR);
	}

	parser = CreateParser();
	if (NULL == parser)
	{
		return (ALLOCATION_ERROR);
	}

	while (OK == *status && !is_end)
	{
		switch(ParseNextToken(parser, *exp_runner)) 
		{
	   		case (PARSER_VALID_OPERAND):
		   		next_element = exp_runner;
		   		num = strtod(exp, (char **)&exp_runner);
		   		if (next_element == exp_runner)
				{
					return (NAN);
				}
				exp = (char *)exp_runner/* + 1*/;
		   		PushOperandToCalculator(calc ,&num);
	     		break;
				
			case (PARSER_VALID_OPERATOR):
				PushOperatorToCalculator(calc ,exp_runner);
				++exp_runner;
				exp = (char *)exp_runner;
				break; 

		  	case (PARSER_VALID_END):
				is_end = 1;
				break; 

			case PARSER_ERROR: 
				*status = ILLEGAL_EXPRESSION;
				DestroyCalculator(calc);
				return (NAN); 	  
		}
	}

	num = Calculate(calc); 
	
	if (num != num)
	{
		*status = ARITHMATIC_EXCEPTION;
	}
	
	return (num);
}


