
#include <stdio.h>
#include "image.h"

int main(int argc, char *argv[])
{

    struct image img = img_create(500, 500);
    img.data[0] = (v3) { 0, 0, 0 };

    for (int x = 0; x < 500; x++)
    {
        for (int y = 0; y < 500; y++)
        {
            v3 color = {
                (scl)x / 500,
                0,
                (scl)y / 500
            };
            img_set_pxl(&img, x, y, color);
        }
    }

    int ret = !img_save(&img, "images/image_test.png");
    img_destroy(&img);

    return ret;
}
