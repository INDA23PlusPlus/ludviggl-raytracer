
#ifndef LIST_H
#define LIST_H

#include "mem.h"

#define LIST_INIT_CAPACITY 32

#define list_data(ls, type) ((type*)(ls)->data)
#define list_append(ls, elem)\
    {\
        list_make_room(ls);\
        list_data(ls, typeof(elem))[(ls)->count++] = elem;\
    }
#define list_create(type) _list_create(__alignof__(type), sizeof(type))


struct list {
    void *data;
    size_t alignment;
    size_t elem_size;
    size_t capacity;
    size_t count;
};

struct list _list_create(size_t alignment, size_t elem_size);
void list_destroy(struct list *ls);
void list_make_room(struct list *ls);

#endif
