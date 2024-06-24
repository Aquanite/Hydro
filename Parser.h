#pragma once
#include "TokenList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Definitions.h"
void AddFunction(const char* name, ValidReturnType returnType, const Parameter* parameters, int parameterCount, char* body);
void FindFunctions(const char* source);
void AddToken(PTokenType type, const char* start, int length, int line);
void PrintFunctions();