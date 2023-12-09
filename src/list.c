
#include "list.h"
#include <string.h>

struct list _list_create(size_t alignment, size_t elem_size)
{
    struct list ls;

    ls.alignment = alignment;
    ls.elem_size = elem_size;
    ls.count     = 0;
    ls.capacity  = LIST_INIT_CAPACITY;
    ls.data      = aligned_alloc(alignment, elem_size * LIST_INIT_CAPACITY);

    return ls;
}

void list_destroy(struct list *ls)
{
    free(ls->data);
    ls->count = 0;
    ls->capacity = 0;
}

void list_make_room(struct list *ls)
{
    if (ls->count >= ls->capacity)
    {
        int new_capacity = 2 * ls->capacity;
        void *new_data = aligned_alloc(ls->alignment, ls->elem_size * new_capacity);

        memcpy(new_data, ls->data, ls->elem_size * ls->capacity);
        free(ls->data);

        ls->data = new_data;
        ls->capacity = new_capacity;
    }
}
