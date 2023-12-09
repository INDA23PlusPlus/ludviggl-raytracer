
#include "intersection.h"

scl sphere_intersect(v3 so, scl r, v3 ro, v3 rd)
{
    v3 od = ro - so;

    scl a = dot(rd, rd);
    scl b = 2 * dot(rd, od);
    scl c = dot(od, od) - r * r;

    scl d = b * b - 4 * a * c;
    if (d < 0) return -1;

    scl t0 = (-b + sqrt(d)) / 2 / a;
    scl t1 = (-b - sqrt(d)) / 2 / a;

    if (t0 < t1 && t0 > 0) return t0;
    else return t1;
}

scl plane_intersect(v3 n, scl d, v3 ro, v3 rd)
{
    scl a = dot(n, rd);
    if (zero(a)) return -1;

    return (d - dot(n, ro)) / a;
}
