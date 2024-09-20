#ifndef __MISERVER_TYPES_H
#define __MISERVER_TYPES_H
#include <stddef.h>

typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef float FLOAT;

#ifdef _WIN32
#define OVERRIDE override
#else
#define OVERRIDE
#endif

#endif