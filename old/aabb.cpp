#include "aabb.h"

AABB::AABB(const Point3 &a, const Point3 &b)
{
    x = (a[0] <= b[0]) ? Interval(a[0], b[0]) : Interval(b[0], a[0]);
    y = (a[1] <= b[1]) ? Interval(a[1], b[1]) : Interval(b[1], a[1]);
    z = (a[2] <= b[2]) ? Interval(a[2], b[2]) : Interval(b[2], a[2]);
}

bool AABB::hit(const Ray &r, Interval ray_t) const
{
    const Point3 &ray_orig = r.origin();
    const Vec3 &ray_dir = r.direction();

    for (i32 axis = 0; axis < 3; axis++)
    {
        const Interval& ax = axis_interval(axis);
        const f64 adinv = 1.0 / ray_dir[axis];

        auto t0 = (ax.min - ray_orig[axis]) * adinv;
        auto t1 = (ax.max - ray_orig[axis]) * adinv;

        if (t0 < t1)
        {
            if (t0 > ray_t.min) ray_t.min = t0;
            if (t1 < ray_t.max) ray_t.max = t1;
        }
        else
        {
            if (t1 > ray_t.min) ray_t.min = t1;
            if (t0 < ray_t.max) ray_t.max = t0;
        }

        if (ray_t.max <= ray_t.min) return false;
    }
    return true;
}
