
#ifndef MEM_H
#define MEM_H

#include <stdlib.h>

#define malloc(s)\
    ({\
        void *__ptr = malloc(s);\
        if (__ptr == NULL) abort();\
        __ptr;\
    })

#define aligned_alloc(a, s)\
    ({\
        void *__ptr = aligned_alloc(a, s);\
        if (__ptr == NULL) abort();\
        __ptr;\
    })

#endif
