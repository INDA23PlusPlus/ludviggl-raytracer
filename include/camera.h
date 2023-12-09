
#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

struct camera {
    v3 orig;
    v3 crn;
    v3 u, v;
};

struct camera cam_from_params(v3 orig,     // camera origin
                              v3 dir,      // camera direction
                              scl aspect,  // aspect ratio
                              scl focal);  // focal length

static inline void cam_gen_ray(struct camera *cam,
                               scl u,
                               scl v,
                               v3 *orig,
                               v3 *dir)
{
    *orig = cam->orig;
    *dir = cam->crn + u * cam->u + v * cam->v - *orig;
}

#endif
