
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define WIDTH 512
#define HEIGHT 512
#define SAMPLES 1024
#define BOUNCES 8
#define NUM_THREADS 4

#include "image.h"
#include "camera.h"
#include "log.h"
#include "scene.h"
#include "skybox.h"

#define logvec(v) log("(%.2f, %.2f, %.2f)\n", x_(v), y_(v), z_(v))

void render_rows(int y0,
                 int y1,
                 int samples,
                 int bounces,
                 struct camera *cam,
                 struct scene  *scn,
                 struct skybox *skb,
                 struct image  *img) {
    for (int y = y0; y < y1; y++)
    {
        if (y % 10 == 0)
        {
            int prct = (int)(100.0 * (scl)(y - y0) / (scl)(y1 - y0));
            log("%d\%\n", prct);
        }
        for (int x = 0; x < img->w; x++)
        {
            v3 acc = v3_(0, 0, 0);
            for (int i = samples; i; i--)
            {
                scl u = ((scl)x + randf()) / (scl)img->w;
                scl v = 1 - ((scl)y + randf()) / (scl)img->h;

                v3 ro, rd;
                cam_gen_ray(cam, u, v, &ro, &rd);

                v3 col = v3_(1, 1, 1);

                for (int b = bounces; b; b--)
                {
                    scl t;
                    v3 n;

                    int id = scene_hit_id(scn, ro, rd, &t, &n);

                    if (id == -1)
                    {
                        col *= skybox_sample(skb, rd);
                        goto escape;
                    }

                    int mat_id =
                        list_data(&scn->entities, struct entity)[id].mat_id;

                    struct material *mat =
                        &list_data(&scn->materials, struct material)[mat_id];

                    v3 new_rd;
                    int stop = 0;
                    scatter(rd, n, mat, &new_rd, &col, &stop);
                    if (stop) goto escape;

                    ro = ro + t * rd;
                    rd = new_rd;
                }

                col = v3_(0, 0, 0);

            escape:
                acc += col;
            }

            img_set_pxl(img, x, y, acc / (scl)samples);
        }
    }
}

int main(void)
{

    srand(time(NULL));

    struct image img = img_create(WIDTH, HEIGHT);

    v3 cam_pos = v3_(-2, 4, -8);
    v3 cam_lookat = v3_(-.5, 2, 0);
    struct camera cam = cam_from_params(cam_pos,
                                        cam_lookat - cam_pos,
                                        (scl)HEIGHT / (scl)WIDTH,
                                        1);

    struct scene scn = scene_create();

    int room = scene_add_diffuse(&scn, v3_(.8, .8, .8));
    int orange = scene_add_diffuse(&scn, v3_(1, .5, 0));
    int blue = scene_add_diffuse(&scn, v3_(.4, .4, 1));
    int metal = scene_add_metallic(&scn, v3_(.9, .9, .9), .05);
    int lamp = scene_add_emissive(&scn, v3_(1, 1, 1), 4);

    scene_add_box(&scn, v3_(-5, 0, -20), v3_(5, 8, 5), room);
    scene_add_box(&scn, v3_(-1, 0, -1), v3_(1, 2, 1), orange);

    scene_add_tri(&scn, v3_(-3, 7, -3), v3_(-3, 7, 1), v3_(1, 7, 1), lamp);
    scene_add_tri(&scn, v3_(-3, 7, -3), v3_(1, 7, -2), v3_(1, 7, 1), lamp);

    scene_add_sphere(&scn, v3_(0, 3, 0), 1, blue);

    scene_add_sphere(&scn, v3_(-1.5, .5, -1), .5, metal);

    const char *skybox_src[] = {
        "skybox/right.jpg",
        "skybox/left.jpg",
        "skybox/bottom.jpg",
        "skybox/top.jpg",
        "skybox/front.jpg",
        "skybox/back.jpg",
    };

    log("loading skybox...\n");
    struct skybox skb = skybox_load(skybox_src);

    log("width=%d, height=%d, samples=%d, bounces=%d\n",
        WIDTH,
        HEIGHT,
        SAMPLES,
        BOUNCES);

    log("rendering...\n");
    render_rows(0,
                img.h,
                SAMPLES,
                BOUNCES,
                &cam,
                &scn,
                &skb,
                &img);


    log("saving image...\n");
    int ret = !img_save(&img, "images/output.png");
    log("done!\n");
    img_destroy(&img);

    return ret;
}
