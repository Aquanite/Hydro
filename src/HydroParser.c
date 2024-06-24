#include <HydroParser.h>
//Variables
Token* tokens = NULL;
int tokenCount = 0;
int tokenCapacity = 0;
Function* functions = NULL;
int functionCount = 0;
int functionCapacity = 0;
//Macros




//Functions
void AddToken(PTokenType type, const char* start, int length, int line)
{
	if (tokenCount + 1 > tokenCapacity)
	{
		int oldCapacity = tokenCapacity;
		tokenCapacity = GROW_CAPACITY(oldCapacity);
		tokens = GROW_ARRAY(tokens, Token, oldCapacity);
	}
	Token* token = &tokens[tokenCount++];
	token->type = type;
	token->start = start;
	token->length = length;
	token->line = line;
}
void AddFunction(const char* name, ValidReturnType returnType, const Parameter* parameters, int parameterCount, char* body)
{
	if (functionCount + 1 > functionCapacity)
	{
		int oldCapacity = functionCapacity;
		functionCapacity = GROW_CAPACITY(oldCapacity);
		functions = GROW_ARRAY(functions, Function, oldCapacity);
	}
	Function* function = &functions[functionCount++];
	function->name = name;
	function->returnType = returnType;
	function->parameters = (Parameter*)parameters;
	function->parameterCount = parameterCount;
	function->body = body;
}
void FindFunctions(const char* source)
{
	//functions are defined as follows:
	//<return type> <function name> (<parameters>) { <body> }
	//<return type> is a keyword (int, char, void)
	//<function name> is an identifier
	//<parameters> is a list of keywords then identifiers
	//<body> is a list of statements

	/// RULES ///

	//1. Find the return type
	//2. Find the function name
	//3. Find the parameters
	//4. Find the body
	//5. This means it is a function
	//6. Check if the function is already defined
	//6.1 If it is, throw an error
	//6.2 If it is not, add it to the list of functions
	//7. Check the return type, if it is not void, check if the function has a return statement
	//7.1 If it does not, throw an error
	//7.2 If it does, check if the return type matches the function's return type
	//7.2.1 If it does not, throw an error
	//7.2.2 If it does, continue

	//search the source for a keyword and then an identifier with a left parenthesis after it
	//confirm that the keyword is a return type
	//add the function to the list of functions

	char* current = (char*)source;
	int line = 1;
	while (*current != '\0')
	{
		if (*current == '\n')
		{
			line++;
		}
		if (*current == 'i' && *(current + 1) == 'n' && *(current + 2) == 't' && *(current + 3) == ' ')
		{
			current += 4;
			ValidReturnType returnType = INT_RETURN;
			const char* name = current;
			while (*current != '(')
			{
				current++;
			}
			const char* parameters = current;
			while (*current != ')')
			{
				current++;
			}
			int parameterCount = 0;
			Parameter* parameterList = NULL;
			if (parameters != current)
			{
				parameterList = (Parameter*)malloc(sizeof(Parameter));
				parameterCount++;
				const char* type = parameters;
				const char* parameterName = parameters;
				while (*parameters != ')')
				{
					if (*parameters == ' ')
					{
						type = parameters + 1;
					}
					if (*parameters == ',')
					{
						parameterList = (Parameter*)realloc(parameterList, sizeof(Parameter) * parameterCount);
						Parameter* parameter = &parameterList[parameterCount - 1];
						parameter->type = type;
						parameter->name = parameterName;
						parameterCount++;
						parameterName = parameters + 1;
					}
					parameters++;
				}
				parameterList = (Parameter*)realloc(parameterList, sizeof(Parameter) * parameterCount);
				Parameter* parameter = &parameterList[parameterCount - 1];
				parameter->type = type;
				parameter->name = parameterName;
			}
			current++;
			const char* body = current;
			while (*current != '}')
			{
				current++;
			}
			AddFunction(name, returnType, parameterList, parameterCount, (char*)body);
		}
		//void
		if (*current == 'v' && *(current + 1) == 'o' && *(current + 2) == 'i' && *(current + 3) == 'd' && *(current + 4) == ' ')
		{
			//add function but throw error if it has a return statement
			current += 5;
			ValidReturnType returnType = VOID_RETURN;
			const char* name = current;
			while (*current != '(')
			{
				current++;
			}
			const char* parameters = current;
			while (*current != ')')
			{
				current++;
			}
			int parameterCount = 0;
			Parameter* parameterList = NULL;
			if (parameters != current)
			{
				parameterList = (Parameter*)malloc(sizeof(Parameter));
				parameterCount++;
				const char* type = parameters;
				const char* parameterName = parameters;
				while (*parameters != ')')
				{
					if (*parameters == ' ')
					{
						type = parameters + 1;
					}
					if (*parameters == ',')
					{
						parameterList = (Parameter*)realloc(parameterList, sizeof(Parameter) * parameterCount);
						Parameter* parameter = &parameterList[parameterCount - 1];
						parameter->type = type;
						parameter->name = parameterName;
						parameterCount++;
						parameterName = parameters + 1;
					}
					parameters++;
				}
				parameterList = (Parameter*)realloc(parameterList, sizeof(Parameter) * parameterCount);
				Parameter* parameter = &parameterList[parameterCount - 1];
				parameter->type = type;
				parameter->name = parameterName;
			}
			current++;
			const char* body = current;
			while (*current != '}')
			{
				current++;
			}
			AddFunction(name, returnType, parameterList, parameterCount, (char*)body);
			//check for return statement
			if (strstr(body, "return") != NULL)
			{
				//set console color to red

				printf("HYDRO 0: Function %s has a return statement but is of type void\n", name);
			}
		}
		current++;
	}
}

void PrintFunctions()
{
	for (int i = 0; i < functionCount; i++)
	{
		Function* function = &functions[i];
		printcolor("Function: ", 1);
		printf("%s\n", function->name);
		printcolor("Return Type: ", 4);
		switch (function->returnType)
		{
		case VOID_RETURN:
			printf("void\n");
			break;
		case INT_RETURN:
			printf("int\n");
			break;
		case CHAR_RETURN:
			printf("char\n");
			break;
		}
		/// AzureianGH 6/24/24: I'm not sure why, but printing parameters causes a segfault, so I'm commenting it out for now.
		///     				It creates a Access Violation reading location error I believe, further testing is needed.
		
		/*
		for (int j = 0; j < function->parameterCount; j++)
		{
			Parameter* parameter = &function->parameters[j];
			printcolor("Parameter Type: ", 5);
			printf("%s\n", parameter->type);
			printcolor("Parameter Name: ", 6);
			printf("%s\n", parameter->name);
		}
		printf("\n");
		*/ 
		printcolor("Body: ", 2);
		printf("%s\n", function->body);

	}
}