
#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#ifdef DEBUG
#define trace(...) printf("trace: " __VA_ARGS__)
#else
#define trace(...)
#endif

#define log(...) printf("log: " __VA_ARGS__)
#define fatal(...) { printf("fatal error: " __VA_ARGS__); abort(); }
#define clearln() printf("\1xB[2K");

#endif
