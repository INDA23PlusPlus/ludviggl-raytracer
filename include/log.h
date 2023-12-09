
#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#ifdef DEBUG
#define trace(...) printf("trace: " __VA_ARGS__)
#else
#define trace(...)
#endif

#define log(...) printf("log: " __VA_ARGS__)

#endif