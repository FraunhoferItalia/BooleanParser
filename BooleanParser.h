// BooleanParser.h

#ifndef _BOOLEANPARSER_h
#define _BOOLEANPARSER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/*

This library is a parser for boolean values. Of course can be extended for other functions but was meant to be
lightweight.

*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define right 0
#define left 1
#define push(x) st1.tok_stack[++st1.size]=x
#define pop() st1.tok_stack[st1.size--]
#define get_assoc(c) (c=='!') ? right : left
#define isalpha(c) ( ( (c>=65 && c<=90) || (c>=97 && c<=122)   ) ? 1 : 0)
#define isdigit(c) ((c>=48 && c<=57) ? 1 : 0) 
#define TOKEN_LEN 3
#define STACK_LEN 31


typedef struct token
{
	char token_str[TOKEN_LEN]; //lenght of character in one token. Minimized for arduino usage.
	char token_type;
	uint8_t precedence;
	uint8_t assoc;
} token;

//char expression[] = "((1 | 0) & (1 & ((1 & !0) | 0)))";
//char expression[] = "ismember(2)";

typedef struct stack
{
	uint8_t size;
	token tok_stack[STACK_LEN];
} stack;

class BooleanParser
{
public:
	BooleanParser(void);
	uint8_t ParseIt(char* toBeConverted,uint8_t executed[],uint8_t lenExecuted);
	uint8_t answer;
private:
	stack st1;
	uint8_t out_length = 0;
	char output[40]; //Contain shunting yard expression
	char expression[40];//contain expression to be given to shunting yard
	uint8_t get_precedence(char c);
	char check_type(char c);
	void get_rpn();
	void eval_rpn( uint8_t executed[], uint8_t lenExecuted);
	void do_op(token temp,uint8_t executed[], uint8_t lenExecuted);
};

#endif





