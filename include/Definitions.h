#pragma once
#include <malloc.h>
#include <stdio.h>
typedef char* string;
typedef const char* cstring;
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)
#define GROW_ARRAY(previous, type, oldCount) (type*)realloc(previous, sizeof(type) * oldCount)

//check if windows
#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS
#include <windows.h>
void printcolor(const char* text, int color, ...);
#endif

//check if linux
#if defined(__linux__)
#define LINUX
#include <unistd.h>
void printcolor(const char* text, int color, ...);
#endif

void HydronixPrintError(const char *message, int line, int column, const char *body, const char* current, int code);