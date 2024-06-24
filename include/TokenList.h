#pragma once

//T means Token so it doesnt conflict with other enums from other libraries
typedef enum PTokenType
{
	// Single-character tokens
	TLEFT_PAREN, TRIGHT_PAREN, TLEFT_BRACE, TRIGHT_BRACE,
	TCOMMA, TDOT, TMINUS, TPLUS, TSEMICOLON, TSLASH, TSTAR, TBANG, TEQUAL, TGREATER, TLESS, TPERCENT,

	// Literals
	TIDENTIFIER, TSTRING, TNUMBER,

	// Keywords
	TVOID, TINT, TCHARS, TIF, TELSE, TRET,
	// End of file
	TEND_OF_FILE
} PTokenType;
typedef enum VALID_RETURN_TYPE
{
	VOID_RETURN,
	INT_RETURN,
	CHAR_RETURN
} ValidReturnType;
typedef struct Token
{
	PTokenType type;
	const char* start;
	int length;
	int line;
} Token;
typedef struct Variable
{
	const char* name;
	const Token* type;
	void* value; // Not const because it will be changed
} Variable;
typedef struct Parameter
{
	const char* type;
	const char* name;
} Parameter;
typedef struct Function
{
	const char* name;
	ValidReturnType returnType;
	Parameter* parameters;
	int parameterCount;
	const char* body;
} Function;