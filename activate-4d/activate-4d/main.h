#ifndef __MAIN_H__
#define __MAIN_H__

#define OPT_PATH					'p'
#define OPT_CLASS				'c'
#define OPT_INFORMATION	'h'
#define OPT_LIST					L"p:c:h"

#include <stdlib.h>
#include <stdio.h>

#ifdef WIN32
#include <stdio.h>
#include <windows.h>
#include "Psapi.h"
#pragma comment(lib, "Psapi.lib")
#define OPTARG_T wchar_t*
#define main wmain
#define NULL	0
#define EOF	(-1)
#define ERR(s, c)	if(opterr){\
char errbuf[2];\
errbuf[0] = c; errbuf[1] = '\n';\
fputws(argv[0], stderr);\
fputws(s, stderr);\
fputwc(c, stderr);}
#else
#define OPTARG_T char*
#endif

#ifdef __GNUC__
#include <getopt.h>
#endif
#ifndef __GNUC__

#ifndef _WINGETOPT_H_
#define _WINGETOPT_H_

#ifdef __cplusplus
extern "C" {
#endif
    
    extern int opterr;
    extern int optind;
    extern int optopt;
    extern OPTARG_T optarg;
    extern int getopt(int argc, OPTARG_T *argv, OPTARG_T opts);
    
#ifdef __cplusplus
}
#endif

#endif  /* _GETOPT_H_ */
#endif  /* __GNUC__ */

#endif