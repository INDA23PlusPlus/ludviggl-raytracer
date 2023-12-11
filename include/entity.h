
#ifndef ENTITY_H
#define ENTITY_H

#include "vector.h"
#include "intersection.h"

enum entity_type {
    ET_SPHERE,
    ET_PLANE,
    ET_BOX,
    ET_TRIANGLE
};

struct sphere {
    scl radius;
    v3  orig;
};

struct plane {
    v3  normal;
    scl dist;
};

struct box {
    v3 c0;
    v3 c1;
};

struct tri {
    v3 v0;
    v3 v1;
    v3 v2;
};

struct entity {
    int type;
    int mat_id;
    union {
        struct sphere sphere;
        struct plane  plane;
        struct box    box;
        struct tri    tri;
    };
};

struct collection {
    struct entity *data;
    int    count;
};

static inline scl ent_intersect(struct entity *ent, v3 ro, v3 rd, v3 *n)
{
    switch (ent->type)
    {
        case ET_SPHERE: return sphere_intersect(ent->sphere.orig,
                                                ent->sphere.radius,
                                                ro, rd, n);

        case ET_PLANE: return plane_intersect(ent->plane.normal,
                                              ent->plane.dist,
                                              ro, rd, n);

        case ET_BOX: return aabb_intersect(ent->box.c0,
                                           ent->box.c1,
                                           ro, rd, n);

        case ET_TRIANGLE: return tri_intersect(ent->tri.v0,
                                               ent->tri.v1,
                                               ent->tri.v2,
                                               ro, rd, n);

    }

    return -1;
}

#endif
