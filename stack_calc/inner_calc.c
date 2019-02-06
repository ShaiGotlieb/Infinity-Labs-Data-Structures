#include <stdlib.h> /* malloc */

#include "stack.h"
#include "calculator.h"
#include "inner_calc.h"

#define OFFSET_OPERATORS (40)
#define OPEN_BRACKET ('(')
#define CLOSE_BRACKET (')')
#define NaN (0.0/0.0)

static void PushToStuck(calculator_t *calculator);
static void MultiplyConv(calculator_t *calculator);
static void AdditionConv(calculator_t *calculator);
static void SubstractionConv(calculator_t *calculator);
static void DivideConv(calculator_t *calculator);
static void FoldUntilBracket(calculator_t *calculator);

typedef void (*action_f_t)(calculator_t *calculator);

struct calculator_s
{
	stack_t *operator_stack;
	stack_t *operand_stack;
	return_status_t *status;
	int current_prec;
};

typedef struct lut_struct_s
{
	int precidence;
	action_f_t execute;
}lut_struct_t;

static const lut_struct_t precidence_table[] = { {0, PushToStuck},  {0, FoldUntilBracket},
												 {3, MultiplyConv}, {1, AdditionConv}, 
												 {0, NULL}, 		{2, SubstractionConv},
												 {0, NULL}, 		{4, DivideConv} };

calculator_t *CreateCalculator(size_t capacity, return_status_t *status)
{
	calculator_t* calc = (calculator_t*)malloc(sizeof(calculator_t));
	if (NULL == calc)
	{
		return (NULL);
	}

	calc->operator_stack = StackCreate(sizeof(char), capacity);
	if (NULL == calc->operator_stack)
	{
		free(calc);
		calc = NULL;

		return (NULL);
	}
	calc->operand_stack = StackCreate(sizeof(double), capacity);
	if (NULL == calc->operator_stack)
	{
		free(calc);
		calc = NULL;
		free(calc->operator_stack);
		calc->operator_stack = NULL;

		return (NULL);
	}

	calc->status = status;
	calc->current_prec = -1;

	return (calc);
}

void PushOperandToCalculator(calculator_t *calculator, double *num)
{
	StackPush(calculator->operand_stack, num);

	return;
}

void PushOperatorToCalculator(calculator_t *calculator, unsigned char *oper)
{
	char current_operator;

	if ((*oper == OPEN_BRACKET) || (*oper == CLOSE_BRACKET))
	{
		precidence_table[*oper - OFFSET_OPERATORS].execute(calculator);

		return;
	}
	else if(precidence_table[*oper - OFFSET_OPERATORS].precidence <= calculator->current_prec)
	{
		current_operator = *(char *)StackPop(calculator->operator_stack);
		precidence_table[current_operator - OFFSET_OPERATORS].execute(calculator);
	}

	calculator->current_prec = precidence_table[*oper - OFFSET_OPERATORS].precidence;
	StackPush(calculator->operator_stack, oper);

	return;
}

double Calculate(calculator_t *calculator)
{
	char current_operator;

	while (0 != (StackSize(calculator->operator_stack)))
	{
		current_operator = *(char *)(StackPop(calculator->operator_stack));
		precidence_table[current_operator - OFFSET_OPERATORS].execute(calculator);
	}

	if (ARITHMATIC_EXCEPTION == *(calculator->status))
	{
		return (NaN);
	}

	return (*(double *)(StackPeek(calculator->operand_stack)));
}

void DestroyCalculator(calculator_t *calculator)
{
	StackDestroy(calculator->operator_stack);
	StackDestroy(calculator->operand_stack);
	free(calculator);
	calculator = NULL;
}

static void FoldUntilBracket(calculator_t *calculator) 
{
	int size = StackSize(calculator->operator_stack);
	char current_operator = *(char *)(StackPop(calculator->operator_stack));

	while (current_operator != OPEN_BRACKET)
	{
		precidence_table[current_operator - OFFSET_OPERATORS].execute(calculator);
		current_operator = *(char *)(StackPop(calculator->operator_stack));
		size--;
	}

	calculator->current_prec = (((size == 0) * (-1)) + ((size != 0) * precidence_table[*(unsigned char *)StackPeek(calculator->operator_stack) - OFFSET_OPERATORS].precidence));

	return;
}

static void PushToStuck(calculator_t *calculator)
{
	char bracket = OPEN_BRACKET;
	StackPush(calculator->operator_stack, &bracket);
	calculator->current_prec = 0;

	return;
}

static void MultiplyConv(calculator_t *calculator)
{
	double first = *(double *)StackPop(calculator->operand_stack);
	double second = *(double *)StackPop(calculator->operand_stack);

	double result = second * first;	
	StackPush(calculator->operand_stack, &result);

	return;
}

static void AdditionConv(calculator_t *calculator)
{
	double first = *(double *)StackPop(calculator->operand_stack);
	double second = *(double *)StackPop(calculator->operand_stack);

	double result = second + first;
	StackPush(calculator->operand_stack, &result);

	return;
}

static void SubstractionConv(calculator_t *calculator)
{
	double first = *(double *)StackPop(calculator->operand_stack);
	double second = *(double *)StackPop(calculator->operand_stack);

	double result = second - first;
	StackPush(calculator->operand_stack, &result);

	return;
}

static void DivideConv(calculator_t *calculator)
{
	double result;
	double first = *(double *)StackPop(calculator->operand_stack);
	double second = *(double *)StackPop(calculator->operand_stack);

	if (0 == first)
	{
		*calculator->status = ARITHMATIC_EXCEPTION;
		first = 1;
	}

	result = second / first;	
	StackPush(calculator->operand_stack, &result);

	return;
}

