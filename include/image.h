
#ifndef IMAGE_H
#define IMAGE_H

#include "vector.h"

struct image {
    int w;
    int h;
    v3  *data;
};

struct image img_create(int w, int h);
void img_destroy(struct image *img);
int img_save(struct image *img, const char *path);

static inline void img_set_pxl(struct image *img, int x, int y, v3 color)
{
    img->data[x + img->w * y] = color;
}

static inline v3 img_get_pxl(struct image *img, int x, int y)
{
    return img->data[x + img->w * y];
}

#endif
