#ifndef QUATERNION_H
#define QUATERNION_H
#include "vec4.h"
#include <math.h>

namespace muon {
namespace math {

    struct Quaternion {
        float w, x, y, z;

        Quaternion();
        Quaternion(const Vec4f& v);
        Quaternion(const Quaternion& v);
        Quaternion(float w, float x, float y, float z);
        Quaternion(const Vec3f& axis, float angle);

        Quaternion operator+(const Quaternion &q) const;
        Quaternion& operator+=(const Quaternion &q);

        Quaternion operator-(const Quaternion &q) const;
        Quaternion& operator-=(const Quaternion &q);

        Quaternion operator*(const Quaternion &q) const;

        inline float sqrMagnitude() const { return w*w+x*x+y*y+z*z; }
        inline float magnitude() const { return sqrtf(sqrMagnitude()); }

        inline void normalize()
        {
            float invmag = 1.0f/magnitude();
            w *= invmag;
            x *= invmag;
            y *= invmag;
            z *= invmag;
        }

        inline Quaternion normalized() const
        {
            float invmag = 1.0f/magnitude();
            return Quaternion(w*invmag, x*invmag, y*invmag, z*invmag);
        }

        inline std::string toString() { return "Quat("+std::to_string(w)+","+std::to_string(x)+","+std::to_string(y)+","+std::to_string(z)+")"; }

    };

}
}

#endif // QUATERNION_H
