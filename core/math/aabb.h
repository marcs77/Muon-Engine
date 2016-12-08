#ifndef AABB_H
#define AABB_H

#include "vec3.h"
#include "mathutils.h"

namespace muon {
namespace math {

template<class T>
struct AABB {
    Vec3<T> min, max;

    AABB() {}
    AABB(Vec3<T> a, Vec3<T> b)
    {
        min.x = MIN(a.x, b.x);
        min.y = MIN(a.y, b.y);
        min.z = MIN(a.z, b.z);

        max.x = MAX(a.x, b.x);
        max.y = MAX(a.y, b.y);
        max.z = MAX(a.z, b.z);
    }

    inline bool isValid() const { return min.x <= max.x && min.y <= max.y && min.z <= max.z; }

    inline Vec3<T> getCenter() const { return (min+max)*0.5; }
    void set(const Vec3<T>& min, const Vec3<T>& max) {
        this->min = min;
        this->max = max;
    }

    inline bool isPointInside(const Vec3<T>& p) const {
        return p.x >= min.x && p.x <= max.x &&
               p.y >= min.y && p.y <= max.y &&
               p.z >= min.z && p.z <= max.x;
    }

    inline bool intersects(const AABB& other) const {
        return min.x <= other.max.x && max.x >= other.min.x &&
               min.y <= other.max.y && max.y >= other.min.y &&
               min.z <= other.max.z && max.z >= other.min.z;
    }

    inline T getSizeX() const { return max.x - min.x; }
    inline T getSizeY() const { return max.y - min.y; }
    inline T getSizeZ() const { return max.z - min.z; }
    inline Vec3<T> getSize() const { return Vec3<T>(getSizeX(), getSizeY(), getSizeZ()); }

    void translate(const Vec3<T>& vector) {
        min += vector;
        max += vector;
    }

    void ext(const Vec3<T>& p) {
        min.x = MIN(min.x, p.x);
        min.y = MIN(min.y, p.y);
        min.z = MIN(min.z, p.z);

        max.x = MAX(max.x, p.x);
        max.y = MAX(max.y, p.y);
        max.z = MAX(max.z, p.z);
    }

    void setPosition(const Vec3<T>& p) {
        Vec3<T> tempMin(min);
        min = (min - max)*0.5 + p;
        max -= (tempMin+max)*0.5 - p;
    }

};

typedef AABB<float> AABBf;
typedef AABB<int> AABBi;
typedef AABB<double> AABBd;

}
}

#endif // AABB_H
