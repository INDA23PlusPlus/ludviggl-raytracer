
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vector.h"

scl sphere_intersect(v3 so, scl r, v3 ro, v3 rd);
scl plane_intersect(v3 n, scl d, v3 ro, v3 rd);

#endif
