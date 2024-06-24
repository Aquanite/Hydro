#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <HydroParser.h>
int main()
{
	char* source = "void main() { return 0; }";
	FindFunctions(source);
	PrintFunctions();
	return 0;
}