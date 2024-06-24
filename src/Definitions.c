#include <Definitions.h>

#if defined(WINDOWS)
void printcolor(const char *text, int color, ...)
{
    //use va_list to get the arguments
    va_list args;
    va_start(args, color);
    //set the color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    //print the text
    vprintf(text, args);
    //reset the color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    //end the va_list
    va_end(args);
}
#endif

#if defined(LINUX)
void printcolor(const char *text, int color, ...)
{
    //use va_list to get the arguments
    va_list args;
    va_start(args, color);
    //set the color
    printf("\033[1;%dm", color);
    //print the text
    vprintf(text, args);
    //reset the color
    printf("\033[0m");
    //end the va_list
    va_end(args);
}
#endif

void HydronixPrintError(const char *message, int line, int column, const char *body, const char* current, int code)
{
    if (code == 0)
    {
        printcolor("Hydronix ", FOREGROUND_RED);
		printcolor("|L%d, C%d|: ", FOREGROUND_BLUE, line, column);
		printf(message);
		printcolor("FATAL 0", FOREGROUND_GREEN);
		//print the return statement with ^s under it
		printf("\n");
		//get the position of the return statement
		const char* returnStatement = strstr(body, "return");
		//print the return statement
		printf("\t ");
		printf("%s\n", returnStatement);
		//print the ^s
		printf("\t ");
		for (int i = 1; i < current - returnStatement; i++)
		{
			printcolor("^", 4);
		}
    }
}