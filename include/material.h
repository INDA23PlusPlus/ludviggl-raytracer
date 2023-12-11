
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

struct emissive {
    v3 color;
    scl brightness;
};

enum material_type {
    MT_DIFFUSE,
    MT_METALLIC,
    MT_EMISSIVE
};

struct material {
    int type;
    union {
        struct diffuse  diffuse;
        struct metallic metallic;
        struct emissive emissive;
    };
};

static inline void scatter(v3 in,                // incident ray
                           v3 n,                 // surface normal
                           struct material *mat, // surface material
                           v3 *out,              // reflected ray
                           v3 *col,              // color
                           int *stop)            // stop ray
{
    switch (mat->type)
    {
        case MT_DIFFUSE:
            (void)in;
            *out = n + randv3();
            *col *= mat->diffuse.color;
            *stop = 0;
            break;
        case MT_METALLIC:
            *out = reflect_n(in, n) +
                mat->metallic.fuzz * randv3();
            *col *= mat->metallic.color;
            *stop = 0;
            break;
        case MT_EMISSIVE:
            *col *= mat->emissive.brightness * mat->emissive.color;
            *stop = 1;
            break;
    }
}

#endif
