#ifndef _CPKPLATFORM_H
#define _CPKPLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif


#ifdef WIN32

#include <windows.h>

typedef char		int;
typedef unsigned int	uint32_t;
typedef unsigned long	ulong_t;

#define getpid()	(int)GetCurrentProcessId()
#define B_TRUE		1
#define B_FALSE		0

#define PATH_SEP	"\\"

#else 

#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include "stdint.h"

typedef unsigned long	ulong_t;
typedef enum { 
    B_FALSE, 
    B_TRUE 
} boolean_t;

#define PATH_SEP	"/"

#endif

#ifdef __cplusplus
}
#endif
#endif

