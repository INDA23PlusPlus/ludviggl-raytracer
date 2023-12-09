
#include "image.h"
#include "log.h"
#include "mem.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct image img_create(int w, int h)
{
    struct image img;
    img.w = w;
    img.h = h;
    img.data = aligned_alloc(__alignof__ (v3), w * h * sizeof *img.data);
    return img;
}

void img_destroy(struct image *img)
{
    free(img->data);
    img->w = 0;
    img->h = 0;
}

int img_save(struct image *img, const char *path)
{
    unsigned char *converted = malloc(img->w * img->h * 3 * sizeof *converted);

    for (int i = 0; i < img->w * img->h; i++)
    {
        v3 c = clamp(img->data[i]);

        converted[3 * i + 0] = (unsigned char)(255.99 * r_(c));
        converted[3 * i + 1] = (unsigned char)(255.99 * g_(c));
        converted[3 * i + 2] = (unsigned char)(255.99 * b_(c));
    }

    int ret = stbi_write_png(path, img->w, img->h, 3, converted, 0);

    free(converted);
    return ret;
}
