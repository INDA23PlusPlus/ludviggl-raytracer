
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
        scl _t = ent_intersect(ent, ro, rd);

        if (_t > 0.0001 && (*t < 0 || _t < *t))
        {
            id = i;
            *t = _t;
            switch (ent->type)
            {
                case ET_PLANE: *n = ent->plane.normal; break;
                case ET_SPHERE: *n = normalize(ro + _t * rd - ent->sphere.orig); break;
            }
        }
    }

    return id;
}


void scene_add_sphere(struct scene *scn, v3 orig, scl radius, int mat_id);
void scene_add_plane(struct scene *scn, v3 normal, scl dist, int mat_id);
int scene_add_diffuse(struct scene *scn, v3 color);
int scene_add_metallic(struct scene *scn, v3 color, scl fuzz);

#endif
