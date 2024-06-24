#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"
int main()
{
	char* source = "int main( int a ) { return 0; }";
	FindFunctions(source);
	PrintFunctions();
	return 0;
}