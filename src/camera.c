
#include "camera.h"


struct camera cam_from_params(v3 orig,     // camera origin
                              v3 dir,      // camera direction
                              scl aspect,  // aspect ratio
                              scl focal)
{
    struct camera cam;
    v3 up = { 0, 1, 0 };

    dir = normalize(dir);

    cam.orig = orig;
    cam.u = cross(up, dir);
    cam.v = aspect * cross(cam.u, dir);
    cam.crn = focal * dir - .5 * cam.u - .5 * cam.v;

    return cam;
}
