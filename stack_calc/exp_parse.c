#include <stdlib.h> /* malloc */
#include "exp_parse.h"

#define MAX_DIGITS (9)
#define TABLE_SIZE (128)
#define ROWS (2)
#define EQUAL (0)
#define OFFSET (48)
#define UNUSED(x) (void)(x)

static parser_status_t IsCloseBracket(parser_t *parser);
static parser_status_t IsOpenBracket(parser_t *parser);
static parser_status_t IsOperator(parser_t *parser);
static parser_status_t IsOperand(parser_t *parser);
static parser_status_t IsNotValid(parser_t *parser);
static parser_status_t HandleEnd(parser_t *parser);
static void InitExpLut();

typedef enum { WAITING_FOR_OPERAND = 0, WAITING_FOR_OPERATOR = 1 }parser_state_t;
typedef parser_status_t(*funcs_table)(parser_t *);

static funcs_table signs_table[ROWS][TABLE_SIZE];

struct parser_s 
{
	size_t num_of_brackets;
	parser_state_t current_state;
};

parser_t *CreateParser()
{
	parser_t *parser = (parser_t *)malloc(sizeof(parser_t));
	if (NULL == parser)
	{
		return (NULL);
	}

	parser->num_of_brackets = 0;
	parser->current_state = WAITING_FOR_OPERAND;

	InitExpLut();

	return (parser);
}

void DestroyParser(parser_t * parser)
{
	free(parser);
	parser = NULL;

	return;
}

parser_status_t ParseNextToken(parser_t *parser, unsigned char token)
{
	return(signs_table[parser->current_state][token](parser));
}

static void InitExpLut()
{
	int row, col;

	for(row = 0; row < ROWS; ++row)
	{
		for(col = 0; col < TABLE_SIZE; ++col)
		{
			signs_table[row][col] = IsNotValid;
		}
	}

	for (row = 0; row < MAX_DIGITS; ++row)
	{
		signs_table[WAITING_FOR_OPERAND][row + OFFSET] = IsOperand;
	}

	signs_table[WAITING_FOR_OPERAND]['-'] = IsOperand;
	signs_table[WAITING_FOR_OPERAND]['+'] = IsOperand;
	signs_table[WAITING_FOR_OPERAND]['.'] = IsOperand;
	signs_table[WAITING_FOR_OPERAND]['('] = IsOpenBracket;
	signs_table[WAITING_FOR_OPERATOR]['/'] = IsOperator;
	signs_table[WAITING_FOR_OPERATOR]['*'] = IsOperator;
	signs_table[WAITING_FOR_OPERATOR]['+'] = IsOperator;
	signs_table[WAITING_FOR_OPERATOR]['-'] = IsOperator;
	signs_table[WAITING_FOR_OPERATOR][')'] = IsCloseBracket;	
	signs_table[WAITING_FOR_OPERATOR]['\0'] = HandleEnd;
}

static parser_status_t IsNotValid(parser_t *parser)
{
	UNUSED(parser);

	return (PARSER_ERROR);
}

static parser_status_t IsOperand(parser_t *parser)
{
	parser->current_state = WAITING_FOR_OPERATOR;

	return (PARSER_VALID_OPERAND);
}

static parser_status_t IsOperator(parser_t *parser)
{
	parser->current_state = WAITING_FOR_OPERAND;

	return (PARSER_VALID_OPERATOR);
}

static parser_status_t IsOpenBracket(parser_t *parser)
{
	++parser->num_of_brackets;

	return (PARSER_VALID_OPERATOR); 	
}

static parser_status_t IsCloseBracket(parser_t *parser)
{
	--parser->num_of_brackets; 

	return (PARSER_VALID_OPERATOR);	
}

static parser_status_t HandleEnd(parser_t *parser)
{
	if (EQUAL == parser->num_of_brackets)
	{
		return (PARSER_VALID_END);
	}

	return (PARSER_ERROR); 	
}
