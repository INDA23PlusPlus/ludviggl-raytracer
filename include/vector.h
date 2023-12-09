
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <math.h>

#define x_(v) (v)[0]
#define y_(v) (v)[1]
#define z_(v) (v)[2]
#define r_(v) (v)[0]
#define g_(v) (v)[1]
#define b_(v) (v)[2]

#define scl double

#define v3_(...) (v3) { __VA_ARGS__ }
#define splat(x) ((v3) { x, x, x, 0 })
#define reduce(v) (x_(v) + y_(v) + z_(v))

#define zero(x) (FP_ZERO == fpclassify(x))
#define min(a, b) ((a) > (b) ? (b) : (a))

#define sqrt(x) _Generic((x), \
              float : sqrtf,  \
              double : sqrt   \
              )(x)

typedef scl v3    __attribute__((vector_size (4 * sizeof (scl))));
typedef long mask __attribute__((vector_size (4 * sizeof (long))));

static inline v3 cross(v3 u, v3 v)
{
    return (v3) {
        y_(u) * z_(v) - z_(u) * y_(v),
        x_(u) * z_(v) - z_(u) * x_(v),
        x_(u) * y_(v) - y_(u) * x_(v)
    };
}

static inline scl dot(v3 u, v3 v)
{
    v3 w = u * v;
    return reduce(w);
}

static inline scl norm(v3 v)
{
    return sqrt(dot(v, v));
}

static inline v3 normalize(v3 v)
{
    scl n = norm(v);
    return v / n;
}

static inline v3 clamp(v3 v)
{
    x_(v) = x_(v) < 0 ? 0 : (x_(v) > 1 ? 1 : x_(v));
    y_(v) = y_(v) < 0 ? 0 : (y_(v) > 1 ? 1 : y_(v));
    z_(v) = z_(v) < 0 ? 0 : (z_(v) > 1 ? 1 : z_(v));
    return v;
}

static inline v3 proj_n(v3 v, v3 n)
{
    return n * dot(v, n);
}

static inline v3 reflect_n(v3 v, v3 n)
{
    return v - 2 * proj_n(v, n);
}

static inline scl randf()
{
    return (scl)rand() / RAND_MAX;
}

static inline v3 randv3()
{
    return normalize((v3) {
        2 * randf() - 1,
        2 * randf() - 1,
        2 * randf() - 1
    });
}

#endif
