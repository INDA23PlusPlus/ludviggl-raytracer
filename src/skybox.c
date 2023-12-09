
#include "skybox.h"
#include "mem.h"
#include "log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct skybox skybox_load(const char *filenames[])
{
    struct skybox skb;
    skb.size = -1;

    for (int i = 0; i < 6; i++)
    {
        const char *name = filenames[i];

        int w, h, n;
        unsigned char *data = stbi_load(name, &w, &h, &n, 3);
        (void)n;

        if (w != h) fatal("non-square skybox texture %s (%dx%d)\n", name, w, h);

        if (skb.size != -1 && w != skb.size)
        {
            fatal("skybox textures are not the same size (%d!=%d)\n", w, skb.size);
        }

        skb.size = w;
        skb.faces[i] = img_create(skb.size, skb.size);

        for (int j = 0; j < skb.size * skb.size; j++)
        {
            v3 color;
            r_(color) = (scl)data[3 * j + 0] / 255.99;
            g_(color) = (scl)data[3 * j + 1] / 255.99;
            b_(color) = (scl)data[3 * j + 2] / 255.99;
            skb.faces[i].data[j] = color;
        }

        free(data);
    }

    return skb;
}

void skybox_destroy(struct skybox *skb)
{
    for (int i = 0; i < 6; i++)
    {
        img_destroy(&skb->faces[i]);
    }
}
