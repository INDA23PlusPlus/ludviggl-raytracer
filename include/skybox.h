
#ifndef SKYBOX_H
#define SKYBOX_H

#include "image.h"

struct skybox {
    struct image faces[6]; int size; };

/*
 `filenames` should be in this order:
    * right
    * left
    * bottom
    * top
    * front
    * back
*/
struct skybox skybox_load(const char *filenames[]);
void skybox_destroy(struct skybox *skb);

static inline v3 skybox_sample(struct skybox *skb, v3 d)
{
    // pick axis
    enum _axis { XP, XN, YP, YN, ZP, ZN };
    scl axis_v = x_(d);
    int axis = axis_v > 0 ? XP : XN;

    if (fabs(y_(d)) > fabs(axis_v))
    {
        axis_v = y_(d);
        axis = axis_v > 0 ? YP : YN;
    }

    if (fabs(z_(d)) > fabs(axis_v))
    {
        axis_v = z_(d);
        axis = axis_v > 0 ? ZP : ZN;
    }

    d /= fabs(axis_v);

    scl u, v;
    int face_id;

    switch (axis)
    {
        case XN:
            face_id = 0;
            u = z_(d);
            v = y_(d);
            break;
        case XP:
            face_id = 1;
            u = -z_(d);
            v = y_(d);
            break;
        case YN:
            face_id = 2;
            u = x_(d);
            v = z_(d);
            break;
        case YP:
            face_id = 3;
            u = -x_(d);
            v = z_(d);
            break;
        case ZN:
            face_id = 4;
            u = -x_(d);
            v = y_(d);
            break;
        case ZP:
            face_id = 5;
            u = x_(d);
            v = y_(d);
            break;
    }

    u = (1 + u) / 2;
    v = (1 - v) / 2;

    int ix = (int)(u * (scl)skb->size);
    int iy = (int)(v * (scl)skb->size);

    struct image *face = &skb->faces[face_id];

    return img_get_pxl(face, ix, iy);
}

#endif
