
#include <stdio.h>
#include "image.h"
#include "camera.h"
#include "intersection.h"
#include "log.h"

#define log_vec(v) trace(#v ": (%.2f, %.2f, %.2f)\n", x_(v), y_(v), z_(v))

int main(void)
{

    struct image img = img_create(500, 500);

    struct camera cam = cam_from_params((v3) { 0, 1, -5 },
                                        (v3) { 0, 0,  1 },
                                        1,
                                        1);

    // ---------------------
    log_vec(cam.u);
    log_vec(cam.v);
    log_vec(cam.crn);

    v3 _ro, _rd;
    cam_gen_ray(&cam, 0.5, 0.5, &_ro, &_rd);
    log_vec(_ro);
    log_vec(_rd);
    // ---------------------

    v3 red = { 1, 0, 0 };
    v3 blue = { 0, 0, 1 };
    v3 green = { 0, 1, 0 };

    for (int x = 0; x < 500; x++)
    {
        for (int y = 0; y < 500; y++)
        {
            scl u = (scl)x / 500.0;
            scl v = 1 - (scl)y / 500.0;

            v3 ro, rd;
            cam_gen_ray(&cam,
                        u,
                        v,
                        &ro,
                        &rd);

            scl t0 = sphere_intersect((v3) { 0, 1, 0 },
                                      1,
                                      ro,
                                      rd);

            scl t1 = plane_intersect((v3) { 0, 1, 0 },
                                     0,
                                     ro,
                                     rd);

            v3 color = blue;

            if (t0 > 0)
            {
                if (t1 > 0 && t1 < t0)
                {
                    color = green;
                }
                else
                {
                    color = red;
                }
            }
            else if (t1 > 0) color = green;

            img_set_pxl(&img, x, y, color);
        }
    }

    int ret = !img_save(&img, "images/image_test.png");
    img_destroy(&img);

    return ret;
}
