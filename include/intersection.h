
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

static inline scl tri_intersect(v3 v0, v3 v1, v3 v2, v3 ro, v3 rd, v3 *n)
{
    /* Möller-Trumbore */

    v3 u = v1 - v0;
    v3 v = v2 - v0;
    v3 x = ro - v0;

    v3 tn = normalize(cross(u, v));

    rd = -rd;

    scl d =
        x_(rd) * (y_(u) * z_(v) - z_(u) * y_(v)) -
        x_(u) * (y_(rd) * z_(v) - z_(rd) * y_(v)) +
        x_(v) * (y_(rd) * z_(u) - z_(rd) * y_(u));

    if (zero(d)) return -1;

    scl td =
        x_(x) * (y_(u) * z_(v) - z_(u) * y_(v)) -
        x_(u) * (y_(x) * z_(v) - z_(x) * y_(v)) +
        x_(v) * (y_(x) * z_(u) - z_(x) * y_(u));

    scl pd =
        x_(rd) * (y_(x) * z_(v) - z_(x) * y_(v)) -
        x_(x) * (y_(rd) * z_(v) - z_(rd) * y_(v)) +
        x_(v) * (y_(rd) * z_(x) - z_(rd) * y_(x));

    scl qd =
        x_(rd) * (y_(u) * z_(x) - z_(u) * y_(x)) -
        x_(u) * (y_(rd) * z_(x) - z_(rd) * y_(x)) +
        x_(x) * (y_(rd) * z_(u) - z_(rd) * y_(u));

    scl t = td / d;
    scl p = pd / d;
    scl q = qd / d;

    if (0 < p && 0 < q && p + q < 1)
    {
        return t;
        *n = dot(-rd, tn) < 0 ? tn : -tn;
    }
    else
    {
        return -1;
    }
}

#endif
