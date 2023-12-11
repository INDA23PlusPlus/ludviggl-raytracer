
#ifndef SCENE_H
#define SCENE_H

#include "list.h"
#include "entity.h"
#include "material.h"

struct scene {
    struct list entities;
    struct list materials;
};

struct scene scene_create();
void scene_destroy(struct scene *scn);

static inline int scene_hit_id(struct scene *scn, v3 ro, v3 rd, scl *t, v3 *n)
{
    int id = -1;
    *t = -1;

    for (size_t i = 0; i < scn->entities.count; i++)
    {
        struct entity *ent = &list_data(&scn->entities, struct entity)[i];
        v3 _n;
        scl _t = ent_intersect(ent, ro, rd, &_n);

        if (_t > tiny && (*t < 0 || _t < *t))
        {
            id = i;
            *t = _t;
            *n = _n;
        }
    }

    return id;
}


void scene_add_sphere(struct scene *scn, v3 orig, scl radius, int mat_id);
void scene_add_plane(struct scene *scn, v3 normal, scl dist, int mat_id);
void scene_add_box(struct scene *scn, v3 c0, v3 c1, int mat_id);
void scene_add_tri(struct scene *scn, v3 v0, v3 v1, v3 v2, int mat_id);
int scene_add_diffuse(struct scene *scn, v3 color);
int scene_add_metallic(struct scene *scn, v3 color, scl fuzz);
int scene_add_emissive(struct scene *scn, v3 color, scl brightness);

#endif
