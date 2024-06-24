#include "Definitions.h"

#if defined(WINDOWS)
void printcolor(const char *text, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    printf("%s", text);
    SetConsoleTextAttribute(hConsole, 15);
}
#endif

#if defined(LINUX)
void printcolor(const char *text, int color)
{
    printf("\033[1;%dm%s\033[0m", color, text);
}
#endif