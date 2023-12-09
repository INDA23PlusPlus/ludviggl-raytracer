
#include <stdio.h>
#include <time.h>

#include "image.h"
#include "camera.h"
#include "intersection.h"
#include "log.h"
#include "scene.h"
#include "skybox.h"

void render_rows(int y0,
                 int y1,
                 int samples,
                 int bounces,
                 struct camera *cam,
                 struct scene  *scn,
                 struct skybox *skb,
                 struct image  *img)
{
    for (int y = y0; y < y1; y++)
    {
        if (y % 50 == 0) log("row %d/%d\n", y - y0, y1 - y0);
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
                    scatter(rd, n, mat, &new_rd, &col);

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

    struct image img = img_create(500, 500);

    v3 cam_pos = v3_(0, 2, -8);
    v3 cam_lookat = v3_(0.5, 0.75, -0.25);
    struct camera cam = cam_from_params(cam_pos,
                                        cam_lookat - cam_pos,
                                        1,
                                        1);

    struct scene scn = scene_create();

    int plane_mat = scene_add_diffuse(&scn, v3_(0.7, 0.7, 0.7));
    int sphere_mat = scene_add_diffuse(&scn, v3_(0.2, 0.0, 0.9));
    int orange = scene_add_metallic(&scn, v3_(0.8, 0.4, 0.1), 0.1);
    int shiny = scene_add_metallic(&scn, v3_(0.9, 0.9, 0.9), 0.0);

    scene_add_plane(&scn, v3_(0, 1, 0), 0, plane_mat);
    scene_add_sphere(&scn, v3_(0, 1, 0), 1, shiny);
    scene_add_sphere(&scn, v3_(0.3, 0.5, -2), 0.5, sphere_mat);
    scene_add_sphere(&scn, v3_(-0.8, 0.25, -2), 0.25, orange);


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

    log("rendering...\n");
    render_rows(0,
                500,
                128,
                6,
                &cam,
                &scn,
                &skb,
                &img);

    int ret = !img_save(&img, "images/image_test.png");
    img_destroy(&img);

    return ret;
}
