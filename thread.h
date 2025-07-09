#ifndef __ABAKDJSKFAJS__
#define __ABAKDJSKFAJS__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define THREAD_NUM 3

void start_thread();

#define printr(fmt,...) printf("[\x1b[31mERR\x1b[0m]"fmt"\n", ##__VA_ARGS__)
#define printg(fmt,...) printf("[\x1b[32mSUCCESS\x1b[0m]"fmt"\n", ##__VA_ARGS__)
#define printy(fmt,...) printf("[\x1b[33mSUCCESS\x1b[0m]"fmt"\n", ##__VA_ARGS__)
#define printb(fmt,...) printf("[\x1b[34mINFO\x1b[0m]"fmt"\n", ##__VA_ARGS__)

#endif
