#include <stdlib.h> /* EXIT_SUCCESS */
 
#include "stack.h"
#include "exp_parse.h"
#include "test.h"
#include "calculator.h"
#include "inner_calc.h"

#define DELIMETER (0.0000001)
#define SIZE_ARRAY_TEST (5)

TestResult TestParser();

int main()
{
	RUN_TEST(TestParser);

	return (EXIT_SUCCESS);
}

TestResult TestParser()
{
	char *expression[SIZE_ARRAY_TEST] = {
		"2+(5*2)+1",
		"2+5*2+1",
		"(2+5)*2+1",
		"(2+5)*(2+1)",
		"(3+1)"
	};
	double results[5] = {13, 13, 15, 21, 4};
	return_status_t status = OK;
	double result = 0;
	int i;

	for (i = 0; i < SIZE_ARRAY_TEST; ++i)
	{
		result = CalculateExpression(expression[i], &status);
		REQUIRE(result - results[i] < DELIMETER);
	}

	return TEST_PASS;
}
