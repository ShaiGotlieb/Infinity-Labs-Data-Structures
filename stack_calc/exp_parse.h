#ifndef __H_EXP_PARSE__
#define __H_EXP_PARSE__

/**************************************************************** 
 * This file handles a Parser for a string format 
 * mathematical expression
 *						  
 * Written by: 		Shai Gotlieb  
 * Last updated : 	6.2.2019									
 ***************************************************************/

typedef enum {	PARSER_VALID_OPERAND = 0, 
				PARSER_VALID_OPERATOR = 1, 
				PARSER_VALID_END = 2, 
				PARSER_ERROR = 3
			} parser_status_t;

typedef struct parser_s parser_t;

parser_t *CreateParser(void);
/***************************************************************** 
 * CreateParser - creates a parser data structure. 
 *
 * Return - a pointer to the parser. if it fails to create, 
 *  will return a NULL pointer.   
 *****************************************************************/

void DestroyParser(parser_t * parser);
/********************************************************************
 * DestroyParser - removes parser from memory                      
 *
 * parser - a pointer to the parser            
 *******************************************************************/

parser_status_t ParseNextToken(parser_t *parser, unsigned char token);
/********************************************************************
 * ParseNextToken - this function will parse the next token in the 
 * string expression. If the token is valid, it will return on of the values: 
 * PARSER_VALID_OPERATOR, PARSER_VALID_OPERAND. 
 * Otherwise, it will return PARSER_ERROR. 
 * If the token equels the end of string character ('\0'), and the
 * parser verifies it's a valid state, PARSER_VALID_END will be returned.
 *
 * token - an expression to be parsed.
 *
 * Returns - parser_status_t
 *******************************************************************/
#endif