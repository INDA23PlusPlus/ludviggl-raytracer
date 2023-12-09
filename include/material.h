
#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

struct diffuse {
    v3 color;
};

struct metallic {
    v3 color;
    scl fuzz;
};

enum material_type {
    MT_DIFFUSE,
    MT_METALLIC
};

struct material {
    int type;
    union {
        struct diffuse diffuse;
        struct metallic metallic;
    };
};

static inline void scatter(v3 in,                // incident ray
                           v3 n,                 // surface normal
                           struct material *mat, // surface material
                           v3 *out,              // reflected ray
                           v3 *col)              // color
{
    switch (mat->type)
    {
        case MT_DIFFUSE:
            (void)in;
            *out = n + randv3();
            *col *= mat->diffuse.color;
            break;
        case MT_METALLIC:
            *out = reflect_n(in, n) +
                mat->metallic.fuzz * randv3();
            *col *= mat->metallic.color;
            break;
    }
}

#endif
