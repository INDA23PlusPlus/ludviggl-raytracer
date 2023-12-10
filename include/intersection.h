
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vector.h"

static inline scl sphere_intersect(v3 so, scl r, v3 ro, v3 rd, v3 *n)
{
    v3 od = ro - so;

    scl a = dot(rd, rd);
    scl b = 2 * dot(rd, od);
    scl c = dot(od, od) - r * r;

    scl d = b * b - 4 * a * c;
    if (d < 0) return -1;

    scl t0 = (-b + sqrt(d)) / 2 / a;
    scl t1 = (-b - sqrt(d)) / 2 / a;

    scl t = t0 < t1 && t0 > 0 ? t0 : t1;
    *n = normalize(ro + t * rd - so);
    return t;
}

static inline scl plane_intersect(v3 pn, scl pd, v3 ro, v3 rd, v3 *n)
{
    scl a = dot(pn, rd);
    if (zero(a)) return -1;

    *n = a < 0 ? pn : -pn;
    return (pd - dot(pn, ro)) / a;
}

static inline scl aabb_intersect(v3 c0, v3 c1, v3 ro, v3 rd, v3 *n)
{
    scl t = -1;
    v3 n_;

    // x-axis
    scl t_ = plane_intersect(v3_(1, 0, 0),
                             x_(c0),
                             ro, rd, &n_);

    if (t_ > tiny && (t_ < t || t < 0))
    {
        v3 p = ro + t_ * rd;
        if (y_(p) > y_(c0) && y_(p) < y_(c1) &&
            z_(p) > z_(c0) && z_(p) < z_(c1))
        {
            t = t_;
            *n = n_;
        }
    }

    t_ = plane_intersect(v3_(1, 0, 0),
                         x_(c1),
                         ro, rd, &n_);

    if (t_ > tiny && (t_ < t || t < 0))
    {
        v3 p = ro + t_ * rd;
        if (y_(p) > y_(c0) && y_(p) < y_(c1) &&
            z_(p) > z_(c0) && z_(p) < z_(c1))
        {
            t = t_;
            *n = n_;
        }
    }

    // y-axis
    t_ = plane_intersect(v3_(0, 1, 0),
                         y_(c0),
                         ro, rd, &n_);

    if (t_ > tiny && (t_ < t || t < 0))
    {
        v3 p = ro + t_ * rd;
        if (x_(p) > x_(c0) && x_(p) < x_(c1) &&
            z_(p) > z_(c0) && z_(p) < z_(c1))
        {
            t = t_;
            *n = n_;
        }
    }

    t_ = plane_intersect(v3_(0, 1, 0),
                         y_(c1),
                         ro, rd, &n_);

    if (t_ > tiny && (t_ < t || t < 0))
    {
        v3 p = ro + t_ * rd;
        if (x_(p) > x_(c0) && x_(p) < x_(c1) &&
            z_(p) > z_(c0) && z_(p) < z_(c1))
        {
            t = t_;
            *n = n_;
        }
    }

    // z-axis
    t_ = plane_intersect(v3_(0, 0, 1),
                         z_(c0),
                         ro, rd, &n_);

    if (t_ > tiny && (t_ < t || t < 0))
    {
        v3 p = ro + t_ * rd;
        if (x_(p) > x_(c0) && x_(p) < x_(c1) &&
            y_(p) > y_(c0) && y_(p) < y_(c1))
        {
            t = t_;
            *n = n_;
        }
    }

    t_ = plane_intersect(v3_(0, 0, 1),
                         z_(c1),
                         ro, rd, &n_);

    if (t_ > tiny && (t_ < t || t < 0))
    {
        v3 p = ro + t_ * rd;
        if (x_(p) > x_(c0) && x_(p) < x_(c1) &&
            y_(p) > y_(c0) && y_(p) < y_(c1))
        {
            t = t_;
            *n = n_;
        }
    }

    return t;
}

#endif
