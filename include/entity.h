
#ifndef ENTITY_H
#define ENTITY_H

#include "vector.h"

enum entity_type {
    ET_SPHERE,
    ET_PLANE
};

struct sphere {
    scl radius;
    v3  orig;
};

struct plane {
    v3  normal;
    scl dist;
};

struct entity {
    int type;
    union {
        struct sphere sphere;
        struct plane plane;
    };
};

struct collection {
    struct entity *data;
    int    count;
};

#endif
